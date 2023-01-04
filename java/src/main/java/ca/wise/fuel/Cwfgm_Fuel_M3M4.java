/***********************************************************************
 * REDapp - Cwfgm_Fuel_M3M4.java
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

/**
 * Implements the FBP M3/M4 fuel type.
 */
public class Cwfgm_Fuel_M3M4 extends Cwfgm_Fuel_Readonly {
	/**
	 * Creates and initializes a read-only fueltype of type M3/M4
	 */
	public Cwfgm_Fuel_M3M4() {
		m_name = "M-3/M-4 Dead Balsam Fir / Mixedwood";
		m_fuel.m_defaultFuelType = this.getClass();
		
		m_fuel.m_spread = new SpreadParms_MixedDead();
		m_fuel.m_spread.setAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_M3_DEFAULTS, 0.0);

		// fuel type-specific calculation engines for the FBPfuel
		m_fuel.m_FMCCalculation = new FMC_Calc();
		m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
		m_fuel.m_SFCCalculation.setAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_M3_DEFAULTS, 0.0);
		m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
		m_fuel.m_RSICalculation = new RSI_M3();
		m_fuel.m_RSICalculation_Greenup = new RSI_M4();
		m_fuel.m_ISFCalculation= new ISF_M3M4();
		m_fuel.m_ISFCalculation_Greenup = new ISF_M3M4();
		m_fuel.m_ISFCalculation_Greenup.setAttributeValue((short)FUELCOM_ATTRIBUTE.RSI_M4_DEFAULTS, 0.0);
		m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
		m_fuel.m_LBCalculation = new LB_C1();
		m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
		m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
	}

	/**
	 * @see CwfgmFBPFuel#clone
	 */
	@Override
	public Cwfgm_Fuel_M3M4 clone() throws CloneNotSupportedException {
		return (Cwfgm_Fuel_M3M4)super.clone();
	}
}
