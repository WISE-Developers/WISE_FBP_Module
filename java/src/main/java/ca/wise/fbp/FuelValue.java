/***********************************************************************
 * REDapp - FuelValue.java
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

package ca.wise.fbp;

import ca.wise.fuel.Cwfgm_Fuel_C1;
import ca.wise.fuel.Cwfgm_Fuel_C2;
import ca.wise.fuel.Cwfgm_Fuel_C3;
import ca.wise.fuel.Cwfgm_Fuel_C4;
import ca.wise.fuel.Cwfgm_Fuel_C5;
import ca.wise.fuel.Cwfgm_Fuel_C6;
import ca.wise.fuel.Cwfgm_Fuel_C7;
import ca.wise.fuel.Cwfgm_Fuel_D1;
import ca.wise.fuel.Cwfgm_Fuel_D1D2;
import ca.wise.fuel.Cwfgm_Fuel_D2;
import ca.wise.fuel.Cwfgm_Fuel_M1;
import ca.wise.fuel.Cwfgm_Fuel_M1M2;
import ca.wise.fuel.Cwfgm_Fuel_M2;
import ca.wise.fuel.Cwfgm_Fuel_M3;
import ca.wise.fuel.Cwfgm_Fuel_M3M4;
import ca.wise.fuel.Cwfgm_Fuel_M4;
import ca.wise.fuel.Cwfgm_Fuel_O1a;
import ca.wise.fuel.Cwfgm_Fuel_O1ab;
import ca.wise.fuel.Cwfgm_Fuel_O1b;
import ca.wise.fuel.Cwfgm_Fuel_S1;
import ca.wise.fuel.Cwfgm_Fuel_S2;
import ca.wise.fuel.Cwfgm_Fuel_S3;

public class FuelValue {
	public String displayName;
	public Class<?> classType;

	public FuelValue(Class<?> tp, String displayName) {
		this.displayName = displayName;
		this.classType = tp;
	}
	
	public static final FuelValue fuels[] = { new FuelValue(Cwfgm_Fuel_C1.class, "C-1:  Spruce-Lichen Woodland"),
								  			  new FuelValue(Cwfgm_Fuel_C2.class, "C-2:  Boreal Spruce"),
								  			  new FuelValue(Cwfgm_Fuel_C3.class, "C-3:  Mature Jack or Lodgepole Pine"),
								  			  new FuelValue(Cwfgm_Fuel_C4.class, "C-4:  Immature Jack or Lodgepole Pine"),
								  			  new FuelValue(Cwfgm_Fuel_C5.class, "C-5:  Red and White Pine"),
								  			  new FuelValue(Cwfgm_Fuel_C6.class, "C-6:  Conifer Plantation"),
								  			  new FuelValue(Cwfgm_Fuel_C7.class, "C-7:  Ponderosa Pine / Douglas Fir"),
								  			  new FuelValue(Cwfgm_Fuel_D1.class, "D-1:  Leafless Aspen"),
								  			  new FuelValue(Cwfgm_Fuel_D2.class, "D-2:  Green Aspen (w/ BUI Thresholding)"),
								  			  new FuelValue(Cwfgm_Fuel_D1D2.class, "D-1/D-2:  Aspen"),
								  			  new FuelValue(Cwfgm_Fuel_M1.class, "M-1:  Boreal Mixedwood - Leafless"),
								  			  new FuelValue(Cwfgm_Fuel_M2.class, "M-2:  Boreal Mixedwood - Green"),
								  			  new FuelValue(Cwfgm_Fuel_M1M2.class, "M-1/M-2:  Boreal Mixedwood"),
								  			  new FuelValue(Cwfgm_Fuel_M3.class, "M-3:  Dead Balsam Fir / Mixedwood - Leafless"),
								  			  new FuelValue(Cwfgm_Fuel_M4.class, "M-4:  Dead Balsam Fir / Mixedwood - Green"),
								  			  new FuelValue(Cwfgm_Fuel_M3M4.class, "M-3/M-4:  Dead Balsam Fir / Mixedwood"),
								  			  new FuelValue(Cwfgm_Fuel_O1a.class, "O-1a:  Matted Grass"),
								  			  new FuelValue(Cwfgm_Fuel_O1b.class, "O-1b:  Standing Grass"),
								  			  new FuelValue(Cwfgm_Fuel_O1ab.class, "O-1ab:  Grass"),
								  			  new FuelValue(Cwfgm_Fuel_S1.class, "S-1:  Jack or Lodgepole Pine Slash"),
								  			  new FuelValue(Cwfgm_Fuel_S2.class, "S-2:  White Spruce / Balsam Slash"),
								  			  new FuelValue(Cwfgm_Fuel_S3.class, "S-3:  Coastal Cedar / Hemlock / Douglas-Fir Slash")
			};
}
