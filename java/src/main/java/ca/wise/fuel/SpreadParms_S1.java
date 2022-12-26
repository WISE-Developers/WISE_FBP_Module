/***********************************************************************
 * REDapp - SpreadParms_S1.java
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
import ca.wise.fuel.proto.*;
import ca.wise.serialize.SerializeProtoOptions;
import ca.hss.math.HSS_Double;

public class SpreadParms_S1 extends SpreadParmsAttribute {
	protected static final long serialVersionUID = 1L;
	
	protected double m_a;
	protected double m_b;
	protected double m_c;

	protected double m_q;		// proportion of max spread rate
	protected double m_bui0;		// the average bui for the fuel type
	protected double m_max_be;	// maximum effect of bui on the ROS.

	public SpreadParms_S1() {
		m_a = -1.0;
		m_b = -1.0;
		m_c = -1.0;
		m_q = -1.0;
		m_bui0 = -1.0;
		m_max_be = -1.0;
	}
	
	public SpreadParms_S1(SpreadParms_S1 toCopy) {
		m_a = toCopy.m_a;
		m_b = toCopy.m_b;
		m_c = toCopy.m_c;
		m_q = toCopy.m_q;
		m_bui0 = toCopy.m_bui0;
		m_max_be = toCopy.m_max_be;
	}

	public boolean equals(FuelAttribute cmp) {
		SpreadParms_S1 compare = null;
		if(!(cmp instanceof SpreadParms_S1)) return false;
		else compare = (SpreadParms_S1) cmp;
		
		if (m_a != compare.m_a)						return false;
		if (m_b != compare.m_b)						return false;
		if (m_c != compare.m_c)						return false;
		if (m_q != compare.m_q)						return false;
		if (m_bui0 != compare.m_bui0)				return false;
		if (m_max_be != compare.m_max_be)			return false;
		return true;
	}
	
	public double a(int flag) { return m_a; };
	public double b(int flag) { return m_b; };
	public double c(int flag) { return m_c; };
	public double q() { return m_q; };
	public double bui0() { return m_bui0; };
	public double maxBE() { return m_max_be; };
	public double height() { return 0.0; };
	public double cbh() { return 0.0; };
	public double cfl() { return 0.0; };
	public double curingDegree() { return -1.0; }
	public double pc() { return -1.0; }
	
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ64_DEFAULTS:
			if ((m_a == 75.0) &&
				(m_b == 0.0297) &&
				(m_c == 1.3) &&
				(m_q == 0.75) &&
				(m_bui0 == 38.0) &&
				(m_max_be == 1.460))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS:
			if ((m_a == 40.0) &&
				(m_b == 0.0438) &&
				(m_c == 1.7) &&
				(m_q == 0.75) &&
				(m_bui0 == 63.0) &&
				(m_max_be == 1.256))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS:
			if ((m_a == 55.0) &&
				(m_b == 0.0829) &&
				(m_c == 3.2) &&
				(m_q == 0.75) &&
				(m_bui0 == 31.0) &&
				(m_max_be == 1.590))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.A:
			return m_a;

		case FUELCOM_ATTRIBUTE.B:
			return m_b;

		case FUELCOM_ATTRIBUTE.C:
			return m_c;

		case FUELCOM_ATTRIBUTE.Q:
			return m_q;

		case FUELCOM_ATTRIBUTE.MAXBE:
			return m_max_be;

		case FUELCOM_ATTRIBUTE.BUI0:
			return m_bui0;

		case FUELCOM_ATTRIBUTE.CBH:
			return 0.0;

		case FUELCOM_ATTRIBUTE.CFL:
			return 0.0;

		case FUELCOM_ATTRIBUTE.TREE_HEIGHT:
			return 0.0;
		}
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ64_DEFAULTS:
			m_a = 75.0;
			m_b = 0.0297;
			m_c = 1.3;
			m_q = 0.75;
			m_bui0 = 38.0;
			m_max_be = 1.460;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS:
			m_a = 40.0;
			m_b = 0.0438;
			m_c = 1.7;
			m_q = 0.75;
			m_bui0 = 63.0;
			m_max_be = 1.256;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS:
			m_a = 55.0;
			m_b = 0.0829;
			m_c = 3.2;
			m_q = 0.75;
			m_bui0 = 31.0;
			m_max_be = 1.590;
			break;

		case FUELCOM_ATTRIBUTE.A:
			m_a = attribute;
			break;

		case FUELCOM_ATTRIBUTE.B:
			m_b = attribute;
			break;

		case FUELCOM_ATTRIBUTE.C:
			m_c = attribute;
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
		
		default:
			super.setAttributeValue(attributeKey, attribute);
		}
	}
	
	public short getExternalDefinition() { return (short)FUELCOM_EQUATION.SELECTION_SPREADPARMS_C1; };

	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder builder = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		builder.setVersion((int)SpreadParmsAttribute.serialVersionUID);
		
		SpreadParmsS1.Builder msgRet = SpreadParmsS1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ64_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz64);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S3);
				serialized = true;
			}
		}

		if(!serialized) {
			SpreadParmsS1.Parms.Builder msg = SpreadParmsS1.Parms.newBuilder();

			msg.setVersion(1);
			msg.setA(HSS_Double.of(m_a));
			msg.setB(HSS_Double.of(m_b));
			msg.setC(HSS_Double.of(m_c));
			msg.setQ(HSS_Double.of(m_q));
			msg.setBui0(HSS_Double.of(m_bui0));
			msg.setMaxBe(HSS_Double.of(m_max_be));
			
			msgRet.setParms(msg.build());
		}

		builder.setS1(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_S1 deserialize(Message proto) {
		SpreadParmsS1 msgRead;
		
		try {
			msgRead = (SpreadParmsS1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsS1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_a = HSS_Double.from(msg.getA());
			m_b = HSS_Double.from(msg.getB());
			m_c = HSS_Double.from(msg.getC());
			m_q = HSS_Double.from(msg.getQ());
			m_bui0 = HSS_Double.from(msg.getBui0());
			m_max_be = HSS_Double.from(msg.getMaxBe());
		}
		else {
			FuelName def = msgRead.getDefault();

			short val = GetDefaultValue(def);

			if(val != (short) -1)
				setAttributeValue(val, 0.0);
			else
				throw new IllegalArgumentException();
		}
		
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
			val = (short) -1;
		}

		return val;
	}
}
