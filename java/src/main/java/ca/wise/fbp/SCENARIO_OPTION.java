/***********************************************************************
 * REDapp - SCENARIO_OPTION.java
 * Copyright (C) 2015-2019 The REDapp Development Team
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

package ca.wise.fbp;

/**
 * Defines to set and get different settings for a scenario
 */
public abstract class SCENARIO_OPTION {
    public static final int ACCEL							= 1;
    public static final int BUI								= 2;
    /**
     * Used for whether to apply slope calculations in FBP calc's
     */
    public static final int TOPOGRAPHY						= 3;
    public static final int GREENUP							= 4;
    /**
     * Used for whether to use standing vs. matted grass
     */
    public static final int GRASSPHENOLOGY					= 0;
    /**
     * Used only for whether or not to apply elevation to calculation of FMC
     */
    public static final int FMC_TERRAIN						= 6;
    public static final int PERIMETER_RESOLUTION			= 27;
    public static final int SPATIAL_THRESHOLD				= 40;
    /**
     * Scenario-specific provided value for FMC to use in the scenarios (means never calculating FMC as per the FBP standard)
     */
    public static final int SPECIFIED_FMC					= 41;
    /**
     * Scenario-specific elevation to use when we have to calculate FMC, but the elevation grid either doesn't exist or has
     * NODATA where we are asked for it
     */
    public static final int DEFAULT_ELEVATION				= 42;
    public static final int WIND							= 10;
    public static final int SINGLETHREADING					= 11;
    public static final int EXTINGUISHMENT					= 12;
    /**
     * Used to select the 2-d elliptical growth model (default 3-d)
     */
    public static final int USE_2DGROWTH					= 13;
    /**
     * Stop when hitting boundary.
     */
    public static final int BOUNDARY_STOP					= 14;
    public static final int MULTITHREADING					= 49;
    /**
     * 0.0 means no smoothing, 1.0 means complete smoothing, 0.5 is default
     */
    public static final int SMOOTHING_WEIGHT				= 16;
    public static final int SPOTTING						= 8;
    public static final int BREACHING						= 9;
    public static final int START_TIME						= 44;
    public static final int END_TIME						= 45;
    public static final int CURRENT_TIME					= 46;
    public static final int TEMPORAL_THRESHOLD				= 47;
    public static final int TEMPORAL_THRESHOLD_ACCEL		= 51;
    public static final int DISPLAY_INTERVAL				= 48;
    public static final int STARTING_POINTS					= 50;
    public static final int IGNITION_SIZE					= 43;
    public static final int NONFUELS_AS_VECTOR_BREAKS		= 15;
    public static final int WEATHER_INTERPOLATE_TEMPORAL 	= 17;
    public static final int WEATHER_INTERPOLATE_SPATIAL 	= 18;
    /**
     * This is by default ON now (and really only BurnP3 could turn this off) - and this specifies to
     * calculate lat, lon from the vertex (x, y) location instead of just the grid's lower left-hand corner
     */
    public static final int ACCURATE_FMC_LOCATION			= 19;
    public static final int PURGE_HIDDEN_STEPS				= 20;
    /**
     * Whether to apply voronoi regions to weather stations to determine local data
     */
    public static final int WEATHER_INTERPOLATE_PRECIP 		= 21;
    /**
     * Whether to apply voronoi regions to weather stations to determine wind data
     */
    public static final int WEATHER_INTERPOLATE_WIND		= 22;
    /**
     * Whether to apply spatial calc's to FWI (TRUE) or simply apply IDW to FWI values
     */
    public static final int WEATHER_INTERPOLATE_CALCFWI 	= 24;
    /**
     * Whether to apply cumulative effects of weather patches, etc. to FWI values (only valid with
     * WEATHER_INTERPOLATE_SPATIAL on)
     */
    public static final int WEATHER_INTERPOLATE_HISTORY 	= 23;
    /**
     * Consistent with GETEVENTTIME_QUERY_PRIMARY_WX_STREAM
     */
    public static final int WEATHER_QUERY_PRIMARY_STREAM 	= 25;
    /**
     * Consistent with GETEVENTTIME_QUERY_ANY_WX_STREAM
     */
    public static final int WEATHER_QUERY_ANY_STREAM		= 26;
    /**
     * Whether to use the simulation (std) or interactive (alternate) cache for spatial interp. calc's
     */
    public static final int WEATHER_ALTERNATE_CACHE			= 31;
    
    public static final int EXPORTRULE_TEXTPROPERTY			= 22000;
    public static final int EXPORTRULE_STATPROPERTY			= 22001;
}
