/***********************************************************************
 * REDapp - SpreadParms_MixedDead.java
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

public class SpreadParms_MixedDead extends SpreadParms_Mixed {
	protected static final long serialVersionUID = 1L;
	
	public SpreadParms_MixedDead(){ 
		super();
	}
	
	public SpreadParms_MixedDead(SpreadParms_Mixed toCopy) throws CloneNotSupportedException {
		super(toCopy);
	}
		
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.SPREADPARMS_M1_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_M2_DEFAULTS:
			case FUELCOM_ATTRIBUTE.PC:
				return ca.hss.general.ERROR.SEVERITY_WARNING;
		
			case FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS:
			case FUELCOM_ATTRIBUTE.SPREADPARMS_M4_DEFAULTS:
				if ((m_q == 0.80) &&
					(m_bui0 == 50.0) &&
					(m_max_be == 1.250) &&
					(m_height == 10.0) &&
					(m_cbh == 6.0) &&
					(m_cfl == 0.80))
					return ca.hss.general.ERROR.S_OK;
				return ca.hss.general.ERROR.S_FALSE;
		
			case FUELCOM_ATTRIBUTE.PDF:
				return m_pc;
		}
		return super.getAttributeValue(attributeKey);
	}

	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {	
		case FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_M4_DEFAULTS:
			m_q = 0.80;
			m_bui0 = 50.0;
			m_max_be = 1.250;
			m_height = 10.0;
			m_cbh = 6.0;
			m_cfl = 0.80;
			break;
			
		case FUELCOM_ATTRIBUTE.PDF:
			if (attribute < 0.0)					break;
			if (attribute > 1.0)					break;
			m_pc = attribute;
			break;
			
		default:
			super.setAttributeValue(attributeKey, attribute);
		}
	}
	
	public short getExternalDefinition() { return (short)FUELCOM_EQUATION.SELECTION_SPREADPARMS_MIXEDDEAD; };

	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder builder = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		builder.setVersion((int)SpreadParmsAttribute.serialVersionUID);
		
		SpreadParmsMixedDead.Builder msgRet = SpreadParmsMixedDead.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		boolean serialized = false;
		
		if(!options.useVerboseOutput()) {
			SpreadParmsMixedDead.DefaultParms.Builder msgDef = null;
			
			if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_M1_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixedDead.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.M1);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_M2_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixedDead.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.M2);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixedDead.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.M3);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_M4_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixedDead.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.M4);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ54_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixedDead.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.Nz54);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			else if (getAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_NZ69_DEFAULTS) == 1.0) {
				msgDef = SpreadParmsMixedDead.DefaultParms.newBuilder();
				msgDef.setDefault(FuelName.Nz69);
				msgRet.setDefault(msgDef.build());
				serialized = true;
			}
			
			if((msgDef != null) && (m_pc != 0.5)) {
				msgDef.setPdf(HSS_Double.of(m_pc * 100.0));
				msgRet.setDefault(msgDef.build());
			}
		}

		if(!serialized) {
			SpreadParmsMixedDead.Parms.Builder msg = SpreadParmsMixedDead.Parms.newBuilder();

			msg.setVersion(1);
			msg.setQ(HSS_Double.of(m_q));
			msg.setBui0(HSS_Double.of(m_bui0));
			msg.setMaxBe(HSS_Double.of(m_max_be));
			msg.setHeight(HSS_Double.of(m_height));
			msg.setCbh(HSS_Double.of(m_cbh));
			msg.setCfl(HSS_Double.of(m_cfl));
			msg.setPdf(HSS_Double.of(m_pc * 100.0));
			
			msgRet.setParms(msg.build());
		}

		builder.setMixedDead(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_MixedDead deserialize(Message proto) {
		SpreadParmsMixedDead msgRead;
		
		try {
			msgRead = (SpreadParmsMixedDead)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsMixedDead.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	
			
			m_q = HSS_Double.from(msg.getQ());
			m_bui0 = HSS_Double.from(msg.getBui0());
			m_max_be = HSS_Double.from(msg.getMaxBe());
			m_height = HSS_Double.from(msg.getHeight());
			m_cbh = HSS_Double.from(msg.getCbh());
			m_cfl = HSS_Double.from(msg.getCfl());
			m_pc = HSS_Double.from(msg.getPdf()) * 0.01;
		}
		else {
			
			SpreadParmsMixedDead.DefaultParms msgDef = msgRead.getDefault();
			FuelName def = msgDef.getDefault();

			short val = GetDefaultValue(def);

			if(val != (short) -1)
				setAttributeValue(val, 0.0);
			else
				throw new IllegalArgumentException();
			
			if(msgDef.hasPdf())
				m_pc = msgDef.getPdf().getValue() * 0.01;
		}
		
		if(m_C2 == null || m_D1 == null)
			throw new IllegalArgumentException();
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
