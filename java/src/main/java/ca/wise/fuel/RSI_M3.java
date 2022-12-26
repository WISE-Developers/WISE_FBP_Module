/***********************************************************************
 * REDapp - FSI_M3.java
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

public class RSI_M3 extends RSI_StdCalc {
	protected static final long serialVersionUID = 1L;
	
	private double m_m_a;
	private double m_m_b;
	private double m_m_c;
	private double m_p;
	
	public RSI_M3() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS, 0.0);
	}
	
	public RSI_M3(final RSI_M3 other) {
		m_m_a = other.m_m_a;
		m_m_b = other.m_m_b;
		m_m_c = other.m_m_c;
		m_p = other.m_p;
	}

	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS:
														if ((m_m_a == 120.0) &&
															(m_m_b == 0.0572) &&
															(m_m_c == 1.4) &&
															(m_p == 1.0))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.RSI_MIX_FACTOR:		return m_p;
			case FUELCOM_ATTRIBUTE.M3M4_C2_A:			return m_m_a;
			case FUELCOM_ATTRIBUTE.M3M4_C2_B:			return m_m_b;
			case FUELCOM_ATTRIBUTE.M3M4_C2_C:			return m_m_c;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS:
				m_m_a = 120.0;
				m_m_b = 0.0572;
				m_m_c = 1.4;
				m_p = 1.0;
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
			case FUELCOM_ATTRIBUTE.M4_D1_B:
			case FUELCOM_ATTRIBUTE.M4_D1_C:
			case FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS: return;
			default:
				super.setAttributeValue(attributeKey, attribute);
				return;
		}
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_RSI_M3;
	}

	@Override
	public double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1) {
		double m3_rsi = _rsi(m_m_a, m_m_b, m_m_c, ISI/*, BE, f*/);			// equation 30, August 2004 article

		double d1_rsi;
		CwfgmFuel d1 = sa.d1();
		
		if (d1 != null)
			d1_rsi = d1.rsi(FFMC, BUI, FMC, ISI, (short)0);
		else {
			d1_rsi = 0.0;
		}
		rsi_c2.value = m3_rsi;
		rsi_d1.value = d1_rsi;

		double PC = sa.pc();
		double newrsi = PC * m3_rsi + m_p * (1.0 - PC) * d1_rsi;			// equation 29, August 2004 article
												// PC is a synonym for PDF here
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
		if (other instanceof RSI_M3) {
			RSI_M3 cother = (RSI_M3)other;
			if (m_p != cother.m_p)	return false;
			if (m_m_a != cother.m_m_a)		return false;
			if (m_m_b != cother.m_m_b)		return false;
			if (m_m_c != cother.m_m_c)		return false;
			return true;
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
		
		RsiM3.Builder msgRet = RsiM3.newBuilder();
		msgRet.setVersion(1);

		boolean serialized = false;
		if(!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
				serialized = true;
			}
		}

		if(!serialized){
			RsiM3.Parms.Builder msg = RsiM3.Parms.newBuilder();

			msg.setVersion(1);
			msg.setA(HSS_Double.of(m_m_a));
			msg.setB(HSS_Double.of(m_m_b));
			msg.setC(HSS_Double.of(m_m_c));
			msg.setP(HSS_Double.of(m_p));
			
			msgRet.setParms(msg.build());
		}

		builder.setM3(msgRet);
		return builder.build();
	}

	@Override
	public RSI_M3 deserialize(Message proto) {
		RsiM3 msgRead;
		
		try {
			msgRead = (RsiM3)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			RsiM3.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_m_a = HSS_Double.from(msg.getA());
			m_m_b = HSS_Double.from(msg.getB());
			m_m_c = HSS_Double.from(msg.getC());
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
