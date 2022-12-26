/***********************************************************************
 * REDapp - ISF.java
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

public class ISF {

	public static double isf_c1(double a, double b, double c, double RSF, double CF) {
		double isf;
		
		if ((a != 0.0) && (b != 0.0) && (c != 0.0) && (RSF != 0.0)) {
									// avoid divide by zero's and unnecessary calc's 
			double temp = 1.0 - Math.pow(RSF / a / CF, 1.0 / c);
			if (temp < 0.01)
				isf = 4.6051701859880913680359829093687 / b;		// ln(0.01) / -b : equation 41b & 43b, August 2004 article
			else
				isf = Math.log(temp/*1.0 - pow(RSF / a, 1.0 / c)*/) / (-b);	// equation 41a & 43a, August 2004 article
		}
		else	isf = 0.0;
		return isf; 		
	}
}
