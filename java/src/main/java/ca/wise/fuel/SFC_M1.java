/***********************************************************************
 * REDapp - SFC_M1.java
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

public class SFC_M1 extends SFCAttribute {
	protected static final long serialVersionUID = 1L;

	public SFC_M1() {
	}
	
	public SFC_M1(final SFC_M1 other) {
	}

	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		super.setAttributeValue(attributeKey, attribute);
	}
	
	public short getExternalDefinition() { 
		return FUELCOM_EQUATION.SELECTION_SFC_M1;
	};

	@Override
	public double SFC(SpreadParmsAttribute sa, int flag, double FFMC, double BUI) {
		double sfc_c2 , sfc_d1;
		flag = 0;
		
		CwfgmFuel c2 = sa.c2();
		CwfgmFuel d1 = sa.d1();
		if (c2 != null)
			sfc_c2 = c2.sfc(FFMC, BUI, (short)flag);
		else {
			sfc_c2 = 0.0;
		}
		if (d1 != null)
			sfc_d1 = d1.sfc(FFMC, BUI, (short)flag);
		else {
			sfc_d1 = 0.0;
		}

		double PC = sa.pc();
		double sfc = (PC * sfc_c2) + ((1.0 - PC) * sfc_d1);		// equation 17
		return sfc; 
	}

	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		return (other instanceof SFC_M1);
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
		
		SfcM1.Builder msgRet = SfcM1.newBuilder();
		msgRet.setVersion(1);

		SfcM1.Parms.Builder msg = SfcM1.Parms.newBuilder();
		msg.setVersion(1);	
		msgRet.setParms(msg.build());

		builder.setM1(msgRet);
		return builder.build();
	}

	@Override
	public SFC_M1 deserialize(Message proto) {
		SfcM1 msgRead;
		
		try {
			msgRead = (SfcM1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SfcM1.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
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
