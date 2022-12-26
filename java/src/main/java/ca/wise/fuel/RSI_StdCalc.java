/***********************************************************************
 * REDapp - RSI_StdCalc.java
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

public abstract class RSI_StdCalc extends RSIAttribute {

	public Object clone() throws CloneNotSupportedException {
		RSI_StdCalc other = (RSI_StdCalc)super.clone();
		return other;
	}

	protected double _rsi(double a, double b, double c, double ISI) {
		if (a == 0.0)
			return 0.0;					// for non-fuels - just short-cut calculation of rsi

		double tempBasic = 1.0 - Math.exp((0.0 - b) * ISI);
		if (tempBasic < 0.0)
			tempBasic = 0.0;
		double tempPower = Math.pow(tempBasic, c);
		return a * tempPower;				// equation 26
	}
}
