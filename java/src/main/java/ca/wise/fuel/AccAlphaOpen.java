/***********************************************************************
 * REDapp - AccAlphaOpen.java
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

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.hss.math.HSS_Double;
import ca.wise.fuel.proto.*;

class AccAlphaOpen extends AccAlphaAttribute {
	protected static final long serialVersionUID = 1L;
	public double m_init;
	
	public AccAlphaOpen() {
		setAttributeValue((short)ACCEL_C1_DEFAULTS, 0.0);
	}
	
	/* (non-Javadoc)
	 * @see fuelcom.AccAlphaAttribute#AccAlpha(double)
	 */
	@Override
	public double accAlpha(double CFB) {
		return m_init;
	}

	/* (non-Javadoc)
	 * @see fuelcom.FuelAttribute#GetAttributeValue(short)
	 */
	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case ACCEL_C1_DEFAULTS:
			case ACCEL_O1A_DEFAULTS:
			case ACCEL_O1B_DEFAULTS:
			case ACCEL_S1_DEFAULTS:
			case ACCEL_S2_DEFAULTS:
			case ACCEL_S3_DEFAULTS:							if (m_init == 0.115)
																return 1.0;
															return 0.0;
			case ACCEL_INIT:								return m_init;
		}

		return super.getAttributeValue(attributeKey);
	}
	
	/* (non-Javadoc)
	 * @see fuelcom.FuelAttribute#SetAttributeValue(short, double)
	 */
	@Override
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case ACCEL_C1_DEFAULTS:
			case ACCEL_O1A_DEFAULTS:
			case ACCEL_O1B_DEFAULTS:
			case ACCEL_S1_DEFAULTS:
			case ACCEL_S2_DEFAULTS:
			case ACCEL_S3_DEFAULTS:		m_init = 0.115;			return;
	
			case ACCEL_INIT:			m_init = attribute;		return;
		}
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_ACCEL_OPEN;
	}

	@Override
	public ca.wise.fuel.proto.AccAlphaAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.AccAlphaAttribute.Builder builder = ca.wise.fuel.proto.AccAlphaAttribute.newBuilder();
		builder.setVersion((int)AccAlphaAttribute.serialVersionUID);
		
		ca.wise.fuel.proto.AccAlphaOpen.Builder msgRet = ca.wise.fuel.proto.AccAlphaOpen.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_C1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_O1A_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1A);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_O1B_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.O1B);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_S1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_S2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.ACCEL_S3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S3);
				serialized = true;
			}
		}

		if(!serialized){

			ca.wise.fuel.proto.AccAlphaOpen.Parms.Builder msg = ca.wise.fuel.proto.AccAlphaOpen.Parms.newBuilder();

			msg.setVersion(1);
			msg.setInit(HSS_Double.of(m_init));
			
			msgRet.setParms(msg.build());
		}

		builder.setAlphaOpen(msgRet);
		return builder.build();
	}

	@Override
	public AccAlphaOpen deserialize(Message proto) {
		ca.wise.fuel.proto.AccAlphaOpen msgRead;
		
		try {
			msgRead = (ca.wise.fuel.proto.AccAlphaOpen)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			ca.wise.fuel.proto.AccAlphaOpen.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
			
			m_init = HSS_Double.from(msg.getInit());

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
				val = (short) -1;
		}

		return val;
	}
}
