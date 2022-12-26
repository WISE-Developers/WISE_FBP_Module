/***********************************************************************
 * REDapp - RSI_M1.java
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

public class RSI_M1 extends RSIAttribute {
	protected static final long serialVersionUID = 1L;
	
	public double m_p1;
	
	public RSI_M1() {
		m_p1 = -1.0;
	}

	public RSI_M1(final RSI_M1 other) {
		m_p1 = other.m_p1;
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_MIX_FACTOR:		return m_p1;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.RSI_MIX_FACTOR:		if (attribute < 0.0)	throw new IllegalArgumentException("One of the arguments is out of range.");
														if (attribute > 1.0)	throw new IllegalArgumentException("One of the arguments is out of range.");
														m_p1 = attribute;		return;
		}

		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_RSI_M1;
	}

	@Override
	public double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1){
		short f = (short)((short)flag & (short)(~(FBPFuel.USE_BUI)));

		CwfgmFuel c2 = sa.c2();
		CwfgmFuel d1 = sa.d1();
		
		if (c2 != null)
			rsi_c2.value = c2.rsi(FFMC, BUI, FMC, ISI, f);	
		else {
			rsi_c2.value = 0.0;
		}
		if (d1 != null)
			rsi_d1.value = d1.rsi(FFMC, BUI, FMC, ISI, f);
		else {
			rsi_d1.value = 0.0;
		}

		double PC = sa.pc();
		double rsi = PC * ((Double)rsi_c2.value) + m_p1 * (1.0 - PC) * ((Double)rsi_d1.value);	// equation 27, 28
		if ((short)(flag & FBPFuel.USE_BUI) != 0)
			rsi *= BE;
		return rsi;
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
		if (other instanceof RSI_M1) {
			RSI_M1 cother = (RSI_M1)other;
			return (m_p1 == cother.m_p1);
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
		
		RsiM1.Builder msgRet = RsiM1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		RsiM1.Parms.Builder msg = RsiM1.Parms.newBuilder();

		msg.setVersion(1);
		msg.setP1(HSS_Double.of(m_p1));
		
		msgRet.setParms(msg.build());
		
		builder.setM1(msgRet);
		return builder.build();
	}

	@Override
	public RSI_M1 deserialize(Message proto) {
		RsiM1 msgRead;
		
		try {
			msgRead = (RsiM1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			RsiM1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_p1 = HSS_Double.from(msg.getP1());
		}
		else {
			throw new IllegalArgumentException("Unknown attributeKey.");
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
