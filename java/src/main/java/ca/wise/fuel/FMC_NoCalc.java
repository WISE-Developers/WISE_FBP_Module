/***********************************************************************
 * REDapp - FMC_NoCalc.java
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
import ca.wise.serialize.*;

import ca.wise.fuel.proto.*;

public class FMC_NoCalc extends FMCAttribute {
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
	
	public FMC_NoCalc() {	
	}

	public FMC_NoCalc(final FMC_NoCalc other) {
	}
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}


	public double fmc(double lat, double lon, double elev, int day) {
		return 0.0;
	}
	
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_FMC_NOCALC;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		return (other instanceof FMC_NoCalc);
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.FmcAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.FmcAttribute.Builder builder = ca.wise.fuel.proto.FmcAttribute.newBuilder();
		builder.setVersion((int)FMCAttribute.serialVersionUID);
		
		FmcNoCalc.Builder msgRet = FmcNoCalc.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		FmcNoCalc.Parms.Builder msg = FmcNoCalc.Parms.newBuilder();

		msg.setVersion(1);
		
		msgRet.setParms(msg.build());

		builder.setNoCalc(msgRet);
		return builder.build();
	}

	@Override
	public FMC_NoCalc deserialize(Message proto) {
		FmcNoCalc msgRead = (FmcNoCalc)proto;

		FmcNoCalc.Parms msg;
		
		try {
			 msg = msgRead.getParms();
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}
		
		if(msg.getVersion() != 1)
			throw new IllegalArgumentException();
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
