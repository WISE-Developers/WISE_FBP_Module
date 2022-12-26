/***********************************************************************
 * REDapp - CFB_C1.java
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

import ca.hss.annotations.Source;
import static ca.wise.fuel.FUELCOM_ATTRIBUTE.*;

import java.io.*;
import java.util.Optional;

import ca.hss.general.OutVariable;
import ca.hss.math.HSS_Double;

import com.google.protobuf.Message;
import ca.wise.serialize.*;

import ca.wise.fuel.proto.*;

@Source(sourceFile="cfb.cpp", project="FuelCOM")
public class CFB_C1 extends CFBAttribute {
	protected static final long serialVersionUID = 1L;
	
	private double m_csi_multiplier;
	private double m_csi_cbh_exponent;
	private double m_csi_exp_adder;
	private double m_csi_exp_multiplier;
	private double m_csi_power;
	private double m_rso_div;
	private double m_cfb_exp;
	private boolean m_cfb_possible;

	public CFB_C1() {
		setAttributeValue((short)CFB_C1_DEFAULTS, 0.0);
	}
	
	public CFB_C1(final CFB_C1 other) {
		m_csi_multiplier = other.m_csi_multiplier;
		m_csi_cbh_exponent = other.m_csi_cbh_exponent;
		m_csi_exp_adder = other.m_csi_exp_adder;
		m_csi_exp_multiplier = other.m_csi_exp_multiplier;
		m_csi_power = other.m_csi_power;
		m_rso_div = other.m_rso_div;
		m_cfb_exp = other.m_cfb_exp;
		m_cfb_possible = other.m_cfb_possible;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		CFB_C1 other = (CFB_C1)super.clone();
		return other;
	}

	public void serialize(ObjectOutputStream out) throws IOException {
		writeObject(out);
	}

	private void writeObject(ObjectOutputStream out) throws IOException {
		out.defaultWriteObject();
	}

	private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		in.defaultReadObject();
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case CFB_C1_DEFAULTS:
			case CFB_C2_DEFAULTS:
			case CFB_C3_DEFAULTS:
			case CFB_C4_DEFAULTS:
			case CFB_C5_DEFAULTS:
			case CFB_C6_DEFAULTS:
			case CFB_C7_DEFAULTS:
			case CFB_D1_DEFAULTS:
			case CFB_M1_DEFAULTS:
			case CFB_M2_DEFAULTS:
			case CFB_M3_DEFAULTS:
			case CFB_M4_DEFAULTS:
			case CFB_O1A_DEFAULTS:
			case CFB_O1B_DEFAULTS:
			case CFB_S1_DEFAULTS:
			case CFB_S2_DEFAULTS:
			case CFB_S3_DEFAULTS:		if ((m_csi_multiplier == 0.001) &&
											(m_csi_cbh_exponent == 1.5) &&
											(m_csi_exp_adder == 460.0) &&
											(m_csi_exp_multiplier == 25.9) &&
											(m_csi_power == 1.5) &&
											(m_rso_div == 300.0) &&
											(m_cfb_exp == 0.23)) {
											if (m_cfb_possible != ((attributeKey == FUELCOM_ATTRIBUTE.CFB_D1_DEFAULTS) ||
													(attributeKey == FUELCOM_ATTRIBUTE.CFB_O1A_DEFAULTS) ||
													(attributeKey == FUELCOM_ATTRIBUTE.CFB_O1B_DEFAULTS) ||
													(attributeKey == FUELCOM_ATTRIBUTE.CFB_S1_DEFAULTS) ||
													(attributeKey == FUELCOM_ATTRIBUTE.CFB_S2_DEFAULTS) ||
													(attributeKey == FUELCOM_ATTRIBUTE.CFB_S3_DEFAULTS) ||
													(attributeKey == FUELCOM_ATTRIBUTE.CFB_NON_DEFAULTS)))
														return 1.0;
										}
										return 0.0;
			case CFB_CSI_MULTIPLIER:	return m_csi_multiplier;
			case CFB_CBH_EXPONENT:		return m_csi_cbh_exponent;
			case CFB_EXP_ADDER:			return m_csi_exp_adder;
			case CFB_EXP_MULTIPLIER:	return m_csi_exp_multiplier;
			case CFB_CSI_POWER:			return m_csi_power;
			case CFB_RSO_DIV:			return m_rso_div;
			case CFB_EXP:				return m_cfb_exp;
			case CFB_POSSIBLE:			return ((m_cfb_possible) ? 1.0 : 0.0);
		}

		return super.getAttributeValue(attributeKey);
	}

	@Override
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case CFB_C1_DEFAULTS:
			case CFB_C2_DEFAULTS:
			case CFB_C3_DEFAULTS:
			case CFB_C4_DEFAULTS:
			case CFB_C5_DEFAULTS:
			case CFB_C6_DEFAULTS:
			case CFB_C7_DEFAULTS:
			case CFB_D1_DEFAULTS:
			case CFB_M1_DEFAULTS:
			case CFB_M2_DEFAULTS:
			case CFB_M3_DEFAULTS:
			case CFB_M4_DEFAULTS:
			case CFB_O1A_DEFAULTS:
			case CFB_O1B_DEFAULTS:
			case CFB_S1_DEFAULTS:
			case CFB_S2_DEFAULTS:
			case CFB_S3_DEFAULTS:		m_csi_multiplier = 0.001;
										m_csi_cbh_exponent = 1.5;
										m_csi_exp_adder = 460.0;
										m_csi_exp_multiplier = 25.9;
										m_csi_power = 1.5;
										m_rso_div = 300.0;
										m_cfb_exp = 0.23;
										m_cfb_possible = (!((attributeKey == FUELCOM_ATTRIBUTE.CFB_D1_DEFAULTS) ||
												(attributeKey == FUELCOM_ATTRIBUTE.CFB_O1A_DEFAULTS) ||
												(attributeKey == FUELCOM_ATTRIBUTE.CFB_O1B_DEFAULTS) ||
												(attributeKey == FUELCOM_ATTRIBUTE.CFB_S1_DEFAULTS) ||
												(attributeKey == FUELCOM_ATTRIBUTE.CFB_S2_DEFAULTS) ||
												(attributeKey == FUELCOM_ATTRIBUTE.CFB_S3_DEFAULTS)));
										return;

			case CFB_CSI_MULTIPLIER:	m_csi_multiplier = attribute;						return;
			case CFB_CBH_EXPONENT:		m_csi_cbh_exponent = attribute;						return;
			case CFB_EXP_ADDER:			m_csi_exp_adder = attribute;						return;
			case CFB_EXP_MULTIPLIER:	m_csi_exp_multiplier = attribute;					return;
			case CFB_CSI_POWER:			m_csi_power = attribute;							return;
			case CFB_RSO_DIV:			m_rso_div = attribute;								return;
			case CFB_EXP:				m_cfb_exp = attribute;								return;
			case CFB_POSSIBLE:			m_cfb_possible = (attribute == 0.0 ? false : true);	return; 
		}

		super.setAttributeValue(attributeKey, attribute);
	}

	@Override
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_CFB_C1;
	}

	@Override
	public double cfb(double CBH, double FMC, double SFC, double ROS, OutVariable<Double> rso, OutVariable<Double> csi)	{
		double c_rso, c_csi, c_cfb;
		
		if(CBH == 0.0)
			c_csi = 0.0;
		else
			c_csi = m_csi_multiplier * Math.pow(CBH, m_csi_cbh_exponent) * Math.pow(m_csi_exp_adder + m_csi_exp_multiplier * FMC, m_csi_power);

		if(SFC == 0.0)
			c_rso = 0.0;
		else
			c_rso = c_csi / m_rso_div / SFC;

		if(!m_cfb_possible)
			c_cfb = 0.0;
		else {
			c_cfb = 1.0 - Math.exp(-1 * m_cfb_exp * (ROS - c_rso));

			if(c_cfb < 0.0)
				c_cfb = 0.0;
		}
		rso.value = c_rso;
		csi.value = c_csi;

		return c_cfb;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof CFB_C1) {
			CFB_C1 cother = (CFB_C1)other;
			return m_csi_multiplier == cother.m_csi_multiplier &&
					   m_csi_cbh_exponent == cother.m_csi_cbh_exponent &&
					   m_csi_exp_adder == cother.m_csi_exp_adder &&
					   m_csi_exp_multiplier == cother.m_csi_exp_multiplier &&
					   m_csi_power == cother.m_csi_power &&
					   m_rso_div == cother.m_rso_div &&
					   m_cfb_exp == cother.m_cfb_exp &&
					   m_cfb_possible == cother.m_cfb_possible;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.CfbAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.CfbAttribute.Builder builder = ca.wise.fuel.proto.CfbAttribute.newBuilder();
		builder.setVersion((int)CFBAttribute.serialVersionUID);
		
		CfbC1.Builder msgRet = CfbC1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_C1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_C2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_C3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_C4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_C5_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C5);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_C6_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C6);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_C7_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C7);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_D1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_M1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_M2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_O1A_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_O1B_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1B);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_S1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_S2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.CFB_S3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S3);
				serialized = true;
			}
		}
	
		if(!serialized) {
			CfbC1.Parms.Builder msg = CfbC1.Parms.newBuilder();

			msg.setVersion(1);

			msg.setCsiMultiplier(HSS_Double.of(m_csi_multiplier));
			msg.setCsiCbhExponent(HSS_Double.of(m_csi_cbh_exponent));
			msg.setCsiExpAdder(HSS_Double.of(m_csi_exp_adder));
			msg.setCsiExpMultiplier(HSS_Double.of(m_csi_exp_multiplier));
			msg.setCsiPower(HSS_Double.of(m_csi_power));
			msg.setRsoDiv(HSS_Double.of(m_rso_div));
			msg.setCfbExp(HSS_Double.of(m_cfb_exp));
			msg.setCfbPossible(m_cfb_possible);
			
			msgRet.setParms(msg.build());
		}

		builder.setC1(msgRet);
		return builder.build();
	}

	@Override
	public CFB_C1 deserialize(Message proto) {
		CfbC1 msgRead;
		
		try {
			msgRead = (CfbC1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			CfbC1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
			
			m_csi_multiplier = HSS_Double.from(msg.getCsiMultiplier());
			m_csi_cbh_exponent = HSS_Double.from(msg.getCsiCbhExponent());
			m_csi_exp_adder = HSS_Double.from(msg.getCsiExpAdder());
			m_csi_exp_multiplier = HSS_Double.from(msg.getCsiExpMultiplier());
			m_csi_power = HSS_Double.from(msg.getCsiPower());
			m_rso_div = HSS_Double.from(msg.getRsoDiv());
			m_cfb_exp = HSS_Double.from(msg.getCfbExp());
			m_cfb_possible = msg.getCfbPossible();

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
	
	private short GetDefaultValue(FuelName def) {
		short val;

		switch (def) {
		case C1:
			val = FUELCOM_ATTRIBUTE.CFB_C1_DEFAULTS;
			break;

		case C2:
			val = FUELCOM_ATTRIBUTE.CFB_C2_DEFAULTS;
			break;

		case C3:
			val = FUELCOM_ATTRIBUTE.CFB_C3_DEFAULTS;
			break;

		case C4:
			val = FUELCOM_ATTRIBUTE.CFB_C4_DEFAULTS;
			break;

		case C5:
			val = FUELCOM_ATTRIBUTE.CFB_C5_DEFAULTS;
			break;

		case C6:
			val = FUELCOM_ATTRIBUTE.CFB_C6_DEFAULTS;
			break;

		case C7:
			val = FUELCOM_ATTRIBUTE.CFB_C7_DEFAULTS;
			break;

		case D1:
			val = FUELCOM_ATTRIBUTE.CFB_D1_DEFAULTS;
			break;

		case M1:
			val = FUELCOM_ATTRIBUTE.CFB_M1_DEFAULTS;
			break;

		case M2:
			val = FUELCOM_ATTRIBUTE.CFB_M2_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.CFB_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.CFB_M4_DEFAULTS;
			break;

		case O1A:
			val = FUELCOM_ATTRIBUTE.CFB_O1A_DEFAULTS;
			break;

		case O1B:
			val = FUELCOM_ATTRIBUTE.CFB_O1B_DEFAULTS;
			break;

		case S1:
			val = FUELCOM_ATTRIBUTE.CFB_S1_DEFAULTS;
			break;

		case S2:
			val = FUELCOM_ATTRIBUTE.CFB_S2_DEFAULTS;
			break;

		case S3:
			val = FUELCOM_ATTRIBUTE.CFB_S3_DEFAULTS;
			break;

		case Non:
			val = FUELCOM_ATTRIBUTE.CFB_C1_DEFAULTS;
			break;

		default:
			val = (short) -1;
		}

		return val;
	}
}
