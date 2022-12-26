/***********************************************************************
 * REDapp - FlameLength_Tree.java
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

public class FlameLength_Tree extends FlameLengthAttribute {
	protected static final long serialVersionUID = 1L;
	
	protected double m_p1, m_th, m_cfb;

	public FlameLength_Tree() {
		m_p1 = 300.0;
		m_th = 2.5;
		m_cfb = 0.9;
	}

	public FlameLength_Tree(final FlameLength_Tree toCopy) {
		m_p1 = toCopy.m_p1;
		m_th = toCopy.m_th;
		m_cfb = toCopy.m_cfb;
	}
	
	public Object clone() throws CloneNotSupportedException {
		FlameLength_Tree other = (FlameLength_Tree)super.clone();
		return other;
	}

	public short getExternalDefinition() {
		return FUELCOM_EQUATION.SELECTION_FLAMELENGTH_TREE;
	}

		@Override
	public double getAttributeValue(short attributeKey) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_DEFAULTS:		if ((m_p1 == 300.0) && (m_th == 2.5) && (m_cfb == 0.9))
																		return 1.0;
																	return 0.0;

			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P1:				return m_p1;
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_TH_FACTOR:		return m_th;
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_CFB_THRESHOLD:	return m_cfb;
		}
		
		return super.getAttributeValue(attributeKey);
	}
	
	public void setAttributeValue(short attributeKey, double attribute) {
		switch (attributeKey) {
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_DEFAULTS:		m_p1 = 300.0; m_th = 2.5; m_cfb = 0.9;	return;

			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_P1:				m_p1 = attribute;						return;
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_TH_FACTOR:		m_th = attribute;						return;
			case FUELCOM_ATTRIBUTE.FLAMELENGTH_TREE_CFB_THRESHOLD:	m_cfb = attribute;						return;
		}
		
		super.setAttributeValue(attributeKey, attribute);
	}

	@Override
	public double flameLength(double height, double CFB, double fi) {
		if (CFB > m_cfb) {
			if (height == 0.0)
				return 0.0;
			return height * m_th;
		}
		if (fi == 0.0)
			return 0.0;
		return Math.sqrt(fi / m_p1);
	}
	
	@Override
	public boolean equals(Object other) {
		if (other == null)
			return false;
		if (other instanceof FlameLength_Tree) {
			FlameLength_Tree a = (FlameLength_Tree)other;
			if ((m_p1 != a.m_p1) || (m_th != a.m_th) || (m_cfb != a.m_cfb))
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
		
		FlameLengthTree.Builder msgRet = FlameLengthTree.newBuilder();
		msgRet.setVersion((int)serialVersionUID);

		FlameLengthTree.Parms.Builder msg = FlameLengthTree.Parms.newBuilder();

		msg.setVersion(1);
		msg.setP1(HSS_Double.of(m_p1));
		msg.setCfb(HSS_Double.of(m_cfb));
		msg.setTh(HSS_Double.of(m_th));
		
		msgRet.setParms(msg.build());

		builder.setTree(msgRet);
		return builder.build();
	}

	@Override
	public FlameLength_Tree deserialize(Message proto) {
		FlameLengthTree msgRead; 
		
		try {
			msgRead = (FlameLengthTree)proto;
		}
		catch (Exception e) {
			throw new IllegalArgumentException();
		}

		FlameLengthTree.Parms msg = msgRead.getParms();

		if(msg.getVersion() != 1)
			throw new IllegalArgumentException();
		
		m_p1 = HSS_Double.from(msg.getP1());
		m_cfb = HSS_Double.from(msg.getCfb());
		m_th = HSS_Double.from(msg.getTh());
		
		return this;
	}

	@Override
	public Optional<Boolean> isDirty() {
		return Optional.empty();
	}
}
