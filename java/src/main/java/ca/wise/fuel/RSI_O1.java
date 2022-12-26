/***********************************************************************
 * REDapp - FSI_O1.java
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

public class RSI_O1 extends RSI_StdCalc {
	protected static final long serialVersionUID = 1L;
	
	private double m_threshold;
	private double m_f1;
	private double m_f2;
	private double m_f3;
	private double m_f4;
	
	public RSI_O1() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_O1_DEFAULTS, 0.0);
	}

	public RSI_O1(final RSI_O1 other) {
		m_threshold = other.m_threshold;
		m_f1 = other.m_f1;
		m_f2 = other.m_f2;
		m_f3 = other.m_f3;
		m_f4 = other.m_f4;
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_O1_DEFAULTS:
													if ((m_threshold == 0.588) &&
														(m_f1 == 0.005) &&
														(m_f2 == 0.061) &&
														(m_f3 == 0.176) &&
														(m_f4 == 0.02))
														return 1.0;
													return 0.0;

			case FUELCOM_ATTRIBUTE.EQ35_THRESHOLD:	return m_threshold;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT1:		return m_f1;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT2:		return m_f2;
			case FUELCOM_ATTRIBUTE.EQ35B_ADDER:		return m_f3;
			case FUELCOM_ATTRIBUTE.EQ35B_MULT1:		return m_f4;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_O1_DEFAULTS:
				m_threshold = 0.588;
				m_f1 = 0.005;
				m_f2 = 0.061;
				m_f3 = 0.176;
				m_f4 = 0.02;
				break;
			case FUELCOM_ATTRIBUTE.EQ35_THRESHOLD:
				if (attribute < 0.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				if (attribute > 1.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				m_threshold = attribute;
				break;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT1:
				m_f1 = attribute;
				break;
			case FUELCOM_ATTRIBUTE.EQ35A_MULT2:
				m_f2 = attribute;
				break;
			case FUELCOM_ATTRIBUTE.EQ35B_ADDER:
				m_f3 = attribute;
				break;
			case FUELCOM_ATTRIBUTE.EQ35B_MULT1:
				m_f4 = attribute;
				break;
			default:
				super.setAttributeValue(attributeKey, attribute);
				return;
		}
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_RSI_O1;
	}
	
	@Override
	public double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1) {
		double CF;
		double C = sa.curingDegree();
		
		if (C < m_threshold)
			CF = m_f1 * (Math.exp(m_f2 * C * 100.0) - 1.0);		// equation 35a, August 2004 article
		else	
			CF = m_f3 + m_f4 * ((C - m_threshold) * 100.0);		// equation 35b, August 2004 article

		double rsi2 = _rsi(sa.a(flag), sa.b(flag), sa.c(flag), ISI) * CF;

		if ((short)(flag & FBPFuel.USE_BUI) != 0)
			rsi2 *= BE;

	 	rsi_c2.value = rsi2;
	 	rsi_d1.value = rsi2;
		return rsi2;
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
		if (other instanceof RSI_O1) {
			RSI_O1 cother = (RSI_O1)other;
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
	public ca.wise.fuel.proto.RsiAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.RsiAttribute.Builder builder = ca.wise.fuel.proto.RsiAttribute.newBuilder();
		builder.setVersion((int)RSIAttribute.serialVersionUID);
		
		RsiO1.Builder msgRet = RsiO1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_O1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
				serialized = true;
			}
		}

		if(!serialized){
			RsiO1.Parms.Builder msg = RsiO1.Parms.newBuilder();

			msg.setVersion(1);
			msg.setThreshold(HSS_Double.of(m_threshold));
			msg.setF1(HSS_Double.of(m_f1));
			msg.setF2(HSS_Double.of(m_f2));
			msg.setF3(HSS_Double.of(m_f3));
			msg.setF4(HSS_Double.of(m_f4));
			
			msgRet.setParms(msg.build());
		}

		builder.setO1(msgRet);
		return builder.build();
	}

	@Override
	public RSI_O1 deserialize(Message proto) {
		RsiO1 msgRead;
		
		try {
			msgRead = (RsiO1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			RsiO1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_threshold = HSS_Double.from(msg.getThreshold());
			m_f1 = HSS_Double.from(msg.getF1());
			m_f2 = HSS_Double.from(msg.getF2());
			m_f3 = HSS_Double.from(msg.getF3());
			m_f4 = HSS_Double.from(msg.getF4());
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
