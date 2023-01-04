/***********************************************************************
 * REDapp - FBP_Fuel.java
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

import ca.wise.fwi.Fwi;
import ca.wise.serialize.ISerializeProto;
import ca.hss.annotations.Source;
import ca.hss.general.OutVariable;
import ca.hss.times.WTime;

import static java.lang.Math.*;

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.wise.fuel.proto.*;

import static ca.wise.fbp.SCENARIO_OPTION.*;
import static ca.hss.math.General.*;

/**
 * @author rbryce
 *
 */
@Source(project = "FuelCOM", sourceFile = "FBPFuel.h")
public final class FBP_Fuel implements ISerializeProto<FBP_Fuel> {
	public static final long IID_ICWFGM_FBPFuel = 0x56E481B1;

	public double	m_max_isf;
	public SpreadParmsAttribute m_spread;
	public CwfgmFuel m_C2;
	public CwfgmFuel m_D1;
	public String m_loadWarning;

	public Class<? extends CwfgmFBPFuel> m_defaultFuelType;

	public double m_pc;		// the percentage ( 0-1 ) of c2 (can also be m_pdf for dead fir for M3/M4/M3M4 fueltypes)

	// the following variable are used only if the species is o1a or o1b
	// m_fuelType == FUEL_TYPE_O1 if and only if this are valid.
	public double m_curingDegree; // degree of curing ( 0-1 )

	public FMCAttribute m_FMCCalculation;
	public SFCAttribute m_SFCCalculation, m_SFCCalculation_Greenup; // my sfc calculation Engine
	public TFCAttribute m_TFCCalculation, m_TFCCalculation_Greenup; // my tfc calculation Engine
	public RSIAttribute m_RSICalculation, m_RSICalculation_Greenup; // my rate of spread calculation Engine
	public ISFAttribute m_ISFCalculation, m_ISFCalculation_Greenup;
	public AccAlphaAttribute m_AccAlphaCalculation;
	public LBAttribute  m_LBCalculation;
	public CFBAttribute m_CFBCalculation, m_CFBCalculation_Greenup;
	public FlameLengthAttribute m_FLCalculation;

	public CwfgmAccelAttribute m_AccelCustom;
	public CwfgmFMCAttribute m_FMCCustom;
	public CwfgmSFCAttribute m_SFCCustom;
	public CwfgmTFCAttribute m_TFCCustom;
	public CwfgmCFBAttribute m_CFBCustom;
	public CwfgmRSIAttribute m_RSICustom;
	public CwfgmISFAttribute m_ISFCustom;
	public CwfgmLBAttribute m_LBCustom;

	protected boolean m_fuelTypeModified;

	protected int USE_ACCELERATION	= ((int)(1 << ACCEL));
	protected int USE_BUI				= ((int)(1 << BUI));
	protected int USE_SLOPE			= ((int)(1 << TOPOGRAPHY));
	protected int USE_WIND			= ((int)(1 << WIND));
	protected int USE_GREENUP			= ((int)(1 << GREENUP));
	protected int FUELCOM_INPUT_MASK	= (int)(USE_ACCELERATION | USE_BUI | USE_SLOPE | USE_WIND | USE_GREENUP);	// for sane inputs
	protected int CALC_FOR_RSF		= ((int)0x4000);

	public FBP_Fuel() {
		m_fuelTypeModified = false;
		
		m_spread = null;
		m_FMCCalculation = null;
		m_SFCCalculation_Greenup = m_SFCCalculation = null;
		m_TFCCalculation_Greenup = m_TFCCalculation = null;
		m_RSICalculation_Greenup = m_RSICalculation = null;
		m_ISFCalculation_Greenup = m_ISFCalculation = null;
		m_AccAlphaCalculation = null;
		m_LBCalculation = null;
		m_CFBCalculation_Greenup = m_CFBCalculation = null;
		m_FLCalculation = null;

		m_AccelCustom = null;
		m_FMCCustom = null;
		m_SFCCustom = null;
		m_TFCCustom = null;
		m_CFBCustom = null;
		m_RSICustom = null;
		m_ISFCustom = null;
		m_LBCustom = null;
	}

	public FBP_Fuel(final FBP_Fuel other) {
		m_defaultFuelType = other.m_defaultFuelType;
		
		try {
			m_spread = (SpreadParmsAttribute) other.m_spread.clone();
			m_fuelTypeModified = other.m_fuelTypeModified;
		}
		catch (CloneNotSupportedException e) {
			throw new RuntimeException(e);//allow everything to crash
		}

		m_pc = other.m_pc;
		m_curingDegree = other.m_curingDegree;

		try {
			m_FMCCalculation = (other.m_FMCCalculation != null) ? (FMCAttribute)other.m_FMCCalculation.clone() : null;
			m_SFCCalculation_Greenup = (other.m_SFCCalculation_Greenup != null) ? (SFCAttribute)other.m_SFCCalculation_Greenup.clone() : null;
			m_SFCCalculation = (other.m_SFCCalculation != null) ? (SFCAttribute)other.m_SFCCalculation.clone() : null;
			m_TFCCalculation_Greenup = (other.m_TFCCalculation_Greenup != null) ? (TFCAttribute)other.m_TFCCalculation_Greenup.clone() : null;
			m_TFCCalculation = (other.m_TFCCalculation != null) ? (TFCAttribute)other.m_TFCCalculation.clone() : null;
			m_RSICalculation_Greenup = (other.m_RSICalculation_Greenup != null) ? (RSIAttribute)other.m_RSICalculation_Greenup.clone() : null;
			m_RSICalculation = (other.m_RSICalculation != null) ? (RSIAttribute)other.m_RSICalculation.clone() : null;
			m_ISFCalculation_Greenup = (other.m_ISFCalculation_Greenup != null) ? (ISFAttribute)other.m_ISFCalculation_Greenup.clone() : null;
			m_ISFCalculation = (other.m_ISFCalculation != null) ? (ISFAttribute)other.m_ISFCalculation.clone() : null;
			m_AccAlphaCalculation = (other.m_AccAlphaCalculation != null) ? (AccAlphaAttribute)other.m_AccAlphaCalculation.clone() : null;
			m_LBCalculation = (other.m_LBCalculation != null) ? (LBAttribute)other.m_LBCalculation.clone() : null;
			m_CFBCalculation_Greenup = (other.m_CFBCalculation_Greenup != null) ? (CFBAttribute)other.m_CFBCalculation_Greenup.clone() : null;
			m_CFBCalculation = (other.m_CFBCalculation != null) ? (CFBAttribute)other.m_CFBCalculation.clone() : null;
			m_FLCalculation = (other.m_FLCalculation != null) ? (FlameLengthAttribute)other.m_FLCalculation.clone() : null;
		}
		catch (CloneNotSupportedException e) {
			throw new RuntimeException(e);
		}
		m_AccelCustom = other.m_AccelCustom;
		m_FMCCustom = other.m_FMCCustom;
		m_SFCCustom = other.m_SFCCustom;
		m_TFCCustom = other.m_TFCCustom;
		m_CFBCustom = other.m_CFBCustom;
		m_RSICustom = other.m_RSICustom;
		m_ISFCustom = other.m_ISFCustom;
		m_LBCustom = other.m_LBCustom;
	}

	private static <T> boolean compare_c(T a, T b) {
		if ((a != null) && (b != null)) {
			if (a != b)
				if (!a.equals(b))
					return false;
		}
		if (a != b)
			return false;
		return true;
	}

	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof FBP_Fuel) {
			FBP_Fuel fuel = (FBP_Fuel)other;
			if (m_defaultFuelType != fuel.m_defaultFuelType)							return false;
	
			if (!m_spread.equals(fuel.m_spread))										return false;
			if (m_fuelTypeModified != fuel.m_fuelTypeModified)							return false;

			if (!compare_c(m_C2, fuel.m_C2))											return false;
			if (!compare_c(m_D1, fuel.m_D1))											return false;

			if (m_pc != fuel.m_pc)														return false;
			if (m_curingDegree != fuel.m_curingDegree)									return false;

			if (!compare_c(m_FMCCalculation, fuel.m_FMCCalculation))					return false;
			if (!compare_c(m_SFCCalculation_Greenup, fuel.m_SFCCalculation_Greenup))	return false;
			if (!compare_c(m_SFCCalculation, fuel.m_SFCCalculation))					return false;
			if (!compare_c(m_TFCCalculation_Greenup, fuel.m_TFCCalculation_Greenup))	return false;
			if (!compare_c(m_TFCCalculation, fuel.m_TFCCalculation))					return false;
			if (!compare_c(m_RSICalculation_Greenup, fuel.m_RSICalculation_Greenup))	return false;
			if (!compare_c(m_RSICalculation, fuel.m_RSICalculation))					return false;
			if (!compare_c(m_ISFCalculation_Greenup, fuel.m_ISFCalculation_Greenup))	return false;
			if (!compare_c(m_ISFCalculation, fuel.m_ISFCalculation))					return false;
			if (!compare_c(m_AccAlphaCalculation, fuel.m_AccAlphaCalculation))			return false;
			if (!compare_c(m_LBCalculation, fuel.m_LBCalculation))						return false;
			if (!compare_c(m_CFBCalculation_Greenup, fuel.m_CFBCalculation_Greenup))	return false;
			if (!compare_c(m_CFBCalculation, fuel.m_CFBCalculation))					return false;
			if (!compare_c(m_FLCalculation, fuel.m_FLCalculation))						return false;

			return true;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	public double sfc(double FFMC, double BUI, int flag) {
		if (!isMixed() && !isMixedDead())
		//if ((m_fuelType != FUEL_TYPE_MIXED) && (m_fuelType != FUEL_TYPE_MIXDEAD))	// do this check 'cause mixed fuel types don't used a, b, c
			if ((m_spread.a(flag) == 0.0) && (m_spread.b(flag) == 0.0) && (m_spread.c(flag) == 0.0))
				return 0.0;

		if(m_SFCCustom != null) {
			CwfgmFuel m_C2 = m_spread.c2();
			CwfgmFuel m_D1 = m_spread.d1();
			double m_pc = m_spread.pc();
			return m_SFCCustom.SFC( ((short)(flag & USE_GREENUP) != 0)? true : false, FFMC, BUI, m_C2, m_D1, m_pc);
		} else {
			if ((short)(flag & USE_GREENUP) == 0)
				return m_SFCCalculation.SFC(m_spread, flag, FFMC, BUI);
			else
				return m_SFCCalculation_Greenup.SFC(m_spread, flag, FFMC, BUI);
		}
	}

	public double tfc(double CFB, double SFC, int flag, OutVariable<Double> CFC) {		
		if(m_TFCCustom != null) {
			double m_pc = m_spread.pc();
			double m_cfl = m_spread.cfl();
			return m_TFCCustom.TFC( ((short)(flag & USE_GREENUP) != 0) ? true : false, m_cfl, CFB, SFC, m_pc, CFC);
		} else {
			if ((short)(flag & USE_GREENUP) == 0)
				return m_TFCCalculation.TFC(m_spread, flag, CFB, SFC, CFC);
			else
				return m_TFCCalculation_Greenup.TFC(m_spread,flag, CFB, SFC, CFC);
		}
	}

	public double isf(double RSF_C2, double RSF_D1, double SF, double ISZ, int flag) {
		if (m_ISFCustom != null) {
			CwfgmFuel m_C2, m_D1;
			m_C2 = m_spread.c2();
			m_D1 = m_spread.d1();
			double m_pc = m_spread.pc();
			double m_curingDegree = m_spread.curingDegree();
			return m_ISFCustom.ISF( ((short)(flag & USE_GREENUP) != 0) ? true : false , m_spread.a(flag), m_spread.b(flag), m_spread.c(flag), RSF_C2, RSF_D1, SF, ISZ, m_C2, m_D1, m_curingDegree, m_pc);
		} else {
			if ((short)(flag & USE_GREENUP) == 0)
				return m_ISFCalculation.ISF(m_spread, flag, RSF_C2, RSF_D1, SF, ISZ);
			else
				return m_ISFCalculation_Greenup.ISF(m_spread, flag, RSF_C2, RSF_D1, SF, ISZ);
		}
	}

	public double cfb(double FMC, double SFC, double RSS, double ROS, int flag, OutVariable<Double> rso, OutVariable<Double> csi) {
		double for_fros = 0.0;
		if (m_RSICustom != null) {
		}
		else {
			if ((short)(flag & USE_GREENUP) == 0)
				for_fros = m_RSICalculation.FOR_FROS(RSS, ROS, 0.0);
			else
				for_fros = m_RSICalculation_Greenup.FOR_FROS(RSS, ROS, 0.0);
		}

		if (m_CFBCustom != null) {
			double cfb;
			cfb = m_CFBCustom.CFB( ((short)(flag & USE_GREENUP) != 0) ? true : false , m_spread.cbh(), FMC, SFC, for_fros, rso, csi);
			return cfb;
		} else {
			if ((short)(flag & USE_GREENUP) == 0)
				return m_CFBCalculation.cfb(m_spread.cbh(), FMC, SFC, for_fros, rso, csi);
			else
				return m_CFBCalculation_Greenup.cfb(m_spread.cbh(), FMC, SFC, for_fros, rso, csi);
		}
	}

	public double fmc(double lat, double lon, double elev, int day) {
		if (m_FMCCustom != null)
			return m_FMCCustom.FMC(lat, lon, elev, day);
		else
			return m_FMCCalculation.fmc(lat, lon, elev, day);
	}

	public double rsi(double FFMC, double BUI, double FMC, double ISI, int flag, OutVariable<Double> RSI_C2, OutVariable<Double> RSI_D1) {
		if (m_RSICustom != null) {
			CwfgmFuel m_C2, m_D1;
			m_C2 = m_spread.c2();
			m_D1 = m_spread.d1();
			double m_pc = m_spread.pc();
			
			return m_RSICustom.RSI( ((short)(flag & USE_GREENUP) != 0) ? true : false , m_spread.a(flag), m_spread.b(flag), m_spread.c(flag), ISI, FMC, BUI, FFMC, be(BUI), m_spread.curingDegree(), m_C2, m_D1, m_pc, flag, RSI_C2, RSI_D1);
		} else {
			if ((short)(flag & USE_GREENUP) == 0)
				return m_RSICalculation.RSI(m_spread, flag, ISI, FMC, BUI, FFMC, be(BUI), RSI_C2, RSI_D1);
			else	return m_RSICalculation_Greenup.RSI(m_spread, flag, ISI, FMC, BUI, FFMC, be(BUI), RSI_C2, RSI_D1);
		}
	}

	public double wsv(double GS, double SAZ, double WS, double WAZ, double BUI, double FMC, double FFMC, double fF, int flag, WTime ffmc_t, OutVariable<Double> raz) {
		double sf;
		if ((flag & USE_SLOPE) == 0)
			GS = 0.0;

		if (GS >= 0.7)
			GS = 0.7;

		sf = exp(3.533 * pow(GS, 1.2));

		if ((flag & USE_WIND) == 0)
			WS = 0.0;

		OutVariable<Double> rsf_c2 = new OutVariable<Double>();
		OutVariable<Double> rsf_d1 = new OutVariable<Double>();

		double DeadWindISI = Fwi.isiFBP(FFMC, 0.0, (long)ffmc_t.getTotalSeconds());

		rsi(FFMC, BUI, FMC, DeadWindISI, (flag & ~USE_BUI) | CALC_FOR_RSF, rsf_c2, rsf_d1);
		rsf_c2.value *= sf;
		rsf_d1.value *= sf;

		double isf = isf(rsf_c2.value, rsf_d1.value, sf, DeadWindISI, flag);

		double wse;

		if ((flag & USE_SLOPE) == 0)
			wse = 0.0;
		else if (isf > 0.0) {
			wse = log(isf / (0.208 * fF)) / 0.05039;
			if (wse > 40.0) {
				double isiMAX = 2.496 * fF * 0.999;
				if (isf > isiMAX)
					isf = isiMAX;
				wse = 28.0 - log(1.0 - (isf / (2.496 * fF))) / 0.0818;
			}
		}
		else
			wse = 0.0;

		double wsv;
		if (abs(WS) <= 0.00000001 && abs(wse) <= 0.0000001) {
			wsv = 0.0;
			raz.value = COMPASS_TO_CARTESIAN_RADIAN(0.0);
		} else {
			double wsx = WS * sin(WAZ) + wse * sin(SAZ);
			double wsy = WS * cos(WAZ) + wse * cos(SAZ);

			wsv = sqrt(wsx * wsx + wsy * wsy);

			raz.value = acos( wsy / wsv);

			if (wsx < 0.0 )
				raz.value = TWO_PI - raz.value;
			raz.value = COMPASS_TO_CARTESIAN_RADIAN(raz.value);
		}
		return wsv;
	}

	public double lb(double WSV, double RSS, double ROS_EQ, double BUI, double FMC, double FFMC, /*double fF,*/ WTime t, int flag) {
		double lb = 0.0;
		if (m_LBCustom != null)
			lb = m_LBCustom.LB(WSV);
		else
			lb = m_LBCalculation.LB(WSV);
	// Acceleration according the draft FBP notes, Dennis Yuan July 21,2004

		if ((flag & USE_ACCELERATION) != 0) {
//			if (m_AccAlpha <= 0)
			double sfc = sfc(FFMC, BUI, flag);
			OutVariable<Double> rso = new OutVariable<Double>();
			OutVariable<Double> csi = new OutVariable<Double>();
			double cfb = cfb(FMC, sfc, RSS, ROS_EQ, flag, rso, csi);
			double m_AccAlpha = acc(cfb);
			lb = (lb - 1.0) * (1.0 - exp(m_AccAlpha * (double)t.getTotalSeconds() / -60.0)) + 1.0;	// equation 81, August 2004 note
		}							// equation 70
		return lb;
	}

	public double fros(double ROS, double BROS, double LB) {
		double fros;
		if (LB > 0.0) {
			fros = (ROS + BROS) / (LB * 2.0);			// equation 89
			if (fros < 0.0)
				fros = 0.0;
		}
		else
			fros = 0.0;
		return fros;
	}

	public double bros(double WSV, double RSS, double ROS_EQ, double BUI, double FMC, double FFMC, double fF, WTime t, int flag, CwfgmPercentileAttribute RSIadjust, OutVariable<Double> bros_eq, OutVariable<Double> brss) {
		double b_fW = Math.exp(-0.05039 * WSV);		// equation 75
		double bisi = b_fW * fF * 0.208;		// equation 76
		OutVariable<Double> bros_c2 = new OutVariable<Double>();
		OutVariable<Double> bros_d1 = new OutVariable<Double>();
		brss.value = rsi(FFMC, BUI, FMC, bisi, flag, bros_c2, bros_d1);

		if (RSIadjust != null) {
			OutVariable<Double> rso = new OutVariable<Double>();
			OutVariable<Double> csi = new OutVariable<Double>();
			double cfb = cfb(FFMC, sfc(FFMC, BUI, flag), brss.value, brss.value, flag, rso, csi);
			double rsi1 = RSIadjust.RSI(m_defaultFuelType, brss.value, cfb);
			if (rsi1 >= 0.0)
				brss.value = rsi1;
		}

		if (m_RSICustom != null) {
			bros_eq.value = m_RSICustom.ROS( ((short)(flag & USE_GREENUP) != 0) ? true : false , (Double)brss.value, m_spread.cbh(), bisi, FMC, sfc(FFMC, BUI, flag));
		} else {
			if  ((short)(flag & USE_GREENUP) == 0)
				bros_eq.value = m_RSICalculation.ROS((Double)brss.value, m_spread.cbh(), bisi, FMC, sfc(FFMC, BUI, flag), m_CFBCalculation);
			else	bros_eq.value = m_RSICalculation_Greenup.ROS((Double)brss.value, m_spread.cbh(), bisi, FMC, sfc(FFMC, BUI, flag), m_CFBCalculation_Greenup);
		}

		double bros = (Double)bros_eq.value;
		if ((short)(flag & USE_ACCELERATION) != 0) {
//			if(m_AccAlpha<=0)
			double sfc = sfc(FFMC, BUI, flag);
			OutVariable<Double> rso = new OutVariable<Double>();
			OutVariable<Double> csi = new OutVariable<Double>();
			double cfb = cfb(FMC, sfc, RSS, ROS_EQ, flag, rso, csi);
			double m_AccAlpha = acc(cfb);
			bros *= 1.0 - exp(m_AccAlpha * ((double)t.getTotalSeconds() / -60.0));
									// equation 70
		}
		return bros;
	}

	public double ros(double WSV, double BUI, double FMC, double FFMC, WTime t, WTime ffmc_t, int flag, CwfgmPercentileAttribute RSIadjust, OutVariable<Double> ros_eq, OutVariable<Double> rss) {
		double isi;
		isi = Fwi.isiFBP(FFMC, WSV, (long)ffmc_t.getTotalSeconds());

		OutVariable<Double> ros_c2 = new OutVariable<Double>();
		OutVariable<Double> ros_d1 = new OutVariable<Double>();
		rss.value = rsi(FFMC, BUI, FMC, isi, flag, ros_c2, ros_d1);

		if (RSIadjust != null) {
			OutVariable<Double> rso = new OutVariable<Double>();
			OutVariable<Double> csi = new OutVariable<Double>();
			double cfb = cfb(FFMC, sfc(FFMC, BUI, flag), rss.value, rss.value, flag, rso, csi);
			double rsi1 = RSIadjust.RSI(m_defaultFuelType, rss.value, cfb);
			if (rsi1 >= 0.0)
				rss.value = rsi1;
		}

		if((Double)rss.value < 0)
			rss.value = 0.0;

		double ros;
		if (m_RSICustom != null) {
			ros = m_RSICustom.ROS( ((short)(flag & USE_GREENUP) != 0) ? true : false , (Double)rss.value, m_spread.cbh(), isi, FMC, sfc(FFMC, BUI, flag));
		} else {
			if ((short)(flag & USE_GREENUP) == 0)
				ros = m_RSICalculation.ROS((Double)rss.value, m_spread.cbh(), isi, FMC, sfc(FFMC, BUI, flag), m_CFBCalculation);
			else	ros = m_RSICalculation_Greenup.ROS((Double)rss.value, m_spread.cbh(), isi, FMC, sfc(FFMC, BUI, flag), m_CFBCalculation_Greenup);
		}

		ros_eq.value = ros;

		if ((short)(flag & USE_ACCELERATION) != 0) {
//			if(m_AccAlpha<=0) {
				double sfc = sfc(FFMC, BUI, flag);
				OutVariable<Double> rso = new OutVariable<Double>();
				OutVariable<Double> csi = new OutVariable<Double>();
				double cfb = cfb(FMC, sfc, (Double)rss.value, (Double)ros_eq.value, flag, rso, csi);
				double m_AccAlpha = acc(cfb);
//			}
			ros *= 1.0 - exp( m_AccAlpha * ((double)t.getTotalSeconds() / -60.0));
		}							// equation 70

		return ros;

	}

	public double acc(double cfb) {
		if (m_AccelCustom != null)
			return m_AccelCustom.Acceleration(cfb);
		else
			return m_AccAlphaCalculation.accAlpha(cfb);
	}

	public double flameLength(double height, double CFB, double fi) {
		double fl = m_FLCalculation.flameLength(height, CFB, fi);
		return fl;
	}

	public double be(double BUI) {
		double be = Math.exp(50.0 * Math.log(m_spread.q()) * (1.0 / BUI - 1.0 / m_spread.bui0()));
		if (be > m_spread.maxBE())
			be = m_spread.maxBE();
		return be;
	}

	public double fi(double TFC, double ROS) {
		return 300.0 * TFC * ROS;
	}

	public void calculateFCValues(double FFMC, double BUI, double FMC, double RSS, double ROS, int flag, OutVariable<Double> cfb,
			OutVariable<Double> cfc, OutVariable<Double> rso, OutVariable<Double> csi, OutVariable<Double> sfc,
			OutVariable<Double> tfc, OutVariable<Double> fi) throws CloneNotSupportedException {
		sfc.value = sfc(FFMC, BUI, flag);
		cfb.value = cfb(FMC, (Double)sfc.value, RSS, ROS, flag, rso, csi);
//		*cfc = CFC(*cfb);
		tfc.value = tfc((Double)cfb.value, (Double)sfc.value, flag, cfc);
		double for_fros;
		if (m_RSICustom != null)
			for_fros = m_RSICustom.For_FROS( ((short)(flag & USE_GREENUP) != 0) , RSS, ROS, (Double)cfb.value);
		else
			for_fros = m_RSICalculation.FOR_FROS(RSS, ROS, (Double)cfb.value);
		fi.value = fi((Double)tfc.value, for_fros);
	}

	public void calculateDistances(double ROS, double FROS, double BROS, double _CFB, WTime time, int flag, OutVariable<Double> dhead,
			OutVariable<Double> dflank, OutVariable<Double> dback) {
		double alpha = acc(_CFB);
		dhead.value = 0.0;
		dflank.value = 0.0;
		dback.value = 0.0;

		if(FROS == 0) return;
		double t = (double)time.getTotalSeconds() / 60.0;
		double LB_t = 0.0;
		double LB = (ROS + BROS)/ (2.0 * FROS);

		if ( (short)(flag & USE_ACCELERATION) != 0) {
			if (alpha > 0.0) {
				LB_t = (LB -1) * (1-Math.exp(-alpha*t)) +1;
			}
		} else {
			LB_t = LB;
		}

		if (LB_t > 0.0) {
			if ( (short)(flag & USE_ACCELERATION) != 0) {
				if (alpha > 0.0) {
					dhead.value = ROS * (t + (Math.exp(-alpha * t) - 1.0) / alpha);
					dback.value	= BROS * (t + (Math.exp(-alpha * t) - 1.0) / alpha);
				}
			} else {
				dhead.value	= ROS * t;
				dback.value	= BROS * t;
			}
			dflank.value = ((Double)dhead.value + (Double)dback.value) / (2.0 * LB_t);
		}
	}

	public void calculateROSTheta(double ROS, double FROS, double BROS, double RAZ, double Theta, OutVariable<Double> rosTheta) {
		// implements equation 94 out of the FBP update article
		double theta = Math.abs(Theta - RAZ);
		if (theta == 0.0) {
			rosTheta.value = FROS;
			return;
		}
		if (theta == Math.PI) {
			rosTheta.value = BROS;
			return;
		}
		if (theta == (Math.PI * 0.5))
			theta -= 1.57079632679489661923132;
		double cost = Math.cos(theta);
		double sint = Math.sin(theta);
		double twocost = 2.0 * cost;
		double cost2 = cost * cost;
		double sint2 = sint * sint;
		double sum_ros = ROS + BROS;
		double ROSt = (ROS - BROS) / twocost + sum_ros / twocost * (
			(FROS * cost * Math.sqrt(FROS * FROS * cost2 + (ROS * BROS) * sint2) - (ROS * ROS - BROS * BROS) / 4.0 * sint2)
			/
			(FROS * FROS * cost2 + sum_ros * sum_ros * 0.25 * sint2)
			);
		rosTheta.value = ROSt;
	}

	public void calculateStatistics(double ROS, double FROS, double BROS, double _CFB, WTime time, int flag,
			OutVariable<Double> area, OutVariable<Double> perimeter) {
		double alpha = acc(_CFB);
//		double alpha = m_AccAlphaCalculation->AccAlpha(_CFB);	// This is the alpha needed for equation 71.
										// Check the appropriate bit in 'flag' to see if acceleration is turned on (example in below method).
										// Calculate Dt by using equation 71 if acceleration is on, or as (ROS + BROS) * time otherwise ?
										// Calculate LB by inverting equation 89 from ST-X-3, there's actually an LB and an LBt (see below) (one with accel, one
										// assuming equilibrium ROS for entire fire - i.e. no accel) - but LB defined our FROS passed in here so that should be okay,
										// and computationally correct?
									// Refer to code below - some testing and verification will be needed against the CFS code to see if they use the LB calculated
									// or the LB which actually exists between ROS, FROS, BROS - since FROS could be 1 of 2 values...
									// implement equations 86, 87 from ST-X-3

		area.value = 0.0;
		perimeter.value = 0.0;

		// if (FROS == 0), there really is no ellipse, thus we can safely return 0
		if (FROS == 0) return;

		double t = (double)time.getTotalSeconds() / 60.0;
		double Dt, LB_t;

		double LB = (ROS + BROS) / (2.0 * FROS);

		if ( (short)(flag & USE_ACCELERATION) != 0) { // use eqn 71
			if (alpha > 0.0) {
				Dt = (ROS + BROS) * (t + (Math.exp(-alpha * t) - 1.0) / alpha);
				LB_t = (LB - 1) * (1 - Math.exp(-alpha*t)) + 1;
			} else {
				Dt = 0.0;
				LB_t = 0.0;
			}
		} else {
			// from eqn 89
			Dt = (ROS + BROS) * t;
			LB_t = LB;
		}

		if (LB_t > 0.0) {
		// eqn 87
			perimeter.value = Math.PI * (Dt / 2.0) * (1.0 + (1.0 / LB_t)) * (1.0 + Math.pow((LB_t - 1.0) / (2.0 * (LB_t + 1.0)), 2));

	///	double rso, csi, cfb_flank = CFB(FMC*100, sfc, FRSS, FROS, flag, &rso, &csi);
	///	fros = m_RSICalculation->FOR_FROS(FRSS, FROS, cfb_flank);
	///
	///	// from eqn 89
	///	if (!(flag & USE_ACCELERATION)) LB_t = (ROS + BROS) / (2.0 * fros);

		// eqn 86
			area.value = (Math.PI / (4.0 * LB_t) * Math.pow(Dt,2)) / 10000;
		}
	}

	public boolean calculateValues( double GS, double SAZ, double WS, double WAZ, double BUI, double FMC, double FFMC, double fF,
		    WTime t, WTime ffmc_t, int flag, CwfgmPercentileAttribute RSIadjust, OutVariable<Double> rss, OutVariable<Double> ros_eq, OutVariable<Double> ros,
		    OutVariable<Double> frss, OutVariable<Double> fros_eq, OutVariable<Double> fros, OutVariable<Double> brss,
		    OutVariable<Double> bros_eq, OutVariable<Double> bros, OutVariable<Double> wsv, OutVariable<Double> raz) {
		if (GS < 0) {
			flag &= (~(USE_SLOPE));
			GS = 0.0;
		} else {
			SAZ = COMPASS_TO_CARTESIAN_RADIAN((float)SAZ);
		}

		WAZ = COMPASS_TO_CARTESIAN_RADIAN((float)WAZ);

		wsv.value = wsv(GS, SAZ, WS, WAZ, BUI, FMC, FFMC, fF, flag, ffmc_t, raz);
		ros.value = ros((Double)wsv.value, BUI, FMC, FFMC, t, ffmc_t, flag, RSIadjust, ros_eq, rss);
		bros.value = bros((Double)wsv.value, (Double)rss.value, (Double)ros_eq.value, BUI, FMC, FFMC, fF, t, flag, RSIadjust, bros_eq, brss);

		double lb;
		lb = lb((Double)wsv.value, (Double)rss.value, (Double)ros_eq.value, BUI, FMC, FFMC, t, (short)(flag & (~(USE_ACCELERATION))));
		frss.value = fros((Double)rss.value, (Double)brss.value, lb);

		fros_eq.value = fros((Double)ros_eq.value, (Double)bros_eq.value, lb);
		lb = lb((Double)wsv.value, (Double)rss.value, (Double)ros_eq.value, BUI, FMC, FFMC, t, flag);	// this is actually (conditionally) LBt
		fros.value = fros((Double)ros.value, (Double)bros.value, lb);

		return true;
	}

	public boolean isNonFuel() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_Non) {
			return true;
		}
		return false;
	}

	public boolean isConifer() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_C1)
			return true;
		return false;
	}

	public boolean isDeciduous() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_D1)
			return true;
		return false;
	}

	public boolean isMixed() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_Mixed)
			return true;
		return false;
	}

	public boolean isGrass() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_O1)
			return true;
		if (m_spread instanceof SpreadParms_O1ab)
			return true;
		return false;
	}
	
	public boolean isFBPGrass() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_O1 ||
			m_spread instanceof SpreadParms_O1ab)
			return true;
		return false;
	}

	public boolean isMixedDead() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_MixedDead)
			return true;
		return false;
	}

	public boolean isSlash() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_S1)
			return true;
		return false;
	}

	public boolean isC6() {
		if (m_fuelTypeModified)
			return false;
		if (m_spread instanceof SpreadParms_C6)
			return true;
		return false;
	}

	public boolean isModified() {
		return m_fuelTypeModified;
	}

	public void getAttributeValue(int attributeKey, OutVariable<Double> attribute) {
		int key = attributeKey & (~(FUELCOM_ATTRIBUTE.GREENUP_MODIFIER));
		int greenup = attributeKey & FUELCOM_ATTRIBUTE.GREENUP_MODIFIER;

		switch(key) {
			case FUELCOM_ATTRIBUTE.M3M4_C2_A:
			case FUELCOM_ATTRIBUTE.M3M4_C2_B:
			case FUELCOM_ATTRIBUTE.M3M4_C2_C:
			case FUELCOM_ATTRIBUTE.M4_D1_A:
			case FUELCOM_ATTRIBUTE.M4_D1_B:
			case FUELCOM_ATTRIBUTE.M4_D1_C:
			case FUELCOM_ATTRIBUTE.EQ35_THRESHOLD:
			case FUELCOM_ATTRIBUTE.EQ35A_MULT1:
			case FUELCOM_ATTRIBUTE.EQ35A_MULT2:
			case FUELCOM_ATTRIBUTE.EQ35B_ADDER:
			case FUELCOM_ATTRIBUTE.EQ35B_MULT1:
						if (greenup != 0) {
							double d1, d2;
							d1 = m_RSICalculation_Greenup.getAttributeValue((short)key);
							d2 = m_ISFCalculation_Greenup.getAttributeValue((short)key);
							if (d1 >= 0.0)
								attribute.value = d1;
							else
								attribute.value = d2;
							return;
						} else {
							double d1, d2;
							d1 = m_RSICalculation.getAttributeValue((short)key);
							d2 = m_ISFCalculation.getAttributeValue((short)key);
							if (d1 >= 0.0)
								attribute.value = d1;
							else
								attribute.value = d2;
							return;
						}
		}
		
		if ((key >= FUELCOM_ATTRIBUTE.SPREAD_START) && (key < FUELCOM_ATTRIBUTE.SPREAD_END)) {
			attribute.value = m_spread.getAttributeValue((short)key);
		}
		
		if ((key >= FUELCOM_ATTRIBUTE.SFC_START) && (key < FUELCOM_ATTRIBUTE.SFC_END)) {
			if (greenup != 0)
				attribute.value = m_SFCCalculation_Greenup.getAttributeValue((short)key);
			else
				attribute.value = m_SFCCalculation.getAttributeValue((short)key);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.RSI_START) && (key < FUELCOM_ATTRIBUTE.RSI_END)) {
			if (greenup != 0)
				attribute.value = m_RSICalculation_Greenup.getAttributeValue((short)key);
			else
				attribute.value = m_RSICalculation.getAttributeValue((short)key);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.LB_START) && (key < FUELCOM_ATTRIBUTE.LB_END)) {
			attribute.value = m_LBCalculation.getAttributeValue((short)key);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.ISF_START) && (key < FUELCOM_ATTRIBUTE.ISF_END)) {
			if (greenup != 0)
				attribute.value = m_ISFCalculation_Greenup.getAttributeValue((short)key);
			else
				attribute.value = m_ISFCalculation.getAttributeValue((short)key);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.CFB_START) && (key < FUELCOM_ATTRIBUTE.CFB_END)) {
			if (greenup != 0)
				attribute.value = m_CFBCalculation_Greenup.getAttributeValue((short)key);
			else
				attribute.value = m_CFBCalculation.getAttributeValue((short)key);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.ACCEL_START) && (key < FUELCOM_ATTRIBUTE.ACCEL_END)) {
			attribute.value = m_AccAlphaCalculation.getAttributeValue((short)key);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.FMC_START) && (key < FUELCOM_ATTRIBUTE.FMC_END)) {
			attribute.value = m_FMCCalculation.getAttributeValue((short)key);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.FLAMELENGTH_START) && (key < FUELCOM_ATTRIBUTE.FLAMELENGTH_END)) {
			attribute.value = m_FLCalculation.getAttributeValue((short)key);
		}

		return;
	}

	public void setAttributeValue(int attributeKey, Object attribute)
	{
		assert attribute instanceof Double;
		setAttributeValue(attributeKey, ((Double)attribute).doubleValue());
	}

	public void setAttributeValue(int attributeKey, double attribute) {
		int key = attributeKey & (~(FUELCOM_ATTRIBUTE.GREENUP_MODIFIER));
		int greenup = attributeKey & FUELCOM_ATTRIBUTE.GREENUP_MODIFIER;

		switch (key) {
			case FUELCOM_ATTRIBUTE.M3M4_C2_A:
			case FUELCOM_ATTRIBUTE.M3M4_C2_B:
			case FUELCOM_ATTRIBUTE.M3M4_C2_C:
			case FUELCOM_ATTRIBUTE.M4_D1_A:
			case FUELCOM_ATTRIBUTE.M4_D1_B:
			case FUELCOM_ATTRIBUTE.M4_D1_C:
			case FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS:
			case FUELCOM_ATTRIBUTE.EQ35_THRESHOLD:
			case FUELCOM_ATTRIBUTE.EQ35A_MULT1:
			case FUELCOM_ATTRIBUTE.EQ35A_MULT2:
			case FUELCOM_ATTRIBUTE.EQ35B_ADDER:
			case FUELCOM_ATTRIBUTE.EQ35B_MULT1:
							if (greenup != 0) {
								m_RSICalculation_Greenup.setAttributeValue((short)key, attribute);
								m_ISFCalculation_Greenup.setAttributeValue((short)key, attribute);
								return;
							} else {
								m_RSICalculation.setAttributeValue((short)key, attribute);
								m_ISFCalculation.setAttributeValue((short)key, attribute);
								return;
							}
		}
		
		if ((key >= FUELCOM_ATTRIBUTE.SPREAD_START) && (key < FUELCOM_ATTRIBUTE.SPREAD_END)) {
			m_spread.setAttributeValue((short)key, attribute);
		}
		
		if ((key >= FUELCOM_ATTRIBUTE.SFC_START) && (key < FUELCOM_ATTRIBUTE.SFC_END)) {
			if (greenup != 0)
				m_SFCCalculation_Greenup.setAttributeValue((short)key, attribute);
			else
				m_SFCCalculation.setAttributeValue((short)key, attribute);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.RSI_START) && (key < FUELCOM_ATTRIBUTE.RSI_END)) {
			if (greenup != 0)
				m_RSICalculation_Greenup.setAttributeValue((short)key, attribute);
			else
				m_RSICalculation.setAttributeValue((short)key, attribute);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.LB_START) && (key < FUELCOM_ATTRIBUTE.LB_END)) {
			m_LBCalculation.setAttributeValue((short)key, attribute);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.ISF_START) && (key < FUELCOM_ATTRIBUTE.ISF_END)) {
			if (greenup != 0)
				m_ISFCalculation_Greenup.setAttributeValue((short)key, attribute);
			else
				m_ISFCalculation.setAttributeValue((short)key, attribute);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.CFB_START) && (key < FUELCOM_ATTRIBUTE.CFB_END)) {
			if (greenup != 0)
				m_CFBCalculation_Greenup.setAttributeValue((short)key, attribute);
			else
				m_CFBCalculation.setAttributeValue((short)key, attribute);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.ACCEL_START) && (key < FUELCOM_ATTRIBUTE.ACCEL_END)) {
			m_AccAlphaCalculation.setAttributeValue((short)key, attribute);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.FMC_START) && (key < FUELCOM_ATTRIBUTE.FMC_END)) {
			m_FMCCalculation.setAttributeValue((short)key, attribute);
		}

		else if ((key >= FUELCOM_ATTRIBUTE.FLAMELENGTH_START) && (key < FUELCOM_ATTRIBUTE.FLAMELENGTH_END)) {
			m_FLCalculation.setAttributeValue((short)key, attribute);
		}

		return;
	}

	public short getEquation(int equationKey) {
		switch(equationKey) {
			case FUELCOM_EQUATION.FMC:			if (m_FMCCalculation == null) return 0; return m_FMCCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.SFC:			if (m_SFCCalculation == null) return 0; return m_SFCCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.SFC_GREENUP:	if (m_SFCCalculation_Greenup == null) return 0; return m_SFCCalculation_Greenup.getExternalDefinition();
			case FUELCOM_EQUATION.TFC:			if (m_TFCCalculation == null) return 0; return m_TFCCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.TFC_GREENUP:	if (m_TFCCalculation_Greenup == null) return 0; return m_TFCCalculation_Greenup.getExternalDefinition();
			case FUELCOM_EQUATION.RSI:			if (m_RSICalculation == null) return 0; return m_RSICalculation.getExternalDefinition();
			case FUELCOM_EQUATION.RSI_GREENUP:	if (m_RSICalculation_Greenup == null) return 0; return m_RSICalculation_Greenup.getExternalDefinition();
			case FUELCOM_EQUATION.ISF:			if (m_ISFCalculation == null) return 0; return m_ISFCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.ISF_GREENUP:	if (m_ISFCalculation_Greenup == null) return 0; return m_ISFCalculation_Greenup.getExternalDefinition();
			case FUELCOM_EQUATION.CFB:			if (m_CFBCalculation == null) return 0; return m_CFBCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.CFB_GREENUP:	if (m_CFBCalculation_Greenup == null) return 0; return m_CFBCalculation_Greenup.getExternalDefinition();
			case FUELCOM_EQUATION.ACCEL:		if (m_AccAlphaCalculation == null) return 0; return m_AccAlphaCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.LB:			if (m_LBCalculation == null) return 0; return m_LBCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.FLAMELENGTH:	if (m_FLCalculation == null) return 0; return m_FLCalculation.getExternalDefinition();
			case FUELCOM_EQUATION.SPREADPARMS:	if (m_spread == null) return 0; return m_spread.getExternalDefinition();
			default:							throw new IllegalArgumentException("One of the inputs is out of range.");
		}
	}

	public void setEquation(int equationKey, int equation) {
		if(equation != this.getEquation(equationKey)) {

			switch (equationKey) {
				case FUELCOM_EQUATION.SPREADPARMS:
									if (equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_S1 &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_C1 &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_C6 &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_O1 &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_O1AB &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_MIXED &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_MIXEDDEAD &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_NON &&
										equationKey != FUELCOM_EQUATION.SELECTION_SPREADPARMS_NZ) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;
			
				case FUELCOM_EQUATION.FMC:		
									if ((equation != FUELCOM_EQUATION.SELECTION_FMC_CALC) &&
										(equation != FUELCOM_EQUATION.SELECTION_FMC_NOCALC)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.SFC:		
				case FUELCOM_EQUATION.SFC_GREENUP:
									if ((equation != FUELCOM_EQUATION.SELECTION_SFC_C1) &&
										(equation != FUELCOM_EQUATION.SELECTION_SFC_C2) &&
										(equation != FUELCOM_EQUATION.SELECTION_SFC_C7) &&
										(equation != FUELCOM_EQUATION.SELECTION_SFC_D2) &&
										(equation != FUELCOM_EQUATION.SELECTION_SFC_M1) &&
										(equation != FUELCOM_EQUATION.SELECTION_SFC_O1) &&
										(equation != FUELCOM_EQUATION.SELECTION_SFC_S1)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.TFC:
				case FUELCOM_EQUATION.TFC_GREENUP:
									if ((equation != FUELCOM_EQUATION.SELECTION_TFC_C1) &&
										(equation != FUELCOM_EQUATION.SELECTION_TFC_D2) &&
										(equation != FUELCOM_EQUATION.SELECTION_TFC_M1) &&
										(equation != FUELCOM_EQUATION.SELECTION_TFC_O1)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.RSI:
				case FUELCOM_EQUATION.RSI_GREENUP:
									if ((equation != FUELCOM_EQUATION.SELECTION_RSI_C1) &&
										(equation != FUELCOM_EQUATION.SELECTION_RSI_C6) &&
										(equation != FUELCOM_EQUATION.SELECTION_RSI_D2) &&
										(equation != FUELCOM_EQUATION.SELECTION_RSI_M1) &&
										(equation != FUELCOM_EQUATION.SELECTION_RSI_M3) &&
										(equation != FUELCOM_EQUATION.SELECTION_RSI_M4) &&
										(equation != FUELCOM_EQUATION.SELECTION_RSI_O1) &&
										(equation != FUELCOM_EQUATION.SELECTION_RSI_CONSTANT)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.ISF:		
				case FUELCOM_EQUATION.ISF_GREENUP:
									if ((equation != FUELCOM_EQUATION.SELECTION_ISF_C1) &&
										(equation != FUELCOM_EQUATION.SELECTION_ISF_M1) &&
										(equation != FUELCOM_EQUATION.SELECTION_ISF_M3M4) &&
										(equation != FUELCOM_EQUATION.SELECTION_ISF_O1)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.CFB:
				case FUELCOM_EQUATION.CFB_GREENUP:
									if ((equation != FUELCOM_EQUATION.SELECTION_CFB_C1) &&
										(equation != FUELCOM_EQUATION.SELECTION_CFB_D2)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.ACCEL:
									if ((equation != FUELCOM_EQUATION.SELECTION_ACCEL_CLOSED) &&
										(equation != FUELCOM_EQUATION.SELECTION_ACCEL_OPEN)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.LB:
									if ((equation != FUELCOM_EQUATION.SELECTION_LB_C1) &&
										(equation != FUELCOM_EQUATION.SELECTION_LB_O1)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				case FUELCOM_EQUATION.FLAMELENGTH:
									if ((equation != FUELCOM_EQUATION.SELECTION_FLAMELENGTH_TREE) &&
										(equation != FUELCOM_EQUATION.SELECTION_FLAMELENGTH_OTHER) &&
										(equation != FUELCOM_EQUATION.SELECTION_FLAMELENGTH_ALEXANDER82) &&
										(equation != FUELCOM_EQUATION.SELECTION_FLAMELENGTH_ALEXANDER82_TREE)) {
										throw new IllegalArgumentException("One of the inputs is out of range.");
									}
									break;

				default:
									throw new IllegalArgumentException("One of the inputs is out of range.");
			}

			FuelAttribute fa = null;
			switch (equation) {
				case FUELCOM_EQUATION.SELECTION_FMC_CALC:	fa = new FMC_Calc(); break;
				case FUELCOM_EQUATION.SELECTION_FMC_NOCALC:	fa = new FMC_NoCalc(); break;

				case FUELCOM_EQUATION.SELECTION_SFC_C1:	fa = new SFC_C1(); break;
				case FUELCOM_EQUATION.SELECTION_SFC_C2:	fa = new SFC_C2(); break;
				case FUELCOM_EQUATION.SELECTION_SFC_C7:	fa = new SFC_C7(); break;
				case FUELCOM_EQUATION.SELECTION_SFC_D2:	fa = new SFC_D2(); break;
				case FUELCOM_EQUATION.SELECTION_SFC_M1:	fa = new SFC_M1(); break;
				case FUELCOM_EQUATION.SELECTION_SFC_O1:	fa = new SFC_O1(); break;
				case FUELCOM_EQUATION.SELECTION_SFC_S1:	fa = new SFC_S1(); break;

				case FUELCOM_EQUATION.SELECTION_TFC_C1:	fa = new TFC_C1(); break;
				case FUELCOM_EQUATION.SELECTION_TFC_D2:	fa = new TFC_D2(); break;
				case FUELCOM_EQUATION.SELECTION_TFC_M1:	fa = new TFC_M1(); break;
				case FUELCOM_EQUATION.SELECTION_TFC_O1:	fa = new TFC_O1(); break;

				case FUELCOM_EQUATION.SELECTION_RSI_C1:	fa = new RSI_C1(); break;
				case FUELCOM_EQUATION.SELECTION_RSI_C6:	fa = new RSI_C6(); break;
				case FUELCOM_EQUATION.SELECTION_RSI_D2:	fa = new RSI_D2(); break;
				case FUELCOM_EQUATION.SELECTION_RSI_M1:	fa = new RSI_M1(); break;
				case FUELCOM_EQUATION.SELECTION_RSI_M3:	fa = new RSI_M3(); break;
				case FUELCOM_EQUATION.SELECTION_RSI_M4:	fa = new RSI_M4(); break;
				case FUELCOM_EQUATION.SELECTION_RSI_O1:	fa = new RSI_O1(); break;
				case FUELCOM_EQUATION.SELECTION_RSI_CONSTANT:	fa = new RSI_Constant(); break;

				case FUELCOM_EQUATION.SELECTION_ISF_C1:	fa = new ISF_C1(); break;
				case FUELCOM_EQUATION.SELECTION_ISF_M1:	fa = new ISF_M1(); break;
				case FUELCOM_EQUATION.SELECTION_ISF_M3M4:	fa = new ISF_M3M4(); break;
				case FUELCOM_EQUATION.SELECTION_ISF_O1:	fa = new ISF_O1(); break;

				case FUELCOM_EQUATION.SELECTION_CFB_C1:	fa = new CFB_C1(); break;
				case FUELCOM_EQUATION.SELECTION_CFB_D2:	fa = new CFB_D2(); break;

				case FUELCOM_EQUATION.SELECTION_ACCEL_CLOSED:	fa = new AccAlphaClosed(); break;
				case FUELCOM_EQUATION.SELECTION_ACCEL_OPEN:	fa = new AccAlphaOpen(); break;

				case FUELCOM_EQUATION.SELECTION_LB_C1:	fa = new LB_C1(); break;
				case FUELCOM_EQUATION.SELECTION_LB_O1:	fa = new LB_O1(); break;

				case FUELCOM_EQUATION.SELECTION_FLAMELENGTH_TREE:	fa = new FlameLength_Tree(); break;
				case FUELCOM_EQUATION.SELECTION_FLAMELENGTH_OTHER:	fa = new FlameLength_Other(); break;
				case FUELCOM_EQUATION.SELECTION_FLAMELENGTH_ALEXANDER82:	fa = new FlameLength_Alexander82(); break;
				case FUELCOM_EQUATION.SELECTION_FLAMELENGTH_ALEXANDER82_TREE:	fa = new FlameLength_Alexander82_Tree(); break;
			
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_S1: fa = new SpreadParms_S1(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_C1: fa = new SpreadParms_C1(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_C6: fa = new SpreadParms_C6(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_O1: fa = new SpreadParms_O1(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_O1AB: fa = new SpreadParms_O1ab(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_MIXED: fa = new SpreadParms_Mixed(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_MIXEDDEAD: fa = new SpreadParms_MixedDead(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_NON: fa = new SpreadParms_Non(); break;
				case FUELCOM_EQUATION.SELECTION_SPREADPARMS_NZ: fa = new SpreadParms_NZ(); break;
			
			}
			if (fa == null)
				throw new IllegalArgumentException("One of the inputs is out of range.");

			switch(equationKey) {
				case FUELCOM_EQUATION.SPREADPARMS: 	m_spread = (SpreadParmsAttribute)fa; break;
				case FUELCOM_EQUATION.FMC:			m_FMCCalculation = (FMCAttribute)fa; break;
				case FUELCOM_EQUATION.SFC:			m_SFCCalculation = (SFCAttribute)fa; break;
				case FUELCOM_EQUATION.SFC_GREENUP:	m_SFCCalculation_Greenup = (SFCAttribute)fa; break;
				case FUELCOM_EQUATION.TFC:			m_TFCCalculation = (TFCAttribute)fa; break;
				case FUELCOM_EQUATION.TFC_GREENUP:	m_TFCCalculation_Greenup = (TFCAttribute)fa; break;
				case FUELCOM_EQUATION.RSI:			m_RSICalculation = (RSIAttribute)fa; break;
				case FUELCOM_EQUATION.RSI_GREENUP:	m_RSICalculation_Greenup = (RSIAttribute)fa; break;
				case FUELCOM_EQUATION.ISF:			m_ISFCalculation = (ISFAttribute)fa; break;
				case FUELCOM_EQUATION.ISF_GREENUP:	m_ISFCalculation_Greenup = (ISFAttribute)fa; break;
				case FUELCOM_EQUATION.CFB:			m_CFBCalculation = (CFBAttribute)fa; break;
				case FUELCOM_EQUATION.CFB_GREENUP:	m_CFBCalculation_Greenup = (CFBAttribute)fa; break;
				case FUELCOM_EQUATION.ACCEL:		m_AccAlphaCalculation = (AccAlphaAttribute)fa; break;
				case FUELCOM_EQUATION.LB:			m_LBCalculation = (LBAttribute)fa; break;
				case FUELCOM_EQUATION.FLAMELENGTH:	m_FLCalculation = (FlameLengthAttribute)fa; break;
				default:							throw new IllegalArgumentException("One of the inputs is out of range.");
			}
			m_fuelTypeModified = true;
		}
	}
	
	public void setC2 (Cwfgm_Fuel newVal) throws CloneNotSupportedException {
		if ((m_spread instanceof SpreadParms_Mixed) || (m_spread instanceof SpreadParms_MixedDead)) {
			SpreadParms_Mixed m = (SpreadParms_Mixed)m_spread;
			m.setC2(newVal);
		}
	}
	
	public void setD1 (Cwfgm_Fuel newVal) throws CloneNotSupportedException {
		if ((m_spread instanceof SpreadParms_Mixed) || (m_spread instanceof SpreadParms_MixedDead)) {
			SpreadParms_Mixed m = (SpreadParms_Mixed)m_spread;
			m.setD1(newVal);
		}
	}
	
	public Cwfgm_Fuel getC2() {
		if ((m_spread instanceof SpreadParms_Mixed) || (m_spread instanceof SpreadParms_MixedDead)) {
			SpreadParms_Mixed m = (SpreadParms_Mixed)m_spread;
			return m.m_C2;
		} else {
			return null;
		}
	}
	
	public Cwfgm_Fuel getD1() {
		if ((m_spread instanceof SpreadParms_Mixed) || (m_spread instanceof SpreadParms_MixedDead)) {
			SpreadParms_Mixed m = (SpreadParms_Mixed)m_spread;
			return m.m_D1;
		} else {
			return null;
		}
	}

	@Override
	public ca.wise.fuel.proto.FbpFuel serialize(SerializeProtoOptions options) {
		FbpFuel.Builder msg = FbpFuel.newBuilder();
		msg.setVersion(1);

		if (m_spread != null)
			msg.setSpread(m_spread.serialize(options));

		if (m_FMCCalculation != null)
			msg.setFmcCalculation(m_FMCCalculation.serialize(options));

		if (m_SFCCalculation != null)
			msg.setSfcCalculation(m_SFCCalculation.serialize(options));
		if (m_SFCCalculation_Greenup != null)
			msg.setSfcCalculationGreenup(m_SFCCalculation_Greenup.serialize(options));

		if (m_TFCCalculation != null)
			msg.setTfcCalculation(m_TFCCalculation.serialize(options));
		if (m_TFCCalculation_Greenup != null)
			msg.setTfcCalculationGreenup(m_TFCCalculation_Greenup.serialize(options));

		if(m_RSICalculation != null)
			msg.setRsiCalculation(m_RSICalculation.serialize(options));
		if (m_RSICalculation_Greenup != null)
			msg.setRsiCalculationGreenup(m_RSICalculation_Greenup.serialize(options));

		if (m_ISFCalculation != null)
			msg.setIsfCalculation(m_ISFCalculation.serialize(options));
		if (m_ISFCalculation_Greenup != null)
			msg.setIsfCalculationGreenup(m_ISFCalculation_Greenup.serialize(options));

		if (m_AccAlphaCalculation != null)
			msg.setAccAlphaCalculation(m_AccAlphaCalculation.serialize(options));

		if (m_LBCalculation != null)
			msg.setLbCalculation(m_LBCalculation.serialize(options));

		if (m_CFBCalculation != null)
			msg.setCfbCalculation(m_CFBCalculation.serialize(options));
		if (m_CFBCalculation_Greenup != null)
			msg.setCfbCalculationGreenup(m_CFBCalculation_Greenup.serialize(options));

		if (m_FLCalculation != null)
			msg.setFlCalculation(m_FLCalculation.serialize(options));

		return msg.build();
	}

	@Override
	public FBP_Fuel deserialize(Message proto) {
		FbpFuel msgRead;
		
		try {
			msgRead = (FbpFuel) proto;
		} catch (Exception e) {
			throw new IllegalArgumentException();
		}
		
		if (msgRead.getVersion() != 1) {
			throw new IllegalArgumentException();
		}
		
		if (msgRead.hasSpread()) {
			SpreadParmsAttribute tmp_spread = new SpreadParmsAttribute();
			ISerializationData_SP def = new ISerializationData_SP();
			def.c2 = (Cwfgm_Fuel) m_spread.c2();
			def.d1 = (Cwfgm_Fuel) m_spread.d1();
			m_spread = (SpreadParmsAttribute)(tmp_spread.deserialize(msgRead.getSpread(), def));
		}

		if (msgRead.hasFmcCalculation()) {
			m_FMCCalculation.deserialize(msgRead.getFmcCalculation());
		}

		if (msgRead.hasSfcCalculation()) {
			m_SFCCalculation.deserialize(msgRead.getSfcCalculation());
		}
		if (msgRead.hasSfcCalculationGreenup()) {
			m_SFCCalculation_Greenup.deserialize(msgRead.getSfcCalculationGreenup());
		}

		if (msgRead.hasTfcCalculation()) {
			m_TFCCalculation.deserialize(msgRead.getTfcCalculation());
		}
		if (msgRead.hasTfcCalculationGreenup()) {
			m_TFCCalculation_Greenup.deserialize(msgRead.getTfcCalculationGreenup());
		}

		if (msgRead.hasRsiCalculation()) {
			m_RSICalculation.deserialize(msgRead.getRsiCalculation());
		}
		if (msgRead.hasRsiCalculationGreenup()) {
			m_RSICalculation_Greenup.deserialize(msgRead.getRsiCalculationGreenup());
		}

		if (msgRead.hasIsfCalculation()) {
			m_ISFCalculation.deserialize(msgRead.getIsfCalculation());
		}
		if (msgRead.hasIsfCalculationGreenup()) {
			m_ISFCalculation_Greenup.deserialize(msgRead.getIsfCalculationGreenup());
		}

		if (msgRead.hasAccAlphaCalculation()) {
			m_AccAlphaCalculation.deserialize(msgRead.getAccAlphaCalculation());
		}

		if (msgRead.hasLbCalculation()) {
			m_LBCalculation.deserialize(msgRead.getLbCalculation());
		}

		if (msgRead.hasCfbCalculation()) {
			m_CFBCalculation.deserialize(msgRead.getCfbCalculation());
		}
		if (msgRead.hasCfbCalculationGreenup()) {
			m_CFBCalculation_Greenup.deserialize(msgRead.getCfbCalculationGreenup());
		}

		if (msgRead.hasFlCalculation()) {
			m_FLCalculation.deserialize(msgRead.getFlCalculation());
		}
			
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		// TODO Auto-generated method stub
		return null;
	}
}
