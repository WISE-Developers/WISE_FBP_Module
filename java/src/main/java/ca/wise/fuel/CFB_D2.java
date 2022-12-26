/***********************************************************************
 * REDapp - CFB_D2.java
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

import java.io.*;
import java.util.Optional;

import com.google.protobuf.Message;

import ca.wise.fuel.proto.CfbD2;
import ca.wise.serialize.*;

import ca.hss.general.OutVariable;

public class CFB_D2 extends CFBAttribute {
	protected static final long serialVersionUID = 1L;
	
	public void serialize(ObjectOutputStream out) throws IOException {
		writeObject(out);
	}
	
	private void writeObject(ObjectOutputStream out) throws IOException {
		out.defaultWriteObject();
	}
	
	private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
		in.defaultReadObject();
	}
	
	public CFB_D2() {
	}

	public CFB_D2(final CFB_D2 other) {
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		CFB_D2 other = (CFB_D2)super.clone();
		return other;
	}

	@Override
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_CFB_D2;
	}
	
	@Override
	public double cfb(double CBH, double FMC, double SFC, double ROS, OutVariable<Double> rso, OutVariable<Double> csi) {
		rso.value = 0.0;
		csi.value = 0.0;
		return 0.0;
	}

	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		return (other instanceof CFB_D2);
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.CfbAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.CfbAttribute.Builder builder = ca.wise.fuel.proto.CfbAttribute.newBuilder();
		builder.setVersion((int)CFBAttribute.serialVersionUID);
		
		CfbD2.Builder msgRet = CfbD2.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		CfbD2.Parms.Builder msg = CfbD2.Parms.newBuilder();
		msg.setVersion(1);

		builder.setD2(msgRet);
		return builder.build();
	}

	@Override
	public CFB_D2 deserialize(Message proto) {
		CfbD2 msgRead;
		
		try {
			msgRead = (CfbD2)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		if (msgRead.hasParms()) {
			CfbD2.Parms msg = msgRead.getParms();

			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
		}
		else {
			throw new IllegalArgumentException();
		}
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
