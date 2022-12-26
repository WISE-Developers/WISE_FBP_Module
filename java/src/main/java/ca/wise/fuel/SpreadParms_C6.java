/***********************************************************************
 * REDapp - SpreadParms_C6.java
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

public class SpreadParms_C6 extends SpreadParms_C1 {
	protected static final long serialVersionUID = 1L;

	public SpreadParms_C6(){
		super();
	}
	
	public SpreadParms_C6(SpreadParms_C6 toCopy) {
		super(toCopy);
	}
	
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C2_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C4_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C7_DEFAULTS:
			return ca.hss.general.ERROR.SEVERITY_WARNING;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ60_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ66_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ67_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ71_DEFAULTS:
			if ((m_a == 30.0) &&
				(m_b == 0.0800) &&
				(m_c == 3.0) &&
				(m_q == 0.80) &&
				(m_bui0 == 62.0) &&
				(m_max_be == 1.197) &&
				(m_height == 14.0) &&
				(m_cbh == 7.0) &&
				(m_cfl == 1.80))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ61_DEFAULTS:
			if ((m_a == 30.0) &&
				(m_b == 0.0800) &&
				(m_c == 3.0) &&
				(m_q == 0.80) &&
				(m_bui0 == 62.0) &&
				(m_max_be == 1.197) &&
				(m_height == 14.0) &&
				(m_cbh == 7.0) &&
				(m_cfl == 1.20))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;
		}
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ60_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ66_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ67_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ71_DEFAULTS:
			m_a = 30.0;
			m_b = 0.0800;
			m_c = 3.0;
			m_q = 0.80;
			m_bui0 = 62.0;
			m_max_be = 1.197;
			m_height = 14.0;
			m_cbh = 7.0;
			m_cfl = 1.80;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ61_DEFAULTS:
			m_a = 30.0;
			m_b = 0.0800;
			m_c = 3.0;
			m_q = 0.80;
			m_bui0 = 62.0;
			m_max_be = 1.197;
			m_height = 14.0;
			m_cbh = 7.0;
			m_cfl = 1.20;
			break;
		
		default:
			super.setAttributeValue(attributeKey, attribute);
		}
	}
	public short getExternalDefinition() { return (short)FUELCOM_EQUATION.SELECTION_SPREADPARMS_C1; };
	
	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options)  {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder builder = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		builder.setVersion((int)SpreadParmsAttribute.serialVersionUID);
		
		SpreadParmsC6.Builder msgRet = SpreadParmsC6.newBuilder();
		msgRet.setVersion((int)serialVersionUID);
		
		boolean serialized = false;
		
		if (!options.useVerboseOutput()) {
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ64_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz64);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.S3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_C1_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C1);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_C2_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C2);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_C3_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C3);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_C4_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C4);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_C5_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C5);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_C6_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C6);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_C7_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.C7);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ70_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz70);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ60_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz60);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ61_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz61);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ66_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz66);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ67_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz67);
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ71_DEFAULTS) == 1.0) {
				msgRet.setDefault(FuelName.Nz71);
				serialized = true;
			}
		}
		
		if (!serialized) {
			SpreadParmsC6.Parms.Builder msg = SpreadParmsC6.Parms.newBuilder();

			msg.setVersion(1);
			msg.setA(HSS_Double.of(m_a));
			msg.setB(HSS_Double.of(m_b));
			msg.setC(HSS_Double.of(m_c));
			msg.setQ(HSS_Double.of(m_q));
			msg.setBui0(HSS_Double.of(m_bui0));
			msg.setMaxBe(HSS_Double.of(m_max_be));
			msg.setHeight(HSS_Double.of(m_height));
			msg.setCbh(HSS_Double.of(m_cbh));
			msg.setCfl(HSS_Double.of(m_cfl));
			
			msgRet.setParms(msg.build());
		}

		builder.setC6(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_C6 deserialize(Message proto) {
		SpreadParmsC6 msgRead;
		
		try {
			msgRead = (SpreadParmsC6)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsC6.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_a = HSS_Double.from(msg.getA());
			m_b = HSS_Double.from(msg.getB());
			m_c = HSS_Double.from(msg.getC());
			m_q = HSS_Double.from(msg.getQ());
			m_bui0 = HSS_Double.from(msg.getBui0());
			m_max_be = HSS_Double.from(msg.getMaxBe());
			m_height = HSS_Double.from(msg.getHeight());
			m_cbh = HSS_Double.from(msg.getCbh());
			m_cfl = HSS_Double.from(msg.getCfl());
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
