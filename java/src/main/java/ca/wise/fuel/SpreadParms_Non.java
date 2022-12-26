/***********************************************************************
 * REDapp - SpreadParms_Non.java
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
import ca.wise.fuel.proto.*;

public class SpreadParms_Non extends SpreadParmsAttribute {

	public SpreadParms_Non(){
	}
	
	public SpreadParms_Non(SpreadParms_Non toCopy) {
	}
	
	public boolean equals(FuelAttribute cmp) {
		if (!(cmp instanceof SpreadParms_Non))
			return false;
		return true;
	}
	
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
		case FUELCOM_ATTRIBUTE.A:
		case FUELCOM_ATTRIBUTE.B:
		case FUELCOM_ATTRIBUTE.C:
		case FUELCOM_ATTRIBUTE.MAXBE:
		case FUELCOM_ATTRIBUTE.CBH:
		case FUELCOM_ATTRIBUTE.CFL:
		case FUELCOM_ATTRIBUTE.TREE_HEIGHT:
			return 0.0;

		case FUELCOM_ATTRIBUTE.Q:
		case FUELCOM_ATTRIBUTE.BUI0:
			return -1.0;
			
		default:
			return super.getAttributeValue(attributeKey);
		}
	}
	public short getExternalDefinition() { return (short)FUELCOM_EQUATION.SELECTION_SPREADPARMS_NON; };
	
	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options)  {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder builder = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		builder.setVersion((int)SpreadParmsAttribute.serialVersionUID);
		
		SpreadParmsNon.Builder msgRet = SpreadParmsNon.newBuilder();
		msgRet.setVersion(1);
		
		SpreadParmsNon.Parms.Builder msg = SpreadParmsNon.Parms.newBuilder();
		msg.setVersion(1);
		msgRet.setParms(msg.build());

		builder.setNon(msgRet);
		return builder.build();
	}

	@Override
	public SpreadParms_Non deserialize(Message proto) {
		SpreadParmsNon msgRead;
		
		try {
			msgRead = (SpreadParmsNon)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			SpreadParmsNon.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();	

		}
		else {
			throw new IllegalArgumentException("Unknown attributeKey.");
		}
		
		return this;
	}
	
	protected short GetDefaultValue(FuelName def) {
		short val;

		switch (def) {
		case M1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M1_DEFAULTS;
			break;

		case M2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M2_DEFAULTS;
			break;

		case M3:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS;
			break;

		case M4:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M4_DEFAULTS;
			break;

		case Nz54:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ54_DEFAULTS;
			break;

		case Nz69:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ69_DEFAULTS;
			break;

		case Nz2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ2_DEFAULTS;
			break;

		case Nz15:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ15_DEFAULTS;
			break;

		case Nz30:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ30_DEFAULTS;
			break;

		case Nz31:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ31_DEFAULTS;
			break;

		case Nz32:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ32_DEFAULTS;
			break;

		case Nz33:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ33_DEFAULTS;
			break;

		case Nz40:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ40_DEFAULTS;
			break;

		case Nz41:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ41_DEFAULTS;
			break;

		case Nz43:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ43_DEFAULTS;
			break;

		case Nz44:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ44_DEFAULTS;
			break;

		case Nz46:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ46_DEFAULTS;
			break;

		case Nz50:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ50_DEFAULTS;
			break;

		case Nz53:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ53_DEFAULTS;
			break;

		case Nz62:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ62_DEFAULTS;
			break;

		case Nz63:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ63_DEFAULTS;
			break;

		case Nz64:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ64_DEFAULTS;
			break;

		case Nz65:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ65_DEFAULTS;
			break;

		case O1A:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_O1A_DEFAULTS;
			break;

		case O1B:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_O1B_DEFAULTS;
			break;

		case O1AB:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_O1AB_DEFAULTS;
			break;

		case S1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_S1_DEFAULTS;
			break;

		case S2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_S2_DEFAULTS;
			break;

		case S3:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_S3_DEFAULTS;
			break;

		case Nz57:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ57_DEFAULTS;
			break;

		case Nz58:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS;
			break;

		case Nz56:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ56_DEFAULTS;
			break;

		case C1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C1_DEFAULTS;
			break;
			
		case C2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C2_DEFAULTS;
			break;

		case C3:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C3_DEFAULTS;
			break;

		case C4:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C4_DEFAULTS;
			break;

		case C5:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C5_DEFAULTS;
			break;

		case C7:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C7_DEFAULTS;
			break;

		case Nz45:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ45_DEFAULTS;
			break;

		case Nz47:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ47_DEFAULTS;
			break;

		case Nz51:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ51_DEFAULTS;
			break;

		case Nz52:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ52_DEFAULTS;
			break;

		case Nz55:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ55_DEFAULTS;
			break;

		case D1:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_D1_DEFAULTS;
			break;

		case D2:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_D2_DEFAULTS;
			break;

		case Nz68:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ68_DEFAULTS;
			break;

		case C6:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_C6_DEFAULTS;
			break;

		case Nz60:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ60_DEFAULTS;
			break;

		case Nz66:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ66_DEFAULTS;
			break;

		case Nz67:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ67_DEFAULTS;
			break;

		case Nz71:
			val = FUELCOM_ATTRIBUTE.SPREADPARMS_NZ71_DEFAULTS;
			break;


		default:
			val = -1;
		}

		return val;
	}
}
