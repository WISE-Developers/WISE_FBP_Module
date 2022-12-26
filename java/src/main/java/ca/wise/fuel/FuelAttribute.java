/***********************************************************************
 * REDapp - FuelAttribute.java
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

import ca.wise.serialize.ISerializeProto;

/**
 * @author rbryce
 *
 */
abstract class FuelAttribute implements Cloneable, ISerializeProto<FuelAttribute> {
	public double getAttributeValue(short attributeKey)  throws IllegalArgumentException { throw new IllegalArgumentException("Unknown attributeKey."); };
	public void setAttributeValue(short attributeKey, double attribute) throws IllegalArgumentException { throw new IllegalArgumentException("Unknown attributeKey."); };
	public abstract short getExternalDefinition();

	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
}
