/***********************************************************************
 * REDapp - DBH_2.java
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

public class DBH_2 extends DBH_HuangCommon {
	protected static final long serialVersionUID = 1L;
	
	public DBH_2() {
		super();
	}

	public DBH_2(final DBH_2 other) {
		super(other);
	}
	
	public Object clone() throws CloneNotSupportedException {
		DBH_2 other = (DBH_2)super.clone();
		return other;
	}

	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_DBH_1;
	}

	@Override
	public double dbh(double height) {
		if (height <= 1.3)
			return 0.0;
		double t = (m_b1 / m_b2) * (1.0 - Math.exp((0.0 - m_b2) * m_b3 * (height - 1.3)));
		double dbh = Math.pow(t, (1.0 / m_b3));
		return dbh;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof DBH_2) {
			return super.equals(other);
		}
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
		
		Dbh2.Builder msgRet = Dbh2.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		if(!options.useVerboseOutput()){
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_C1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_C2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_C3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_C4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_C5_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C5);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_C6_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C6);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_C7_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C7);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_D1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_D2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.D2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_M1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_M2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_M3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.HUANG_DBH_M4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.M4);
				serialized = true;
			}
		}
	
		if(!serialized){

			Dbh2.Parms.Builder msg = Dbh2.Parms.newBuilder();

			msg.setVersion(1);
			msg.setB1(HSS_Double.of(m_b1));
			msg.setB2(HSS_Double.of(m_b2));
			msg.setB3(HSS_Double.of(m_b3));
			msg.setSpeciesCode(getSpeciesCode());
			
			msgRet.setParms(msg.build());
		}

		builder.setTwo(msgRet);
		return builder.build();
	}

	@Override
	public DBH_2 deserialize(Message proto) {
		Dbh2 msgRead;
		
		try {
			msgRead = (Dbh2)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			Dbh2.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
			
			m_b1 = HSS_Double.from(msg.getB1());
			m_b2 = HSS_Double.from(msg.getB2());
			m_b3 = HSS_Double.from(msg.getB3());
			setSpeciesCode(msg.getSpeciesCode());
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
