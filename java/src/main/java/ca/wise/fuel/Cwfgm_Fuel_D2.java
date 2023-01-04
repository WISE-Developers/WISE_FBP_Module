/***********************************************************************
 * REDapp - Cwfgm_Fuel_D2.java
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
 * Implements the FBP D2 fuel type.
 */
public class Cwfgm_Fuel_D2 extends Cwfgm_Fuel_Readonly {
	/**
	 * Creates and initializes a read-only fueltype of type D2
	 */
	public Cwfgm_Fuel_D2() {
		m_name = "D-2 Green Aspen (with BUI Thresholding)";
		m_fuel.m_defaultFuelType = this.getClass();
		
		m_fuel.m_spread = new SpreadParms_D1();
		m_fuel.m_spread.setAttributeValue((short)FUELCOM_ATTRIBUTE.SPREADPARMS_D2_DEFAULTS, 0.0);

		// fuel type-specific calculation engines for the FBPfuel
		m_fuel.m_FMCCalculation = new FMC_NoCalc();
		m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_D2();
		m_fuel.m_SFCCalculation.setAttributeValue((short)FUELCOM_ATTRIBUTE.SFC_D2_DEFAULTS, 0.0);
		m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_D2();
		m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_D2();
		m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
		m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
		m_fuel.m_LBCalculation = new LB_C1();
		m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_D2();
		m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
	}

	/**
	 * @see CwfgmFBPFuel#clone
	 */
	@Override
	public Cwfgm_Fuel_D2 clone() throws CloneNotSupportedException {
		return (Cwfgm_Fuel_D2)super.clone();
	}
}
