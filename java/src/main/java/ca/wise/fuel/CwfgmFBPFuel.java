/***********************************************************************
 * REDapp - CwfgmFBPFuel.java
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

import java.lang.String;

/**
 * @author rbryce
 *
 */
public abstract class CwfgmFBPFuel extends CwfgmFuel {
	
	public CwfgmFBPFuel() { }
	
	public CwfgmFBPFuel(CwfgmFBPFuel other) {
		super(other);
	}

	@Override
	public CwfgmFBPFuel clone() throws CloneNotSupportedException {
		return (CwfgmFBPFuel)super.clone();
	}

	public abstract void setName(String name);
	public abstract void setSpeciesCode(String speciesCode);
	public abstract CwfgmFuel getC2();
	public abstract void setC2(CwfgmFuel C2);
	public abstract CwfgmFuel getD1();	
	public abstract void setD1(CwfgmFuel D1);

	public abstract short getEquation(short equationKey);
	public abstract void setEquation(short equationKey, short equation);
	public abstract CwfgmAccelAttribute getCustomEquation_Accel();
	public abstract void setCustomEquation_Accel(CwfgmAccelAttribute newVal);
	public abstract CwfgmFMCAttribute getCustomEquation_FMC();
	public abstract void setCustomEquation_FMC(CwfgmFMCAttribute newVal);
	public abstract CwfgmSFCAttribute getCustomEquation_SFC();
	public abstract void setCustomEquation_SFC(CwfgmSFCAttribute newVal);
	public abstract CwfgmTFCAttribute getCustomEquation_TFC();
	public abstract void setCustomEquation_TFC(CwfgmTFCAttribute newVal);	
	public abstract CwfgmCFBAttribute getCustomEquation_CFB();	
	public abstract void setCustomEquation_CFB(CwfgmCFBAttribute newVal);
	public abstract CwfgmRSIAttribute getCustomEquation_RSI();	
	public abstract void setCustomEquation_RSI(CwfgmRSIAttribute newVal);
	public abstract CwfgmISFAttribute getCustomEquation_ISF();
	public abstract void setCustomEquation_ISF(CwfgmISFAttribute newVal);
	public abstract CwfgmLBAttribute getCustomEquation_LB();	
	public abstract void setCustomEquation_LB(CwfgmLBAttribute newVal);
	public abstract CwfgmDBHAttribute getCustomEquation_DBH();
	public abstract void setCustomEquation_DBH(CwfgmDBHAttribute newVal);
}
