/***********************************************************************
 * REDapp - FlameLength_Alexander82.java
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

public class FlameLength_Alexander82 extends FlameLengthAttribute {
	protected static final long serialVersionUID = 1L;
	
	protected double m_p1, m_p2;

	public FlameLength_Alexander82() {
		m_p1 = 0.0775;
		m_p2 = 0.46;
	}

	public FlameLength_Alexander82(final FlameLength_Alexander82 toCopy) {
		m_p1 = toCopy.m_p1;
		m_p2 = toCopy.m_p2;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		FlameLength_Alexander82 other = (FlameLength_Alexander82)super.clone();
		return other;
	}

	@Override
	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_FLAMELENGTH_ALEXANDER82;
	}

	@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_DEFAULTS:		if ((m_p1 == 0.0775) && (m_p2 == 0.46))
																		return 1.0;
																	return 0.0;

			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P1:				return m_p1;	
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P2:				return m_p2;
		}
		
		return super.getAttributeValue(attributeKey);
	}

	@Override
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_DEFAULTS:		m_p1 = 0.0775; m_p2 = 0.46;	return;

			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P1:				m_p1 = attribute;			return;
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P2:				m_p2 = attribute;			return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}

	@Override
	public double flameLength(double height, double CFB, double fi) {
		double fl = m_p1 * Math.pow(fi, m_p2);
		return fl;
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof FlameLength_Alexander82) {
			FlameLength_Alexander82 a = (FlameLength_Alexander82)other;
			if ((m_p1 != a.m_p1) || (m_p2 != a.m_p2))
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
		
		FlameLengthAlexander82.Builder msgRet = FlameLengthAlexander82.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		FlameLengthAlexander82.Parms.Builder msg = FlameLengthAlexander82.Parms.newBuilder();

		msg.setVersion(1);
		msg.setP1(HSS_Double.of(m_p1));
		msg.setP2(HSS_Double.of(m_p2));
		
		msgRet.setParms(msg.build());

		builder.setAlexander82(msgRet);
		return builder.build();
	}

	@Override
	public FlameLength_Alexander82 deserialize(Message proto) {
		FlameLengthAlexander82 msgRead;
		
		try {
			msgRead = (FlameLengthAlexander82)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}
		
		FlameLengthAlexander82.Parms msg = msgRead.getParms();

		if(msg.getVersion() != 1)
			throw new IllegalArgumentException();
		
		m_p1 = HSS_Double.from(msg.getP1());
		m_p2 = HSS_Double.from(msg.getP2());
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
