/***********************************************************************
 * REDapp - SpreadParms_C1.java
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
import ca.wise.fuel.proto.*;
import ca.wise.serialize.SerializeProtoOptions;
import ca.hss.math.HSS_Double;

public class SpreadParms_C1 extends SpreadParms_S1 {
	protected static final long serialVersionUID = 1L;
	
	protected double m_height;	// stand height (m)
	protected double m_cbh;		// height to live crown base
	protected double m_cfl;		// crown fuel load

	public SpreadParms_C1(){
		super();
		m_height = -1.0;
		m_cbh = -1.0;
		m_cfl = -1.0;
	}
	
	public SpreadParms_C1(SpreadParms_C1 toCopy) {
		super(toCopy);
		m_height = toCopy.m_height;
		m_cbh = toCopy.m_cbh;
		m_cfl = toCopy.m_cfl;
	}
	
	public boolean equals (FuelAttribute cmp){
		SpreadParms_C1 compare = null;
		if(!(cmp instanceof SpreadParms_C1)) return false;
		else compare = (SpreadParms_C1) cmp;
		
		if (!super.equals(compare))
			return false;
		if (m_height != compare.m_height)			return false;
		if (m_cbh != compare.m_cbh)					return false;
		if (m_cfl != compare.m_cfl)					return false;
		return true;
	}
	public double height() { return m_height; };
	public double cbh() { return m_cbh; };
	public double cfl() { return m_cfl; };

	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS:
			return ca.hss.general.ERROR.SEVERITY_WARNING;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ70_DEFAULTS:
			if ((m_a == 90.0) &&
				(m_b == 0.0649) &&
				(m_c == 4.5) &&
				(m_q == 0.90) &&
				(m_bui0 == 72.0) &&
				(m_max_be == 1.076) &&
				(m_height == 10.0) &&
				(m_cbh == 2.0) &&
				(m_cfl == 0.75))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C2_DEFAULTS:
			if ((m_a == 110.0) &&
				(m_b == 0.0282) &&
				(m_c == 1.5) &&
				(m_q == 0.70) &&
				(m_bui0 == 64.0) &&
				(m_max_be == 1.321) &&
				(m_height == 7.0) &&
				(m_cbh == 3.0) &&
				(m_cfl == 0.80))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C3_DEFAULTS:
			if ((m_a == 110.0) &&
				(m_b == 0.0444) &&
				(m_c == 3.0) &&
				(m_q == 0.75) &&
				(m_bui0 == 62.0) &&
				(m_max_be == 1.261) &&
				(m_height == 18.0) &&
				(m_cbh == 8.0) &&
				(m_cfl == 1.15))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C4_DEFAULTS:
			if ((m_a == 110.0) &&
				(m_b == 0.0293) &&
				(m_c == 1.5) &&
				(m_q == 0.80) &&
				(m_bui0 == 66.0) &&
				(m_max_be == 1.184) &&
				(m_height == 10.0) &&
				(m_cbh == 4.0) &&
				(m_cfl == 1.20))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C5_DEFAULTS:
			if ((m_a == 30.0) &&
				(m_b == 0.0697) &&
				(m_c == 4.0) &&
				(m_q == 0.80) &&
				(m_bui0 == 56.0) &&
				(m_max_be == 1.220) &&
				(m_height == 25.0) &&
				(m_cbh == 18.0) &&
				(m_cfl == 1.20))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C7_DEFAULTS:
			if ((m_a == 45.0) &&
				(m_b == 0.0305) &&
				(m_c == 2.0) &&
				(m_q == 0.85) &&
				(m_bui0 == 106.0) &&
				(m_max_be == 1.134) &&
				(m_height == 20.0) &&
				(m_cbh == 10.0) &&
				(m_cfl == 0.50))
				return ca.hss.general.ERROR.S_OK;
			return ca.hss.general.ERROR.S_FALSE;

		case FUELCOM_ATTRIBUTE.CBH:
			return m_cbh;

		case FUELCOM_ATTRIBUTE.CFL:
			return m_cfl;

		case FUELCOM_ATTRIBUTE.TREE_HEIGHT:
			return m_height;
		}
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.SPREADPARMS_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE.SPREADPARMS_NZ70_DEFAULTS:
			m_a = 90.0;
			m_b = 0.0649;
			m_c = 4.5;
			m_q = 0.90;
			m_bui0 = 72.0;
			m_max_be = 1.076;
			m_height = 10.0;
			m_cbh = 2.0;
			m_cfl = 0.75;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C2_DEFAULTS:
			m_a = 110.0;
			m_b = 0.0282;
			m_c = 1.5;
			m_q = 0.70;
			m_bui0 = 64.0;
			m_max_be = 1.321;
			m_height = 7.0;
			m_cbh = 3.0;
			m_cfl = 0.80;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C3_DEFAULTS:
			m_a = 110.0;
			m_b = 0.0444;
			m_c = 3.0;
			m_q = 0.75;
			m_bui0 = 62.0;
			m_max_be = 1.261;
			m_height = 18.0;
			m_cbh = 8.0;
			m_cfl = 1.15;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C4_DEFAULTS:
			m_a = 110.0;
			m_b = 0.0293;
			m_c = 1.5;
			m_q = 0.80;
			m_bui0 = 66.0;
			m_max_be = 1.184;
			m_height = 10.0;
			m_cbh = 4.0;
			m_cfl = 1.20;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C5_DEFAULTS:
			m_a = 30.0;
			m_b = 0.0697;
			m_c = 4.0;
			m_q = 0.80;
			m_bui0 = 56.0;
			m_max_be = 1.220;
			m_height = 25.0;
			m_cbh = 18.0;
			m_cfl = 1.20;
			break;

		case FUELCOM_ATTRIBUTE.SPREADPARMS_C7_DEFAULTS:
			m_a = 45.0;
			m_b = 0.0305;
			m_c = 2.0;
			m_q = 0.85;
			m_bui0 = 106.0;
			m_max_be = 1.134;
			m_height = 20.0;
			m_cbh = 10.0;
			m_cfl = 0.50;
			break;

		case FUELCOM_ATTRIBUTE.TREE_HEIGHT:
			if ((attribute < 0.0) &&
				(attribute != -1.0))				break;
			if (attribute > 50.0)					break;
			m_height = attribute;
			break;

		case FUELCOM_ATTRIBUTE.CBH:
			if (attribute < 0.0)					break;
			if (attribute > 50.0)					break;
			m_cbh = attribute;
			break;

		case FUELCOM_ATTRIBUTE.CFL:
			if (attribute < 0.0)					break;
			if (attribute > 5.0)					break;
			m_cfl = attribute;
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
		
		SpreadParmsC1.Builder msgRet = SpreadParmsC1.newBuilder();
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
		}
		
		if (!serialized) {
			SpreadParmsC1.Parms.Builder msg = SpreadParmsC1.Parms.newBuilder();

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

		builder.setC1(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_C1 deserialize(Message proto) {
		SpreadParmsC1 msgRead;
		
		try {
			msgRead = (SpreadParmsC1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsC1.Parms msg = msgRead.getParms();

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
