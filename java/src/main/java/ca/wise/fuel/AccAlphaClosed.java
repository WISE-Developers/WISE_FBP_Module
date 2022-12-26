/***********************************************************************
 * REDapp - AccAlphaClosed.java
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

import static ca.wise.fuel.FUELCOM_ATTRIBUTE.*;
import static java.lang.Math.*;

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.hss.math.HSS_Double;
import ca.wise.fuel.proto.*;

/**
 * @author rbryce
 *
 */

class AccAlphaClosed extends AccAlphaAttribute {
	protected static final long serialVersionUID = 1L;
	// equation 72, for species "O1","C1","S1","S2","S3"
	public double m_init;
	public double m_multiplier;
	public double m_power;
	public double m_exp_multiplier;

	public AccAlphaClosed() {
		m_init = 0.115;
		m_multiplier = 18.8;
		m_power = 2.5;
		m_exp_multiplier = 8.0;
	}
	
	/* (non-Javadoc)
	 * @see fuelcom.FuelAttribute#GetAttributeValue(short)
	 */
	@Override
	public double getAttributeValue(short attributeKey) {
		//double attribute;
		switch (attributeKey) {
			case ACCEL_C2_DEFAULTS:
			case ACCEL_C3_DEFAULTS:
			case ACCEL_C4_DEFAULTS:
			case ACCEL_C5_DEFAULTS:
			case ACCEL_C6_DEFAULTS:
			case ACCEL_C7_DEFAULTS:
			case ACCEL_D1_DEFAULTS:
			case ACCEL_M1_DEFAULTS:
			case ACCEL_M2_DEFAULTS:
			case ACCEL_M3_DEFAULTS:
			case ACCEL_M4_DEFAULTS:		if ((m_init == 0.115) &&
											(m_multiplier == 18.8) &&
											(m_power == 2.5) &&
											(m_exp_multiplier == 8.0))
											return 1.0;
										return 0.0;

			case ACCEL_INIT:			return m_init;
			case ACCEL_MULTIPLIER:		return  m_multiplier;
			case ACCEL_POWER:			return  m_power;
			case ACCEL_EXP_MULTIPLIER:	return  m_exp_multiplier;
		}

		return super.getAttributeValue(attributeKey);
	}

	/* (non-Javadoc)
	 * @see fuelcom.FuelAttribute#SetAttributeValue(short, double)
	 */
	@Override
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case ACCEL_C2_DEFAULTS:
			case ACCEL_C3_DEFAULTS:
			case ACCEL_C4_DEFAULTS:
			case ACCEL_C5_DEFAULTS:
			case ACCEL_C6_DEFAULTS:
			case ACCEL_C7_DEFAULTS:
			case ACCEL_D1_DEFAULTS:
			case ACCEL_M1_DEFAULTS:
			case ACCEL_M2_DEFAULTS:
			case ACCEL_M3_DEFAULTS:
			case ACCEL_M4_DEFAULTS:	m_init = 0.115;
									m_multiplier = 18.8;
									m_power = 2.5;
									m_exp_multiplier = 8.0;
	//								m_cfb = -1.0;
									return;
	
			case ACCEL_INIT:			m_init = attribute;				return;
			case ACCEL_MULTIPLIER:		m_multiplier = attribute;		return;
			case ACCEL_POWER:			m_power = attribute;			return;
			case ACCEL_EXP_MULTIPLIER:	m_exp_multiplier = attribute;	return;
		}
		super.setAttributeValue(attributeKey, attribute);
	}

	/* (non-Javadoc)
	 * @see fuelcom.AccAlphaAttribute#AccAlpha(double)
	 */
	@Override
	public double accAlpha(double CFB) {
		double aa = m_init - m_multiplier * pow(CFB, m_power) * exp((0.0 - m_exp_multiplier) * CFB);	// equation 72
		return aa; 
	}

	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_ACCEL_CLOSED;
	}
	
	@Override
	public ca.wise.fuel.proto.AccAlphaAttribute serialize(SerializeProtoOptions options)  {
		ca.wise.fuel.proto.AccAlphaAttribute.Builder builder = ca.wise.fuel.proto.AccAlphaAttribute.newBuilder();
		builder.setVersion((int)AccAlphaAttribute.serialVersionUID);
		
		ca.wise.fuel.proto.AccAlphaClosed.Builder msgRet = ca.wise.fuel.proto.AccAlphaClosed.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_C2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_C3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_C4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_C5_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C5);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_C6_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C6);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_C7_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C7);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_D1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_M1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_M2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
				serialized = true;
			}
		}

		if(!serialized){

			ca.wise.fuel.proto.AccAlphaClosed.Parms.Builder msg = ca.wise.fuel.proto.AccAlphaClosed.Parms.newBuilder();

			msg.setVersion(1);
			msg.setInit(HSS_Double.of(m_init));
			msg.setMultiplier(HSS_Double.of(m_multiplier));
			msg.setPower(HSS_Double.of(m_power));
			msg.setExpMultiplier(HSS_Double.of(m_exp_multiplier));
			
			msgRet.setParms(msg.build());
		}

		builder.setAlphaClosed(msgRet);
		return builder.build();
	}

	@Override
	public AccAlphaClosed deserialize(Message proto) {
		ca.wise.fuel.proto.AccAlphaClosed msgRead;
		
		try {
			msgRead = (ca.wise.fuel.proto.AccAlphaClosed)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			ca.wise.fuel.proto.AccAlphaClosed.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();

			m_init = HSS_Double.from(msg.getInit());
			m_multiplier = HSS_Double.from(msg.getMultiplier());
			m_power = HSS_Double.from(msg.getPower());
			m_exp_multiplier = HSS_Double.from(msg.getExpMultiplier());

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
			case C2:
				val = FUELCOM_ATTRIBUTE.ACCEL_C2_DEFAULTS;
				break;

			case C3:
				val = FUELCOM_ATTRIBUTE.ACCEL_C3_DEFAULTS;
				break;

			case C4:
				val = FUELCOM_ATTRIBUTE.ACCEL_C4_DEFAULTS;
				break;

			case C5:
				val = FUELCOM_ATTRIBUTE.ACCEL_C5_DEFAULTS;
				break;

			case C6:
				val = FUELCOM_ATTRIBUTE.ACCEL_C6_DEFAULTS;
				break;

			case C7:
				val = FUELCOM_ATTRIBUTE.ACCEL_C7_DEFAULTS;
				break;

			case D1:
				val = FUELCOM_ATTRIBUTE.ACCEL_D1_DEFAULTS;
				break;

			case M1:
				val = FUELCOM_ATTRIBUTE.ACCEL_M1_DEFAULTS;
				break;

			case M2:
				val = FUELCOM_ATTRIBUTE.ACCEL_M2_DEFAULTS;
				break;

			case M3:
				val = FUELCOM_ATTRIBUTE.ACCEL_M3_DEFAULTS;
				break;

			case M4:
				val = FUELCOM_ATTRIBUTE.ACCEL_M4_DEFAULTS;
				break;

			case O1A:
				val = FUELCOM_ATTRIBUTE.ACCEL_O1A_DEFAULTS;
				break;

			case O1B:
				val = FUELCOM_ATTRIBUTE.ACCEL_O1B_DEFAULTS;
				break;

			case S1:
				val = FUELCOM_ATTRIBUTE.ACCEL_S1_DEFAULTS;
				break;

			case S2:
				val = FUELCOM_ATTRIBUTE.ACCEL_S2_DEFAULTS;
				break;

			case S3:
				val = FUELCOM_ATTRIBUTE.ACCEL_S3_DEFAULTS;
				break;

			default:
				val = -1;
		}

		return val;
	}
}
