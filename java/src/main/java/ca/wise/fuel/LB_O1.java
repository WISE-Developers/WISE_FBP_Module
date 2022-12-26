/***********************************************************************
 * REDapp - LB_O1.java
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

public class LB_O1 extends LBAttribute {
	protected static final long serialVersionUID = 1L;
	
	private double m_init;
	private double m_power;
	
	public LB_O1() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.LB_O1A_DEFAULTS, 0.0);
	}

	public LB_O1(final LB_O1 other) {
		m_init = other.m_init;
	}
	
	public Object clone() throws CloneNotSupportedException {
		LB_O1 other = (LB_O1)super.clone();
		return other;
	}

	public double getAttributeValue(short attributeKey) {
			switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.LB_O1A_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_O1B_DEFAULTS:	if ((m_init == 1.1) &&
														(m_power == 0.464))
														return 1.0;
													return 0.0;
			case FUELCOM_ATTRIBUTE.LB_INIT:			return m_init;
			case FUELCOM_ATTRIBUTE.LB_POWER:		return m_power;
		}
		
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.LB_O1A_DEFAULTS:
			case FUELCOM_ATTRIBUTE.LB_O1B_DEFAULTS:	m_init = 1.1;
													m_power = 0.464;		return;
			case FUELCOM_ATTRIBUTE.LB_INIT:			m_init = attribute;		return;
			case FUELCOM_ATTRIBUTE.LB_POWER:		m_power = attribute;	return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_LB_O1;
	}
	
	@Override
	public double LB(double WSV) {
		Double lb;
		lb = (WSV < 1.0) ? 1.0 : m_init * Math.pow(WSV, m_power);	// equations 80, 81... now equations 80a, 80b in the August 2004 article
		return lb; 
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof LB_O1) {
			LB_O1 cother = (LB_O1)other;
			return m_init == cother.m_init &&
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
		
		LbO1.Builder msgRet = LbO1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_O1A_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.LB_O1B_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1B);
				serialized = true;
			}
		}
	
		if(!serialized) {
			LbO1.Parms.Builder msg = LbO1.Parms.newBuilder();

			msg.setVersion(1);
			msg.setInit(HSS_Double.of(m_init));
			msg.setPower(HSS_Double.of(m_power));
			
			msgRet.setParms(msg.build());
		}

		builder.setO1(msgRet);
		return builder.build();
	}

	@Override
	public LB_O1 deserialize(Message proto) {
		LbO1 msgRead;
		
		try {
			msgRead = (LbO1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			LbO1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_init = HSS_Double.from(msg.getInit());
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
