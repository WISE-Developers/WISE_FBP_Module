/***********************************************************************
 * REDapp - ISF_O1.java
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

public class ISF_O1 extends ISFAttribute {
	protected static final long serialVersionUID = 1L;
	
	private double m_threshold;
	private double m_f1;
	private double m_f2;
	private double m_f3;
	private double m_f4;
	
	public ISF_O1() {
		m_threshold = 0.588;
		m_f1 = 0.005;
		m_f2 = 0.061;
		m_f3 = 0.176;
		m_f4 = 0.02;
	}

	public ISF_O1(final ISF_O1 other) {
		m_threshold = other.m_threshold;
		m_f1 = other.m_f1;
		m_f2 = other.m_f2;
		m_f3 = other.m_f3;
		m_f4 = other.m_f4;
	}
	
	public Object clone() throws CloneNotSupportedException {
		ISF_O1 other = (ISF_O1)super.clone();
		return other;
	}

	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.ISF_O1A_DEFAULTS:
			case FUELCOM_ATTRIBUTE.ISF_O1B_DEFAULTS:	if ((m_threshold == 0.588) &&
															(m_f1 == 0.005) &&
															(m_f2 == 0.061) &&
															(m_f3 == 0.176) &&
															(m_f4 == 0.02))
															return 1.0;
														return 0.0;
			case FUELCOM_ATTRIBUTE.EQ35_THRESHOLD:		return m_threshold;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT1:			return m_f1;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT2:			return m_f2;
			case FUELCOM_ATTRIBUTE.EQ35B_ADDER:			return m_f3;
			case FUELCOM_ATTRIBUTE.EQ35B_MULT1:			return m_f4;
		}
	
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.ISF_O1A_DEFAULTS:
			case FUELCOM_ATTRIBUTE.ISF_O1B_DEFAULTS:	m_threshold = 0.588;
														m_f1 = 0.005;
														m_f2 = 0.061;
														m_f3 = 0.176;
														m_f4 = 0.02;				return;
	
			case FUELCOM_ATTRIBUTE.EQ35_THRESHOLD:	m_threshold = attribute;	return;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT1:		m_f1 = attribute;			return;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT2:		m_f2 = attribute;			return;
			case FUELCOM_ATTRIBUTE.EQ35B_ADDER:		m_f3 = attribute;			return;
			case FUELCOM_ATTRIBUTE.EQ35B_MULT1:		m_f4 = attribute;			return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_ISF_O1;
	}

	@Override
	public double ISF(SpreadParmsAttribute sa, int flag, double RSF_C2, double RSF_D1, double SF, double ISZ) {
		double CF;
		double C = sa.curingDegree();
		
		if (C < m_threshold)
			CF = m_f1 * (Math.exp(m_f2 * C * 100.0) - 1.0);		// equation 35a, August 2004 article
		else
			CF = m_f3 + m_f4 * ((C - m_threshold) * 100.0);		// equation 35b, August 2004 article

		if (CF == 0.0)
			return 0.0;
		else
			return ISF.isf_c1(sa.a(flag), sa.b(flag), sa.c(flag), RSF_C2, CF);
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof ISF_O1) {
			ISF_O1 cother = (ISF_O1)other;
			return m_threshold == cother.m_threshold &&
					   m_f1 == cother.m_f1 &&
					   m_f2 == cother.m_f2 &&
					   m_f3 == cother.m_f3 &&
					   m_f4 == cother.m_f4;
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
		
		IsfO1.Builder msgRet = IsfO1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ISF_O1A_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ISF_O1B_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1B);
				serialized = true;
			}
		}
	
		if(!serialized){
			IsfO1.Parms.Builder msg = IsfO1.Parms.newBuilder();
			msg.setVersion(1);
			msg.setF1(HSS_Double.of(m_f1));
			msg.setF2(HSS_Double.of(m_f2));
			msg.setF3(HSS_Double.of(m_f3));
			msg.setF4(HSS_Double.of(m_f4));
			msg.setThreshold(HSS_Double.of(m_threshold));
			msgRet.setParms(msg.build());
		}

		builder.setO1(msgRet);
		return builder.build();
	}

	@Override
	public ISF_O1 deserialize(Message proto) {
		IsfO1 msgRead;
		
		try {
			msgRead = (IsfO1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			IsfO1.Parms msg = msgRead.getParms();

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
