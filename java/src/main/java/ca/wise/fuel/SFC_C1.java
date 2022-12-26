/***********************************************************************
 * REDapp - SFC_C1.java
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

public class SFC_C1 extends SFCAttribute {
	protected static final long serialVersionUID = 1L;
	
	private double m_p1;
	private double m_p2;
	private double m_p3;
	private double m_p4;
	private double m_multiplier;
	
	public SFC_C1() {
		m_p1 = -1.0;
		m_p2 = -1.0; 
		m_p3 = -1.0;
		m_p4 = -1.0;
		m_multiplier = 1.0;
	}

	public SFC_C1(final SFC_C1 other) {
		m_p1 = other.m_p1;
		m_p2 = other.m_p2;
		m_p3 = other.m_p3;
		m_p4 = other.m_p4;
		m_multiplier = other.m_multiplier;
	}
	
	public Object clone() throws CloneNotSupportedException {
		SFC_C1 other = (SFC_C1)super.clone();
		return other;
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_C1_DEFAULTS:			if ((m_p1 == 0.75) &&
																(m_p2 == 0.75) &&
																(m_p3 == 0.230) &&
																(m_p4 == 84.0) &&
																(m_multiplier == 1.0))
																return 1.0;
															return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_C1_CLR_DEFAULTS:		if ((m_p1 == 0.0) &&
																(m_p2 == 0.0) &&
																(m_p3 == 0.0) &&
																(m_p4 == 0.0) &&
																(m_multiplier == 0.0))
																return 1.0;
															return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_EQ9_ADDER:			return m_p1;
			case FUELCOM_ATTRIBUTE.SFC_EQ9_MULT1:			return m_p2;
			case FUELCOM_ATTRIBUTE.SFC_EQ9_MULT2:			return m_p3;
			case FUELCOM_ATTRIBUTE.SFC_EQ9_FFMC_THRESHOLD:	return m_p4;
			case FUELCOM_ATTRIBUTE.SFC_MULTIPLIER:			return m_multiplier;
		}
		
		return super.getAttributeValue(attributeKey);
	}
	
	@Override
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_C1_DEFAULTS:			m_p1 = 0.75;//1.5;	// the equation is changed in Errata, equations 9a, 9b
															m_p2 = 0.75;
															m_p3 = 0.230;
															m_p4 = 84.0;//81.0;
															m_multiplier = 1.0;
															return;

			case FUELCOM_ATTRIBUTE.SFC_C1_CLR_DEFAULTS:		m_p1 = m_p2 = m_p3 = m_p4 = m_multiplier = 0.0;
															return;

			case FUELCOM_ATTRIBUTE.SFC_EQ9_ADDER:			m_p1 = attribute;			return;
			case FUELCOM_ATTRIBUTE.SFC_EQ9_MULT1:			m_p2 = attribute;			return;
			case FUELCOM_ATTRIBUTE.SFC_EQ9_MULT2:			m_p3 = attribute;			return;
			case FUELCOM_ATTRIBUTE.SFC_EQ9_FFMC_THRESHOLD:	if (attribute < 0.0) throw new IllegalArgumentException("One of the inputs is out of range.");
															m_p4 = attribute;			return;
			case FUELCOM_ATTRIBUTE.SFC_MULTIPLIER:			m_multiplier = attribute;	return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() { 
		return FUELCOM_EQUATION.SELECTION_SFC_C1;
	};

	@Override
	public double SFC(SpreadParmsAttribute sa, int flag, double FFMC, double BUI) {
		double m_sfc;

		if (FFMC > m_p4)
			m_sfc = m_p1 + m_p2 * Math.sqrt(1.0 - Math.exp(-m_p3 * (FFMC - m_p4)));	// equation 9a, August 04 paper
		else		
			m_sfc = m_p1 - m_p2 * Math.sqrt(1.0 - Math.exp(m_p3 * (FFMC - m_p4)));	// equation 9b, August 04 paper
		if (m_sfc < 0.0)
			m_sfc = 0.0;
		else if (m_sfc > 0.0)
			m_sfc *= m_multiplier;
		return m_sfc;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof SFC_C1) {
			SFC_C1 cother = (SFC_C1)other;
			return m_p1 == cother.m_p1 &&
					   m_p2 == cother.m_p2 &&
					   m_p3 == cother.m_p3 &&
					   m_p4 == cother.m_p4 &&
					   m_multiplier == cother.m_multiplier;
		}
		return false;
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
		
		SfcC1.Builder msgRet = SfcC1.newBuilder();
		msgRet.setVersion(1);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_C1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C1);
				serialized = true;
			}
		}

		if(!serialized){
			SfcC1.Parms.Builder msg = SfcC1.Parms.newBuilder();

			msg.setVersion(1);
			
			msg.setP1(HSS_Double.of(m_p1));
			msg.setP2(HSS_Double.of(m_p2));
			msg.setP3(HSS_Double.of(m_p3));
			msg.setP4(HSS_Double.of(m_p4));
			msg.setMultiplier(HSS_Double.of(m_multiplier));
			
			msgRet.setParms(msg.build());
		}

		builder.setC1(msgRet);
		return builder.build();
	}

	@Override
	public SFC_C1 deserialize(Message proto) {
		SfcC1 msgRead;
		
		try {
			msgRead = (SfcC1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SfcC1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_p1 = HSS_Double.from(msg.getP1());
			m_p2 = HSS_Double.from(msg.getP2());
			m_p3 = HSS_Double.from(msg.getP3());
			m_p4 = HSS_Double.from(msg.getP4());
			m_multiplier = HSS_Double.from(msg.getMultiplier());
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
		case S1:
			val = FUELCOM_ATTRIBUTE.SFC_S1_DEFAULTS;
			break;

		case S2:
			val = FUELCOM_ATTRIBUTE.SFC_S2_DEFAULTS;
			break;

		case S3:
			val = FUELCOM_ATTRIBUTE.SFC_S3_DEFAULTS;
			break;

		case Nz63:
			val = FUELCOM_ATTRIBUTE.SFC_NZ63_DEFAULTS;
			break;

		case Nz64:
			val = FUELCOM_ATTRIBUTE.SFC_NZ64_DEFAULTS;
			break;

		case Nz65:
			val = FUELCOM_ATTRIBUTE.SFC_NZ65_DEFAULTS;
			break;

		case Nz66:
			val = FUELCOM_ATTRIBUTE.SFC_NZ66_DEFAULTS;
			break;

		case O1A:
			val = FUELCOM_ATTRIBUTE.SFC_O1A_DEFAULTS;
			break;

		case O1B:
			val = FUELCOM_ATTRIBUTE.SFC_O1B_DEFAULTS;
			break;

		case Nz62:
			val = FUELCOM_ATTRIBUTE.SFC_NZ62_DEFAULTS;
			break;

		case Nz2:
			val = FUELCOM_ATTRIBUTE.SFC_NZ2_DEFAULTS;
			break;

		case Nz15:
			val = FUELCOM_ATTRIBUTE.SFC_NZ15_DEFAULTS;
			break;

		case Nz32:
			val = FUELCOM_ATTRIBUTE.SFC_NZ32_DEFAULTS;
			break;

		case Nz33:
			val = FUELCOM_ATTRIBUTE.SFC_NZ33_DEFAULTS;
			break;

		case Nz44:
			val = FUELCOM_ATTRIBUTE.SFC_NZ44_DEFAULTS;
			break;

		case Nz30:
			val = FUELCOM_ATTRIBUTE.SFC_NZ30_DEFAULTS;
			break;

		case Nz45:
			val = FUELCOM_ATTRIBUTE.SFC_NZ45_DEFAULTS;
			break;

		case Nz46:
			val = FUELCOM_ATTRIBUTE.SFC_NZ46_DEFAULTS;
			break;

		case Nz53:
			val = FUELCOM_ATTRIBUTE.SFC_NZ53_DEFAULTS;
			break;

		case Nz40:
			val = FUELCOM_ATTRIBUTE.SFC_NZ40_DEFAULTS;
			break;

		case Nz41:
			val = FUELCOM_ATTRIBUTE.SFC_NZ41_DEFAULTS;
			break;

		case Nz43:
			val = FUELCOM_ATTRIBUTE.SFC_NZ43_DEFAULTS;
			break;

		case Nz47:
			val = FUELCOM_ATTRIBUTE.SFC_NZ47_DEFAULTS;
			break;

		case Nz50:
			val = FUELCOM_ATTRIBUTE.SFC_NZ50_DEFAULTS;
			break;

		case Nz56:
			val = FUELCOM_ATTRIBUTE.SFC_NZ56_DEFAULTS;
			break;

		case Nz57:
			val = FUELCOM_ATTRIBUTE.SFC_NZ57_DEFAULTS;
			break;

		case Nz58:
			val = FUELCOM_ATTRIBUTE.SFC_NZ58_DEFAULTS;
			break;

		case Nz51:
			val = FUELCOM_ATTRIBUTE.SFC_NZ51_DEFAULTS;
			break;

		case Nz52:
			val = FUELCOM_ATTRIBUTE.SFC_NZ52_DEFAULTS;
			break;

		case Nz55:
			val = FUELCOM_ATTRIBUTE.SFC_NZ55_DEFAULTS;
			break;

		case Nz70:
			val = FUELCOM_ATTRIBUTE.SFC_NZ70_DEFAULTS;
			break;

		case D2:
			val = FUELCOM_ATTRIBUTE.SFC_D2_DEFAULTS;
			break;

		case C7:
			val = FUELCOM_ATTRIBUTE.SFC_C7_DEFAULTS;
			break;

		case C2:
			val = FUELCOM_ATTRIBUTE.SFC_C2_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.SFC_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.SFC_M4_DEFAULTS;
			break;

		case Nz67:
			val = FUELCOM_ATTRIBUTE.SFC_M3_DEFAULTS;
			break;

		case C3:
			val = FUELCOM_ATTRIBUTE.SFC_C3_DEFAULTS;
			break;

		case C4:
			val = FUELCOM_ATTRIBUTE.SFC_C4_DEFAULTS;
			break;

		case C5:
			val = FUELCOM_ATTRIBUTE.SFC_C5_DEFAULTS;
			break;

		case C6:
			val = FUELCOM_ATTRIBUTE.SFC_C6_DEFAULTS;
			break;

		case Nz54:
			val = FUELCOM_ATTRIBUTE.SFC_NZ54_DEFAULTS;
			break;

		case Nz61:
			val = FUELCOM_ATTRIBUTE.SFC_NZ61_DEFAULTS;
			break;

		case Nz60:
			val = FUELCOM_ATTRIBUTE.SFC_NZ60_DEFAULTS;
			break;

		case C1:
			val = FUELCOM_ATTRIBUTE.SFC_C1_DEFAULTS;
			break;

		case D1:
			val = FUELCOM_ATTRIBUTE.SFC_D1_DEFAULTS;
			break;

		case Nz68:
			val = FUELCOM_ATTRIBUTE.SFC_D1_DEFAULTS;
			break;

		case Nz71:
			val = FUELCOM_ATTRIBUTE.SFC_NZ71_DEFAULTS;
			break;

		default:
			val = (short) -1;
		}

		return val;
	}
}
