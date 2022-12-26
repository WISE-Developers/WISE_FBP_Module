/***********************************************************************
 * REDapp - DBH_None
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
import ca.wise.fuel.proto.*;

public class DBH_None extends DBHAttribute {
	protected static final long serialVersionUID = 1L;
	
	private String m_SpeciesCode;
	
	public DBH_None() {
		m_SpeciesCode = "";
	}

	public DBH_None(final DBH_None toCopy) {
	m_SpeciesCode = toCopy.m_SpeciesCode;
	}
	
	public Object clone() throws CloneNotSupportedException {
		DBH_None other = (DBH_None)super.clone();
		return other;
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		super.setAttributeValue(attributeKey, attribute);
	}

	public String getSpeciesCode() {
		return m_SpeciesCode;
	}

	public void setSpeciesCode(String code) {
		m_SpeciesCode = code;
	}

	public short getExternalDefinition() { 
		return FUELCOM_EQUATION.SELECTION_DBH_NONE;
	};

	@Override
	public double dbh(double height) {
		return 0.0;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof DBH_None)
			return true;
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.DbhAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.DbhAttribute.Builder builder = ca.wise.fuel.proto.DbhAttribute.newBuilder();
		builder.setVersion((int)DBHAttribute.serialVersionUID);
		
		DbhNone.Builder msgRet = DbhNone.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		DbhNone.Parms.Builder msg = DbhNone.Parms.newBuilder();

		msg.setVersion(1);
		msg.setSpeciesCode(m_SpeciesCode);
		
		msgRet.setParms(msg.build());

		builder.setNone(msgRet);
		return builder.build();
	}

	@Override
	public DBH_None deserialize(Message proto) {
		DbhNone msgRead;
		
		try {
			msgRead = (DbhNone)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			DbhNone.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
			
			m_SpeciesCode = msg.getSpeciesCode();
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
	
	public short GetDefaultValue(FuelName def) {
		short val;

		switch (def) {
		case C1:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_C1_DEFAULTS;
			break;

		case C2:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_C2_DEFAULTS;
			break;

		case C3:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_C3_DEFAULTS;
			break;

		case C4:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_C4_DEFAULTS;
			break;

		case C5:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_C5_DEFAULTS;
			break;

		case C6:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_C6_DEFAULTS;
			break;

		case C7:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_C7_DEFAULTS;
			break;

		case D1:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_D1_DEFAULTS;
			break;

		case D2:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_D2_DEFAULTS;
			break;

		case M1:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_M1_DEFAULTS;
			break;

		case M2:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_M2_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.HUANG_DBH_M4_DEFAULTS;
			break;

		default:
			val = (short) -1;
		}

		return val;
	}
}
