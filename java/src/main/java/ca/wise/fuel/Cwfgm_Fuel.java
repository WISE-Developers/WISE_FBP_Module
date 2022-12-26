/***********************************************************************
 * REDapp - Cwfgm_Fuel.java
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
import java.util.Optional;

import com.google.protobuf.Message;

import ca.wise.fuel.proto.CcwfgmFuel;
import ca.wise.fuel.proto.FbpFuel;
import ca.wise.fuel.proto.FuelName;
import ca.wise.serialize.*;

import ca.hss.general.OutVariable;
import ca.hss.times.WTime;

/**
 * A class to read/write FBP fuel type.
 * 
 * @author rbryce
 */
public class Cwfgm_Fuel extends CwfgmFBPFuel {
	protected final FBP_Fuel m_fuel;
	public boolean m_bRequiresSave;

	public Cwfgm_Fuel() {
		m_fuel = new FBP_Fuel();
		m_name = "";
		m_bRequiresSave = false;
	}
	
	public Cwfgm_Fuel(final Cwfgm_Fuel other) {
		super(other);
		m_fuel = new FBP_Fuel(other.m_fuel);
		m_bRequiresSave = false;
	}
	
	@Override
	public void setName(String name) {
		m_name = name;
		m_bRequiresSave = true;
	}

	@Override
	public void setSpeciesCode(String name) {
		if (m_fuel.m_DBHCalculation == null)
			throw new IllegalStateException("The object is in an unexpected state.");
		m_fuel.m_DBHCalculation.setSpeciesCode(name);
		m_bRequiresSave = true;
	}

	@Override
	public String getSpeciesCode() {
		if (m_fuel.m_DBHCalculation == null)
			throw new IllegalStateException("The object is in an unexpected state.");
		return m_fuel.m_DBHCalculation.getSpeciesCode();
	}
	
	@Override
	public double fmc(double latitude, double longitude, double elev, int day) {
		return m_fuel.fmc(latitude, longitude, elev, day);
	}

	@Override
	public void calculateROSValues(double GS, double SAZ, double WS, double WAZ, double BUI, double FMC, double FFMC, double fF,
		    				WTime t, WTime ffmc_t, int flag, CwfgmPercentileAttribute RSIadjust,
							OutVariable<Double> rss, OutVariable<Double> ros_eq, OutVariable<Double> ros,
    						OutVariable<Double> frss, OutVariable<Double> fros_eq, OutVariable<Double> fros, OutVariable<Double> brss,
							OutVariable<Double> bros_eq, OutVariable<Double> bros, OutVariable<Double> wsv, OutVariable<Double> raz) throws CloneNotSupportedException {

		assert rss != null;
		assert brss != null;
		assert frss != null;
		assert ros_eq != null;
		assert bros_eq!= null;
		assert fros_eq != null;
		assert ros != null;
		assert fros != null;
		assert bros != null;
		assert wsv != null;
		assert raz != null;
		m_fuel.calculateValues(GS, SAZ, WS, WAZ, BUI, FMC, FFMC, fF, t, ffmc_t, (short)(flag & m_fuel.FUELCOM_INPUT_MASK), RSIadjust,
			    rss, ros_eq, ros, frss, fros_eq, fros, brss, bros_eq, bros, wsv, raz);
	}

	@Override
	public void calculateFCValues(double FFMC, double BUI, double FMC,	double RSS, double ROS, int flag, OutVariable<Double> cfb,
						   OutVariable<Double> cfc, OutVariable<Double> rso, OutVariable<Double> csi, OutVariable<Double> sfc, OutVariable<Double> tfc,
						   OutVariable<Double> fi) throws CloneNotSupportedException {
		assert cfb != null;
		assert rso != null;
		assert csi != null;
		assert sfc != null;
		assert tfc != null;
		assert fi != null;
		m_fuel.calculateFCValues(FFMC, BUI, FMC, RSS, ROS, flag, cfb, cfc, rso, csi, sfc, tfc, fi);
	}

	@Override
	public void calculateStatistics(double ROS, double FROS, double BROS, double _CFB, WTime time, int flag, OutVariable<Double> area, OutVariable<Double> perimeter) {
		assert area != null;
		assert perimeter != null;

		m_fuel.calculateStatistics(ROS, FROS, BROS, _CFB, time, (short)(flag & m_fuel.FUELCOM_INPUT_MASK), area, perimeter);
	}

	@Override
	public void calculateDistances(double ROS, double FROS, double BROS, double _CFB, WTime time, int flag, OutVariable<Double> dhead,
							OutVariable<Double> dflank, OutVariable<Double> dback) {
		assert dhead != null;
		assert dflank != null;
		assert dback != null;

		m_fuel.calculateDistances(ROS, FROS, BROS, _CFB, time, (short)(flag & m_fuel.FUELCOM_INPUT_MASK), dhead, dflank, dback);
	}

	@Override
	public void calculateROSTheta(double ROS, double FROS, double BROS, double RAZ, double Theta, OutVariable<Double> rosTheta) {
		assert rosTheta != null;

		m_fuel.calculateROSTheta(ROS, FROS, BROS, RAZ, Theta, rosTheta);
	}

	@Override
	public double isf(double RSF, double SF, double ISZ, short flag) {
		return m_fuel.isf(RSF, RSF, SF, ISZ, (short)(flag & m_fuel.FUELCOM_INPUT_MASK));
	}

	@Override
	public double flameLength(double height, double CFB, double FI) {
		return m_fuel.flameLength(height, CFB, FI);
	}

	@Override
	public double dbh(double height) {
		return m_fuel.dbh(height);
	}

	@Override
	public double sfc(double FFMC, double BUI, short flag) {
		return m_fuel.sfc(FFMC, BUI, (short)(flag & m_fuel.FUELCOM_INPUT_MASK));
	}

	@Override
	public double rsi(double FFMC, double BUI, double FMC, double ISI, short flag){
		OutVariable<Double> RSI_C2 = new OutVariable<Double>();
		OutVariable<Double> RSI_D1 = new OutVariable<Double>();

		return m_fuel.rsi(FFMC, BUI, FMC, ISI, flag, RSI_C2, RSI_D1);
	}

	@Override
	public boolean isConiferFuelType() {
		return m_fuel.isConifer();
	}

	@Override
	public boolean isDeciduousFuelType() {
		return m_fuel.isDeciduous();
	}

	@Override
	public boolean isMixedFuelType() {
		return m_fuel.isMixed();
	}

	@Override
	public boolean isSlashFuelType() {
		return m_fuel.isSlash();
	}

	@Override
	public boolean isGrassFuelType() {
		return m_fuel.isGrass();
	}

	@Override
	public boolean isC6FuelType() {
		return m_fuel.isC6();
	}

	@Override
	public boolean isMixedDeadFir() {
		return m_fuel.isMixedDead();
	}

	@Override
	public boolean isNonFuel() {
		return m_fuel.isNonFuel();
	}

	@Override
	public Class<? extends CwfgmFuel> getDefaultClassID() {
		return m_fuel.m_defaultFuelType;
	}

	@Override
	public Object getAttribute(short attributeKey) {
		OutVariable<Double> attribute = new OutVariable<Double>();
		m_fuel.getAttributeValue(attributeKey, attribute);
		return attribute.value;
	}

	@Override
	public void setAttribute(int attributeKey, Object attribute) {
		m_fuel.setAttributeValue(attributeKey, (Double)attribute);
		m_bRequiresSave = true;
	}

	public CwfgmFuel getC2() {
		return m_fuel.m_C2;
	}
	
	public CwfgmFuel getD1() {
		return m_fuel.m_D1;
	}
	
	@Override
	public void setC2(CwfgmFuel C2) {
		if (m_fuel.m_C2 != C2)
			m_bRequiresSave = true;
		m_fuel.m_C2 = C2;
	}

	@Override
	public void setD1(CwfgmFuel D1) {
		if (m_fuel.m_D1 != D1)
			m_bRequiresSave = true;
		m_fuel.m_D1 = D1;
	}

	@Override
	public short getEquation(short equationKey) {
		return m_fuel.getEquation(equationKey);
	}
	
	@Override
	public void setEquation(short equationKey, short equation) {
		m_fuel.setEquation(equationKey, equation);
		m_bRequiresSave = true;
	}

	@Override
	public CwfgmAccelAttribute getCustomEquation_Accel() {
		return m_fuel.m_AccelCustom;
	}
	
	@Override
	public void setCustomEquation_Accel(CwfgmAccelAttribute newVal) {
		m_fuel.m_AccelCustom = newVal;
	}

	@Override
	public CwfgmFMCAttribute getCustomEquation_FMC() {
		return m_fuel.m_FMCCustom;
	}
	
	@Override
	public void setCustomEquation_FMC(CwfgmFMCAttribute newVal) {
		m_fuel.m_FMCCustom = newVal;
	}

	@Override
	public CwfgmSFCAttribute getCustomEquation_SFC() {
		return m_fuel.m_SFCCustom;
	}
	
	@Override
	public void setCustomEquation_SFC(CwfgmSFCAttribute newVal) {
		m_fuel.m_SFCCustom = newVal;
	}

	@Override
	public CwfgmTFCAttribute getCustomEquation_TFC() {
		return m_fuel.m_TFCCustom;
	}
	
	@Override
	public void setCustomEquation_TFC(CwfgmTFCAttribute newVal) {
		m_fuel.m_TFCCustom = newVal;
	}

	@Override
	public CwfgmCFBAttribute getCustomEquation_CFB() {
		return m_fuel.m_CFBCustom;
	}
	
	@Override
	public void setCustomEquation_CFB(CwfgmCFBAttribute newVal) {
		m_fuel.m_CFBCustom = newVal;
	}

	@Override
	public CwfgmRSIAttribute getCustomEquation_RSI() {
		return m_fuel.m_RSICustom;
	}

	@Override
	public void setCustomEquation_RSI(CwfgmRSIAttribute newVal) {
		m_fuel.m_RSICustom = newVal;
	}

	@Override
	public CwfgmISFAttribute getCustomEquation_ISF() {
		return m_fuel.m_ISFCustom;
	}

	@Override
	public void setCustomEquation_ISF(CwfgmISFAttribute newVal) {
		m_fuel.m_ISFCustom = newVal;
	}

	@Override
	public CwfgmLBAttribute getCustomEquation_LB() {
		return m_fuel.m_LBCustom;
	}

	@Override
	public void setCustomEquation_LB(CwfgmLBAttribute newVal) {
		m_fuel.m_LBCustom = newVal;
	}

	public CwfgmDBHAttribute getCustomEquation_DBH() {
		return m_fuel.m_DBHCustom;
	}
	
	@Override
	public void setCustomEquation_DBH(CwfgmDBHAttribute newVal) {
		m_fuel.m_DBHCustom = newVal;
	}

	public Object queryInterface(long riid)
	{
		if (riid == FBP_Fuel.IID_ICWFGM_FBPFuel)
			return m_fuel;
		return null;
	}

	@Override
	public CcwfgmFuel serialize(SerializeProtoOptions options) {
		CcwfgmFuel.Builder msg = CcwfgmFuel.newBuilder();
		msg.setVersion(1);
		
		boolean serialized = false;
		
		if (!options.useVerboseOutput()) {
			if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_C1.class)) {
				msg.setReadonly(FuelName.C1);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_C2.class)) {
				msg.setReadonly(FuelName.C2);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_C3.class)) {
				msg.setReadonly(FuelName.C3);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_C4.class)) {
				msg.setReadonly(FuelName.C4);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_C5.class)) {
				msg.setReadonly(FuelName.C5);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_C6.class)) {
				msg.setReadonly(FuelName.C6);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_C7.class)) {
				msg.setReadonly(FuelName.C7);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_D1.class)) {
				msg.setReadonly(FuelName.D1);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_D1D2.class)) {
				msg.setReadonly(FuelName.D1D2);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_D2.class)) {
				msg.setReadonly(FuelName.D2);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_M1.class)) {
				msg.setReadonly(FuelName.M1);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_M1M2.class)) {
				msg.setReadonly(FuelName.M1M2);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_M2.class)) {
				msg.setReadonly(FuelName.M2);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_M3.class)) {
				msg.setReadonly(FuelName.M3);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_M3M4.class)) {
				msg.setReadonly(FuelName.M3M4);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_M4.class)) {
				msg.setReadonly(FuelName.M4);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_Non.class)) {
				msg.setReadonly(FuelName.Non);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_O1a.class)) {
				msg.setReadonly(FuelName.O1A);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_O1ab.class)) {
				msg.setReadonly(FuelName.O1AB);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_O1b.class)) {
				msg.setReadonly(FuelName.O1B);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_S1.class)) {
				msg.setReadonly(FuelName.S1);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_S2.class)) {
				msg.setReadonly(FuelName.S2);
				serialized = true;
			}
			else if(m_fuel.m_defaultFuelType.isAssignableFrom(Cwfgm_Fuel_S3.class)) {
				msg.setReadonly(FuelName.S3);
				serialized = true;
			}
		}
		
		if (!serialized) {
			CcwfgmFuel.FuelData.Builder data = CcwfgmFuel.FuelData.newBuilder();
			
			data.setName(m_name);
			data.setFuel((FbpFuel) m_fuel.serialize(options));
			
			msg.setData(data.build());
		}

		return msg.build();
	}

	@Override
	public CwfgmFuel deserialize(Message proto) {
		CcwfgmFuel msgRead;
		
		try {
			msgRead = (CcwfgmFuel)proto;
		} catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasData()) {
			CcwfgmFuel.FuelData msg = msgRead.getData();
			Cwfgm_Fuel fuel = new Cwfgm_Fuel();
			
			if(msgRead.getVersion() != 1)
				throw new IllegalArgumentException();
			
			FuelName fn = msgRead.getData().getFuel().getDefaultFuelType();
			
			try { 
				getFuel(fn, fuel); 
			} catch (IllegalArgumentException e) {
				fuel.m_name = msg.getName();
				fuel.m_fuel.deserialize(msg.getFuel());
			}

			return fuel;

		}
		else
		{
			FuelName fn = msgRead.getReadonly();	
			Cwfgm_Fuel fuel = null;
			
			getFuel(fn, fuel);
			
			return new Cwfgm_Fuel(fuel);
		}
	}
	
	private void getFuel(FuelName fn, Cwfgm_Fuel fuel) {
		switch(fn) {
			case C1:
				fuel = new Cwfgm_Fuel_C1();
				break;
			case C2:
				fuel = new Cwfgm_Fuel_C2();
				break;
			case C3:
				fuel = new Cwfgm_Fuel_C3();
				break;
			case C4:
				fuel = new Cwfgm_Fuel_C4();
				break;
			case C5:
				fuel = new Cwfgm_Fuel_C5();
				break;
			case C6:
				fuel = new Cwfgm_Fuel_C6();
				break;
			case C7:
				fuel = new Cwfgm_Fuel_C7();
				break;
			case D1:
				fuel = new Cwfgm_Fuel_D1();
				break;
			case D1D2:
				fuel = new Cwfgm_Fuel_D1D2();
				break;
			case D2:
				fuel = new Cwfgm_Fuel_D1();
				break;
			case M1:
				fuel = new Cwfgm_Fuel_M1();
				break;
			case M1M2:
				fuel = new Cwfgm_Fuel_M1M2();
				break;
			case M2:
				fuel = new Cwfgm_Fuel_M2();
				break;
			case M3:
				fuel = new Cwfgm_Fuel_M3();
				break;
			case M3M4:
				fuel = new Cwfgm_Fuel_M3M4();
				break;
			case M4:
				fuel = new Cwfgm_Fuel_M4();
				break;
			case Non:
				fuel = new Cwfgm_Fuel_Non();
				break;
			case O1A:
				fuel = new Cwfgm_Fuel_O1a();
				break;
			case O1AB:
				fuel = new Cwfgm_Fuel_O1ab();
				break;
			case O1B:
				fuel = new Cwfgm_Fuel_O1b();
				break;
			case S1:
				fuel = new Cwfgm_Fuel_S1();
				break;
			case S2:
				fuel = new Cwfgm_Fuel_S2();
				break;
			case S3:
				fuel = new Cwfgm_Fuel_S3();
				break;
			default:
				throw new IllegalArgumentException();
		}
	}

	@Override
	public Optional<Boolean> isDirty() {
		// TODO Auto-generated method stub
		return null;
	}
}
