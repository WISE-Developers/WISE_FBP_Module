/***********************************************************************
 * REDapp - LB_C1.java
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

public class LB_C1 extends LBAttribute {
	protected static final long serialVersionUID = 1L;
	
	private double m_init;
	private double m_multiplier;
	private double m_exp_multiplier;
	private double m_power;
	
	public LB_C1() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C1_DEFAULTS, 0.0);
	}

	public LB_C1(final LB_C1 other) {
		m_init = other.m_init;
		m_multiplier = other.m_multiplier;
		m_exp_multiplier = other.m_exp_multiplier;
		m_power = other.m_power;
	}
	
	public Object clone() throws CloneNotSupportedException {
		LB_C1 other = (LB_C1)super.clone();
		return other;
	}

	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.LB_C1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C4_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C5_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C6_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C7_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_D1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_D2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M4_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_S1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_S2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_S3_DEFAULTS:		if ((m_init == 1.0) &&
															(m_multiplier == 8.729) &&
															(m_exp_multiplier == 0.030) &&
															(m_power == 2.155))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.LB_INIT:				return m_init;
			case FUELCOM_ATTRIBUTE.LB_MULTIPLIER:		return m_multiplier;
			case FUELCOM_ATTRIBUTE.LB_EXP_MULTIPLIER:	return m_exp_multiplier;
			case FUELCOM_ATTRIBUTE.LB_POWER:			return m_power;	
		}
		
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.LB_C1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C4_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C5_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C6_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_C7_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_D1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_D2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_M4_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_S1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_S2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_S3_DEFAULTS:		m_init = 1.0;
														m_multiplier = 8.729;
														m_exp_multiplier = 0.030;
														m_power = 2.155;				return;
			case FUELCOM_ATTRIBUTE.LB_INIT:				m_init = attribute;				return;
			case FUELCOM_ATTRIBUTE.LB_MULTIPLIER:		m_multiplier = attribute;		return;
			case FUELCOM_ATTRIBUTE.LB_EXP_MULTIPLIER:	m_exp_multiplier = attribute;	return;
			case FUELCOM_ATTRIBUTE.LB_POWER:			m_power = attribute;			return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_LB_C1;
	}
	
	@Override
	public double LB(double WSV) {
		Double lb;
		lb = m_init + m_multiplier * Math.pow(1.0 - Math.exp((0.0 - m_exp_multiplier) * WSV), m_power);	// equation 79
		return lb;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof LB_C1) {
			LB_C1 cother = (LB_C1)other;
			return m_init == cother.m_init &&
					   m_multiplier == cother.m_multiplier &&
					   m_exp_multiplier == cother.m_exp_multiplier &&
					   m_power == cother.m_power;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.LbAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.LbAttribute.Builder builder = ca.wise.fuel.proto.LbAttribute.newBuilder();
		builder.setVersion((int)LBAttribute.serialVersionUID);
		
		LbC1.Builder msgRet = LbC1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C5_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C5);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C6_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C6);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_C7_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C7);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_D1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_D2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_M1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_M2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_S1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_S2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_S3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S3);
				serialized = true;
			}
		}

		if(!serialized) {
			LbC1.Parms.Builder msg = LbC1.Parms.newBuilder();

			msg.setVersion(1);
			msg.setInit(HSS_Double.of(m_init));
			msg.setMultiplier(HSS_Double.of(m_multiplier));
			msg.setExpMultiplier(HSS_Double.of(m_exp_multiplier));
			msg.setPower(HSS_Double.of(m_power));
			
			msgRet.setParms(msg.build());
		}

		builder.setC1(msgRet);
		return builder.build();
	}

	@Override
	public LB_C1 deserialize(Message proto) {
		LbC1 msgRead;
		
		try {
			msgRead = (LbC1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			LbC1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_init = HSS_Double.from(msg.getInit());
			m_multiplier = HSS_Double.from(msg.getMultiplier());
			m_exp_multiplier = HSS_Double.from(msg.getExpMultiplier());
			m_power = HSS_Double.from(msg.getPower());
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
	
	private short GetDefaultValue(FuelName def) {
		short val;

		switch (def) {
		case C1:
			val = FUELCOM_ATTRIBUTE.LB_C1_DEFAULTS;
			break;

		case C2:
			val = FUELCOM_ATTRIBUTE.LB_C2_DEFAULTS;
			break;

		case C3:
			val = FUELCOM_ATTRIBUTE.LB_C3_DEFAULTS;
			break;

		case C4:
			val = FUELCOM_ATTRIBUTE.LB_C4_DEFAULTS;
			break;

		case C5:
			val = FUELCOM_ATTRIBUTE.LB_C5_DEFAULTS;
			break;

		case C6:
			val = FUELCOM_ATTRIBUTE.LB_C6_DEFAULTS;
			break;

		case C7:
			val = FUELCOM_ATTRIBUTE.LB_C7_DEFAULTS;
			break;

		case D1:
			val = FUELCOM_ATTRIBUTE.LB_D1_DEFAULTS;
			break;

		case D2:
			val = FUELCOM_ATTRIBUTE.LB_D2_DEFAULTS;
			break;

		case M1:
			val = FUELCOM_ATTRIBUTE.LB_M1_DEFAULTS;
			break;

		case M2:
			val = FUELCOM_ATTRIBUTE.LB_M2_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.LB_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.LB_M4_DEFAULTS;
			break;

		case O1A:
			val = FUELCOM_ATTRIBUTE.LB_O1A_DEFAULTS;
			break;

		case O1B:
			val = FUELCOM_ATTRIBUTE.LB_O1B_DEFAULTS;
			break;

		case S1:
			val = FUELCOM_ATTRIBUTE.LB_S1_DEFAULTS;
			break;

		case S2:
			val = FUELCOM_ATTRIBUTE.LB_S2_DEFAULTS;
			break;

		case S3:
			val = FUELCOM_ATTRIBUTE.LB_S3_DEFAULTS;
			break;

		default:
			val = (short) -1;
		}

		return val;
	}
}
