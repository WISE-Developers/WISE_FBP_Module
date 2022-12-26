/***********************************************************************
 * REDapp - RSIAttribute.java
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

/**
 * 
 */
package ca.wise.fuel;

import ca.wise.serialize.SerializeProtoOptions;
import ca.hss.general.OutVariable;

/**
 * @author rbryce
 *
 */
abstract class RSIAttribute extends FuelAttribute {
	protected static final long serialVersionUID = 1L;
	
	public abstract double RSI(SpreadParmsAttribute sa, int flag, double ISI, double FMC, double BUI, double FFMC, double BE, OutVariable<Double> rsi_c2, OutVariable<Double> rsi_d1);
	public abstract double ROS(double RSI, double CBH, double ISI, double FMC, double SFC, CFBAttribute cfb);
	public abstract double FOR_FROS(double RSS, double ROS, double CFB);
	
	@Override
	public abstract ca.wise.fuel.proto.RsiAttribute serialize(SerializeProtoOptions options);
}
