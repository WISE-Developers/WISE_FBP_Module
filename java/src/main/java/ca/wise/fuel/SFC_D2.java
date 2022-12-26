/***********************************************************************
 * REDapp - SFC_D2.java
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

public class SFC_D2 extends SFC_C2 {
	protected static final long serialVersionUID = 1L;
	
	private double m_threshold, m_scale1, m_scale2;
	
	public SFC_D2() {
		m_threshold = 80.0;
		m_scale1 = 0.0;
		m_scale2 = 1.0;	
	}

	public SFC_D2(final SFC_D2 other) {
		m_threshold = other.m_threshold;
		m_scale1 = other.m_scale1;
		m_scale2 = other.m_scale2;
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_D2_DEFAULTS:		if ((m_p1 == 1.5) &&
															(m_p2 == 0.0183) &&
															(m_power == 1.00) &&
															(m_multiplier == 1.0) &&
															(m_threshold == 80.0) &&
															(m_scale1 == 0.0) &&
															(m_scale2 == 1.0))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_D2_THRESHOLD:	return m_threshold;
			case FUELCOM_ATTRIBUTE.SFC_D2_SCALE1:		return m_scale1;
			case FUELCOM_ATTRIBUTE.SFC_D2_SCALE2:		return m_scale2;
		}
			
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_D2_DEFAULTS:		m_p1 = 1.5;
														m_p2 = 0.0183;
														m_power = 1.00;
														m_multiplier = 1.0;
														m_threshold = 80.0;
														m_scale1 = 0.0;
														m_scale2 = 1.0;					return; // RWB: 051005: changed this modifier back to 1.0 after emails between Cordy and Mike Wotton

			case FUELCOM_ATTRIBUTE.SFC_D2_THRESHOLD:	if (attribute < 0.0)			throw new IllegalArgumentException("One of the inputs is out of range.");
														m_threshold = attribute;		return;

			case FUELCOM_ATTRIBUTE.SFC_D2_SCALE1:		if (attribute < 0.0)			throw new IllegalArgumentException("One of the inputs is out of range.");
														if (attribute > 2.0)			throw new IllegalArgumentException("One of the inputs is out of range.");
														m_scale1 = attribute;			return;

			case FUELCOM_ATTRIBUTE.SFC_D2_SCALE2:		if (attribute < 0.0)			throw new IllegalArgumentException("One of the inputs is out of range.");
														if (attribute > 2.0)			throw new IllegalArgumentException("One of the inputs is out of range.");
														m_scale2 = attribute;			return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() { 
		return FUELCOM_EQUATION.SELECTION_SFC_D2;
	}

	@Override
	public double SFC(SpreadParmsAttribute sa, int flag, double FFMC, double BUI) {
		double scale;
		if (BUI < m_threshold)	scale = m_scale1;
		else			scale = m_scale2;

		if (scale == 0.0)
			return 0.0;

		// equation 63 is applied in the following statement, just like D2, with any BE affect applied
		double sfc = super.SFC(sa, flag, FFMC, BUI);
		return scale * sfc;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof SFC_D2) {
			SFC_D2 a = (SFC_D2)other;
			if (m_p1 != a.m_p1)		return false;
			if (m_p2 != a.m_p2)		return false;
			if (m_power != a.m_power)	return false;
			if (m_multiplier != a.m_multiplier)	return false;
			if (m_threshold != a.m_threshold)	return false;
			if (m_scale1 != a.m_scale1)	return false;
			if (m_scale2 != a.m_scale2)	return false;
		} else
			return false;
		return super.equals(other);
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.SfcAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.SfcAttribute.Builder builder = ca.wise.fuel.proto.SfcAttribute.newBuilder();
		builder.setVersion((int)SFCAttribute.serialVersionUID);
		
		SfcD2.Builder msgRet = SfcD2.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_C2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_C3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_C4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_C5_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C5);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_C6_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C6);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_D1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_D2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D2);
				serialized = true;
			}
		}

		if(!serialized) {
			SfcD2.Parms.Builder msg = SfcD2.Parms.newBuilder();

			msg.setVersion(1);
			
			msg.setP1(HSS_Double.of(m_p1));
			msg.setP2(HSS_Double.of(m_p2));
			msg.setPower(HSS_Double.of(m_power));
			msg.setMultiplier(HSS_Double.of(m_multiplier));
			msg.setThreshold(HSS_Double.of(m_threshold));
			msg.setScale1(HSS_Double.of(m_scale1));
			msg.setScale2(HSS_Double.of(m_scale2));
			
			msgRet.setParms(msg.build());
		}

		builder.setD2(msgRet);
		return builder.build();
	}

	@Override
	public SFC_D2 deserialize(Message proto) {
		SfcD2 msgRead;
		
		try {
			msgRead = (SfcD2)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SfcD2.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_p1 = HSS_Double.from(msg.getP1());
			m_p2 = HSS_Double.from(msg.getP2());
			m_power = HSS_Double.from(msg.getPower());
			m_multiplier = HSS_Double.from(msg.getMultiplier());
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
