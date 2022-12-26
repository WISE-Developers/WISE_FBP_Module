/***********************************************************************
 * REDapp - ISF_C1.java
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

public class ISF_C1 extends ISFAttribute {
	protected static final long serialVersionUID = 1L;

	public ISF_C1() {		
	}

	public ISF_C1(final ISF_C1 other) {
	}

	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_ISF_C1;
	}
	
	public double ISF(SpreadParmsAttribute sa, int flag, double RSF_C2, double RSF_D1, double SF, double ISZ) {
		return ISF.isf_c1(sa.a(flag), sa.b(flag), sa.c(flag), RSF_C2, 1.0);
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		return (other instanceof ISF_C1);
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
		
		IsfC1.Builder msgRet = IsfC1.newBuilder();
		msgRet.setVersion(1);

		IsfC1.Parms.Builder msg = IsfC1.Parms.newBuilder();
		msg.setVersion(1);
		msgRet.setParms(msg.build());

		builder.setC1(msgRet);
		return builder.build();
	}

	@Override
	public ISF_C1 deserialize(Message proto) {
		IsfC1 msgRead;
		
		try {
			msgRead = (IsfC1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			IsfC1.Parms msg = msgRead.getParms();

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
