/***********************************************************************
 * REDapp - SFC_C7.java
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

public class SFC_C7 extends SFCAttribute {
	protected static final long serialVersionUID = 1L;
	
	private double m_p1_f;
	private double m_p2_f;
	private double m_p3_f;
	private double m_p1_w;
	private double m_p2_w;
	private double m_ffc_multiplier, m_wfc_multiplier, m_sfc_multiplier;
	
	public SFC_C7() {
		m_p1_f = -1.0; 
		m_p2_f = -1.0; 
		m_p3_f = -1.0; 
		m_p1_w = -1.0; 
		m_p2_w = -1.0; 
		m_ffc_multiplier = m_wfc_multiplier = m_sfc_multiplier = 1.0;
	}

	public SFC_C7(final SFC_C7 other) {
		m_p1_f = other.m_p1_f;
		m_p2_f = other.m_p2_f;
		m_p3_f = other.m_p3_f;
		m_p1_w = other.m_p1_w;
		m_p2_w = other.m_p2_w;
		m_ffc_multiplier = other.m_ffc_multiplier;
		m_wfc_multiplier = other.m_wfc_multiplier;
		m_sfc_multiplier = other.m_sfc_multiplier;
	}
	
	public Object clone() throws CloneNotSupportedException {
		SFC_C7 other = (SFC_C7)super.clone();
		return other;
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_C7_DEFAULTS:		if ((m_p1_f == 2.0) &&
															(m_p2_f == 0.104) &&
															(m_p3_f == 70.0) &&
															(m_p1_w == 1.5) &&
															(m_p2_w == 0.0201) &&
															(m_sfc_multiplier == 1.0) &&
															(m_wfc_multiplier == 1.0) &&
															(m_ffc_multiplier == 1.0))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_EQ13_MULT1:		return m_p1_f;
			case FUELCOM_ATTRIBUTE.SFC_EQ13_MULT2:		return m_p2_f;
			case FUELCOM_ATTRIBUTE.SFC_EQ13_ADDER:		return m_p3_f;
			case FUELCOM_ATTRIBUTE.SFC_EQ14_MULT1:		return m_p1_w;
			case FUELCOM_ATTRIBUTE.SFC_EQ14_MULT2:		return m_p2_w;
			case FUELCOM_ATTRIBUTE.SFC_MULTIPLIER:		return m_sfc_multiplier;
			case FUELCOM_ATTRIBUTE.WFC_MULTIPLIER:		return m_wfc_multiplier;
			case FUELCOM_ATTRIBUTE.FFC_MULTIPLIER:		return m_ffc_multiplier;
		}
		
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_C7_DEFAULTS:		m_p1_f = 2.0;
														m_p2_f = 0.104;
														m_p3_f = 70.0;
														m_p1_w = 1.5;
														m_p2_w = 0.0201;
														m_sfc_multiplier = 1.0;
														m_wfc_multiplier = 1.0;
														m_ffc_multiplier = 1.0;				return;
			case FUELCOM_ATTRIBUTE.SFC_EQ13_MULT1:		m_p1_f = attribute;					return;
			case FUELCOM_ATTRIBUTE.SFC_EQ13_MULT2:		m_p2_f = attribute;					return;
			case FUELCOM_ATTRIBUTE.SFC_EQ13_ADDER:		m_p3_f = attribute;					return;
			case FUELCOM_ATTRIBUTE.SFC_EQ14_MULT1:		m_p1_w = attribute;					return;
			case FUELCOM_ATTRIBUTE.SFC_EQ14_MULT2:		m_p2_w = attribute;					return;
			case FUELCOM_ATTRIBUTE.SFC_MULTIPLIER:		m_sfc_multiplier = attribute;		return;
			case FUELCOM_ATTRIBUTE.WFC_MULTIPLIER:		m_wfc_multiplier = attribute;		return;
			case FUELCOM_ATTRIBUTE.FFC_MULTIPLIER:		m_ffc_multiplier = attribute;		return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() { 
		return FUELCOM_EQUATION.SELECTION_SFC_C7;
	};

	@Override
	public double SFC(SpreadParmsAttribute sa, int flag, double FFMC, double BUI) {
		Double m_sfc;
		double ffc = m_p1_f * (1.0 - Math.exp(-m_p2_f * (FFMC - m_p3_f)));
									// equation 13
		if (ffc < 0.0)
			ffc = 0.0;
		else if (ffc > 0.0)
			ffc *= m_ffc_multiplier;
		double wfc = m_p1_w * (1.0 - Math.exp(-m_p2_w * BUI));	// equation 14
		if (wfc > 0.0)
			wfc *= m_wfc_multiplier;
		m_sfc = ffc + wfc;					// equation 15
		m_sfc *= m_sfc_multiplier;
		return m_sfc;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof SFC_C7) {
			SFC_C7 cother = (SFC_C7)other;
			return m_p1_f == cother.m_p1_f &&
					   m_p2_f == cother.m_p2_f &&
					   m_p3_f == cother.m_p3_f &&
					   m_p1_w == cother.m_p1_w &&
					   m_p2_w == cother.m_p2_w &&
					   m_sfc_multiplier == cother.m_sfc_multiplier &&
					   m_wfc_multiplier == cother.m_wfc_multiplier &&
					   m_ffc_multiplier == cother.m_ffc_multiplier;
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
		
		SfcC7.Builder msgRet = SfcC7.newBuilder();
		msgRet.setVersion(1);

		boolean serialized = false;
		if(!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_C7_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C7);
				serialized = true;
			}
		}

		if(!serialized) {
			SfcC7.Parms.Builder msg = SfcC7.Parms.newBuilder();

			msg.setVersion(1);
			
			msg.setP1F(HSS_Double.of(m_p1_f));
			msg.setP2F(HSS_Double.of(m_p2_f));
			msg.setP3F(HSS_Double.of(m_p3_f));
			msg.setP1W(HSS_Double.of(m_p1_w));
			msg.setP2W(HSS_Double.of(m_p2_w));
			msg.setFfcMultiplier(HSS_Double.of(m_ffc_multiplier));
			msg.setWfcMultiplier(HSS_Double.of(m_wfc_multiplier));
			msg.setSfcMultiplier(HSS_Double.of(m_sfc_multiplier));
			
			msgRet.setParms(msg.build());
		}

		builder.setC7(msgRet);
		return builder.build();
	}

	@Override
	public SFC_C7 deserialize(Message proto) {
		SfcC7 msgRead;
		
		try {
			msgRead = (SfcC7)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SfcC7.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_p1_f = HSS_Double.from(msg.getP1F());
			m_p2_f = HSS_Double.from(msg.getP2F());
			m_p3_f = HSS_Double.from(msg.getP3F());
			m_p1_w = HSS_Double.from(msg.getP1W());
			m_p2_w = HSS_Double.from(msg.getP2W());
			m_ffc_multiplier = HSS_Double.from(msg.getFfcMultiplier());
			m_wfc_multiplier = HSS_Double.from(msg.getWfcMultiplier());
			m_sfc_multiplier = HSS_Double.from(msg.getSfcMultiplier());
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
