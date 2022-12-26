/***********************************************************************
 * REDapp - FSI_M4.java
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

import ca.hss.general.OutVariable;
import ca.hss.math.HSS_Double;

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.wise.fuel.proto.*;

public class RSI_M4 extends RSI_StdCalc {
	protected static final long serialVersionUID = 1L;
	
	private double m_m_a;
    private double m_m_b;
    private double m_m_c;
    private double m_d1_a;
    private double m_d1_b;
    private double m_d1_c;
    private double m_p;
	
	public RSI_M4() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS, 0.0);
	}
	
	public RSI_M4(final RSI_M4 other) {
		m_m_a = other.m_m_a;
		m_m_b = other.m_m_b;
		m_m_c = other.m_m_c;
		m_d1_a = other.m_d1_a;
		m_d1_b = other.m_d1_b;
		m_d1_c = other.m_d1_c;
		m_p = other.m_p;
	}

	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS:
													if ((m_m_a == 100.0) &&
														(m_m_b == 0.0404) &&
														(m_m_c == 1.48) &&
														(m_d1_a == 30.0) &&
														(m_d1_b == 0.0232) &&
														(m_d1_c == 1.6) &&
														(m_p == 0.2))
														return 1.0;
													return 0.0;

			case FUELCOM_ATTRIBUTE.RSI_MIX_FACTOR:	return m_p;
			case FUELCOM_ATTRIBUTE.M3M4_C2_A:		return m_m_a;
			case FUELCOM_ATTRIBUTE.M3M4_C2_B:		return m_m_b;
			case FUELCOM_ATTRIBUTE.M3M4_C2_C:		return m_m_c;
			case FUELCOM_ATTRIBUTE.M4_D1_A:			return m_d1_a;
			case FUELCOM_ATTRIBUTE.M4_D1_B:			return m_d1_b;
			case FUELCOM_ATTRIBUTE.M4_D1_C:			return m_d1_c;
			case FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS: return 0.0;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS:
				m_m_a = 100.0;
				m_m_b = 0.0404;
				m_m_c = 1.48;
				m_d1_a = 30.0;
				m_d1_b = 0.0232;
				m_d1_c = 1.6;
				m_p = 0.2;
				break;
			case FUELCOM_ATTRIBUTE.RSI_MIX_FACTOR:
				if (attribute < 0.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				if (attribute > 1.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				m_p = attribute;
				break;
			case FUELCOM_ATTRIBUTE.M3M4_C2_A:
				m_m_a = attribute;
				break;
			case FUELCOM_ATTRIBUTE.M3M4_C2_B:
				m_m_b = attribute;
				break;
			case FUELCOM_ATTRIBUTE.M3M4_C2_C:
				m_m_c = attribute;
				break;
			case FUELCOM_ATTRIBUTE.M4_D1_A:
				m_d1_a = attribute;
				break;
			case FUELCOM_ATTRIBUTE.M4_D1_B:
				m_d1_b = attribute;
				break;
			case FUELCOM_ATTRIBUTE.M4_D1_C:
				m_d1_c = attribute;
				break;
			default:
				super.setAttributeValue(attributeKey, attribute);
				return;
		}
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_RSI_M4;
	}
	
	@Override
	public double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1) {
		double PC = sa.pc();
		double m4_rsi = _rsi(m_m_a, m_m_b, m_m_c, ISI/*, BE, f*/);			// equation 32, August 2004 article
		double d1_rsi = _rsi(m_d1_a, m_d1_b, m_d1_c, ISI/*, BE, f*/);
		double newrsi = PC * m4_rsi + m_p * (1.0 - PC) * d1_rsi;			// equation 31, August 2004 article
												// PC is a synonym for PDF here
		rsi_c2.value = m4_rsi;
		rsi_d1.value = d1_rsi;

		if ((short)(flag & FBPFuel.USE_BUI) != 0) 
			newrsi *= BE;
		return newrsi;
	}

	@Override
	public double ROS(double RSI, double CBH, double ISI, double FMC, double SFC,
			CFBAttribute cfb) {
		return RSI;
	}

	@Override
	public double FOR_FROS(double RSS, double ROS, double CFB) {
		return ROS;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof RSI_M4) {
			RSI_M4 cother = (RSI_M4)other;
			return m_p == cother.m_p &&
					   m_m_a == cother.m_m_a &&
					   m_m_b == cother.m_m_b &&
					   m_m_c == cother.m_m_c &&
					   m_d1_a == cother.m_d1_a &&
					   m_d1_b == cother.m_d1_b &&
					   m_d1_c == cother.m_d1_c;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.RsiAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.RsiAttribute.Builder builder = ca.wise.fuel.proto.RsiAttribute.newBuilder();
		builder.setVersion((int)RSIAttribute.serialVersionUID);
		
		RsiM4.Builder msgRet = RsiM4.newBuilder();
		msgRet.setVersion(1);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
			}
		}
	
		if(!serialized){
			RsiM4.Parms.Builder msg = RsiM4.Parms.newBuilder();

			msg.setVersion(1);
			msg.setA(HSS_Double.of(m_m_a));
			msg.setB(HSS_Double.of(m_m_b));
			msg.setC(HSS_Double.of(m_m_c));
			msg.setD1A(HSS_Double.of(m_d1_a));
			msg.setD1B(HSS_Double.of(m_d1_b));
			msg.setD1C(HSS_Double.of(m_d1_c));
			msg.setP(HSS_Double.of(m_p));
			
			msgRet.setParms(msg.build());
		}

		builder.setM4(msgRet);
		return builder.build();
	}

	@Override
	public RSI_M4 deserialize(Message proto) {
		RsiM4 msgRead;
		
		try {
			msgRead = (RsiM4)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			RsiM4.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_m_a = HSS_Double.from(msg.getA());
			m_m_b = HSS_Double.from(msg.getB());
			m_m_c = HSS_Double.from(msg.getC());
			m_d1_a = HSS_Double.from(msg.getD1A());
			m_d1_b = HSS_Double.from(msg.getD1B());
			m_d1_c = HSS_Double.from(msg.getD1C());
			m_p = HSS_Double.from(msg.getP());
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
		case C6:
			val = FUELCOM_ATTRIBUTE.RSI_C6_DEFAULTS;
			break;

		case D2:
			val = FUELCOM_ATTRIBUTE.RSI_D2_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS;
			break;

		case O1A:
			val = FUELCOM_ATTRIBUTE.RSI_O1_DEFAULTS;
			break;

		case Nz70:
			val = FUELCOM_ATTRIBUTE.RSI_NZ70_DEFAULTS;
			break;

		default:
			val = (short) -1;
		}

		return val;
	}
}
