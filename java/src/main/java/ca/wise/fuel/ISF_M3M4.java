/***********************************************************************
 * REDapp - ISF_M3M4.java
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

public class ISF_M3M4 extends ISFAttribute {
	protected static final long serialVersionUID = 1L;
	
	private double m_m_a;
	private double m_m_b;
	private double m_m_c;
	
	public ISF_M3M4() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS, 0.0);
	}

	public ISF_M3M4(final ISF_M3M4 other) {
		m_m_a = other.m_m_a;
		m_m_b = other.m_m_b;
		m_m_c = other.m_m_c;
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
	
	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS:		if ((m_m_a == 120.0) &&
															(m_m_b == 0.0572) &&
															(m_m_c == 1.4))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS:		if ((m_m_a == 100.0) &&
															(m_m_b == 0.0404) &&
															(m_m_c == 1.48))
															return 1.0;
														return 0.0;
			case FUELCOM_ATTRIBUTE.M3M4_C2_A:			return m_m_a;
			case FUELCOM_ATTRIBUTE.M3M4_C2_B:			return m_m_b;
			case FUELCOM_ATTRIBUTE.M3M4_C2_C:			return m_m_c;
			case FUELCOM_ATTRIBUTE.M4_D1_A:		
			case FUELCOM_ATTRIBUTE.M4_D1_B:			
			case FUELCOM_ATTRIBUTE.M4_D1_C:				return 0.0;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS:		m_m_a = 120.0;
														m_m_b = 0.0572;
														m_m_c = 1.4;		return;
			case FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS:		m_m_a = 100.0;
														m_m_b = 0.0404;
														m_m_c = 1.48;		return;
			case FUELCOM_ATTRIBUTE.M3M4_C2_A:			m_m_a = attribute;	return;
			case FUELCOM_ATTRIBUTE.M3M4_C2_B:			m_m_b = attribute;	return;	
			case FUELCOM_ATTRIBUTE.M3M4_C2_C:			m_m_c = attribute;	return;
			case FUELCOM_ATTRIBUTE.M4_D1_A:
			case FUELCOM_ATTRIBUTE.M4_D1_B:	
			case FUELCOM_ATTRIBUTE.M4_D1_C:				return;
		}

		super.setAttributeValue(attributeKey, attribute);
	}

	@Override
	public double ISF(SpreadParmsAttribute sa, int flag, double RSF_C2, double RSF_D1, double SF, double ISZ) {
		double c2_isf = ISF.isf_c1(m_m_a, m_m_b, m_m_c, RSF_C2, 1.0);			// equation 32, August 2004 article
		double d1_isf;

		CwfgmFuel d1 = sa.d1();
		
		if (d1 != null)
			d1_isf = d1.isf(RSF_D1, SF, ISZ, (short)0);
		else {
			d1_isf = 0.0;
		}

		double PC = sa.pc();
	 	double newisf = PC * c2_isf + (1.0 - PC) * d1_isf;			// equation 31, August 2004 article, equations 42b, 42c in the FBP update note
		return newisf;
	}

	@Override
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_ISF_M3M4;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof ISF_M3M4) {
			ISF_M3M4 cother = (ISF_M3M4)other;
			return m_m_a == cother.m_m_a &&
					   m_m_b == cother.m_m_b &&
					   m_m_c == cother.m_m_c;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.IsfAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.IsfAttribute.Builder builder = ca.wise.fuel.proto.IsfAttribute.newBuilder();
		builder.setVersion((int)ISFAttribute.serialVersionUID);
		
		IsfM3M4.Builder msgRet = IsfM3M4.newBuilder();
		msgRet.setVersion(1);

		boolean serialized = false;
		if(!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
				serialized = true;
			}
		}

		if(!serialized) {
			IsfM3M4.Parms.Builder msg = IsfM3M4.Parms.newBuilder();
			msg.setVersion(1);
			msg.setA(HSS_Double.of(m_m_a));
			msg.setB(HSS_Double.of(m_m_b));
			msg.setC(HSS_Double.of(m_m_c));
			msgRet.setParms(msg.build());
		}

		builder.setM3M4(msgRet);
		return builder.build();
	}

	@Override
	public ISF_M3M4 deserialize(Message proto) {
		IsfM3M4 msgRead;
		
		try {
			msgRead = (IsfM3M4)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			IsfM3M4.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
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
		case O1A:
			val = FUELCOM_ATTRIBUTE.ISF_O1A_DEFAULTS;
			break;

		case O1B:
			val = FUELCOM_ATTRIBUTE.ISF_O1B_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS;
			break;

		default:
			val = (short) -1;
		}

		return val;
	}
}
