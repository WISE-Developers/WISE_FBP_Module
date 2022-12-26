/***********************************************************************
 * REDapp - FUELCOM_ATTRIBUTE.java
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

public abstract class FUELCOM_ATTRIBUTE {
	
	public static final int GREENUP_MODIFIER		= 32768;

	public static final int SPREAD_START			= 15500;
	public static final int SPREADPARMS_C1_DEFAULTS	= 15500;
	public static final int SPREADPARMS_C2_DEFAULTS	= 15501;
	public static final int SPREADPARMS_C3_DEFAULTS	= 15502;
	public static final int SPREADPARMS_C4_DEFAULTS	= 15503;
	public static final int SPREADPARMS_C5_DEFAULTS	= 15504;
	public static final int SPREADPARMS_C6_DEFAULTS	= 15505;
	public static final int SPREADPARMS_C7_DEFAULTS	= 15506;
	public static final int SPREADPARMS_D1_DEFAULTS	= 15507;
	public static final int SPREADPARMS_D2_DEFAULTS	= 15508;
	public static final int SPREADPARMS_M1_DEFAULTS	= 15509;
	public static final int SPREADPARMS_M2_DEFAULTS	= 15510;
	public static final int SPREADPARMS_M3_DEFAULTS	= 15511;
	public static final int SPREADPARMS_M4_DEFAULTS	= 15512;
	public static final int SPREADPARMS_O1A_DEFAULTS	= 15513;
	public static final int SPREADPARMS_O1B_DEFAULTS	= 15514;
	public static final int SPREADPARMS_O1AB_DEFAULTS	= 15515;
	public static final int SPREADPARMS_S1_DEFAULTS	= 15516;
	public static final int SPREADPARMS_S2_DEFAULTS	= 15517;
	public static final int SPREADPARMS_S3_DEFAULTS	= 15518;
	public static final int SPREADPARMS_NON_DEFAULTS	= 15519;
	public static final int SPREADPARMS_NZ2_DEFAULTS	= 15520;
	public static final int SPREADPARMS_NZ15_DEFAULTS	= 15521;
	public static final int SPREADPARMS_NZ30_DEFAULTS = 15522;
	public static final int SPREADPARMS_NZ31_DEFAULTS = 15523;
	public static final int SPREADPARMS_NZ32_DEFAULTS = 15524;
	public static final int SPREADPARMS_NZ33_DEFAULTS = 15525;
	public static final int SPREADPARMS_NZ40_DEFAULTS = 15526;
	public static final int SPREADPARMS_NZ41_DEFAULTS = 15527;
	public static final int SPREADPARMS_NZ43_DEFAULTS = 15528;
	public static final int SPREADPARMS_NZ44_DEFAULTS = 15529;
	public static final int SPREADPARMS_NZ45_DEFAULTS = 15530;
	public static final int SPREADPARMS_NZ46_DEFAULTS = 15531;
	public static final int SPREADPARMS_NZ47_DEFAULTS = 15532;
	public static final int SPREADPARMS_NZ50_DEFAULTS = 15533;
	public static final int SPREADPARMS_NZ51_DEFAULTS = 15534;
	public static final int SPREADPARMS_NZ52_DEFAULTS = 15535;
	public static final int SPREADPARMS_NZ53_DEFAULTS = 15536;
	public static final int SPREADPARMS_NZ54_DEFAULTS = 15537;
	public static final int SPREADPARMS_NZ55_DEFAULTS = 15538;
	public static final int SPREADPARMS_NZ56_DEFAULTS = 15539;
	public static final int SPREADPARMS_NZ57_DEFAULTS = 15540;
	public static final int SPREADPARMS_NZ58_DEFAULTS = 15541;
	public static final int SPREADPARMS_NZ60_DEFAULTS = 15542;
	public static final int SPREADPARMS_NZ61_DEFAULTS = 15543;
	public static final int SPREADPARMS_NZ62_DEFAULTS = 15544;
	public static final int SPREADPARMS_NZ63_DEFAULTS = 15545;
	public static final int SPREADPARMS_NZ64_DEFAULTS = 15546;
	public static final int SPREADPARMS_NZ65_DEFAULTS = 15547;
	public static final int SPREADPARMS_NZ66_DEFAULTS = 15548;
	public static final int SPREADPARMS_NZ67_DEFAULTS = 15549;
	public static final int SPREADPARMS_NZ68_DEFAULTS = 15550;
	public static final int SPREADPARMS_NZ69_DEFAULTS = 15551;
	public static final int SPREADPARMS_NZ70_DEFAULTS = 15551;
	public static final int SPREADPARMS_NZ71_DEFAULTS = 15553;

	public static final int A							= 15600;
	public static final int B							= 15601;
	public static final int C							= 15602;
	public static final int Q							= 15603;
	public static final int MAXBE						= 15604;
	public static final int BUI0						= 15605;
	public static final int CBH						= 15606;
	public static final int CFL						= 15607;
	public static final int TREE_HEIGHT				= 15608;
	public static final int PC						= 15609;
	public static final int PDF						= 15610;
	public static final int CURINGDEGREE				= 15611;
	public static final int M3M4_C2_A					= 15612;
	public static final int M3M4_C2_B					= 15613;
	public static final int M3M4_C2_C					= 15614;
	public static final int M4_D1_A					= 15615;
	public static final int M4_D1_B					= 15616;
	public static final int M4_D1_C					= 15617;
	public static final int EQ35_THRESHOLD			= 15618;
	public static final int EQ35A_MULT1				= 15619;
	public static final int EQ35A_MULT2				= 15620;
	public static final int EQ35B_ADDER				= 15621;
	public static final int EQ35B_MULT1				= 15622;
	public static final int FUELLOAD					= 15623;
	public static final int O1AB_MATTED_A				= 15624;
	public static final int O1AB_MATTED_B				= 15625;
	public static final int O1AB_MATTED_C				= 15626;
	public static final int O1AB_STANDING_A			= 15627;
	public static final int O1AB_STANDING_B			= 15628;
	public static final int O1AB_STANDING_C			= 15629;

	public static final int SPREAD_END				= 15699;


	public static final int RSI_START					= 15700;
	public static final int RSI_C6_DEFAULTS			= 15700; // can't use GetAttributeValue() on these Defaults settings
	public static final int RSI_D2_DEFAULTS			= 15701;
	public static final int RSI_M3_DEFAULTS			= 15702;
	public static final int RSI_M4_DEFAULTS			= 15703;
	public static final int RSI_O1_DEFAULTS			= 15704;
	public static final int RSI_NZ70_DEFAULTS			= 15705;

	public static final int RSI_CONSTANT_RSI			= 15800;
	public static final int ROS_EQ61_MULT1			= 15801;
	public static final int ROS_EQ61_MULT2			= 15802;
	public static final int ROS_EQ61_MULT3			= 15803;
	public static final int ROS_EQ61_ADDER1			= 15804;
	public static final int ROS_EQ61_ADDER2			= 15805;
	public static final int ROS_EQ61_POWER			= 15806;
	public static final int ROS_EQ64_MULT1			= 15807;
	public static final int ROS_EQ64_MULT2			= 15808;
	public static final int ROS_EQ64_FMEAVG			= 15809;
	public static final int RSI_D2_THRESHOLD			= 15810;
	public static final int RSI_D2_SCALE1				= 15811;
	public static final int RSI_D2_SCALE2				= 15812;
	public static final int RSI_MIX_FACTOR			= 15813;

	public static final int RSI_END					= 15899;

	public static final int SFC_START					= 15900;
	public static final int SFC_C1_DEFAULTS			= 15900;// can't use GetAttributeValue() on these Defaults settings
	public static final int SFC_C2_DEFAULTS			= 15901;
	public static final int SFC_C3_DEFAULTS			= 15902;
	public static final int SFC_C4_DEFAULTS			= 15903;
	public static final int SFC_C5_DEFAULTS			= 15904;
	public static final int SFC_C6_DEFAULTS			= 15905;
	public static final int SFC_C7_DEFAULTS			= 15906;
	public static final int SFC_D1_DEFAULTS			= 15907;
	public static final int SFC_D2_DEFAULTS			= 15908;
	public static final int SFC_M3_DEFAULTS			= 15909;
	public static final int SFC_M4_DEFAULTS			= 15910;
	public static final int SFC_O1A_DEFAULTS			= 15911;
	public static final int SFC_O1B_DEFAULTS			= 15912;
	public static final int SFC_S1_DEFAULTS			= 15913;
	public static final int SFC_S2_DEFAULTS			= 15914;
	public static final int SFC_S3_DEFAULTS			= 15915;
	public static final int SFC_NZ2_DEFAULTS			= 15916;
	public static final int SFC_NZ15_DEFAULTS			= 15917;
	public static final int SFC_NZ30_DEFAULTS			= 15918;
	public static final int SFC_NZ31_DEFAULTS			= 15919;
	public static final int SFC_NZ32_DEFAULTS			= 15920;
	public static final int SFC_NZ33_DEFAULTS			= 15921;
	public static final int SFC_NZ40_DEFAULTS			= 15922;
	public static final int SFC_NZ41_DEFAULTS			= 15923;
	public static final int SFC_NZ43_DEFAULTS			= 15924;
	public static final int SFC_NZ44_DEFAULTS			= 15925;
	public static final int SFC_NZ45_DEFAULTS			= 15926;
	public static final int SFC_NZ46_DEFAULTS			= 15927;
	public static final int SFC_NZ47_DEFAULTS			= 15928;
	public static final int SFC_NZ50_DEFAULTS			= 15929;
	public static final int SFC_NZ51_DEFAULTS			= 15930;
	public static final int SFC_NZ52_DEFAULTS			= 15931;
	public static final int SFC_NZ53_DEFAULTS			= 15932;
	public static final int SFC_NZ54_DEFAULTS			= 15933;
	public static final int SFC_NZ55_DEFAULTS			= 15934;
	public static final int SFC_NZ56_DEFAULTS			= 15935;
	public static final int SFC_NZ57_DEFAULTS			= 15936;
	public static final int SFC_NZ58_DEFAULTS			= 15937;
	public static final int SFC_NZ60_DEFAULTS			= 15938;
	public static final int SFC_NZ61_DEFAULTS			= 15939;
	public static final int SFC_NZ62_DEFAULTS			= 15940;
	public static final int SFC_NZ63_DEFAULTS			= 15941;
	public static final int SFC_NZ64_DEFAULTS			= 15942;
	public static final int SFC_NZ65_DEFAULTS			= 15943;
	public static final int SFC_NZ66_DEFAULTS			= 15944;
	public static final int SFC_NZ67_DEFAULTS			= 15945;
	public static final int SFC_NZ68_DEFAULTS			= 15946;
	public static final int SFC_NZ69_DEFAULTS			= 15947;
	public static final int SFC_NZ70_DEFAULTS			= 15948;
	public static final int SFC_NZ71_DEFAULTS			= 15949;

	public static final int SFC_C1_CLR_DEFAULTS		= 15951;

	public static final int SFC_MULTIPLIER			= 16000;
	public static final int FFC_MULTIPLIER			= 16001;
	public static final int WFC_MULTIPLIER			= 16002;
	public static final int FFC_BUI_MULTIPLIER		= 16003;
	public static final int WFC_BUI_MULTIPLIER		= 16004;
	public static final int SFC_EQ9_ADDER				= 16005;
	public static final int SFC_EQ9_MULT1				= 16006;
	public static final int SFC_EQ9_MULT2				= 16007;
	public static final int SFC_EQ9_FFMC_THRESHOLD	= 16008;
	public static final int SFC_EQ10_MULT1			= 16009;
	public static final int SFC_EQ10_ADDER			= 16010;
	public static final int SFC_EQ10_POWER			= 16011;
	public static final int SFC_EQ13_MULT1			= 16012;
	public static final int SFC_EQ13_MULT2			= 16013;
	public static final int SFC_EQ13_ADDER			= 16014;
	public static final int SFC_EQ14_MULT1			= 16015;
	public static final int SFC_EQ14_MULT2			= 16016;
	public static final int SFC_D2_THRESHOLD			= 16017;
	public static final int SFC_D2_SCALE1				= 16018;
	public static final int SFC_D2_SCALE2				= 16019;
	public static final int SFC_EQ19_MULT1			= 16020;
	public static final int SFC_EQ19_MULT2			= 16021;
	public static final int SFC_EQ20_MULT1			= 16022;
	public static final int SFC_EQ20_MULT2			= 16023;
	public static final int GFL						= 16024;
	public static final int SFC_END					= 16099;

	public static final int LB_START					= 16100;
	public static final int LB_C1_DEFAULTS			= 16100;// can't use GetAttributeValue() on these Defaults settings
	public static final int LB_C2_DEFAULTS			= 16101;
	public static final int LB_C3_DEFAULTS			= 16102;
	public static final int LB_C4_DEFAULTS			= 16103;
	public static final int LB_C5_DEFAULTS			= 16104;
	public static final int LB_C6_DEFAULTS			= 16105;
	public static final int LB_C7_DEFAULTS			= 16106;
	public static final int LB_D1_DEFAULTS			= 16107;
	public static final int LB_D2_DEFAULTS			= 16108;
	public static final int LB_M1_DEFAULTS			= 16109;
	public static final int LB_M2_DEFAULTS			= 16110;
	public static final int LB_M3_DEFAULTS			= 16111;
	public static final int LB_M4_DEFAULTS			= 16112;
	public static final int LB_O1A_DEFAULTS			= 16113;
	public static final int LB_O1B_DEFAULTS			= 16114;
	public static final int LB_S1_DEFAULTS			= 16115;
	public static final int LB_S2_DEFAULTS			= 16116;
	public static final int LB_S3_DEFAULTS			= 16117;

	public static final int LB_INIT					= 16200;
	public static final int LB_MULTIPLIER				= 16201;
	public static final int LB_EXP_MULTIPLIER			= 16202;
	public static final int LB_POWER					= 16203;
	public static final int LB_END					= 16299;

	public static final int ISF_START					= 16300;
	public static final int ISF_O1A_DEFAULTS			= 16300;
	public static final int ISF_O1B_DEFAULTS			= 16301;
	public static final int ISF_END					= 16399;

	public static final int CFB_START					= 16400;
	public static final int CFB_C1_DEFAULTS			= 16400;// can't use GetAttributeValue() on these Defaults settings
	public static final int CFB_C2_DEFAULTS			= 16401;
	public static final int CFB_C3_DEFAULTS			= 16402;
	public static final int CFB_C4_DEFAULTS			= 16403;
	public static final int CFB_C5_DEFAULTS			= 16404;
	public static final int CFB_C6_DEFAULTS			= 16405;
	public static final int CFB_C7_DEFAULTS			= 16406;
	public static final int CFB_D1_DEFAULTS			= 16407;
	public static final int CFB_M1_DEFAULTS			= 16408;
	public static final int CFB_M2_DEFAULTS			= 16409;
	public static final int CFB_M3_DEFAULTS			= 16410;
	public static final int CFB_M4_DEFAULTS			= 16411;
	public static final int CFB_O1A_DEFAULTS			= 16412;
	public static final int CFB_O1B_DEFAULTS			= 16413;
	public static final int CFB_S1_DEFAULTS			= 16414;
	public static final int CFB_S2_DEFAULTS			= 16415;
	public static final int CFB_S3_DEFAULTS			= 16416;
	public static final int CFB_NON_DEFAULTS			= 16417;

	public static final int CFB_CSI_MULTIPLIER		= 16500;
	public static final int CFB_CBH_EXPONENT			= 16501;
	public static final int CFB_EXP_ADDER				= 16502;
	public static final int CFB_EXP_MULTIPLIER		= 16503;
	public static final int CFB_CSI_POWER				= 16504;
	public static final int CFB_RSO_DIV				= 16505;
	public static final int CFB_EXP					= 16506;
	public static final int CFB_POSSIBLE				= 16507;
	public static final int CFB_END					= 16599;

	public static final int ACCEL_START				= 16600;
	public static final int ACCEL_C1_DEFAULTS			= 16601;	// can't use GetAttributeValue() on these Defaults settings
	public static final int ACCEL_C2_DEFAULTS			= 16602;
	public static final int ACCEL_C3_DEFAULTS			= 16603;
	public static final int ACCEL_C4_DEFAULTS			= 16604;
	public static final int ACCEL_C5_DEFAULTS			= 16605;
	public static final int ACCEL_C6_DEFAULTS			= 16606;
	public static final int ACCEL_C7_DEFAULTS			= 16607;
	public static final int ACCEL_D1_DEFAULTS			= 16608;
	public static final int ACCEL_D2_DEFAULTS			= 16609;
	public static final int ACCEL_M1_DEFAULTS			= 16610;
	public static final int ACCEL_M2_DEFAULTS			= 16611;
	public static final int ACCEL_M3_DEFAULTS			= 16612;
	public static final int ACCEL_M4_DEFAULTS			= 16613;
	public static final int ACCEL_O1A_DEFAULTS		= 16614;
	public static final int ACCEL_O1B_DEFAULTS		= 16615;
	public static final int ACCEL_S1_DEFAULTS			= 16616;
	public static final int ACCEL_S2_DEFAULTS			= 16617;
	public static final int ACCEL_S3_DEFAULTS			= 16618;

	public static final int ACCEL_INIT				= 16700;
	public static final int ACCEL_MULTIPLIER			= 16701;
	public static final int ACCEL_POWER				= 16702;
	public static final int ACCEL_EXP_MULTIPLIER		= 16703;
	public static final int ACCEL_END					= 16799;

	public static final int FMC_START					= 16800;
	public static final int FMC_DAY0					= 16801;
	public static final int FMC_END					= 16899;

	public static final int HUANG_DBH_START			= 16900;
	public static final int HUANG_DBH_B1				= 16901;
	public static final int HUANG_DBH_B2				= 16902;
	public static final int HUANG_DBH_B3				= 16903;

	public static final int HUANG_DBH_C1_DEFAULTS		= 17000;
	public static final int HUANG_DBH_C2_DEFAULTS		= 17001;
	public static final int HUANG_DBH_C3_DEFAULTS		= 17002;
	public static final int HUANG_DBH_C4_DEFAULTS		= 17003;
	public static final int HUANG_DBH_C5_DEFAULTS		= 17004;
	public static final int HUANG_DBH_C6_DEFAULTS		= 17005;
	public static final int HUANG_DBH_C7_DEFAULTS		= 17006;
	public static final int HUANG_DBH_D1_DEFAULTS		= 17007;
	public static final int HUANG_DBH_D2_DEFAULTS		= 17008;
	public static final int HUANG_DBH_M1_DEFAULTS		= 17009;
	public static final int HUANG_DBH_M2_DEFAULTS		= 17010;
	public static final int HUANG_DBH_M3_DEFAULTS		= 17011;
	public static final int HUANG_DBH_M4_DEFAULTS		= 17012;
	public static final int HUANG_DBH_END				= 17099;

	public static final int FLAMELENGTH_START				= 17100;
	public static final int FLAMELENGTH_TREE_DEFAULTS		= 17100;
	public static final int FLAMELENGTH_OTHER_DEFAULTS	= 17101;

	public static final int FLAMELENGTH_TREE_P1			= 17200;
	public static final int FLAMELENGTH_TREE_P2			= 17201;
	public static final int FLAMELENGTH_TREE_TH_FACTOR	= 17202;
	public static final int FLAMELENGTH_TREE_CFB_THRESHOLD = 17203;
	public static final int FLAMELENGTH_OTHER_P1			= 17204;
	public static final int FLAMELENGTH_END				= 17299;
}