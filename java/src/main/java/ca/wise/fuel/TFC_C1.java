/***********************************************************************
 * REDapp - TFC_C1.java
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

import ca.hss.general.OutVariable;

import java.util.Optional;

import com.google.protobuf.Message;
import ca.wise.serialize.*;
import ca.wise.fuel.proto.*;

public class TFC_C1 extends TFCAttribute {
	protected static final long serialVersionUID = 1L;
	
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	public short getExternalDefinition() { 
		return FUELCOM_EQUATION.SELECTION_TFC_C1;
	};
		
	@Override
	public double TFC(SpreadParmsAttribute sa, int flag, double CFB, double SFC, OutVariable<Double> CFC) {
		CFC.value = sa.cfl() * CFB;			// equation 66
		double tfc = SFC + (Double)(CFC.value);		// equation 67
		return tfc; 
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		return (other instanceof TFC_C1);
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.TfcAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.TfcAttribute.Builder builder = ca.wise.fuel.proto.TfcAttribute.newBuilder();
		builder.setVersion((int)TFCAttribute.serialVersionUID);
		
		TfcC1.Builder msgRet = TfcC1.newBuilder();
		msgRet.setVersion(1);

		TfcC1.Parms.Builder msg = TfcC1.Parms.newBuilder();

		msg.setVersion(1);
		
		msgRet.setParms(msg.build());

		builder.setC1(msgRet);
		return builder.build();
	}

	@Override
	public TFC_C1 deserialize(Message proto) {
		TfcC1 msgRead;
		
		try {
			msgRead = (TfcC1)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}
		
		if(msgRead.getVersion() != 1)
			throw new IllegalArgumentException();
		
		if(msgRead.hasParms()) {
			TfcC1.Parms msg = msgRead.getParms();
			
			if(msg.getVersion() != 1)
				throw new IllegalArgumentException();
		}
		else
		{
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
	
	public short GetDefaultValue(FuelName def) {
		short val;
		
		switch(def) {
			default:
				val = (short) -1;
		}
		
		return val;
	}
}
