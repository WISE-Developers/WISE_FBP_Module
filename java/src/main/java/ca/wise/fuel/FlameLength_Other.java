/***********************************************************************
 * REDapp - FlameLength_Other.java
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

public class FlameLength_Other extends FlameLengthAttribute {
	protected static final long serialVersionUID = 1L;
	
	protected double m_p1;

	public FlameLength_Other() {
		m_p1 = 300.0;
	}

	public FlameLength_Other(final FlameLength_Other toCopy) {
		m_p1 = toCopy.m_p1;
	}
	
	public Object clone() throws CloneNotSupportedException {
		FlameLength_Other other = (FlameLength_Other)super.clone();
		return other;
	}

	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_FLAMELENGTH_OTHER;
	}

		@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_DEFAULTS:		if (m_p1 == 300.0)
																		return 1.0;
																	return 0.0;

			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P1:				return m_p1;	
		}
		
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_DEFAULTS:		m_p1 = 300.0;		return;

			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P1:				m_p1 = attribute;	return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}

	@Override
	public double flameLength(double height, double CFB, double fi) {
		if (fi == 0.0)
			return 0.0;
		return Math.sqrt(fi / m_p1);
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof FlameLength_Other) {
			FlameLength_Other a = (FlameLength_Other)other;
			if (m_p1 != a.m_p1)
				return false;
			return super.equals(other);
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		assert false : "hashCode not designed";
		return 42;
	}

	@Override
	public ca.wise.fuel.proto.FlameLengthAttribute serialize(SerializeProtoOptions options) {
		ca.wise.fuel.proto.FlameLengthAttribute.Builder builder = ca.wise.fuel.proto.FlameLengthAttribute.newBuilder();
		builder.setVersion((int)FlameLengthAttribute.serialVersionUID);
		
		FlameLengthOther.Builder msgRet = FlameLengthOther.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		FlameLengthOther.Parms.Builder msg = FlameLengthOther.Parms.newBuilder();

		msg.setVersion(1);
		msg.setP1(HSS_Double.of(m_p1));
		
		msgRet.setParms(msg.build());

		builder.setOther(msgRet);
		return builder.build();
	}

	@Override
	public FlameLength_Other deserialize(Message proto) {
		FlameLengthOther msgRead;
		
		try {
			msgRead = (FlameLengthOther)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException("");
		}

		FlameLengthOther.Parms msg = msgRead.getParms();
		
		if(msg.getVersion() != 1)
			throw new IllegalArgumentException("");

		m_p1 = HSS_Double.from(msg.getP1());
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
