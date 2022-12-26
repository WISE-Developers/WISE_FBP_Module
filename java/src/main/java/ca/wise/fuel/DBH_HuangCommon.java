/***********************************************************************
 * REDapp - DBH_HuangCommon.java
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

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.hss.math.HSS_Double;
import ca.wise.fuel.proto.*;

abstract class DBH_HuangCommon extends DBHAttribute {
	protected static final long serialVersionUID = 1L;
	
	protected double m_b1, m_b2, m_b3;
	private String m_SpeciesCode;
	
	public DBH_HuangCommon() {
		m_b1 = -1.0;
		m_b2 = -1.0;
		m_b3 = -1.0;
		m_SpeciesCode = "";
	}

	public DBH_HuangCommon(final DBH_HuangCommon toCopy) {
		m_b1 = toCopy.m_b1;
		m_b2 = toCopy.m_b2;
		m_b3 = toCopy.m_b3;
		m_SpeciesCode = toCopy.m_SpeciesCode;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		DBH_HuangCommon other = (DBH_HuangCommon)super.clone();
		return other;
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.HUANG_DBH_C1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.HUANG_DBH_C2_DEFAULTS:	if ((m_b1 == 2.1948) &&
																(m_b2 == 0.6184) &&
																(m_b3 == -0.0273))
																return 1.0;
															return 0.0;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_C3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.HUANG_DBH_C4_DEFAULTS:	if ((m_b1 == 2.0408) &&
																(m_b2 == 0.5377) &&
																(m_b3 == -0.0455))
																return 1.0;
															return 0.0;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_C5_DEFAULTS:
			case FUELCOM_ATTRIBUTE.HUANG_DBH_C6_DEFAULTS:	if ((m_b1 == 2.1881) &&
																(m_b2 == 0.6161) &&
																(m_b3 == -0.0264))
																return 1.0;
															return 0.0;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_C7_DEFAULTS:	if ((m_b1 == 2.9394) &&
																(m_b2 == 0.4047) &&
																(m_b3 == -0.0626))
																return 1.0;
															return 0.0;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_D1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.HUANG_DBH_D2_DEFAULTS:	if ((m_b1 == 1.1091) &&
																(m_b2 == 0.8055) &&
																(m_b3 == -0.0332))
																return 1.0;
															return 0.0;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_M1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.HUANG_DBH_M2_DEFAULTS:	if ((m_b1 == 2.2494) &&
																(m_b2 == 0.6556) &&
																(m_b3 == -0.0233))
																return 1.0;
															return 0.0;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_M3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.HUANG_DBH_M4_DEFAULTS:	if ((m_b1 == 2.1260) &&
																(m_b2 == 0.7151) &&
																(m_b3 == -0.0182))
																return 1.0;
															return 0.0;

			case FUELCOM_ATTRIBUTE.HUANG_DBH_B1:	return m_b1;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_B2:	return m_b2;
			case FUELCOM_ATTRIBUTE.HUANG_DBH_B3:	return m_b3;
		}
		
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.HUANG_DBH_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.HUANG_DBH_C2_DEFAULTS:	m_b1 = 2.1948;	m_b2 = 0.6184;	m_b3 = -0.0273;	m_SpeciesCode = "Sb";	return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE.HUANG_DBH_C4_DEFAULTS:	m_b1 = 2.0408;	m_b2 = 0.5377;	m_b3 = -0.0455;	m_SpeciesCode = "Pj";	return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE.HUANG_DBH_C6_DEFAULTS:	m_b1 = 2.1881;	m_b2 = 0.6161;	m_b3 = -0.0264;	m_SpeciesCode = "Pl";	return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_C7_DEFAULTS:	m_b1 = 2.9394;	m_b2 = 0.4047;	m_b3 = -0.0626; m_SpeciesCode = "Fd";	return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.HUANG_DBH_D2_DEFAULTS:	m_b1 = 1.1091;	m_b2 = 0.8055;	m_b3 = -0.0332;	m_SpeciesCode = "Aw";	return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.HUANG_DBH_M2_DEFAULTS:	m_b1 = 2.2494;	m_b2 = 0.6556;	m_b3 = -0.0233;	m_SpeciesCode = "Sw";	return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE.HUANG_DBH_M4_DEFAULTS:	m_b1 = 2.1260;	m_b2 = 0.7151;	m_b3 = -0.0182;	m_SpeciesCode = "Fb";	return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_B1:			m_b1 = attribute;		return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_B2:			m_b2 = attribute;		return;
		case FUELCOM_ATTRIBUTE.HUANG_DBH_B3:			m_b3 = attribute;		return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public String getSpeciesCode() {
		return m_SpeciesCode;
	}

	public void setSpeciesCode(String code) {
		m_SpeciesCode = code;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof DBH_HuangCommon) {
			DBH_HuangCommon a = (DBH_HuangCommon)other;
			if (m_b1 != a.m_b1)			return false;
			if (m_b2 != a.m_b2)			return false;
			if (m_b3 != a.m_b3)			return false;
			return true;
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
		
		DbhHuangCommon.Builder msgRet = DbhHuangCommon.newBuilder();
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

		if(!serialized) {
			DbhHuangCommon.Parms.Builder msg = DbhHuangCommon.Parms.newBuilder();

			msg.setVersion(1);
			msg.setB1(HSS_Double.of(m_b1));
			msg.setB2(HSS_Double.of(m_b2));
			msg.setB3(HSS_Double.of(m_b3));
			msg.setSpeciesCode(m_SpeciesCode);
			
			msgRet.setParms(msg.build());
		}

		builder.setHuangCommon(msgRet);
		return builder.build();
	}

	@Override
	public DBH_HuangCommon deserialize(Message proto) {
		DbhHuangCommon msgRead;
		
		try {
			msgRead = (DbhHuangCommon)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			DbhHuangCommon.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
			
			m_b1 = HSS_Double.from(msg.getB1());
			m_b2 = HSS_Double.from(msg.getB2());
			m_b3 = HSS_Double.from(msg.getB3());
			m_SpeciesCode = msg.getSpeciesCode();

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
