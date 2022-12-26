/***********************************************************************
 * REDapp - RSI_Constant.java
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
import ca.wise.fuel.proto.FuelName;

public class RSI_Constant extends RSIAttribute {
	protected static final long serialVersionUID = 1L;

	public double m_rsi;
	
	public RSI_Constant() {
		m_rsi = 0.0;
	}

	public RSI_Constant(final RSI_Constant other) {
		m_rsi = other.m_rsi;
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_CONSTANT_RSI:	return m_rsi;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_CONSTANT_RSI:	if (attribute < 0.0)		throw new IllegalArgumentException("One of the arguments is out of range.");
														m_rsi = attribute;			return;
		}

		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_RSI_CONSTANT;
	}	
	
	@Override
	public double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1) {
		rsi_c2.value = m_rsi;
		rsi_d1.value = m_rsi;
		return m_rsi;
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
		if (other instanceof RSI_Constant) {
			RSI_Constant cother = (RSI_Constant)other;
			return m_rsi == cother.m_rsi;
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
		
		RsiConstant.Builder msgRet = RsiConstant.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		RsiConstant.Parms.Builder msg = RsiConstant.Parms.newBuilder();
		msg.setVersion(1);
		msg.setRsi(HSS_Double.of(m_rsi));
		msgRet.setParms(msg.build());

		builder.setConstant(msgRet);
		return builder.build();
	}

	@Override
	public RSI_Constant deserialize(Message proto) {
		RsiConstant msgRead;
		
		try {
			msgRead = (RsiConstant)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			RsiConstant.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
			
			m_rsi = HSS_Double.from(msg.getRsi());
		}
		else {
			FuelName def = msgRead.getDefault();
			short val = GetDefaultValue(def);
			
			if(val != (short) - 1)
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
