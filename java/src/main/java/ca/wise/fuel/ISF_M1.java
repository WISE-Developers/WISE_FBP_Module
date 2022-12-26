/***********************************************************************
 * REDapp - ISF_M1.java
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

public class ISF_M1 extends ISFAttribute {
	protected static final long serialVersionUID = 1L;

	public ISF_M1() {	
	}

	public ISF_M1(final ISF_M1 other) {
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_ISF_M1;
	}
	
	public double ISF(SpreadParmsAttribute sa, int flag, double RSF_C2, double RSF_D1, double SF, double ISZ) {
		CwfgmFuel c2 = sa.c2();
		CwfgmFuel d1 = sa.d1();
		double PC = sa.pc();
		double c2Value, d1Value, newisf;
		
		if (c2 != null)
			c2Value = c2.isf(RSF_C2, SF, ISZ, (short)0);
		else {
			c2Value = 0.0;
		}
		if (d1 != null)
			d1Value = d1.isf(RSF_D1, SF, ISZ, (short)0);
		else {

			d1Value = 0.0;
		}
//		isf = log(1.0 - pow(RSF / a / PC, 1.0 / c)) / (-b);	// equation 42, old book and August 2004 book
		newisf = PC * c2Value + (1.0 - PC) * d1Value;		// equation 42a, FBP note
		return newisf; 
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		return (other instanceof ISF_M1);
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.IsfAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.IsfAttribute.Builder builder = ca.wise.fuel.proto.IsfAttribute.newBuilder();
		builder.setVersion((int)ISFAttribute.serialVersionUID);
		
		IsfM1.Builder msgRet = IsfM1.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		IsfM1.Parms.Builder msg = IsfM1.Parms.newBuilder();
		msg.setVersion(1);	
		msgRet.setParms(msg.build());

		builder.setM1(msgRet);
		return builder.build();
	}

	@Override
	public ISF_M1 deserialize(Message proto) {
		IsfM1 msgRead;
		
		try {
			msgRead = (IsfM1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			IsfM1.Parms msg = msgRead.getParms();

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
}
