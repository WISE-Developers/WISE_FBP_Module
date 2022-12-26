/***********************************************************************
 * REDapp - SpreadParms_O1.java
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

public class SpreadParms_O1 extends SpreadParms_S1{
	protected static final long serialVersionUID = 1L;
	
	protected double m_curingDegree;	// degree of curing ( 0-1 )

	public SpreadParms_O1() {
		m_curingDegree = -1.0;
	}
	
	public SpreadParms_O1(SpreadParms_O1 toCopy) {
		m_curingDegree = toCopy.m_curingDegree;
	}

	public boolean equals (FuelAttribute cmp){
		SpreadParms_O1 compare = null;
		if(!(cmp instanceof SpreadParms_O1)) return false;
		else compare = (SpreadParms_O1) cmp;
		
		if (!super.equals(compare))
			return false;
		if (m_curingDegree != compare.m_curingDegree)return false;
		return true;
	}
	
	public double curingDegree() { return m_curingDegree; }
	
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS:
			return ca.hss.general.ERROR.SEVERITY_WARNING;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ2_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ31_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ32_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ33_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ40_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ41_DEFAULTS:
			if ((m_a == 190.0) &&
				(m_b == 0.0310) &&
				(m_c == 1.4) &&
				(m_q == 1.00) &&
				(m_bui0 == 1.0) &&
				(m_max_be == 1.000) &&
				(m_curingDegree == 0.6))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS:
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
			if ((m_a == 250.0) &&
				(m_b == 0.0350) &&
				(m_c == 1.7) &&
				(m_q == 1.00) &&
				(m_bui0 == 1.0) &&
				(m_max_be == 1.000) &&
				(m_curingDegree == 0.6))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.O1AB_MATTED_A:
		case FUELCOM_ATTRIBUTE.O1AB_STANDING_A:
			return m_a;

		case FUELCOM_ATTRIBUTE.O1AB_MATTED_B:
		case FUELCOM_ATTRIBUTE.O1AB_STANDING_B:
			return m_b;

		case FUELCOM_ATTRIBUTE.O1AB_MATTED_C:
		case FUELCOM_ATTRIBUTE.O1AB_STANDING_C:
			return m_c;

		case FUELCOM_ATTRIBUTE.CURINGDEGREE:
			return m_curingDegree;
		}
		return super.getAttributeValue(attributeKey);
	}

	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ31_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ32_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ33_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ40_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ41_DEFAULTS:
				m_a = 190.0;
				m_b = 0.0310;
				m_c = 1.4;
				m_q = 1.00;
				m_bui0 = 1.0;
				m_max_be = 1.000;
				m_curingDegree = 0.6;
				break;
	
			case FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS:
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
				m_a = 250.0;
				m_b = 0.0350;
				m_c = 1.7;
				m_q = 1.00;
				m_bui0 = 1.0;
				m_max_be = 1.000;
				m_curingDegree = 0.6;
				break;
	
			case FUELCOM_ATTRIBUTE.O1AB_MATTED_A:
			case FUELCOM_ATTRIBUTE.O1AB_STANDING_A:
				m_a = attribute;
				break;
	
			case FUELCOM_ATTRIBUTE.O1AB_MATTED_B:
			case FUELCOM_ATTRIBUTE.O1AB_STANDING_B:
				m_b = attribute;
				break;
	
			case FUELCOM_ATTRIBUTE.O1AB_MATTED_C:
			case FUELCOM_ATTRIBUTE.O1AB_STANDING_C:
				m_c = attribute;
				break;
	
			case FUELCOM_ATTRIBUTE.CURINGDEGREE:
				if (attribute < 0.0)					break;
				if (attribute > 1.0)					break;
				m_curingDegree = attribute;
				break;
				
			default:
				super.setAttributeValue(attributeKey, attribute);
		}
	}
	
	public short getExternalDefinition() { return (short)FUELCOM_EQUATION.SELECTION_SPREADPARMS_O1; };

	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder builder = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		builder.setVersion((int)SpreadParmsAttribute.serialVersionUID);
		
		SpreadParmsO1.Builder msgRet = SpreadParmsO1.newBuilder();
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
			SpreadParmsO1.Parms.Builder msg = SpreadParmsO1.Parms.newBuilder();

			msg.setVersion(1);
			msg.setA(HSS_Double.of(m_a));
			msg.setB(HSS_Double.of(m_b));
			msg.setC(HSS_Double.of(m_c));
			msg.setQ(HSS_Double.of(m_q));
			msg.setBui0(HSS_Double.of(m_bui0));
			msg.setMaxBe(HSS_Double.of(m_max_be));
			msg.setCuringDegree(HSS_Double.of(m_curingDegree));
			
			msgRet.setParms(msg.build());
		}

		builder.setO1(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_O1 deserialize(Message proto) {
		SpreadParmsO1 msgRead;
		
		try {
			msgRead = (SpreadParmsO1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsO1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_a = HSS_Double.from(msg.getA());
			m_b = HSS_Double.from(msg.getB());
			m_c = HSS_Double.from(msg.getC());
			m_q = HSS_Double.from(msg.getQ());
			m_bui0 = HSS_Double.from(msg.getBui0());
			m_max_be = HSS_Double.from(msg.getMaxBe());
			m_curingDegree = HSS_Double.from(msg.getCuringDegree());
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
