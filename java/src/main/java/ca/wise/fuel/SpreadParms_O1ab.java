/***********************************************************************
 * REDapp - SpreadParms_O1ab.java
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

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.hss.math.HSS_Double;
import ca.wise.fuel.proto.*;

import static ca.wise.fbp.SCENARIO_OPTION.GRASSPHENOLOGY;

import java.util.Optional;

public class SpreadParms_O1ab extends SpreadParms_O1{
	protected static final long serialVersionUID = 1L;
	
	private double m_o1ab_standing_a;
	private double m_o1ab_standing_b;
	private double m_o1ab_standing_c;
	public static final short USE_GRASSPHENOLOGY = ((short)(1 << GRASSPHENOLOGY));
	
	public SpreadParms_O1ab(){
		m_o1ab_standing_a = -1.0;
		m_o1ab_standing_b = -1.0;
		m_o1ab_standing_c = -1.0;
	}
	
	public SpreadParms_O1ab(SpreadParms_O1ab toCopy) {
		m_o1ab_standing_a = toCopy.m_o1ab_standing_a;
		m_o1ab_standing_b = toCopy.m_o1ab_standing_b;
		m_o1ab_standing_c = toCopy.m_o1ab_standing_c;
	}
	
	public boolean equals (FuelAttribute cmp){
		SpreadParms_O1ab compare = null;
		if(!(cmp instanceof SpreadParms_O1ab)) return false;
		else compare = (SpreadParms_O1ab) cmp;

		if (m_o1ab_standing_a != compare.m_o1ab_standing_a)	return false;
		if (m_o1ab_standing_b != compare.m_o1ab_standing_b)	return false;
		if (m_o1ab_standing_c != compare.m_o1ab_standing_c)	return false;
		return super.equals(compare);
	}
	
	public double a(int flag) {
		if (flag == USE_GRASSPHENOLOGY)
			return m_o1ab_standing_a;
		return m_a;
	}
	
	public double b(int flag) {
		if (flag == USE_GRASSPHENOLOGY)
			return m_o1ab_standing_b;
		return m_b;
	}
	
	public double c(int flag) {
		if (flag == USE_GRASSPHENOLOGY)
			return m_o1ab_standing_c;
		return m_c;
	}
	
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ2_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ31_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ32_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ33_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ40_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ41_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ15_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ30_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ43_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ44_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ46_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ50_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ53_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ62_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ63_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ65_DEFAULTS:
			return ca.hss.general.ERROR.SEVERITY_WARNING;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS:
			if (!((m_o1ab_standing_a == 190.0) &&
				(m_o1ab_standing_b == 0.0310) &&
				(m_o1ab_standing_c == 0.0310)))
				return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS:
			if (!((m_o1ab_standing_a == 250.0) &&
				(m_o1ab_standing_b == 0.0350) &&
				(m_o1ab_standing_c == 1.7)))
				return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1AB_DEFAULTS:
			if ((m_a == 190.0) &&
				(m_b == 0.0310) &&
				(m_c == 1.4) &&
				(m_o1ab_standing_a == 250.0) &&
				(m_o1ab_standing_b == 0.0350) &&
				(m_o1ab_standing_c == 1.7) &&
				(m_q == 1.00) &&
				(m_bui0 == 1.0) &&
				(m_max_be == 1.000) &&
				(m_curingDegree == 0.6))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;


		case FUELCOM_ATTRIBUTE.O1AB_STANDING_A:
			return m_o1ab_standing_a;

		case FUELCOM_ATTRIBUTE.O1AB_STANDING_B:
			return m_o1ab_standing_b;
			
		case FUELCOM_ATTRIBUTE.O1AB_STANDING_C:
			return m_o1ab_standing_c;
		}
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS:
			m_o1ab_standing_a = 190.0;
			m_o1ab_standing_b = 0.0310;
			m_o1ab_standing_c = 1.4;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS:
			m_o1ab_standing_a = 250.0;
			m_o1ab_standing_b = 0.0350;
			m_o1ab_standing_c = 1.7;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1AB_DEFAULTS:
			m_a = m_o1ab_standing_a = 190.0;
			m_b = m_o1ab_standing_b = 0.0310;
			m_c = m_o1ab_standing_c = 1.4;
			m_o1ab_standing_a = 250.0;
			m_o1ab_standing_b = 0.0350;
			m_o1ab_standing_c = 1.7;
			m_q = 1.00;
			m_bui0 = 1.0;
			m_max_be = 1.000;
			m_curingDegree = 0.6;
			break;

		case FUELCOM_ATTRIBUTE.O1AB_STANDING_A:
			m_o1ab_standing_a = attribute;
			break;

		case FUELCOM_ATTRIBUTE.O1AB_STANDING_B:
			m_o1ab_standing_b = attribute;
			break;

		case FUELCOM_ATTRIBUTE.O1AB_STANDING_C:
			m_o1ab_standing_c = attribute;
			break;
			
		default:
			super.setAttributeValue(attributeKey, attribute);
		}
	}
	
	public short getExternalDefinition() { return (short)FUELCOM_EQUATION.SELECTION_SPREADPARMS_O1AB; };

	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder builder = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		builder.setVersion((int)SpreadParmsAttribute.serialVersionUID);
		
		SpreadParmsO1ab.Builder msgRet = SpreadParmsO1ab.newBuilder();
		msgRet.setVersion(1);

		boolean serialized = false;
		if(!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ64_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz64);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1B);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_O1AB_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1AB);
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
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1B);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ31_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz31);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ32_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz32);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ33_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz33);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ40_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz40);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ41_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz41);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ15_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz15);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ30_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz30);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ43_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz43);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ44_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz44);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ46_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz46);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ50_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz50);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ53_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz53);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ62_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz62);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ63_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz63);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ65_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz65);
				serialized = true;
			}
		}

		if(!serialized) {
			SpreadParmsO1ab.Parms.Builder msg = SpreadParmsO1ab.Parms.newBuilder();

			msg.setVersion(1);
			msg.setA(HSS_Double.of(m_a));
			msg.setB(HSS_Double.of(m_b));
			msg.setC(HSS_Double.of(m_c));
			msg.setQ(HSS_Double.of(m_q));
			msg.setBui0(HSS_Double.of(m_bui0));
			msg.setMaxBe(HSS_Double.of(m_max_be));
			msg.setCuringDegree(HSS_Double.of(m_curingDegree));
			msg.setO1AbStandingA(HSS_Double.of(m_o1ab_standing_a));
			msg.setO1AbStandingB(HSS_Double.of(m_o1ab_standing_b));
			msg.setO1AbStandingC(HSS_Double.of(m_o1ab_standing_c));
			
			msgRet.setParms(msg.build());
		}

		builder.setO1Ab(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_O1ab deserialize(Message proto) {
		SpreadParmsO1ab msgRead;
		
		try {
			msgRead = (SpreadParmsO1ab)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsO1ab.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_a = HSS_Double.from(msg.getA());
			m_b = HSS_Double.from(msg.getB());
			m_c = HSS_Double.from(msg.getC());
			m_q = HSS_Double.from(msg.getQ());
			m_bui0 = HSS_Double.from(msg.getBui0());
			m_max_be = HSS_Double.from(msg.getMaxBe());
			m_curingDegree = HSS_Double.from(msg.getCuringDegree());
			m_o1ab_standing_a = HSS_Double.from(msg.getO1AbStandingA());
			m_o1ab_standing_b = HSS_Double.from(msg.getO1AbStandingB());
			m_o1ab_standing_c = HSS_Double.from(msg.getO1AbStandingC());
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
}
