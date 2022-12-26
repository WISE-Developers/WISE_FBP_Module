/***********************************************************************
 * REDapp - SpreadParms_Mixed.java
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

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.hss.math.HSS_Double;
import ca.wise.fuel.proto.*;

public class SpreadParms_Mixed extends SpreadParmsAttribute {
	protected static final long serialVersionUID = 1L;
	
	protected double m_q;		// proportion of max spread rate
	protected double m_bui0;		// the average bui for the fuel type
	protected double m_max_be;	// maximum effect of bui on the ROS.

	protected double m_height;	// stand height (m)
	protected double m_cbh;		// height to live crown base
	protected double m_cfl;		// crown fuel load

	double m_pc;
	Cwfgm_Fuel_C2 m_C2;
	Cwfgm_Fuel_D1 m_D1;

	public SpreadParms_Mixed() {
		m_q = -1.0;
		m_bui0 = -1.0;
		m_max_be = -1.0;
		m_height = -1.0;
		m_cbh = -1.0;
		m_cfl = -1.0;
		m_pc = 0.5;
	}
	
	public SpreadParms_Mixed(SpreadParms_Mixed toCopy) throws CloneNotSupportedException {
		m_q = toCopy.m_q;
		m_bui0 = toCopy.m_bui0;
		m_max_be = toCopy.m_max_be;
		m_height = toCopy.m_height;
		m_cbh = toCopy.m_cbh;
		m_cfl = toCopy.m_cfl;
		m_pc = toCopy.m_pc;
		
		if(toCopy.m_C2 == null || toCopy.m_D1 == null)
			throw new IllegalArgumentException();
		
		m_C2 = toCopy.m_C2.clone();
		m_D1 = toCopy.m_D1.clone();
		
		if(m_C2 == null || m_D1 == null)
			throw new IllegalArgumentException();
	}
	
	public boolean equals (FuelAttribute cmp){
		SpreadParms_Mixed compare = null;
		if(!(cmp instanceof SpreadParms_Mixed)) return false;
		else compare = (SpreadParms_Mixed) cmp;

		if (m_q != compare.m_q)						return false;
		if (m_bui0 != compare.m_bui0)				return false;
		if (m_max_be != compare.m_max_be)			return false;
		if (m_height != compare.m_height)			return false;
		if (m_cbh != compare.m_cbh)					return false;
		if (m_cfl != compare.m_cfl)					return false;
		if (m_pc != compare.m_pc)					return false;
		return true;
	}

	public double a(int flag) { return -1.0; };
	public double b(int flag) { return -1.0; };
	public double c(int flag) { return -1.0; };
	public double q() { return m_q; }
	public double bui0() { return m_bui0; }
	public double maxBE() { return m_max_be; }
	public double height() { return m_height; }
	public double cbh() { return m_cbh; }
	public double cfl() { return m_cfl; }
	public double curingDegree() { return -1.0; };
	public double pc() { return m_pc; }
	
	public CwfgmFuel c2() { return m_C2; }
	public CwfgmFuel d1() { return m_D1; }

	public void setC2(CwfgmFuel C2) throws CloneNotSupportedException { m_C2 = (Cwfgm_Fuel_C2)C2.clone(); }
	public void setD1(CwfgmFuel D1) throws CloneNotSupportedException { m_D1 = (Cwfgm_Fuel_D1)D1.clone(); }
	
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_M2_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ54_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ69_DEFAULTS:
			if ((m_q == 0.80) &&
				(m_bui0 == 50.0) &&
				(m_max_be == 1.250) &&
				(m_height == 13.0) &&
				(m_cbh == 6.0) &&
				(m_cfl == 0.80))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.Q:
			return m_q;

		case FUELCOM_ATTRIBUTE.MAXBE:
			return m_max_be;

		case FUELCOM_ATTRIBUTE.BUI0:
			return m_bui0;

		case FUELCOM_ATTRIBUTE.CBH:
			return m_cbh;

		case FUELCOM_ATTRIBUTE.CFL:
			return m_cfl;

		case FUELCOM_ATTRIBUTE.TREE_HEIGHT:
			return m_height;

		case FUELCOM_ATTRIBUTE.PC:
			return m_pc;
		
		default:
			return super.getAttributeValue(attributeKey);
		}
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_M2_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ54_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ69_DEFAULTS:
			m_q = 0.80;
			m_bui0 = 50.0;
			m_max_be = 1.250;
			m_height = 13.0;
			m_cbh = 6.0;
			m_cfl = 0.80;
			break;

		case FUELCOM_ATTRIBUTE.Q:
			m_q = attribute;
			break;

		case FUELCOM_ATTRIBUTE.MAXBE:
			if (attribute < 0.0)					break;
			if (attribute > 2.0)					break;
			m_max_be = attribute;
			break;

		case FUELCOM_ATTRIBUTE.BUI0:
			if (attribute < 0.0)					break;
			if (attribute > 200.0)					break;
			m_bui0 = attribute;
			break;

		case FUELCOM_ATTRIBUTE.TREE_HEIGHT:
			if ((attribute < 0.0) &&
				(attribute != -1.0))				break;
			if (attribute > 50.0)					break;
			m_height = attribute;
			break;

		case FUELCOM_ATTRIBUTE.CBH:
			if (attribute < 0.0)					break;
			if (attribute > 50.0)					break;
			m_cbh = attribute;
			break;

		case FUELCOM_ATTRIBUTE.CFL:
			if (attribute < 0.0)					break;
			if (attribute > 5.0)					break;
			m_cfl = attribute;
			break;

		case FUELCOM_ATTRIBUTE.PC:
			if (attribute < 0.0)					break;
			if (attribute > 1.0)					break;
			m_pc = attribute;
			break;
		
		default:
			super.setAttributeValue(attributeKey, attribute);
		}
	}
	
	public short getExternalDefinition() { return (short)FUELCOM_EQUATION.SELECTION_SPREADPARMS_MIXED; };
	
	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options)  {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder builder = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		builder.setVersion((int)SpreadParmsAttribute.serialVersionUID);
		
		SpreadParmsMixed.Builder msgRet = SpreadParmsMixed.newBuilder();
		msgRet.setVersion((int)serialVersionUID);
		
		boolean serialized = false;
		
		if(!options.useVerboseOutput()) {
			SpreadParmsMixed.DefaultParms.Builder msgDef = null;
			
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_M1_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixed.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.M1);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_M2_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixed.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.M2);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ54_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixed.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.Nz54);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ69_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixed.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.Nz69);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			
			if((msgDef != null) && (m_pc != 0.5)) {
				msgDef.setPc(HSS_Double.of(m_pc * 100.0));
				msgRet.setDefault(msgDef.build());
			}
		}
		
		if(!serialized) {
			SpreadParmsMixed.Parms.Builder msg = SpreadParmsMixed.Parms.newBuilder();

			msg.setVersion(1);
			msg.setQ(HSS_Double.of(m_q));
			msg.setBui0(HSS_Double.of(m_bui0));
			msg.setMaxBe(HSS_Double.of(m_max_be));
			msg.setHeight(HSS_Double.of(m_height));
			msg.setCbh(HSS_Double.of(m_cbh));
			msg.setCfl(HSS_Double.of(m_cfl));
			msg.setPc(HSS_Double.of(m_pc * 100.0));
			
			msgRet.setParms(msg.build());
		}

		builder.setMixed(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_Mixed deserialize(Message proto) {
		SpreadParmsMixed msgRead;
		
		try {
			msgRead = (SpreadParmsMixed)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsMixed.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_q = HSS_Double.from(msg.getQ());
			m_bui0 = HSS_Double.from(msg.getBui0());
			m_max_be = HSS_Double.from(msg.getMaxBe());
			m_height = HSS_Double.from(msg.getHeight());
			m_cbh = HSS_Double.from(msg.getCbh());
			m_cfl = HSS_Double.from(msg.getCfl());
			m_pc = HSS_Double.from(msg.getPc()) * 0.01;
		}
		else {
			SpreadParmsMixed.DefaultParms msgDef = msgRead.getDefault();
			FuelName def = msgDef.getDefault();

			short val = GetDefaultValue(def);

			if(val != (short) -1)
				setAttributeValue(val, 0.0);
			else
				throw new IllegalArgumentException();
			
			if(msgDef.hasPc())
				m_pc = msgDef.getPc().getValue() * 0.01;
		}
		
		if(m_C2 == null || m_D1 == null)
			throw new IllegalArgumentException();
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
	
	protected short GetDefaultValue(FuelName def) {
		short val;

		switch (def) {
		case M1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M1_DEFAULTS;
			break;

		case M2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M2_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M4_DEFAULTS;
			break;

		case Nz54:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ54_DEFAULTS;
			break;

		case Nz69:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ69_DEFAULTS;
			break;

		case Nz2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ2_DEFAULTS;
			break;

		case Nz15:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ15_DEFAULTS;
			break;

		case Nz30:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ30_DEFAULTS;
			break;

		case Nz31:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ31_DEFAULTS;
			break;

		case Nz32:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ32_DEFAULTS;
			break;

		case Nz33:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ33_DEFAULTS;
			break;

		case Nz40:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ40_DEFAULTS;
			break;

		case Nz41:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ41_DEFAULTS;
			break;

		case Nz43:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ43_DEFAULTS;
			break;

		case Nz44:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ44_DEFAULTS;
			break;

		case Nz46:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ46_DEFAULTS;
			break;

		case Nz50:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ50_DEFAULTS;
			break;

		case Nz53:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ53_DEFAULTS;
			break;

		case Nz62:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ62_DEFAULTS;
			break;

		case Nz63:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ63_DEFAULTS;
			break;

		case Nz64:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ64_DEFAULTS;
			break;

		case Nz65:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ65_DEFAULTS;
			break;

		case O1A:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS;
			break;

		case O1B:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS;
			break;

		case O1AB:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_O1AB_DEFAULTS;
			break;

		case S1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS;
			break;

		case S2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS;
			break;

		case S3:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS;
			break;

		case Nz57:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ57_DEFAULTS;
			break;

		case Nz58:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS;
			break;

		case Nz56:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ56_DEFAULTS;
			break;

		case C1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C1_DEFAULTS;
			break;
			
		case C2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C2_DEFAULTS;
			break;

		case C3:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C3_DEFAULTS;
			break;

		case C4:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C4_DEFAULTS;
			break;

		case C5:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C5_DEFAULTS;
			break;

		case C7:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C7_DEFAULTS;
			break;

		case Nz45:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ45_DEFAULTS;
			break;

		case Nz47:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ47_DEFAULTS;
			break;

		case Nz51:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ51_DEFAULTS;
			break;

		case Nz52:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ52_DEFAULTS;
			break;

		case Nz55:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ55_DEFAULTS;
			break;

		case D1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_D1_DEFAULTS;
			break;

		case D2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_D2_DEFAULTS;
			break;

		case Nz68:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ68_DEFAULTS;
			break;

		case C6:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C6_DEFAULTS;
			break;

		case Nz60:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ60_DEFAULTS;
			break;

		case Nz66:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ66_DEFAULTS;
			break;

		case Nz67:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ67_DEFAULTS;
			break;

		case Nz71:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ71_DEFAULTS;
			break;


		default:
			val = -1;
		}

		return val;
	}
}
