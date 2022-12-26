/***********************************************************************
 * REDapp - RSI_D2.java
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


public class RSI_D2 extends RSI_C1 {
	protected static final long serialVersionUID = 1L;
	
	private double m_threshold;
	private double m_scale1;
	private double m_scale2;
	
	public RSI_D2() {
		setAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_D2_DEFAULTS, 0.0);
	}
	
	public RSI_D2(final RSI_D2 other) {
		super(other);
		m_threshold = other.m_threshold;
		m_scale1 = other.m_scale1;
		m_scale2 = other.m_scale2;
	}

	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_D2_DEFAULTS:
														if ((m_threshold == 80.0) &&
															(m_scale1 == 0.0) &&
															(m_scale2 == 0.2))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.RSI_D2_THRESHOLD:	return m_threshold;
			case FUELCOM_ATTRIBUTE.RSI_D2_SCALE1:		return m_scale1;
			case FUELCOM_ATTRIBUTE.RSI_D2_SCALE2:		return m_scale2;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_D2_DEFAULTS:
				m_threshold = 80.0;
				m_scale1 = 0.0;
				m_scale2 = 0.2;
				break;
			case FUELCOM_ATTRIBUTE.RSI_D2_THRESHOLD:
				if (attribute < 0.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				m_threshold = attribute;
				break;
			case FUELCOM_ATTRIBUTE.RSI_D2_SCALE1:
				if (attribute < 0.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				if (attribute > 2.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				m_scale1 = attribute;
				break;
			case FUELCOM_ATTRIBUTE.RSI_D2_SCALE2:
				if (attribute < 0.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				if (attribute > 2.0)
					throw new IllegalArgumentException("One of the arguments is out of range.");
				m_scale2 = attribute;
				break;
			default:
				super.setAttributeValue(attributeKey, attribute);
				return;
		}
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_RSI_D2;
	}

	@Override
	public double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1) {
		double scale;
		if (BUI < m_threshold)	scale = m_scale1;
		else			scale = m_scale2;
//		if (!(flag & CALC_FOR_RSF))
			if (scale == 0.0) {
				rsi_d1.value = 0.0;
				rsi_c2.value = 0.0;
				return 0.0;
			}
		// equation 63 is applied in the following statement, just like D2, with any BE affect applied
		double rsi = super.RSI(sa, flag, ISI, FMC, BUI, FFMC, BE, rsi_c2, rsi_d1);
		
		if ((short)(flag & FBPFuel.CALC_FOR_RSF) != 0) {
			rsi_d1.value = rsi;
			rsi_c2.value = rsi;
		} else {
			rsi_d1.value = scale * rsi;
			rsi_c2.value = scale * rsi;		// RWB: 120805: this scale factor is only applied to calculate RSI, not to calculate RSF
		}
		return (Double)rsi_c2.value;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof RSI_D2) {
			RSI_D2 cother = (RSI_D2)other;
			if (m_threshold != cother.m_threshold)	return false;
			if (m_scale1 != cother.m_scale1)		return false;
			if (m_scale2 != cother.m_scale2)		return false;
		}
		return super.equals(other);
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
		
		RsiD2.Builder msgRet = RsiD2.newBuilder();
		msgRet.setVersion(1);

		boolean serialized = false;
		if(!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_D2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D2);
				serialized = true;
			}
		}
	
		if(!serialized) {
			RsiD2.Parms.Builder msg = RsiD2.Parms.newBuilder();

			msg.setVersion(1);
			msg.setThreshold(HSS_Double.of(m_threshold));
			msg.setScale1(HSS_Double.of(m_scale1));
			msg.setScale2(HSS_Double.of(m_scale2));
			
			msgRet.setParms(msg.build());
		}

		builder.setD2(msgRet);
		return builder.build();
	}

	@Override
	public RSI_D2 deserialize(Message proto) {
		RsiD2 msgRead;
		
		try {
			msgRead = (RsiD2)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			RsiD2.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_threshold = HSS_Double.from(msg.getThreshold());
			m_scale1 = HSS_Double.from(msg.getScale1());
			m_scale2 = HSS_Double.from(msg.getScale2());
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
