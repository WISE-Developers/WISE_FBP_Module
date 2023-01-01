/**
 * WISE_FBP_Module: CWFGM_Fuel_Shared.h
 * Copyright (C) 2023  WISE
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CWFGM_FUEL_H_
#define __CWFGM_FUEL_H_

#include "FBPFuel.h"
#include "FuelCom_ext.h"
#include "semaphore.h"
#include "ICWFGM_FBPFuel.h"

#ifdef _MSC_VER
#pragma pack(push, 8)
#endif

/** Read/write FBP fuel type.
 *
 * CCWFGM_Fuel implements both ICWFGM_Fuel and ICWFGM_FBPFuel interfaces.
 * This fuel type is read/write and is normally created by cloning a read-only template
 * fuel type, then applying necesssary and appropriate modifications.
 */
class FUELCOM_API CCWFGM_Fuel : public ICWFGM_FBPFuel, public ISerializeProto {
public:
	friend class CWFGM_FuelHelperPrivate;
	friend class CWFGM_FuelHelper;

	CCWFGM_Fuel();
	CCWFGM_Fuel(const CCWFGM_Fuel &toCopy);

public:
	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override;
	virtual google::protobuf::Message* serialize(const SerializeProtoOptions& options) override;
	virtual CCWFGM_Fuel *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); throw std::logic_error("Missing deserialization"); }
	virtual std::optional<bool> isdirty() const noexcept override { return m_bRequiresSave; }

	static CCWFGM_Fuel *deserializeFuel(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name);

	/**
	 * Changes the state of the object with respect to access rights.
	 * When the object is used by an active simulation, it must not be modified.
	 * When the object is somehow modified, it must be done so in an atomic action
	 * to prevent concerns with arising from multithreading.
	 * 
	 * Note that these locks are only needed for calls to this object via this interface.
	 * Method calls from the other interface are already multithreading friendly. 
	 * \param exclusive TRUE if the requester wants a write lock, false for read/shared access
	 * \param obtain TRUE to obtain the lock, FALSE to release the lock. If this is FALSE, then the exclusive parameter must match the initial call used to obtain the lock.
	 * 
	 * \retval SUCCESS_STATE_OBJECT_UNLOCKED Lock was released.
	 * \retval SUCCESS_STATE_OBJECT_LOCKED_WRITE Exclusive/write lock obtained
	 * \retval SUCCESS_STATE_OBJECT_LOCKED_SCENARIO A scenario has successfully locked the fuel type for simulation(shared read lock obtained)
	 * \retval SUCCSS_STATE_OBJECT_LOCKED_READ Shared/read lock obtained
	 * \retval S_OK Successful
	 */
	virtual NO_THROW HRESULT MT_Lock( bool exclusive, std::uint16_t obtain) override;
	/**
	 * Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	 * \param newFuel Address of memory to contain the reference for a newly created fuel object.
	 * 
	 * \retval E_POINTER The address provided for newFuel is invalid
	 * \retval S_OK Successful
	 * \retval E_OUTOFMEMORY Insufficient memory
	 * \retval ERROR_SEVERITY_WARNING Unspecified failure
	 * \retval E_NOINTERFACE Interface does not exist
	 */
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;
	virtual NO_THROW HRESULT Mutate(boost::intrusive_ptr<ICWFGM_Fuel> *newFuel) const override;
	/**
	 * Calculates the FMC (foliar moisture content) value based on several parameters.
	 * If elevation is negative, then the normalized latitude is calculated based on equation
	 * 1 of "Development and the Structure of the Canadian Forest Fire Behaviour Prediction
	 * System -Information Report ST-X-3", otherwise it is calculated from equation 3.
	 * Similarly, minimum FMC is calculated using either equation 2 or 4.
	 * 
	 * If the latitude and longitude are outside the general extents of Canada
	 * (latitude: 42 to 83 degrees, longitude: -52 to -141 degrees), then the latitude
	 * and/or longitude are modified to be within these ranges.
	 * \param lat Specific location (latitude, radians, signed) on the earth's surface.
	 * \param lon Specific location (longitude, radians, signed) on the earth's surface.
	 * \param elev Elevation of the specific location (metres) from sea level.
	 * \param day Julian day (day of the year, 0-365)
	 * \param fmc The calculated FMC value (percentage value expressed as a decimal 0-1).
	 * 
	 * \retval E_POINTER The address provided for fmc is invalid
	 * \retval S_OK Successful
	 * \retval E_INVALIDARG An input value is out of range or has caused (likely) a divide by zero error.
	 */
	virtual NO_THROW HRESULT FMC(double lat, double lon, double elev, std::uint16_t day, const CCWFGM_FuelOverrides* overrides, double* fmc) const override;
	/**
	 * Given several input parameters, calculates various of rate of spread (ROS) values.
	 * The specific set of equations used to calculate ROS values is determined by the fuel
	 * type and/or any modifications which have been applied.
	 * 
	 * Automatic caching of previously calculated values is performed for efficiency.
	 * \param GS	Percentage ground slope specified as a decimal value (0 - 1)
	 * \param SAZ	Slope azimuth, upslope (radians, Cartesian)
	 * \param WS	Observed wind speed (kph)
	 * \param WAZ	Wind azimuth (radians, Cartesian)
	 * \param BUI	Buildup index (FWI output)
	 * \param FMC	Foliar moisture code (FBP output) (0-1)
	 * \param FFMC	Fine fuel moister code (FWI output)
	 * \param fF	Fine fuel moisture function in the ISI (FWI output)
	 * \param t	Time in seconds since ignition, used for purposes of calculating acceleration
	 * \param ffmc_t	Time in seconds for the duration used to calculate FFMC
	 * \param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code> Boolean. If TRUE, then acceleration is applied to various output statistics in the FBP standard. This value should only applicable to point ignitions. If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code> Boolean. If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code> Boolean. If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided. This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code> Boolean. Specific FBP fuel types use different equations during green-up. This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY</code> Boolean. Specific FBP grass fuel types use different values during standing vs. matted. If TRUE, then grass is standing. If FALSE, then matted.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code> Boolean. If FALSE, then the wind component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h For consistency of outputs.
	 * \param RSIadjust - pointer to a class to modify RSI values, potentially for specifying percentiles (where the default RSI value is at the 50th percentile)
	 * \param rss	Calculated value, RSS (metres per minute)
	 * \param roseq	Calculated value, ROSeq (equilibrium rate of spread) (metres per minute)
	 * \param ros	Calculated value, ROS (rate of spread) (metres per minute)
	 * \param frss	Calculated value, FRSS (flank RSS) (metres per minute)
	 * \param froseq	Calculated value, FROSeq (flank equilibrium rate of spread) (metres per minute)
	 * \param fros	Calculated value, FROS (flank rate of spread) (metres per minute)
	 * \param brss Calculated value, BRSS (back RSS) (metres per minute)
	 * \param broseq	Calculated value, BROSeq (back equilibrium rate of spread) (metres per minute)
	 * \param bros	Calculated value, BROS (back rate of spread) (metres per minute)
	 * \param wsv	Calculated value, WSV (wind speed vector) (metres per minute)
	 * \param raz	Calculated value, RAZ (wind speed vector azimuth) (radians, Cartesian)
	 * 
	 * \retval E_POINTER	The address of any pointers passed into the function (rss, ros, fros, bros, wsv or raz) are invalid.
	 * \retval S_OK	Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused (likely) a divide by zero error.
	 */
	virtual NO_THROW HRESULT CalculateROSValues(double GS, double SAZ, double WS, double WAZ, 
			double BUI, double FMC, double FFMC, double fF, const HSS_Time::WTimeSpan &t, const HSS_Time::WTimeSpan &ffmc_t, short flag, const CCWFGM_FuelOverrides* overrides, ICWFGM_PercentileAttribute *RSIadjust,
			double * rss, double *roseq, double *ros, double *frss, double *froseq, double *fros,
			double *brss, double *broseq, double *bros, double *lb, double *wsv, double *raz) const override;

	/**
	 * Given several input parameters, calculates FC (fuel consumption) values. The specific set of equations used to calculate FC values is determined by the fuel type and/or any modifications which have been applied.
	 * 
	 * Automatic caching of previously calculated values is performed for efficiency.
	 * \param FFMC	Fine fuel moister code (FWI output)
	 * \param BUI	Buildup index (FWI output)
	 * \param FMC	Foliar moisture code (FBP output) (0-1)
	 * \param RSS	(metres per minute)
	 * \param ROS	Rate of spread (metres per minute)
	 * \param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code> Boolean. If TRUE, then acceleration is applied to various output statistics in the FBP standard. This value should only applicable to point ignitions. If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code> Boolean. If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code> Boolean. If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided. This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code> Boolean. Specific FBP fuel types use different equations during green-up. This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY</code> Boolean. Specific FBP grass fuel types use different values during standing vs. matted. If TRUE, then grass is standing. If FALSE, then matted.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code> Boolean. If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * \param cfb	Calculated value, crown fraction burned (unitless).
	 * \param cfc	Calculated value, crown fuel consumption (kg/m2).
	 * \param rso	Calculated value, critical spread rate for crowning
	 * \param csi	Calculated value, critical surface intensity for crowning
	 * \param sfc	Calculated value, surface fuel consumption (kg/m2).
	 * \param tfc	Calculated value, total fuel consumption (kg/m2).
	 * \param fi	Calculated value, fire intensity.
	 * 
	 * \retval E_POINTER	The address of any pointers passed into the function (cfb, cfc, sfc, tfc or fi) are invalid
	 * \retval S_OK	Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused (likely) a divide by zero error.
	 */
	virtual NO_THROW HRESULT CalculateFCValues( double FFMC, double BUI, double FMC, double RSS, double ROS, /*unsigned*/ short flag, const CCWFGM_FuelOverrides* overrides, double* cfb,
			double* cfc, double* rso, double* csi, double* sfc, double* tfc, double* fi) const override;
	/**
	 * Calculates statistics of the theoretical ellipse defined by ROS, FROS, BROS.
	 * 
	 * To match the CFS code, these values should be equilibrium values. To match Prometheus implementations, these should values should be instantaneous, after corrections through any ellipse equations.
	 * \param ROS	Rate of spread (metres per minute).
	 * \param FROS	Flank rate of spread (metres per minute).
	 * \param BROS	Back rate of spread (metres per minute).
	 * \param CFB	Crown fraction burned.
	 * \param time	Time since fire start, important if acceleration is turned on.
	 * \param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code> Boolean. If TRUE, then acceleration is applied to various output statistics in the FBP standard. This value should only applicable to point ignitions. If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code> Boolean. If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code> Boolean. If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided. This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code> Boolean. Specific FBP fuel types use different equations during green-up. This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY</code> Boolean. Specific FBP grass fuel types use different values during standing vs. matted. If TRUE, then grass is standing. If FALSE, then matted.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code> Boolean. If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * \param area	Calculated value, fire area.
	 * \param perimeter	Calculated value, fire perimeter.
	 * 
	 * \retval E_POINTER	the address provided is invalid
	 * \retval S_OK	Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused an error 
	 */
	virtual NO_THROW HRESULT CalculateStatistics(double ROS, double FROS, double BROS, double CFB, const HSS_Time::WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
			double *area, double *perimeter) const override;
	/**
	 * Calculates spread distances of the theoretical ellipse defined by ROS, FROS, BROS.
	 * \param ROS	Equilibrium rate of spread (metres per minute).
	 * \param FROS	Equilibrium flank rate of spread (metres per minute).
	 * \param BROS	Equilibrium back rate of spread (metres per minute).
	 * \param CFB	Crown fraction burned.
	 * \param time	Time since fire start, important if acceleration is turned on.
	 * \param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code> Boolean. If TRUE, then acceleration is applied to various output statistics in the FBP standard. This value should only applicable to point ignitions. If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code> Boolean. If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code> Boolean. If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided. This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code> Boolean. Specific FBP fuel types use different equations during green-up. This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY</code> Boolean. Specific FBP grass fuel types use different values during standing vs. matted. If TRUE, then grass is standing. If FALSE, then matted.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code> Boolean. If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * \param dhead	Calculated value, head fire spread distance.
	 * \param dflank	Calculated value, flank fire spread distance.
	 * \param dback	Calculated value, back fire spread distance.
	 * 
	 * \retval E_POINTER	the address provided is invalid
	 * \retval S_OK	Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused an error
	 */
	virtual NO_THROW HRESULT CalculateDistances( double ROS, double FROS, double BROS, double CFB, const HSS_Time::WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
			double *dhead, double *dflank, double *dback) const override;

	/**
	 * Calculates spread ROS in a particular direction (theta) of the theoretical ellipse defined by ROS, FROS, BROS, RAZ.
	 * \param ROS	Rate of spread (metres per minute).
	 * \param FROS Flank rate of spread (metres per minute).
	 * \param BROS Back rate of spread (metres per minute).
	 * \param RAZ Wind speed vector azimuth (radians, Cartesian)
	 * \param Theta	Direction at which to orient the vector on the ellipse (radians, Cartesian)
	 * \param rosTheta Calculated value, rate of spread in direction theta.
	 * 
	 * \retval E_POINTER		The address provided is invalid
	 * \retval S_OK			Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused an error
	 */
	virtual NO_THROW HRESULT CalculateROSTheta(double ROS, double FROS, double BROS, double RAZ, double Theta, double* rosTheta) const override;

	/**
	 * Calculates the value for ISF based on parameters passed in. Note that this
	 * method is used by mixed fuel types only and likely should not be called directly. 		Automatic caching of previously calculated values is performed for efficiency.
	 * \param RSF	Intermediate output for calculating ROS values.
	 * \param SF	Slope factor.
	 * \param ISZ	Dead wind ISI.
	 * \param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code> Boolean. If TRUE, then acceleration is applied to various output statistics in the FBP standard. This value should only applicable to point ignitions. If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code> Boolean. If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code> Boolean. If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided. This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code> Boolean. Specific FBP fuel types use different equations during green-up. This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY</code> Boolean. Specific FBP grass fuel types use different values during standing vs. matted. If TRUE, then grass is standing. If FALSE, then matted.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code> Boolean. If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * \param isfValue	the calculated ISF value
	 * 
	 * \retval E_POINTER	The address provided for the calculated value is invalid
	 * \retval S_OK	Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused (likely) a divide by zero error.
	 */
	virtual NO_THROW HRESULT ISF(double RSF, double SF, double ISZ, short flag, const CCWFGM_FuelOverrides* overrides,double *isfValue) const override;
	/**
	 * Calculates the SFC (surface fuel consumption) value based on several parameters. Note that this routine may seem redundant to CalculateFCValues() but is used by mixed fuel types. Typically, the CalculateFCValues() method should be called. Automatic caching of previously calculated values is performed for efficiency.
	 * \param FFMC	Fine fuel moister code (FWI output)
	 * \param BUI	Buildup index (FWI output)
	 * \param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code> Boolean. If TRUE, then acceleration is applied to various output statistics in the FBP standard. This value should only applicable to point ignitions. If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code> Boolean. If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code> Boolean. If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided. This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code> Boolean. Specific FBP fuel types use different equations during green-up. This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY</code> Boolean. Specific FBP grass fuel types use different values during standing vs. matted. If TRUE, then grass is standing. If FALSE, then matted.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code> Boolean. If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * \param sfc	the calculated SFC value
	 * 
	 * \retval E_POINTER	the address provided for sfc is invalid
	 * \retval S_OK	Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused (likely) a divide by zero error.
	 */
	virtual NO_THROW HRESULT SFC( double FFMC, double BUI, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double* sfc) const override;
	/**
	 * Calculates RSI (initial rate of spread) without BUI effect. Note that this routine may seem redundant to CalculateROSValues() but is used by mixed fuel types. Typically CalculateROSValues) should be called. Automatic caching of previously calculated values is performed for efficiency.
	 * \param FFMC	Fine fuel moister code (FWI output)
	 * \param BUI	Buildup index (FWI output)
	 * \param FMC	Foliar moisture code (FBP output) (0-1)
	 * \param ISI	Initial spread index (FWI output). Note that the FBP version of the ISI calculation (in the FWI module) should be used.
	 * \param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code> Boolean. If TRUE, then acceleration is applied to various output statistics in the FBP standard. This value should only applicable to point ignitions. If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code> Boolean. If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code> Boolean. If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided. This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code> Boolean. Specific FBP fuel types use different equations during green-up. This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY</code> Boolean. Specific FBP grass fuel types use different values during standing vs. matted. If TRUE, then grass is standing. If FALSE, then matted.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code> Boolean. If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0. If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * \param rsi The calculated RSI value
	 * 
	 * \retval E_POINTER	The address provided for rsi is invalid
	 * \retval S_OK	Successful
	 * \retval E_INVALIDARG	Invalid inputs have caused (likely) a divide by zero error.
	 */
	virtual NO_THROW HRESULT RSI(double FFMC, double BUI, double FMC, double ISI, short flag, const CCWFGM_FuelOverrides* overrides, double *rsi) const override;
	/**
	 * Calculates flame length. Note that this routine is not part of the FBP standard. 
	 * \param height	Tree Height
	 * \param CFB	Crown fraction burned
	 * \param FI	Fire intensity
	 * \param fl	The calculated RSI value
	 * 
	 * \retval E_POINTER	The address provided for fi is invalid
	 * \retval S_OK		Successful
	 * \retval E_INVALIDARG	Invalid input parameter
	 */
	virtual NO_THROW HRESULT FlameLength(double height, double CFB, double FI, const CCWFGM_FuelOverrides* overrides, double *fl) const override;

	/**
	 * The name of the fuel type.
	 * \param pVal	The fuel type name.
	 * 
	 * \retval E_POINTER	The address provided for pVal is invalid.
	 * \retval E_FAIL	An attempt to change the name of a read-only fuel type was a tried.
	 * \retval S_OK	Successful
	 */
	virtual NO_THROW HRESULT get_Name( std::string *pVal) const override;
	/**
	 * Get the name of the fuel type.
	 * \param newVal	The fuel type name.
	 * 
	 * \retval E_POINTER	The address provided for pVal is invalid.
	 * \retval S_OK	Successful
	 */
	virtual NO_THROW HRESULT put_Name( const std::string &newVal) override;

	/**
	 * These properties are used only for M-1, M-2 fuel types. They define extra parameters that are needed for those fuel types.
	 * For any other fuel types, these parameters are unused.
	 * C-2 and D-1 are pointers to ICWFGM_Fuel objects which represent the appropriate fuel type.
		If the fuel type is not mixed (or modified), then attempts to get or set these parameters will result in a returned error code. Specific rules regarding this error code are expected to change slightly.
		Retrieval of C-2 or D-1 pointer values does not modify the COM reference counter for either of these objects. Assignment will increment the reference counter for the new object and decrement the reference counter for the old object.
	 * \param pVal	The fuel type name.
		\sa ICWFGM_FBPFuel::C2

		\retval E_POINTER	The address provided for newVal is invalid.
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT get_C2( boost::intrusive_ptr<ICWFGM_Fuel> *pVal) const override;
	/*! These properties are used only for M-1, M-2 fuel types. They define extra parameters that are needed for those fuel types. For any other fuel types, these parameters are unused. C-2 and D-1 are pointers to ICWFGM_Fuel objects which represent the appropriate fuel type.
		If the fuel type is not mixed (or modified), then attempts to get or set these parameters will result in a returned error code. Specific rules regarding this error code are expected to change slightly.
		Retrieval of C-2 or D-1 pointer values does not modify the COM reference counter for either of these objects. Assignment will increment the reference counter for the new object and decrement the reference counter for the old object.
	 * \param newVal	When setting the property.
		\sa ICWFGM_FBPFuel::C2

		\retval E_POINTER	The address provided for pVal is invalid.
		\retval S_OK	Successful.
		\retval E_UNEXPECTED	The fuel type which is being asked to assign a C-2 or D-1 value is not mixed.
		\retval E_NOINTERFACE	The object that the pointer being passed as C-2 (or D-1) represents does not support the ICWFGM_Fuel interface.
		\retval ERROR_SCENARIO_SIMULATION_RUNNING	The current scenario uses this fuel type and is running, the fuel cannot be changed at this time.
	*/
	virtual NO_THROW HRESULT put_C2( const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) override;
	/*! These properties are used only for M-1, M-2 fuel types. They define extra parameters that are needed for those fuel types. For any other fuel types, these parameters are unused. C-2 and D-1 are pointers to ICWFGM_Fuel objects which represent the appropriate fuel type.
		If the fuel type is not mixed (or modified), then attempts to get or set these parameters will result in a returned error code. Specific rules regarding this error code are expected to change slightly.
		Retrieval of C-2 or D-1 pointer values does not modify the COM reference counter for either of these objects. Assignment will increment the reference counter for the new object and decrement the reference counter for the old object.
	 * \param pVal	When retrieving the property.
		\sa ICWFGM_FBPFuel::D1

		\retval E_POINTER	The address provided for pVal is invalid.
		\retval S_OK	Successful.
	*/
	virtual NO_THROW HRESULT get_D1( boost::intrusive_ptr<ICWFGM_Fuel> *pVal) const override;
	/*! These properties are used only for M-1, M-2 fuel types. They define extra parameters that are needed for those fuel types. For any other fuel types, these parameters are unused. C-2 and D-1 are pointers to ICWFGM_Fuel objects which represent the appropriate fuel type.
		If the fuel type is not mixed (or modified), then attempts to get or set these parameters will result in a returned error code. Specific rules regarding this error code are expected to change slightly.
		Retrieval of C-2 or D-1 pointer values does not modify the COM reference counter for either of these objects. Assignment will increment the reference counter for the new object and decrement the reference counter for the old object.
	 * \param newVal	When setting the property.
		\sa ICWFGM_FBPFuel::D1

		\retval E_POINTER	The address provided for pVal is invalid.
		\retval S_OK	Successful.
		\retval E_UNEXPECTED	The fuel type which is being asked to assign a C-2 or D-1 value is not mixed.
		\retval E_NOINTERFACE	The object that the pointer being passed as C-2 (or D-1) represents does not support the ICWFGM_Fuel interface.
		\retval ERROR_SCENARIO_SIMULATION_RUNNING	The current scenario uses this fuel type and is running, the fuel cannot be changed at this time.
	*/
	virtual NO_THROW HRESULT put_D1( const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) override;
	/*! Reports whether the fuel type is C-1, C-2, C-3, C-4, C-5, C-6, or C-7.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool Always false / 0
		\sa ICWFGM_Fuel::IsConiferFuelType

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsConiferFuelType( bool *retbool) const override;
	/*! Reports whether the fuel type is D-1, D-2, or D-1/D-2.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool Always false / 0
		\sa ICWFGM_Fuel::IsDeciduousFuelType

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsDeciduousFuelType( bool *retbool) const override;
	/*! Reports whether the fuel type is M-1 or M-2.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool result of the test
		\sa ICWFGM_Fuel::IsMixedFuelType

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsMixedFuelType( bool *retbool) const override;
	/*! Reports whether the fuel type is O-1a or O-1b.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool result of the test
		\sa ICWFGM_Fuel::IsGrassFuelType

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsGrassFuelType( bool *retbool) const override;
	/*! Reports whether the fuel type is C-6.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool result of the test
		\sa ICWFGM_Fuel::IsC6FuelType

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsC6FuelType( bool *retbool) const override;
	/*! Reports whether the fuel type is S-1, S-2, or S-3.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool result of the test
		\sa ICWFGM_Fuel::IsSlashFuelType

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsSlashFuelType(bool *retbool) const override;
	/*! Reports whether the fuel type is M-3 or M-4.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool result of the test
		\sa ICWFGM_Fuel::IsMixedDeadFirFuelType

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsMixedDeadFirFuelType(bool *retbool) const override;
	/*! Reports whether the fuel type is non-fuel.
		This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	 * \param retbool result of the test
		\sa ICWFGM_Fuel::IsNonFuel

		\retval E_POINTER	the address provided for retbool is invalid
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT IsNonFuel( bool *retbool) const override;
	/*! Sets the default _GUID. Typically this value identifies the original read-only fuel type used to create/clone the fuel type, but can be used to store any value (because this value is unused by this COM DLL).
	 * \param clsID	the default _GUID
		\sa ICWFGM_FBPFuel::SetDefaultCLSID

		\retval E_POINTER	The address provided for clsId is invalid 
		\retval S_OK	Successful 
		\retval ERROR_SCENARIO_SIMULATION_RUNNING	Value cannot be changed as it is being used in a currently running simulation
	*/
	virtual NO_THROW HRESULT SetDefaultCLSID(_GUID *clsID) override;
	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
		For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
		For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
		This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	 * \param clsID	return value for _GUID
		\sa ICWFGM_Fuel::GetDefaultCLSID
		
		\retval E_POINTER	The address provided for clsId is invalid 
		\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;
	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
	/*! Polymorphic. Gets a particular attribute for a fuel. Each fuel type comprises of a variety of equations and values. This function allows the client application to retrieve most any value that would define some aspect of the calculations for this fuel type.
	 * \param option	This parameter identifies which attribute value to retrieve. Refer to the following table for key values and descriptions.
	 * \param value	The value of the attribute being requested.
		\sa ICWFGM_Fuel::GetAttribute

		\retval E_POINTER	The address provided for attribute is invalid.
		\retval S_OK	Successful.
		\retval E_UNEXPECTED	The fuel type (or some aspect of it) is inconsistent with the attribute requested (e.g. asking for attribute A from a mixed fuel type).
	*/
	virtual NO_THROW HRESULT GetAttribute( std::uint16_t option, PolymorphicAttribute *value) const override;
	/*! Polymorphic. Sets a particular attribute for a fuel. This method can be used to modify some generic value associated with the fuel, or most any coefficient of specific equations used to calculated values for the fuel.
	 * \param option	This parameter identifies which attribute value to set. Refer to following table for key values and descriptions.
	 * \param value	The value of the attribute to be set.
		\sa ICWFGM_Fuel::SetAttribute

		\retval S_OK	Successful.
		\retval E_UNEXPECTED	The fuel type (or some aspect of it) is inconsistent with the attribute requested (e.g. trying to set attribute A for a mixed fuel type).
		\retval ERROR_SCENARIO_SIMULATION_RUNNING	Value cannot be changed as it is being used in a currently running simulation.
	*/
	virtual NO_THROW HRESULT SetAttribute( std::uint16_t option, const PolymorphicAttribute &value) override;
	/*! Given a request for a specific type of equation, retrieves the index for the specific equation (set) used for a particular calculation.
	 * \param equationKey	One of the following values, as defined in FuelCOM_ext.h
			<ul>
			<li> FUELCOM_EQUATION_FMC
			<li> FUELCOM_EQUATION_SFC
			<li> FUELCOM_EQUATION_SFC_GREENUP
			<li> FUELCOM_EQUATION_TFC
			<li> FUELCOM_EQUATION_TFC_GREENUP
			<li> FUELCOM_EQUATION_RSI
			<li> FUELCOM_EQUATION_RSI_GREENUP
			<li> FUELCOM_EQUATION_ISF
			<li> FUELCOM_EQUATION_ISF_GREENUP
			<li> FUELCOM_EQUATION_CFB
			<li> FUELCOM_EQUATION_CFB_GREENUP
			<li> FUELCOM_EQUATION_ACCEL
			<li> FUELCOM_EQUATION_LB
			</ul>
	 * \param equation	Index of the requested equation. Refer to the following table for equation indices and what they refer to.
		\sa ICWFGM_FBPFuel::GetEquation

		\retval E_POINTER	The address provided for equation index is invalid.
		\retval S_OK	Successful.
		\retval E_INVALIDARG	The equationKey index is invalid.
	*/
	virtual NO_THROW HRESULT GetEquation(std::uint16_t equationKey, std::uint16_t *equation) const override;
	/*! Requests to change a specific equation defining part of the operations for the fuel type. If the request matches the type of the current equation, then nothing is performed. Once a given equation format has been chosen, virtually any coefficient or attribute of that equation (set) can be modified using the method SetAttribute.
	 * \param equationKey	One of the following values, as defined in FuelCOM_ext.h
			<ul>
			<li> FUELCOM_EQUATION_FMC
			<li> FUELCOM_EQUATION_SFC
			<li> FUELCOM_EQUATION_SFC_GREENUP
			<li> FUELCOM_EQUATION_TFC
			<li> FUELCOM_EQUATION_TFC_GREENUP
			<li> FUELCOM_EQUATION_RSI
			<li> FUELCOM_EQUATION_RSI_GREENUP
			<li> FUELCOM_EQUATION_ISF
			<li> FUELCOM_EQUATION_ISF_GREENUP
			<li> FUELCOM_EQUATION_CFB
			<li> FUELCOM_EQUATION_CFB_GREENUP
			<li> FUELCOM_EQUATION_ACCEL
			<li> FUELCOM_EQUATION_LB
			</ul>
	 * \param equation	The index identifying the equation to be set. Refer to the following table for equestion indices and what they refer to.
		\sa ICWFGM_FBPFuel::SetEquation

		\retval E_INVALIDARG	The type of equation was invalid or did not match the equationKey type
		\retval FUELCOM_SUCCESS_NO_CHANGE	If the setting of the equation resulted in no actual change to the equation
		\retval ERROR_SCENARIO_SIMULATION_RUNNING	Value cannot be changed as it is being used in a currently running scenario
		\retval S_OK	Success
	*/
	virtual NO_THROW HRESULT SetEquation(std::uint16_t equationKey, std::uint16_t equation) override;

	virtual NO_THROW HRESULT get_CustomEquation_Accel( boost::intrusive_ptr<ICWFGM_AccelAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_Accel( const boost::intrusive_ptr<ICWFGM_AccelAttribute> &newVal) override;
	virtual NO_THROW HRESULT get_CustomEquation_FMC( boost::intrusive_ptr<ICWFGM_FMCAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_FMC( const boost::intrusive_ptr<ICWFGM_FMCAttribute> &newVal) override;
	virtual NO_THROW HRESULT get_CustomEquation_SFC( boost::intrusive_ptr<ICWFGM_SFCAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_SFC( const boost::intrusive_ptr<ICWFGM_SFCAttribute> &newVal) override;
	virtual NO_THROW HRESULT get_CustomEquation_TFC( boost::intrusive_ptr<ICWFGM_TFCAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_TFC( const boost::intrusive_ptr<ICWFGM_TFCAttribute> &newVal) override;
	virtual NO_THROW HRESULT get_CustomEquation_CFB( boost::intrusive_ptr<ICWFGM_CFBAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_CFB( const boost::intrusive_ptr<ICWFGM_CFBAttribute> &newVal) override;
	virtual NO_THROW HRESULT get_CustomEquation_RSI( boost::intrusive_ptr<ICWFGM_RSIAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_RSI( const boost::intrusive_ptr<ICWFGM_RSIAttribute> &newVal) override;
	virtual NO_THROW HRESULT get_CustomEquation_ISF( boost::intrusive_ptr<ICWFGM_ISFAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_ISF( const boost::intrusive_ptr<ICWFGM_ISFAttribute> &newVal) override;
	virtual NO_THROW HRESULT get_CustomEquation_LB( boost::intrusive_ptr<ICWFGM_LBAttribute> *pVal) const override;
	virtual NO_THROW HRESULT put_CustomEquation_LB( const boost::intrusive_ptr<ICWFGM_LBAttribute> &newVal) override;
	virtual NO_THROW HRESULT Equals(const boost::intrusive_ptr<ICWFGM_Fuel> &fuel, bool compareName) const override;

	CCWFGM_Fuel &operator=(const CCWFGM_Fuel &toCopy);
	
#ifndef DOXYGEN_IGNORE_CODE

	static NO_THROW HRESULT FromCLSID(const _GUID &guid, boost::intrusive_ptr<ICWFGM_Fuel> *pVal);

public:
	bool				m_bRequiresSave;

protected:
	std::string			m_name;
	CRWThreadSemaphore	m_mt_lock;
	FBPFuel				m_fuel;

#endif
};


class FUELCOM_API CCWFGM_Fuel_Readonly : public CCWFGM_Fuel {
	CCWFGM_Fuel_Readonly(const CCWFGM_Fuel &toCopy);

public:
	CCWFGM_Fuel_Readonly();

	virtual std::optional<bool> isdirty() const noexcept override { return false; }

	virtual NO_THROW HRESULT SetDefaultCLSID(_GUID *clsID) override;
	virtual NO_THROW HRESULT put_Name( const std::string &newVal) override;
	virtual NO_THROW HRESULT put_C2( const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) override;
	virtual NO_THROW HRESULT put_D1( const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) override;
	virtual NO_THROW HRESULT SetAttribute( std::uint16_t option, const PolymorphicAttribute &value) override;
	virtual NO_THROW HRESULT SetEquation(std::uint16_t equationKey, std::uint16_t equation) override;
	virtual NO_THROW HRESULT put_CustomEquation_Accel( const boost::intrusive_ptr<ICWFGM_AccelAttribute> &newVal) override;
	virtual NO_THROW HRESULT put_CustomEquation_FMC( const boost::intrusive_ptr<ICWFGM_FMCAttribute> &newVal) override;
	virtual NO_THROW HRESULT put_CustomEquation_SFC( const boost::intrusive_ptr<ICWFGM_SFCAttribute> &newVal) override;
	virtual NO_THROW HRESULT put_CustomEquation_TFC( const boost::intrusive_ptr<ICWFGM_TFCAttribute> &newVal) override;
	virtual NO_THROW HRESULT put_CustomEquation_CFB( const boost::intrusive_ptr<ICWFGM_CFBAttribute> &newVal) override;
	virtual NO_THROW HRESULT put_CustomEquation_RSI( const boost::intrusive_ptr<ICWFGM_RSIAttribute> &newVal) override;
	virtual NO_THROW HRESULT put_CustomEquation_ISF( const boost::intrusive_ptr<ICWFGM_ISFAttribute> &newVal) override;
	virtual NO_THROW HRESULT put_CustomEquation_LB( const boost::intrusive_ptr<ICWFGM_LBAttribute> &newVal) override;
};

#endif //__CWFGM_FUEL_H_


// Declaration of the CCWFGM_Fuel_C1

#ifndef __CWFGM_FUEL_C1_H_
#define __CWFGM_FUEL_C1_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_C1

class FUELCOM_API CCWFGM_Fuel_C1 : public CCWFGM_Fuel_Readonly
{ 
public:
	CCWFGM_Fuel_C1();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif

 //__CWFGM_FUEL_C1_H_

// CWFGM_Fuel_C2.h : Declaration of the CCWFGM_Fuel_C2

#ifndef __CWFGM_FUEL_C2_H_
#define __CWFGM_FUEL_C2_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_C2

class FUELCOM_API CCWFGM_Fuel_C2 : public CCWFGM_Fuel_Readonly
{
public:
	CCWFGM_Fuel_C2();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_C2_H_

// CWFGM_Fuel_C3.h : Declaration of the CCWFGM_Fuel_C3

#ifndef __CWFGM_FUEL_C3_H_
#define __CWFGM_FUEL_C3_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_C3

class FUELCOM_API CCWFGM_Fuel_C3 : public CCWFGM_Fuel_Readonly
{
public:
	CCWFGM_Fuel_C3();

public:


public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_C3_H_

// CWFGM_Fuel_C4.h : Declaration of the CCWFGM_Fuel_C4

#ifndef __CWFGM_FUEL_C4_H_
#define __CWFGM_FUEL_C4_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_C4

class FUELCOM_API CCWFGM_Fuel_C4 : public CCWFGM_Fuel_Readonly
{

public:
	CCWFGM_Fuel_C4();

public:

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_C4_H_

// CWFGM_Fuel_C5.h : Declaration of the CCWFGM_Fuel_C5

#ifndef __CWFGM_FUEL_C5_H_
#define __CWFGM_FUEL_C5_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_C5

class FUELCOM_API CCWFGM_Fuel_C5 : public CCWFGM_Fuel_Readonly
{
public:
	CCWFGM_Fuel_C5();

public:

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_C5_H_

// CWFGM_Fuel_C6.h : Declaration of the CCWFGM_Fuel_C6

#ifndef __CWFGM_FUEL_C6_H_
#define __CWFGM_FUEL_C6_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_C6

class FUELCOM_API CCWFGM_Fuel_C6 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_C6();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_C6_H_


// CWFGM_Fuel_C7.h : Declaration of the CCWFGM_Fuel_C7

#ifndef __CWFGM_FUEL_C7_H_
#define __CWFGM_FUEL_C7_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_C7

class FUELCOM_API CCWFGM_Fuel_C7 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_C7();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_C7_H_

// CWFGM_Fuel_D1.h : Declaration of the CCWFGM_Fuel_D1

#ifndef __CWFGM_FUEL_D1_H_
#define __CWFGM_FUEL_D1_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_D1

class FUELCOM_API CCWFGM_Fuel_D1 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_D1();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_D1_H_

// CWFGM_Fuel_D2.h : Declaration of the CCWFGM_Fuel_D2

#ifndef __CWFGM_FUEL_D2_H_
#define __CWFGM_FUEL_D2_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_D2

class FUELCOM_API CCWFGM_Fuel_D2 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_D2();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_D2_H_

// CWFGM_Fuel_D1D2.h : Declaration of the CCWFGM_Fuel_D1D2

#ifndef __CWFGM_FUEL_D1D2_H_
#define __CWFGM_FUEL_D1D2_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_D1D2

class FUELCOM_API CCWFGM_Fuel_D1D2 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_D1D2();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;


	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;
	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_D1D2_H_

// CWFGM_Fuel_M1.h : Declaration of the CCWFGM_Fuel_M1

#ifndef __CWFGM_FUEL_M1_H_
#define __CWFGM_FUEL_M1_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_M1

class FUELCOM_API CCWFGM_Fuel_M1 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_M1();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_M1_H_

// CWFGM_Fuel_M2.h : Declaration of the CCWFGM_Fuel_M2

#ifndef __CWFGM_FUEL_M2_H_
#define __CWFGM_FUEL_M2_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_M2

class FUELCOM_API CCWFGM_Fuel_M2 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_M2();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_M2_H_

// CWFGM_Fuel_M1M2.h : Declaration of the CCWFGM_Fuel_M1M2

#ifndef __CWFGM_FUEL_M1M2_H_
#define __CWFGM_FUEL_M1M2_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_M1M2

class FUELCOM_API CCWFGM_Fuel_M1M2 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_M1M2();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_M1M2_H_

// CWFGM_Fuel_M3.h : Declaration of the CCWFGM_Fuel_M3

#ifndef __CWFGM_FUEL_M3_H_
#define __CWFGM_FUEL_M3_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_M3

class FUELCOM_API CCWFGM_Fuel_M3 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_M3();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_M3_H_

// CWFGM_Fuel_M4.h : Declaration of the CCWFGM_Fuel_M4

#ifndef __CWFGM_FUEL_M4_H_
#define __CWFGM_FUEL_M4_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_M4

class FUELCOM_API CCWFGM_Fuel_M4 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_M4();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_M3M4_H_

// CWFGM_Fuel_M3M4.h : Declaration of the CCWFGM_Fuel_M3M4

#ifndef __CWFGM_FUEL_M3M4_H_
#define __CWFGM_FUEL_M3M4_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_M3M4

class FUELCOM_API CCWFGM_Fuel_M3M4 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_M3M4();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_M3M4_H_

// CWFGM_Fuel_O1a.h : Declaration of the CCWFGM_Fuel_O1a

#ifndef __CWFGM_FUEL_O1A_H_
#define __CWFGM_FUEL_O1A_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_O1a

class FUELCOM_API CCWFGM_Fuel_O1a : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_O1a();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_O1A_H_

// CWFGM_Fuel_O1b.h : Declaration of the CCWFGM_Fuel_O1b

#ifndef __CWFGM_FUEL_O1B_H_
#define __CWFGM_FUEL_O1B_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_O1b

class FUELCOM_API CCWFGM_Fuel_O1b : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_O1b();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_O1B_H_

// CWFGM_Fuel_O1ab.h : Declaration of the CCWFGM_Fuel_O1a

#ifndef __CWFGM_FUEL_O1AB_H_
#define __CWFGM_FUEL_O1AB_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_O1ab

class FUELCOM_API CCWFGM_Fuel_O1ab : public CCWFGM_Fuel_Readonly
{
public:
	CCWFGM_Fuel_O1ab();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_O1AB_H_

// CWFGM_Fuel_S1.h : Declaration of the CCWFGM_Fuel_S1

#ifndef __CWFGM_FUEL_S1_H_
#define __CWFGM_FUEL_S1_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_S1

class FUELCOM_API CCWFGM_Fuel_S1 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_S1();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_S1_H_

// CWFGM_Fuel_S2.h : Declaration of the CCWFGM_Fuel_S2

#ifndef __CWFGM_FUEL_S2_H_
#define __CWFGM_FUEL_S2_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_S2

class FUELCOM_API CCWFGM_Fuel_S2 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_S2();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_S2_H_

// CWFGM_Fuel_S3.h : Declaration of the CCWFGM_Fuel_S3

#ifndef __CWFGM_FUEL_S3_H_
#define __CWFGM_FUEL_S3_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_S3

class FUELCOM_API CCWFGM_Fuel_S3 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_S3();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#endif //__CWFGM_FUEL_S3_H_

// CWFGM_Fuel_NON.h : Declaration of the CCWFGM_Fuel_NON

#ifndef __CWFGM_FUEL_NON_H_
#define __CWFGM_FUEL_NON_H_

/////////////////////////////////////////////////////////////////////////////
// CCWFGM_Fuel_NON

class FUELCOM_API CCWFGM_Fuel_Non : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_Non();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ2 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ2();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ15 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ15();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ30 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ30();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ31 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ31();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ32 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ32();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ33 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ33();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ40 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ40();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ41 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ41();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ43 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ43();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ44 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ44();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ45 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ45();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ46 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ46();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ47 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ47();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ50 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ50();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ51 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ51();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ52 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ52();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ53 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ53();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ54 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ54();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ55 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ55();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ56 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ56();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ57 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ57();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ58 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ58();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ60 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ60();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ61 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ61();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ62 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ62();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ63 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ63();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ64 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ64();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ65 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ65();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ66 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ66();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ67 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ67();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ68 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ68();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ69 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ69();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ70 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ70();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};


class FUELCOM_API CCWFGM_Fuel_NZ71 : public CCWFGM_Fuel_Readonly {
public:
	CCWFGM_Fuel_NZ71();

public:
	/*! Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.
	\param newFuel Address of memory to contain the reference for a newly created fuel object.
	\sa ICWFGM_Fuel::Clone

	\retval E_POINTER The address provided for newFuel is invalid
	\retval S_OK Successful
	\retval E_OUTOFMEMORY Insufficient memory
	\retval ERROR_SEVERITY_WARNING Unspecified failure
	\retval E_NOINTERFACE Interface does not exist
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const override;

	/*! Returns the default _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself.
	For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the _GUID for the C-1 read-only fuel type.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetDefaultCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsID) const override;

	/*! Returns the _GUID for this fuel type. A _GUID is the identifier for the class of a COM object.
	This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for _GUID
	\sa ICWFGM_Fuel::GetCLSID

	\retval E_POINTER	The address provided for clsId is invalid
	\retval S_OK	Successful
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsID) const override;
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif

#endif //__CWFGM_FUEL_Non_H_
