/**
 * WISE_FBP_Module: ICWFGM_Fuel.h
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

#pragma once

#include "ICWFGM_CommonBase.h"
#include "guid.h"
#include "hssconfig/config.h"
#include <map>

#define __FuelCom_h__

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(push, 8)
#endif

/*
	Declaration for the ICWFGM_PercentileAttribute class

	Method list:
		No argument constructor
		RSI (initial spread rate without BUI effect) with a return type HRESULT that takes the following parameters:
			A clsId value of type _GUID
			A RSIin value of type double
			A CFBin value of type double
			A RSIout value of type double
*/
class FUELCOM_API ICWFGM_PercentileAttribute
{
public:
	ICWFGM_PercentileAttribute();

	virtual NO_THROW HRESULT RSI(const _GUID *clsId, double RSIin, double CFBin, double *RSIout) = 0;
};

/*
	Declaration for the ICWFGM_Fuel class

	Method list:
		No argument constructor
		Destructor method
		Clone with a return type of HRESULT that takes the following parameters:
			A newFuel object of type ICWFGM_CommonBase
		Clone with a return type of HRESULT that takes the following parameters:
			A newFuel object of type ICWFGM_Fuel
		get_Name with a return type of HRESULT that takes the following parameters:
			A pVal value of type String
		get_SpeciesCode with a return type of HRESULT that takes the following parameters:
			A pVal value of type String
		MT_Lock with a return type of HRESULT that takes the following parameters:
			A exclusive value of type unint16
			A obtain value of type uint16_t
		FMC (foliar moisture content) with a return type of HRESULT that takes the following parameters:
			A latitude value of type double
			A longitude value of type double
			A elevation value of type double
			A day value of type uint16
			A fmc value of type double
		CalculateROSValues with a return type of HRESULT that takes the following parameters:
			A GS value of type double
			A SAZ value of type double
			A WS value of type double
			A WAZ value of type double
			A BUI value of type double
			A FMC value of type double
			A FFMC value of type double
			A fF value of type double
			A time value of type WTimeSpan
			A ffmc_time value of type WTimeSpan
			A flag value of type short
			A RSIadjust value of type ICWFGM_PercentileAttribute
			
*/


class FUELCOM_API CCWFGM_FuelOverrides {
	struct entry {
		std::uint16_t key;
		PolymorphicAttribute value;
	};

	std::vector<entry> overrides;

public:
	CCWFGM_FuelOverrides() = default;
	~CCWFGM_FuelOverrides() = default;

	bool AddOverride(const std::uint16_t option, const PolymorphicAttribute value);
	bool RemoveOverride(const std::uint16_t option);
	bool ContainsOverride(const std::uint16_t option) const;
	bool RetrieveOverride(const std::uint16_t option, PolymorphicAttribute& value) const;
};


/** Interface CWFGM Fuel

ICWFGM_Fuel interface is a generic interface used by the FireEngine Module (or other tools such as FBPTester) to extract a variety of statistical data about the fuel type given specific conditions.\n\n
A given simulation/scenario may use many fuel types, each via the ICWFGM_Fuel COM interface for the purposes of calculating values such as rate-of-spread (ROS).  A fuel type may match the published FBP standard, or it may have different, user-defined coefficients for the equations.  A fuel type may also represent a fuel that is not defined by the FBP standard (e.g. urban areas).\n\n
Applications can also define new fuel types outside the FBP standard that may work with the simulation engine providing they conform to this interface definition and semantics.
*/
class FUELCOM_API ICWFGM_Fuel : public ICWFGM_CommonBase {
public:
	ICWFGM_Fuel();
	virtual ~ICWFGM_Fuel();

	/**
	Creates a new fuel object with properties which are identical to that of the object being called, returns a handle to the new object in newFuel.  This may call a copy constructor but this way, the client code doesn't need the type information of the fuel type to copy.
	\param newFuel Address of memory to contain the reference for a newly created fuel object
	*/
	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const = 0;

	// creates a copy in a read/write version
	virtual NO_THROW HRESULT Mutate(boost::intrusive_ptr<ICWFGM_Fuel> *newFuel) const = 0;

	/**
	Return the name of the fuel type
	\param pVal Name of the fuel type
	*/
	virtual NO_THROW HRESULT get_Name(std::string *pVal) const = 0;

	/**
	Changes the state of the object with respect to access rights. When the object is used by an active simulation, it must not be modified. When the object is somehow modified, it must be done so in an atomic action to prevent concerns with arising from multithreading. Note that these locks are only needed for calls to this object via this interface. Method calls from the other interface are already multithreading friendly.
	\param exclusive TRUE if the requester wants a write lock, false for read/shared access
	\param obtain TRUE to obtain the lock, FALSE to release the lock.  If this is FALSE, then the exclusive parameter must match the initial call used to obtain the lock.
	*/
	virtual NO_THROW HRESULT MT_Lock(bool exclusive, std::uint16_t obtain) = 0;

	/**
	Calculates the FMC (foliar moisture content) value based on several parameters. If elevation is negative, then the normalized latitude is calculated based on equation 1 of "Development and the Structure of the Canadian Forest Fire Behaviour Prediction System -Information Report ST-X-3", otherwise it is calculated from equation 3. Similarly, minimum FMC is calculated using either equation 2 or 4.
	If the latitude and longitude are outside the general extents of Canada (latitude: 42 to 83 degrees, longitude: -52 to -141 degrees), then the latitude and/or longitude are modified to be within these ranges.
	\param latitude Specific location (latitude, radians, signed) on the earth's surface.
	\param longitude Specific location (longitude, radians, signed) on the earth's surface.
	\param elev Elevation of the specific location (metres) from sea level.
	\param day Julian day (day of the year, 0-365)
	\param fmc The calculated FMC value (percentage value expressed as a decimal 0-1)
	*/
	virtual NO_THROW HRESULT FMC(double latitude, double longitude, double elev,
			std::uint16_t day, const CCWFGM_FuelOverrides *overrides, double *fmc) const = 0;

	/**
	Given several input parameters, calculates various of rate of spread (ROS) values. The specific set of equations used to calculate ROS values is determined by the fuel type and/or any modifications which have been applied.
	Automatic caching of previously calculated values is performed for efficiency.
	\param GS	Percentage ground slope specified as a decimal value (0 - 1)
	\param SAZ	Slope azimuth, upslope (radians, Cartesian)
	\param WS	Observed wind speed (kph)
	\param WAZ	Wind azimuth (radians, Cartesian)
	\param BUI	Buildup index (FWI output)
	\param FMC	Foliar moisture code (FBP output) (0-1)
	\param FFMC	Fine fuel moister code (FWI output)
	\param fF	Fine fuel moisture function in the ISI (FWI output)
	\param t	Time in seconds since ignition,  used for purposes of calculating acceleration
	\param ffmc_t	Time in seconds for the duration used to calculate FFMC
	\param flag	A combination of
	<ul>
	<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	</ul>
	bit flags, defined in FireEngine_Ext.h
	\param RSIadjust - pointer to a class to modify RSI values, potentially for specifying percentiles (where the default RSI value is at the 50th percentile)
	\param rss	Calculated value, RSS (metres per minute)
	\param roseq	Calculated value, ROSeq (equilibrium rate of spread) (metres per minute)
	\param ros	Calculated value, ROS (rate of spread) (metres per minute)
	\param frss	Calculated value, FRSS (flank RSS) (metres per minute)
	\param froseq	Calculated value, FROSeq (flank equilibrium rate of spread) (metres per minute)
	\param fros	Calculated value, FROS (flank rate of spread) (metres per minute)
	\param brss Calculated value, BRSS (back RSS) (metres per minute)
	\param broseq	Calculated value, BROSeq (back equilibrium rate of spread) (metres per minute)
	\param bros	Calculated value, BROS (back rate of spread) (metres per minute)
	\param wsv	Calculated value, WSV (wind speed vector) (metres per minute)
	\param raz	Calculated value, RAZ (wind speed vector azimuth) (radians, Cartesian)
	*/
	virtual NO_THROW HRESULT CalculateROSValues(double GS, double SAZ, double WS, double WAZ,
			double BUI, double FMC, double FFMC, double fF, const HSS_Time::WTimeSpan &time,
			const HSS_Time::WTimeSpan &ffmc_time, short flag, const CCWFGM_FuelOverrides* overrides,
			ICWFGM_PercentileAttribute *RSIadjust, double *rss, double *roseq, double *ros,
			double *frss, double *froseq, double *fros, double *brss, double *broseq,
			double *bros, double *lb, double *wsv, double *raz) const = 0;

	/**
	Given several input parameters, calculates FC (fuel consumption) values. The specific set of equations used to calculate FC values is determined by the fuel type and/or any modifications which have been applied.
	Automatic caching of previously calculated values is performed for efficiency.
	\param FFMC	Fine fuel moister code (FWI output)
	\param BUI	Buildup index (FWI output)
	\param FMC	Foliar moisture code (FBP output) (0-1)
	\param RSS	(metres per minute)
	\param ROS	Rate of spread (metres per minute)
	\param flag	A combination of
	<ul>
	<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	</ul>
	bit flags, defined in FireEngine_Ext.h For consistency of outputs, these flags should match those provided to determine the ROS values.
	\param cfb	Calculated value, crown fraction burned (unitless).
	\param cfc	Calculated value, crown fuel consumption (kg/m2).
	\param rso	Calculated value, critical spread rate for crowning
	\param csi	Calculated value, critical surface intensity for crowning
	\param sfc	Calculated value, surface fuel consumption (kg/m2).
	\param tfc	Calculated value, total fuel consumption (kg/m2).
	\param fi	Calculated value, fire intensity
	*/
	virtual NO_THROW HRESULT CalculateFCValues(double FFMC, double BUI, double FMC, double RSS,
			double ROS, short flag, const CCWFGM_FuelOverrides* overrides, double *cfb, double *cfc,
			double *rso, double *csi, double *sfc, double *tfc, double *fi) const = 0;

	/**
	Calculates statistics of the theoretical ellipse defined by ROS, FROS, BROS.
	To match the CFS code, these values should be equilibrium values. To match Prometheus implementations, these should values should be instantaneous, after corrections through any ellipse equations.
	\param ROS	Rate of spread (metres per minute).
	\param FROS	Flank rate of spread (metres per minute).
	\param BROS	Back rate of spread (metres per minute).
	\param CFB	Crown fraction burned.
	\param time	Time since fire start, important if acceleration is turned on.
	\param flag	A combination of
	<ul>
	<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	</ul>
	bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	\param area	Calculated value, fire area.
	\param perimeter	Calculated value, fire perimeter.
	*/
	virtual NO_THROW HRESULT CalculateStatistics(double ROS, double FROS, double BROS, double CFB,
			const HSS_Time::WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
			double *area, double *perimeter) const = 0;

	/**
	Calculates spread distances of the theoretical ellipse defined by ROS, FROS, BROS.
	\param ROS	Equilibrium rate of spread (metres per minute).
	\param FROS	Equilibrium flank rate of spread (metres per minute).
	\param BROS	Equilibrium back rate of spread (metres per minute).
	\param CFB	Crown fraction burned.
	\param time	Time since fire start, important if acceleration is turned on.
	\param flag	A combination of
	<ul>
	<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	</ul>
	bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	\param dhead	Calculated value, head fire spread distance.
	\param dflank	Calculated value, flank fire spread distance.
	\param dback	Calculated value, back fire spread distance.
	*/
	virtual NO_THROW HRESULT CalculateDistances(double ROS, double FROS, double BROS, double CFB,
			const HSS_Time::WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
			double *dhead, double *dflank, double *dback) const = 0;

	virtual NO_THROW HRESULT CalculateROSTheta(double ROS, double FROS, double BROS,
			double RAZ, double Theta, double* rosTheta) const = 0;

	/**
	Calculates the value for ISF based on parameters passed in. Note that this method is used by mixed fuel types only and likely should not be called directly. Automatic caching of previously calculated values is performed for efficiency.
	\param RSF	Intermediate output for calculating ROS values.
	\param SF	Slope factor.
	\param ISZ	Dead wind ISI.
	\param flag	A combination of
	<ul>
	<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	</ul>
	bit flags, defined in FireEngine_Ext.h.
	\param isfValue	the calculated ISF value
	*/
	virtual NO_THROW HRESULT ISF(double RSF, double SF, double ISZ, short flag,
			const CCWFGM_FuelOverrides* overrides, double *isfValue) const = 0;

	/**
	Calculates the SFC (surface fuel consumption) value based on several parameters. Note that this routine may seem redundant to CalculateFCValues() but is used by mixed fuel types. Typically, the CalculateFCValues() method should be called. Automatic caching of previously calculated values is performed for efficiency.
	\param FFMC	Fine fuel moister code (FWI output)
	\param BUI	Buildup index (FWI output)
	\param flag	A combination of
	<ul>
	<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	</ul>
	bit flags, defined in FireEngine_Ext.h
	\param sfc	the calculated SFC value
	*/
	virtual NO_THROW HRESULT SFC(double FFMC, double BUI, short flag,
			const CCWFGM_FuelOverrides* overrides, double *sfc) const = 0;

	/**
	Calculates RSI (initial rate of spread) without BUI effect. Note that this routine may seem redundant to CalculateROSValues()  but is used by mixed fuel types. Typically CalculateROSValues) should be called. Automatic caching of previously calculated values is performed for efficiency.
	\param FFMC	Fine fuel moister code (FWI output)
	\param BUI	Buildup index (FWI output)
	\param FMC	Foliar moisture code (FBP output) (0-1)
	\param ISI	Initial spread index (FWI output).  Note that the FBP version of the ISI calculation (in the FWI module) should be used.
	\param flag	A combination of
	<ul>
	<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	</ul>
	bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS value.
	\param rsi Returned calculated RSI
	*/
	virtual NO_THROW HRESULT RSI(double FFMC, double BUI, double FMC, double ISI,
			short flag, const CCWFGM_FuelOverrides* overrides, double *rsi) const = 0;

	virtual  NO_THROW HRESULT FlameLength(double height, double CFB, double FI, 
			const CCWFGM_FuelOverrides* overrides, double *fl) const = 0;

	/**
	Reports whether the fuel type is C-1, C-2, C-3, C-4, C-5, C-6, or C-7. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsConiferFuelType(bool *retbool) const = 0;

	/**
	Reports whether the fuel type is D-1 or D-2. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsDeciduousFuelType(bool *retbool) const = 0;

	/**
	Reports whether the fuel type is M-1 or M-2. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsMixedFuelType(bool *retbool) const = 0;

	/**
	Reports whether the fuel type is O-1a or O-1b. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsGrassFuelType(bool *retbool) const = 0;

	/**
	Reports whether the fuel type is C-6. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsC6FuelType(bool *retbool) const = 0;

	/**
	Reports whether the fuel type is M-3 or M-4. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsMixedDeadFirFuelType(bool *retbool) const = 0;

	/**
	Reports whether the fuel type is S-1, S-2, or S-3. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsSlashFuelType(bool *retbool) const = 0;

	/**
	Reports whether the fuel type is a non-fuel. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced.
	\param retbool result of the test
	*/
	virtual NO_THROW HRESULT IsNonFuel(bool *retbool) const = 0;

	/**
	Returns the  CLSID for this fuel type. A CLSID is the identifier for the class of a COM object. For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself. For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the CLSID for the C-1 read-only fuel type. This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for CLSID
	*/
	virtual NO_THROW HRESULT GetCLSID(_GUID *clsId) const = 0;

	/**
	Returns the default CLSID for this fuel type. A CLSID is the identifier for the class of a COM object. For read-only fuel types, this value is set to the same class as itself. I.e., it's default fuel type is itself. For read/write fuel types which were cloned from another fuel type, this value is set to the class of the original default fuel type used to create it. I.e., if a C-1 fuel type was cloned into a read/write fuel type, this value would be the CLSID for the C-1 read-only fuel type. This value is unused by this COM DLL and may be removed in future releases. Its purpose is to facilitate the client application ability to reset a fuel type back to its default values.
	\param clsID	return value for CLSID
	*/
	virtual NO_THROW HRESULT GetDefaultCLSID(_GUID *clsId) const = 0;

	/**
	Polymorphic.  Gets a particular attribute for a fuel. Each fuel type comprises of a variety of equations and values. This function allows the client application to retrieve most any value that would define some aspect of the calculations for this fuel type.
	\param option	This parameter identifies which attribute value to retrieve.
	\param value	The value of the attribute being requested.
	*/
	virtual NO_THROW HRESULT GetAttribute(std::uint16_t option, PolymorphicAttribute *pVal) const = 0;

	/**
	Sets a particular attribute for a fuel. This method can be used to modify some generic value associated with the fuel, or most any coefficient of specific equations used to calculated values for the fuel.
	\param option	This parameter identifies which attribute value to retrieve.
	\param value	The value of the attribute being requested.
	*/
	virtual NO_THROW HRESULT SetAttribute(std::uint16_t option, const PolymorphicAttribute &newVal) = 0;

	virtual NO_THROW HRESULT Equals(const boost::intrusive_ptr<ICWFGM_Fuel> &toCopy, bool compareName) const = 0;
};

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(pop)
#endif
