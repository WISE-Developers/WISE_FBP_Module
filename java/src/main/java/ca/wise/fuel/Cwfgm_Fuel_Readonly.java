/***********************************************************************
 * REDapp - Cwfgm_Fuel_Readonly.java
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

public class Cwfgm_Fuel_Readonly extends Cwfgm_Fuel {
	public Cwfgm_Fuel_Readonly() {
	}

	public Cwfgm_Fuel mutate() {
		return new Cwfgm_Fuel(this);
	}

	@Override
	public Cwfgm_Fuel_Readonly clone() throws CloneNotSupportedException {
		return (Cwfgm_Fuel_Readonly)super.clone();
	}
	
	@Override
	public void setName(String name) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}

	@Override
	public void setSpeciesCode(String name) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setC2(CwfgmFuel C2) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setD1(CwfgmFuel D1) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setAttribute(int attributeKey, Object attribute) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setEquation(short equationKey, short equation) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setCustomEquation_Accel(CwfgmAccelAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setCustomEquation_FMC(CwfgmFMCAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}

	@Override
	public void setCustomEquation_SFC(CwfgmSFCAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setCustomEquation_TFC(CwfgmTFCAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setCustomEquation_CFB(CwfgmCFBAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}

	@Override
	public void setCustomEquation_RSI(CwfgmRSIAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setCustomEquation_ISF(CwfgmISFAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}

	@Override
	public void setCustomEquation_LB(CwfgmLBAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}
	
	@Override
	public void setCustomEquation_DBH(CwfgmDBHAttribute newVal) {
		throw new IllegalStateException("The object is in an unexpected state.");
	}	
}
