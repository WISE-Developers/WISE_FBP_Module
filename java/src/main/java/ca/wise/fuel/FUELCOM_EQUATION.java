/***********************************************************************
 * REDapp - FUELCOM_EQUATION.java
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

package ca.wise.fuel;

import static ca.wise.fuel.FUELCOM_ATTRIBUTE.GREENUP_MODIFIER;

public abstract class FUELCOM_EQUATION {
	public static final int FMC							= 18250;
	public static final int SFC							= 18251;
	public static final int SFC_GREENUP					= (SFC | GREENUP_MODIFIER);
	public static final int TFC							= 18252;
	public static final int TFC_GREENUP					= (TFC | GREENUP_MODIFIER);
	public static final int RSI							= 18253;
	public static final int RSI_GREENUP					= (RSI | GREENUP_MODIFIER);
	public static final int ISF							= 18254;
	public static final int ISF_GREENUP					= (ISF | GREENUP_MODIFIER);
	public static final int CFB							= 18255;
	public static final int CFB_GREENUP					= (CFB | GREENUP_MODIFIER);
	public static final int ACCEL			= 18256;
	public static final int LB				= 18257;
	public static final int DBH			= 18258;
	public static final int FLAMELENGTH	= 18259;
	public static final int SPREADPARMS	= 18260;

	public static final int SELECTION_FMC_CALC	= 18300;
	public static final int SELECTION_FMC_NOCALC	= 18301;

	public static final int SELECTION_SFC_C1	= 18310;
	public static final int SELECTION_SFC_C2	= 18311;
	public static final int SELECTION_SFC_C7	= 18312;
	public static final int SELECTION_SFC_D2	= 18313;
	public static final int SELECTION_SFC_M1	= 18314;
	public static final int SELECTION_SFC_O1	= 18315;
	public static final int SELECTION_SFC_S1	= 18316;

	public static final int SELECTION_TFC_C1	= 18330;
	public static final int SELECTION_TFC_D2	= 18331;
	public static final int SELECTION_TFC_M1	= 18332;
	public static final int SELECTION_TFC_O1	= 18333;

	public static final int SELECTION_RSI_C1	= 18350;
	public static final int SELECTION_RSI_C6	= 18351;
	public static final int SELECTION_RSI_D2	= 18352;
	public static final int SELECTION_RSI_M1	= 18353;
	public static final int SELECTION_RSI_M3	= 18354;
	public static final int SELECTION_RSI_M4	= 18355;
	public static final int SELECTION_RSI_O1	= 18356;
	public static final int SELECTION_RSI_CONSTANT	= 18357;

	public static final int SELECTION_ISF_C1	= 18370;
	public static final int SELECTION_ISF_M1	= 18371;
	public static final int SELECTION_ISF_M3M4	= 18372;
	public static final int SELECTION_ISF_O1	= 18373;

	public static final int SELECTION_CFB_C1	= 18390;
	public static final int SELECTION_CFB_D2	= 18391;

	public static final int SELECTION_ACCEL_CLOSED	= 18410;
	public static final int SELECTION_ACCEL_OPEN	= 18411;

	public static final int SELECTION_LB_C1	= 18420;
	public static final int SELECTION_LB_O1	= 18421;

	public static final int SELECTION_DBH_1	= 18430;
	public static final int SELECTION_DBH_2	= 18431;
	public static final int SELECTION_DBH_3	= 18432;
	public static final int SELECTION_DBH_4	= 18433;
	public static final int SELECTION_DBH_NONE	= 18434;

	public static final int SELECTION_FLAMELENGTH_TREE				= 18450;
	public static final int SELECTION_FLAMELENGTH_OTHER			= 18451;
	public static final int SELECTION_FLAMELENGTH_ALEXANDER82		= 18452;
	public static final int SELECTION_FLAMELENGTH_ALEXANDER82_TREE	= 18453;

	public static final int SELECTION_SPREADPARMS_S1			= 18460;
	public static final int SELECTION_SPREADPARMS_C1			= 18461;
	public static final int SELECTION_SPREADPARMS_C6			= 18462;
	public static final int SELECTION_SPREADPARMS_D1			= 18463;
	public static final int SELECTION_SPREADPARMS_O1			= 18464;
	public static final int SELECTION_SPREADPARMS_O1AB			= 18465;
	public static final int SELECTION_SPREADPARMS_MIXED		= 18466;
	public static final int SELECTION_SPREADPARMS_MIXEDDEAD	= 18467;
	public static final int SELECTION_SPREADPARMS_NON			= 18468;
	public static final int SELECTION_SPREADPARMS_NZ			= 18469;
}
