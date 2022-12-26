/***********************************************************************
 * REDapp - SpreadParmsAttribute.java
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

import ca.wise.fuel.proto.SpreadParmsC6;
import ca.wise.serialize.ISerializationData;
import ca.wise.serialize.ISerializationData_SP;
import ca.wise.serialize.SerializeProtoOptions;

public class SpreadParmsAttribute extends FuelAttribute {
	protected static final long serialVersionUID = 1L;
	
	public double a(int flag) { return 0.0; };
	public double b(int flag) { return 0.0; };
	public double c(int flag) { return 0.0; };
	public double q() { return 0.0; };
	public double bui0() { return 0.0; };
	public double maxBE() { return 0.0; };
	public double height() { return 0.0; };
	public double cbh() { return 0.0; };
	public double cfl() { return 0.0; };
	public double curingDegree() { return 0.0; };
	public double pc() { return 0.0; };

	public void c2(CwfgmFuel C2) { }
	public void d1(CwfgmFuel D1) { }
	
	public CwfgmFuel c2() { return null; }
	public CwfgmFuel d1() { return null; }
	
	public short getExternalDefinition() { return 0; }
	
	@Override
	public ca.wise.fuel.proto.SpreadParmsAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.SpreadParmsAttribute.Builder msg = ca.wise.fuel.proto.SpreadParmsAttribute.newBuilder();
		msg.setVersion((int)serialVersionUID);
		return msg.build();
	}

	public SpreadParmsAttribute deserialize(Message proto, ISerializationData defaults) {
		ca.wise.fuel.proto.SpreadParmsAttribute msg;

		try {
			msg = (ca.wise.fuel.proto.SpreadParmsAttribute)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}
		
		if (msg.getVersion() != 1) {
			throw new IllegalArgumentException();
		}

		SpreadParmsAttribute acc;

		if (msg.hasC1()) {
			acc = new SpreadParms_C1();
			return (SpreadParmsAttribute) acc.deserialize(msg.getC1());
		}
		if (msg.hasC6()) {
			acc = new SpreadParms_C6();
			return (SpreadParmsAttribute) acc.deserialize(msg.getC6());
		}
		if (msg.hasD1()) {
			acc = new SpreadParms_D1();
			return (SpreadParmsAttribute) acc.deserialize(msg.getD1());
		}
		if (msg.hasMixed()) {
			SpreadParms_Mixed m = new SpreadParms_Mixed();
			acc = m;

			ISerializationData_SP def = (ISerializationData_SP)defaults;
			if (def != null) {
				try {
					m.setC2(def.c2);
					m.setD1(def.d1);
				} catch (CloneNotSupportedException e) {
					throw new IllegalArgumentException();
				}
			}

			return (SpreadParmsAttribute) acc.deserialize(msg.getMixed());
		}
		if (msg.hasMixedDead()) {
			SpreadParms_MixedDead m = new SpreadParms_MixedDead();
			acc = m;

			ISerializationData_SP def = (ISerializationData_SP)defaults;
			if (def != null) {
				try {
					m.setC2(def.c2);
					m.setD1(def.d1);
				} catch (CloneNotSupportedException e) {
					throw new IllegalArgumentException();
				}
			}

			return (SpreadParmsAttribute) acc.deserialize(msg.getMixedDead());
		}
		if (msg.hasNon()) {
			acc = new SpreadParms_Non();
			return (SpreadParmsAttribute) acc.deserialize(msg.getNon());
		}
		if (msg.hasNz()) {
			acc = new SpreadParms_NZ();
			return (SpreadParmsAttribute) acc.deserialize(msg.getNz());
		}
		if (msg.hasO1()) {
			acc = new SpreadParms_O1();
			return (SpreadParmsAttribute) acc.deserialize(msg.getO1());
		}
		if (msg.hasO1Ab()) {
			acc = new SpreadParms_O1ab();
			return (SpreadParmsAttribute) acc.deserialize(msg.getO1Ab());
		}
		if (msg.hasS1()) {
			acc = new SpreadParms_S1();
			return (SpreadParmsAttribute) acc.deserialize(msg.getS1());
		}

		return null;
	}
	
	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
	@Override
	public FuelAttribute deserialize(Message proto) {
		return null;
	}
}
