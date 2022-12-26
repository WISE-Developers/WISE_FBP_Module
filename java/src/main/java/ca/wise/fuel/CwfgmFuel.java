/***********************************************************************
 * REDapp - CwfgmFuel.java
 * Copyright (C) 2015-2021 The REDapp Development Team
 * Homepage: http://redapp.org
 * 
 * REDapp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * REDapp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with REDapp. If not see <http://www.gnu.org/licenses/>. 
 **********************************************************************/

package ca.wise.fuel;

import java.lang.String;

import ca.wise.serialize.ISerializeProto;
import ca.hss.general.OutVariable;
import ca.hss.times.WTime;

/**
 * @author rbryce
 *
 */
public abstract class CwfgmFuel implements Cloneable, ISerializeProto<CwfgmFuel> {
	protected String m_name;
	protected Object m_userData = null;

	String getName() { return m_name; }

	public abstract String getSpeciesCode();
	
	public CwfgmFuel() { }

	/**
	 * Creates a new fuel object with properties which are identical to that of the object being called(non-Javadoc)
	 */
	public CwfgmFuel(CwfgmFuel other) {
		m_name = other.m_name;
	}

	/**
	 * Creates a new fuel object with properties which are identical to that of the object being called(non-Javadoc)
	 */
	@Override
	public Object clone() throws CloneNotSupportedException {
		CwfgmFuel f = (CwfgmFuel)super.clone();
		f.m_name = m_name;
		return f;
	}

	/** 
	 * Calculates the FMC (foliar moisture content) value based on several parameters. If elevation is negative, then the normalized latitude is calculated based on equation 1 of "Development and the Structure of the Canadian Forest Fire Behaviour Prediction System -Information Report ST-X-3", otherwise it is calculated from equation 3. Similarly, minimum FMC is calculated using either equation 2 or 4.
	 * If the latitude and longitude are outside the general extents of Canada (latitude: 42 to 83 degrees, longitude: -52 to -141 degrees), then the latitude and/or longitude are modified to be within these ranges. 
	 * @param latitude Specific location (latitude, radians, signed) on the earth's surface.
	 * @param longitude Specific location (longitude, radians, signed) on the earth's surface.
	 * @param elev Elevation of the specific location (metres) from sea level.
	 * @param day Julian day (day of the year, 0-365)
	 * @return The calculated FMC value (percentage value expressed as a decimal 0-1)
 	 */
	public abstract double fmc(double latitude, double longitude, double elev, int day);

	/**
	 * Given several input parameters, calculates various of rate of spread (ROS) values. The specific set of equations used to calculate ROS values is determined by the fuel type and/or any modifications which have been applied.
	 * Automatic caching of previously calculated values is performed for efficiency. 
	 * @param GS	Percentage ground slope specified as a decimal value (0 - 1)
	 * @param SAZ	Slope azimuth, upslope (radians, Cartesian)
	 * @param WS	Observed wind speed (kph)
	 * @param WAZ	Wind azimuth (radians, Cartesian)
	 * @param BUI	Buildup index (FWI output)
	 * @param FMC	Foliar moisture code (FBP output) (0-1)
	 * @param FFMC	Fine fuel moister code (FWI output)
	 * @param fF	Fine fuel moisture function in the ISI (FWI output)
	 * @param t	Time in seconds since ignition,  used for purposes of calculating acceleration
	 * @param ffmc_t	Time in seconds for the duration used to calculate FFMC
	 * @param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h
	 * @param RSIadjust - pointer to a class to modify RSI values, potentially for specifying percentiles (where the default RSI value is at the 50th percentile)
	 * @param rss	Calculated value, RSS (metres per minute)
	 * @param roseq	Calculated value, ROSeq (equilibrium rate of spread) (metres per minute)
	 * @param ros	Calculated value, ROS (rate of spread) (metres per minute)
	 * @param frss	Calculated value, FRSS (flank RSS) (metres per minute)
	 * @param froseq	Calculated value, FROSeq (flank equilibrium rate of spread) (metres per minute)
	 * @param fros	Calculated value, FROS (flank rate of spread) (metres per minute)
	 * @param brss Calculated value, BRSS (back RSS) (metres per minute)
	 * @param broseq	Calculated value, BROSeq (back equilibrium rate of spread) (metres per minute)
	 * @param bros	Calculated value, BROS (back rate of spread) (metres per minute)
	 * @param wsv	Calculated value, WSV (wind speed vector) (metres per minute)
	 * @param raz	Calculated value, RAZ (wind speed vector azimuth) (radians, Cartesian)
	 * @throws CloneNotSupportedException 
	 */
	public abstract void calculateROSValues(double GS, double SAZ, double WS, double WAZ, double BUI, double FMC, double FFMC, double fF,
		    				WTime t, WTime ffmc_t, int flag, CwfgmPercentileAttribute RSIadjust,
							OutVariable<Double> rss, OutVariable<Double> ros_eq, OutVariable<Double> ros,
    						OutVariable<Double> frss, OutVariable<Double> fros_eq, OutVariable<Double> fros, OutVariable<Double> brss,
							OutVariable<Double> bros_eq, OutVariable<Double> bros, OutVariable<Double> wsv, OutVariable<Double> raz) throws CloneNotSupportedException;
	
	/**
	 * Given several input parameters, calculates FC (fuel consumption) values. The specific set of equations used to calculate FC values is determined by the fuel type and/or any modifications which have been applied.
	 * Automatic caching of previously calculated values is performed for efficiency. 
	 * @param FFMC	Fine fuel moister code (FWI output)
	 * @param BUI	Buildup index (FWI output)
	 * @param FMC	Foliar moisture code (FBP output) (0-1)
	 * @param RSS	(metres per minute)
	 * @param ROS	Rate of spread (metres per minute)
	 * @param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * @param cfb	Calculated value, crown fraction burned (unitless).
	 * @param cfc	Calculated value, crown fuel consumption (kg/m2).
	 * @param rso	Calculated value, critical spread rate for crowning
	 * @param csi	Calculated value, critical surface intensity for crowning
	 * @param sfc	Calculated value, surface fuel consumption (kg/m2).
	 * @param tfc	Calculated value, total fuel consumption (kg/m2).
	 * @param fi	Calculated value, fire intensity
	 * @throws CloneNotSupportedException 
	 */
	public abstract void calculateFCValues(double FFMC, double BUI, double FMC,	double RSS, double ROS, int flag, OutVariable<Double> cfb,
						   OutVariable<Double> cfc, OutVariable<Double> rso, OutVariable<Double> csi, OutVariable<Double> sfc, OutVariable<Double> tfc,
						   OutVariable<Double> fi) throws CloneNotSupportedException;
	
	/**
	 * Calculates statistics of the theoretical ellipse defined by ROS, FROS, BROS.
	 * To match the CFS code, these values should be equilibrium values. To match Prometheus implementations, these should values should be instantaneous, after corrections through any ellipse equations. 
	 * @param ROS	Rate of spread (metres per minute).
	 * @param FROS	Flank rate of spread (metres per minute).
	 * @param BROS	Back rate of spread (metres per minute).
	 * @param CFB	Crown fraction burned.
	 * @param time	Time since fire start, important if acceleration is turned on.
	 * @param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * @param area	Calculated value, fire area.
	 * @param perimeter	Calculated value, fire perimeter.
	 */
	public abstract void calculateStatistics(double ROS, double FROS, double BROS, double _CFB, WTime time, int flag, OutVariable<Double> area, OutVariable<Double> perimeter);
	
	/**
	 * Calculates spread distances of the theoretical ellipse defined by ROS, FROS, BROS. 
	 * @param ROS	Equilibrium rate of spread (metres per minute).
	 * @param FROS	Equilibrium flank rate of spread (metres per minute).
	 * @param BROS	Equilibrium back rate of spread (metres per minute).
	 * @param CFB	Crown fraction burned.
	 * @param time	Time since fire start, important if acceleration is turned on.
	 * @param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS values.
	 * @param dhead	Calculated value, head fire spread distance.
	 * @param dflank	Calculated value, flank fire spread distance.
	 * @param dback	Calculated value, back fire spread distance.
	 */
	public abstract void calculateDistances(double ROS, double FROS, double BROS, double _CFB, WTime time, int flag, OutVariable<Double> dhead,
							OutVariable<Double> dflank, OutVariable<Double> dback);

	/**
	 * Calculates spread ROS in a specific direction (Theta) of the theoretical ellipse defined by ROS, FROS, BROS. 
	 * @param ROS	Equilibrium rate of spread (metres per minute).
	 * @param FROS	Equilibrium flank rate of spread (metres per minute).
	 * @param BROS	Equilibrium back rate of spread (metres per minute).
	 * @param RAZ	Orientation for the ellipse
	 * @param Theta Direction of vector to calculate, out of the ellipse
	 * @param rosTheta	Calculated value, ROS based on vector defined by RAZ, Theta.
	 */
	public abstract void calculateROSTheta(double ROS, double FROS, double BROS, double RAZ, double Theta, OutVariable<Double> rosTheta);
	
	/**
	 * Calculates the value for ISF based on parameters passed in. Note that this method is used by mixed fuel types only and likely should not be called directly. Automatic caching of previously calculated values is performed for efficiency.
	 * @param RSF	Intermediate output for calculating ROS values.
	 * @param SF	Slope factor.
	 * @param ISZ	Dead wind ISI.
	 * @param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. 
	 * @return	the calculated ISF value 
	 * @throws CloneNotSupportedException 
	 */
	public abstract double isf(double RSF, double SF, double ISZ, short flag);
	
	/**
	 * Calculates the SFC (surface fuel consumption) value based on several parameters. Note that this routine may seem redundant to CalculateFCValues() but is used by mixed fuel types. Typically, the CalculateFCValues() method should be called. Automatic caching of previously calculated values is performed for efficiency. 
	 * @param FFMC	Fine fuel moister code (FWI output)
	 * @param BUI	Buildup index (FWI output)
	 * @param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h
	 * @return	the calculated SFC value
	 * @throws CloneNotSupportedException 
	 */
	public abstract double sfc(double FFMC, double BUI, short flag);
	
	/**
	 * Calculates RSI (initial rate of spread) without BUI effect. Note that this routine may seem redundant to CalculateROSValues()  but is used by mixed fuel types. Typically CalculateROSValues) should be called. Automatic caching of previously calculated values is performed for efficiency. 
	 * @param FFMC	Fine fuel moister code (FWI output)
	 * @param BUI	Buildup index (FWI output)
	 * @param FMC	Foliar moisture code (FBP output) (0-1)
	 * @param ISI	Initial spread index (FWI output).  Note that the FBP version of the ISI calculation (in the FWI module) should be used.
	 * @param flag	A combination of
	 * 		<ul>
	 * 		<li><code>CWFGM_SCENARIO_OPTION_ACCEL</code>  Boolean.  If TRUE, then acceleration is applied to various output statistics in the FBP standard.  This value should only applicable to point ignitions.  If FALSE, then the fire is assumed to be always at equilibrium.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_BUI</code>  Boolean.  If TRUE, then the BUI build-up effect is applied to various statistics in the FBP standard.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_TOPOGRAPHY</code>  Boolean.  If TRUE, then the slope component to calculating the WSV output statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.  This setting also affects the slope component in Dr. Richards' 3D equations.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_GREENUP</code>  Boolean.  Specific FBP fuel types use different equations during green-up.  This flag determines whether to use green-up equations or not.
	 * 		<li><code>CWFGM_SCENARIO_OPTION_WIND</code>  Boolean.  If FALSE, then the wind component to calculating the WSV statistic in the FBP standard is set to 0.0.  If TRUE, then the wind speed is used as provided.
	 * 		</ul>
	 * 		bit flags, defined in FireEngine_Ext.h. For consistency of outputs, these flags should match those provided to determine the ROS value.
	 * @return Returned calculated RSI
	 * @throws CloneNotSupportedException 
	 */
	public abstract double rsi(double FFMC, double BUI, double FMC, double ISI, short flag);
	
	/**
 	 * Calculates flame length.  Note that this routine is not part of the FBP standard.
	 * @param height Tree height
	 * @param CFB	Crown Fraction Burned
	 * @param FI	Fire Intensity
	 * @return	Returned Flame Length
	 */
	public abstract double flameLength(double height, double CFB, double FI);
	
	/**
	 * Calculates DBH (diameter at breast height, measured at 1.3m above the ground).  Note that this routine is not part of the FBP standard.
	 * @param height Tree height
	 * @return	Returned Diameter at Breast Height (DBH)
	 */
	public abstract double dbh(double height);
	
	/**			
 	 * Reports whether the fuel type is C-1, C-2, C-3, C-4, C-5, C-6, or C-7. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isConiferFuelType();
	
	/**			
	 * Reports whether the fuel type is D-1 or D-2. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isDeciduousFuelType();
	
	/**
	 * Reports whether the fuel type is M-1 or M-2. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isMixedFuelType();
	
	/**
	 * Reports whether the fuel type is S-1, S-2, or S-3. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isSlashFuelType();
	
	/**			
	 * Reports whether the fuel type is O-1a or O-1b. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isGrassFuelType();
	
	/**
	 * Reports whether the fuel type is C-6. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isC6FuelType();

	/**			
	 * Reports whether the fuel type is M-3 or M-4. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isMixedDeadFir();
	
	/**
	 * Reports whether the fuel type is a non-fuel. This fuel type information is retained after cloning a read-only template into a read/write fuel type. This information will become invalid once an equation in the read/write fuel has been replaced. 
	 * @return result of the test
	 */
	public abstract boolean isNonFuel();
	public abstract Class<? extends CwfgmFuel> getDefaultClassID();
	
	/**
	 * Polymorphic.  Gets a particular attribute for a fuel. Each fuel type comprises of a variety of equations and values. This function allows the client application to retrieve most any value that would define some aspect of the calculations for this fuel type. 
	 * @param attributeKey	This parameter identifies which attribute value to retrieve.
	 * @return The value of the attribute being requested.
	 */
	public abstract Object getAttribute(short attributeKey);
	
	/**
	 * Sets a particular attribute for a fuel. This method can be used to modify some generic value associated with the fuel, or most any coefficient of specific equations used to calculated values for the fuel. 
	 * @param attributeKey	This parameter identifies which attribute value to retrieve.
	 * @param attribute	The value of the attribute being requested.
	 */
	public abstract void setAttribute(int attributeKey, Object attribute);

	/**
	 * This property is unused by the fuel object, and is available for exclusive use by the client code.  It is an object to ensure
	 * that the client code can store a pointer value (if it chooses) for use in manual subclassing this object.  This value is not loaded or
	 * saved during serialization operations, and it is the responsibility of the client code to manage any value or object stored here.
	 * Access to this property is not thread-safe.
	 * @return The address provided for pVal is invalid
	 */
	public Object getUserData() {
		return m_userData;
	}

	/**
	 * This property is unused by the fuel object, and is available for exclusive use by the client code.  It is an object to ensure
	 * that the client code can store a pointer value (if it chooses) for use in manual subclassing this object.  This value is not loaded or
	 * saved during serialization operations, and it is the responsibility of the client code to manage any value or object stored here.
	 * Access to this property is not thread-safe.
	 * @param newVal when setting the property
	 */
	public void setUserData(Object newVal) {
		m_userData = newVal;
	}

	public static final short FUELCOM_SUCCESS_NO_CHANGE						= 15450;
}


