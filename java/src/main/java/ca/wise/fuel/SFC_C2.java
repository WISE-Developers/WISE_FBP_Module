/***********************************************************************
 * REDapp - SFC_C2.java
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

import ca.hss.math.HSS_Double;
import ca.hss.math.ValueCache;

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.wise.fuel.proto.*;

public class SFC_C2 extends SFCAttribute {
	protected static final long serialVersionUID = 1L;
	
	private ValueCache<Double, Double> m_cache = new ValueCache<Double, Double>(16);
	protected double m_p1;
	protected double m_p2;
	protected double m_power;
	protected double m_multiplier;
	
	public SFC_C2() {
		m_p1 = -1.0;				// 5.0			5.0		5.0		1.5
		m_p2 = -1.0;				// 0.0115		0.0164		0.0149		0.0183
		m_power = -1.0;				// 1.00			2.24		2.48		1.00
//		m_bui = -99.0;
		m_multiplier = 1.0;
	}

	public SFC_C2(final SFC_C2 other) {
		m_p1 = other.m_p1;
		m_p2 = other.m_p2;
		m_power = other.m_power;
		m_multiplier = other.m_multiplier;
	}
	
	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_C2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SFC_M3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SFC_M4_DEFAULTS:		if ((m_p1 == 5.0) &&
															(m_p2 == 0.0115) &&
															(m_power == 1.00) &&
															(m_multiplier == 1.0))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_C3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SFC_C4_DEFAULTS:		if ((m_p1 == 5.0) &&
															(m_p2 == 0.0164) &&
															(m_power == 2.24) &&
															(m_multiplier == 1.0))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_C5_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SFC_C6_DEFAULTS:		if ((m_p1 == 5.0) &&
															(m_p2 == 0.0149) &&
															(m_power == 2.48) &&
															(m_multiplier == 1.0))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_D1_DEFAULTS:		if ((m_p1 == 1.5) &&
															(m_p2 == 0.0183) &&
															(m_power == 1.00) &&
															(m_multiplier == 1.0))
															return 1.0;
														return 0.0;

			case FUELCOM_ATTRIBUTE.SFC_EQ10_MULT1:		return m_p1;
			case FUELCOM_ATTRIBUTE.SFC_EQ10_ADDER:		return m_p2;
			case FUELCOM_ATTRIBUTE.SFC_EQ10_POWER:		return m_power;
			case FUELCOM_ATTRIBUTE.SFC_MULTIPLIER:		return m_multiplier;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SFC_C2_DEFAULTS:	
			case FUELCOM_ATTRIBUTE.SFC_M3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SFC_M4_DEFAULTS:		m_p1 = 5.0;
														m_p2 = 0.0115;
														m_power = 1.00;
														m_multiplier = 1.0;			m_cache.clear();	return;
			case FUELCOM_ATTRIBUTE.SFC_C3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SFC_C4_DEFAULTS:		m_p1 = 5.0;
														m_p2 = 0.0164;
														m_power = 2.24;
														m_multiplier = 1.0;			m_cache.clear();	return;
			case FUELCOM_ATTRIBUTE.SFC_C5_DEFAULTS:	
			case FUELCOM_ATTRIBUTE.SFC_C6_DEFAULTS:		m_p1 = 5.0;
														m_p2 = 0.0149;
														m_power = 2.48;
														m_multiplier = 1.0;			m_cache.clear();	return;

			case FUELCOM_ATTRIBUTE.SFC_D1_DEFAULTS:		m_p1 = 1.5;
														m_p2 = 0.0183;
														m_power = 1.00;
														m_multiplier = 1.0;			m_cache.clear();	return;

			case FUELCOM_ATTRIBUTE.SFC_EQ10_MULT1:		m_p1 = attribute;			m_cache.clear();	return;
			case FUELCOM_ATTRIBUTE.SFC_EQ10_ADDER:		m_p2 = attribute;			m_cache.clear();	return;
			case FUELCOM_ATTRIBUTE.SFC_EQ10_POWER:		m_power = attribute;		m_cache.clear();	return;
			case FUELCOM_ATTRIBUTE.SFC_MULTIPLIER:		m_multiplier = attribute;	m_cache.clear();	return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() { 
		return FUELCOM_EQUATION.SELECTION_SFC_C2;
	};

	@Override
	public double SFC(SpreadParmsAttribute sa, int flag, double FFMC, double BUI) {
		Double sfc;
		if ((sfc = m_cache.get(BUI)) != null)
			return sfc;
		double m_sfc = m_p1 * Math.pow(1.0 - Math.exp((0.0 - m_p2) * BUI), m_power);
		if (m_sfc > 0.0)
			m_sfc *= m_multiplier;	
						// equation 10, 11, 12, 16
		m_cache.put(BUI, m_sfc);
		return m_sfc; 
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof SFC_C2) {
			SFC_C2 cother = (SFC_C2)other;
			return m_p1 == cother.m_p1 &&
					   m_p2 == cother.m_p2 &&
					   m_power == cother.m_power &&
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
		
		SfcC2.Builder msgRet = SfcC2.newBuilder();
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
		}
	
		if(!serialized) {
			SfcC2.Parms.Builder msg = SfcC2.Parms.newBuilder();

			msg.setVersion(1);
			
			msg.setP1(HSS_Double.of(m_p1));
			msg.setP2(HSS_Double.of(m_p2));
			msg.setPower(HSS_Double.of(m_power));
			msg.setMultiplier(HSS_Double.of(m_multiplier));
			
			msgRet.setParms(msg.build());
		}

		builder.setC2(msgRet);
		return builder.build();
	}

	@Override
	public SFC_C2 deserialize(Message proto) {
		SfcC2 msgRead;
		
		try {
			msgRead = (SfcC2)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SfcC2.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_p1 = HSS_Double.from(msg.getP1());
			m_p2 = HSS_Double.from(msg.getP2());
			m_power = HSS_Double.from(msg.getPower());
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
