/***********************************************************************
 * REDapp - FBPCalculations.java
 * Copyright (C) 2015-2021 The REDapp Development Team
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

import static ca.hss.math.General.*;

import java.util.Calendar;

import ca.wise.fuel.CwfgmFBPFuel;
import ca.wise.fuel.Cwfgm_Fuel_C1;
import ca.wise.fuel.Cwfgm_Fuel_Readonly;
import ca.wise.fuel.FUELCOM_ATTRIBUTE;
import ca.wise.fwi.Fwi;
import ca.hss.general.OutVariable;
import ca.hss.text.TranslationCallback;
import ca.hss.times.WTime;
import ca.hss.times.WTimeManager;
import ca.hss.times.WorldLocation;

public class FBPCalculations {
	/**
	 * [Output] Rate or Spread, after elapsed time t.
	 */
	public double ros_t;
	/**
	 * [Output] Rate of Spread, Equilibrium
	 */
	public double ros_eq;
	/**
	 * [Output] Flank Rate of Spread
	 */
	public double fros;
	/**
	 * [Output] Back Rate of Spread
	 */
	public double bros;
	/**
	 * [Output] Critical Surface Fire Rate of Spread
	 */
	public double rso;
	/**
	 * [Output] Head Fire Intensity
	 */
	public double hfi;
	/**
	 * [Output] Flank Fire Intensity
	 */
	public double ffi;
	/**
	 * [Output] Back Fire Intensity
	 */
	public double bfi;
	/**
	 * [Output] Elliptical Fire Area
	 */
	public double area;
	/**
	 * [Output] Elliptical Fire Perimeter
	 */
	public double perimeter;
	/**
	 * [Output] Distance Head
	 */
	public double distanceHead;
	/**
	 * [Output] Distance Flank
	 */
	public double distanceFlank;
	/**
	 * [Output] Distance Back
	 */
	public double distanceBack;
	/**
	 * [Output] Length-to-Breadth Ratio
	 */
	public double lb;
	/**
	 * [Output] Critical Surface Fire Intensity
	 */
	public double csi;
	/**
	 * [Output] Crown Fraction Burned
	 */
	public double cfb;
	/**
	 * [Output] Surface Fuel Consumption
	 */
	public double sfc;
	/**
	 * [Output] Total Fuel Consumption
	 */
	public double tfc;
	/**
	 * [Output] Crown Fuel Consumption
	 */
	public double cfc;
	/**
	 * [Output] Final ISI, accounting for wind and slope
	 */
	public double isi;
	/**
	 * [Output] Foliar Moisture Content
	 */
	public double fmc;
	/**
	 * [Output] Net Vectored Wind Speed
	 */
	public double wsv;
	/**
	 * [Output] Spread Direction Azimuth
	 */
	public double raz;
	/**
	 * [Input] Percent conifer.
	 */
	public double conifMixedWood;
	/**
	 * [Input] Percent dead fir.
	 */
	public double deadBalsam;
	/**
	 * [Input] Percent grass curing.
	 */
	public double grassCuring;
	/**
	 * [Input] Grass fuel load (kg/m^2).
	 */
	public double grassFuelLoad;
	/**
	 * [Input] Crown base height (m).
	 */
	public double crownBase;
	/**
	 * [Input] Time elapsed since ignition (min).
	 */
	public double elapsedTime;
	/**
	 * [Input] Fine fuel moisture code.
	 */
	public double ffmc;
	/**
	 * [Input] The wind speed (km/h).
	 */
	public double windSpeed;
	/**
	 * [Input] The wind direction (degrees).
	 */
	public double windDirection;
	/**
	 * [Input/Output] The buildup index. If useBui is true this value is used, otherwise it's calculated from the DMC and DC.
	 */
	public double bui;
	/**
	 * [Input] The duff moisture code. Only needed if useBui is false.
	 */
	public double dmc;
	/**
	 * [Input] The drought code. Only needed if useBui if false.
	 */
	public double dc;
	/**
	 * [Input] The slope the ignition was on (ignored if useSlope is false).
	 */
	public double slopeValue;
	/**
	 * [Input] The aspect the ignition was on.
	 */
	public double aspect;
	/**
	 * [Input] The latitude of the ignition (degrees).
	 */
	public double latitude;
	/**
	 * [Input] The longitude of the ignition (degrees).
	 */
	public double longitude;
	/**
	 * [Input] The elevation of the ignition.
	 */
	public double elevation;

	/**
	 * [Input] Calculate with acceleration (point sources).
	 */
	public boolean acceleration;
	/**
	 * [Input] Use crown base height. Should be set to true for fuel type C-6.
	 */
	public boolean useCrownBaseHeight;
	/**
	 * [Input] If true the specified BUI is used, otherwise it is calulated from the DMC and DC.
	 */
	public boolean useBui;
	/**
	 * [Input] Use buildup effect.
	 */
	public boolean useBuildup;
	/**
	 * [Input] Calculate with a slope value.
	 */
	public boolean useSlope;
	/**
	 * [Input] Calculate with greenup on.
	 */
	public boolean useGreenup;

	/**
	 * [Input] The fuel type.
	 *
	 * 0 - C-1<br>
	 * 1 - C-2<br>
	 * 2 - C-3<br>
	 * 3 - C-4<br>
	 * 4 - C-5<br>
	 * 5 - C-6<br>
	 * 6 - C-7<br>
	 * 7 - D-1<br>
	 * 8 - D-2<br>
	 * 10 - M-1<br>
	 * 11 - M-2<br>
	 * 13 - M-3<br>
	 * 14 - M-4<br>
	 * 16 - O-1a<br>
	 * 17 - O-1b<br>
	 * 18 - O-1ab<br>
	 * 19 - S-1<br>
	 * 20 - S-2<br>
	 * 21 - S-3
	 */
	public int fuelType;

	public String fireDescription;
	public String headFireDescription;
	public String flankFireDescription;
	public String backFireDescription;

	/**
	 * [Input] The date of the ignition.
	 */
	public Calendar m_date;
	
	public boolean cfbPossible = true;

	/**
	 * The default constructor.
	 */
	public FBPCalculations() {
		initializeInputValues();
		initializeOutputValues();
	}

	//! @cond
	private void initializeInputValues() {
		// initialize inputs to default values.
		fuelType = 0; // C-1: Spruce-Lichen Woodland
		conifMixedWood = 50.0; // 50%
		deadBalsam = 50.0; // 50%
		grassCuring = 60.0; // 60%
		grassFuelLoad = 0.35; // 0.35 kg/m^2
		crownBase = 7.0; // <depends on currently selected fueltype>
		useGreenup = false; // greenup off

		// IgTypePtIgn turn ON
		acceleration = true; // acceleration on (point ignition)

		elapsedTime = 60.0; // 60 minutes
		useSlope = true; // slope on
		ffmc = 85.0; // ffmc = 85
		bui = 40.0; // bui = 40
		windSpeed = 0.0; // no wind
		windDirection = 0.0; // travelling due west
		useBui = true; // use build-up effect
		useBuildup = true;
		slopeValue = 0.0; // no slope (0% slope)
		aspect = 0.0; // upwards to the west
		latitude = 54.00; // 54 degrees
		longitude = -115.00; // -115 degrees
		elevation = 500.0; // 500 meters
		m_date = Calendar.getInstance();
		dc = 200;
		dmc = 25;

		// if project != null
		// initialize lat, lon
		// initialize elevation
	}

	private void initializeOutputValues() {
		ros_t = 0.0;
		ros_eq = 0.0;
		fros = 0.0;
		lb = 0.0;
		bros = 0.0;
		rso = 0.0;
		hfi = 0.0;
		ffi = 0.0;
		bfi = 0.0;
		area = 0.0;
		perimeter = 0.0;
		distanceHead = 0.0;
		distanceFlank = 0.0;
		distanceBack = 0.0;
		csi = 0.0;
		cfb = 0.0;
		sfc = 0.0;
		tfc = 0.0;
		cfc = 0.0;
		isi = 0.0;
		fmc = 0.0;
		wsv = 0.0;
		raz = 0.0;
		fireDescription = "";
	}
	//! @endcond

	/**
	 * Calculate the FBP values based on the given inputs.
	 *
	 * @throws CloneNotSupportedException
	 */
	public void FBPCalculateStatisticsCOM() throws CloneNotSupportedException {
		//isi_fbp
		int flags = 0;
		double FF;
		WTime newDate;
		newDate = new WTime(m_date.get(Calendar.YEAR), m_date.get(Calendar.MONTH) + 1, m_date.get(Calendar.DAY_OF_MONTH), m_date.get(Calendar.HOUR_OF_DAY), m_date.get(Calendar.MINUTE), m_date.get(Calendar.SECOND), new WTimeManager(new WorldLocation()));

		int julian = (int)newDate.getDayOfYear(WTime.FORMAT_STRING_DD_MM_YYYY);
		Cwfgm_Fuel_Readonly fuel0;
		try
		{
			fuel0 = (Cwfgm_Fuel_Readonly)FuelValue.fuels[fuelType].classType.getDeclaredConstructor().newInstance();
		}
		catch (Exception e)
		{
			fuel0 = new Cwfgm_Fuel_C1();
		}
		CwfgmFBPFuel fuel = fuel0.mutate();
		useCrownBaseHeight = fuel.isC6FuelType();

		if (useBuildup)
			flags |= 1 << SCENARIO_OPTION.BUI;
		if (elevation >= 0.0)
			flags |= 1 << SCENARIO_OPTION.FMC_TERRAIN;
		if (useSlope)
			flags |= 1 << SCENARIO_OPTION.TOPOGRAPHY;
		if (windSpeed > 0.0)
			flags |= 1 << SCENARIO_OPTION.WIND;
		if (useGreenup)
			flags |= 1 << SCENARIO_OPTION.GREENUP;
		if (acceleration)
			flags |= 1 << SCENARIO_OPTION.ACCEL;

		switch (fuelType) {
		case 16:
		case 17:
			// this is a grass fuel type
			fuel.setAttribute(FUELCOM_ATTRIBUTE.CURINGDEGREE, grassCuring / 100.0);
			fuel.setAttribute(FUELCOM_ATTRIBUTE.GFL, grassFuelLoad);
			break;
		case 10:
		case 11:
		case 12:
			// this is M1 or M2 or M1M2
			fuel.setAttribute(FUELCOM_ATTRIBUTE.PC, (Double)(conifMixedWood / 100.0));
			break;
		case 13:
		case 14:
		case 15:
			// if it's M3 or M4 or M3M4
			fuel.setAttribute(FUELCOM_ATTRIBUTE.PDF, (Double)(deadBalsam / 100.0));
			break;
		}

		if (useCrownBaseHeight) {
			// this fuel type uses CBH, which may have been modified by the user
			fuel.setAttribute(FUELCOM_ATTRIBUTE.CBH, (Double)(crownBase));
		}

		fmc = fuel.fmc(DEGREE_TO_RADIAN(latitude), DEGREE_TO_RADIAN(longitude), (elevation < 0.0) ? -99.0
				: elevation, julian);

		FF = Fwi.ff(ffmc, elapsedTime * 60);
		if (!useBui)
			bui = Fwi.bui(dc, dmc);

		double WAZ = NORMALIZE_ANGLE_RADIAN(DEGREE_TO_RADIAN(COMPASS_TO_CARTESIAN_DEGREE(windDirection + 180.0)));
		double SAZ = NORMALIZE_ANGLE_RADIAN(DEGREE_TO_RADIAN(COMPASS_TO_CARTESIAN_DEGREE(aspect + 180.0)));
		OutVariable<Double> frss_ov = new OutVariable<Double>();
		OutVariable<Double> brss_ov = new OutVariable<Double>();
		OutVariable<Double> fros_eq_ov = new OutVariable<Double>();
		OutVariable<Double> bros_eq_ov = new OutVariable<Double>();
		OutVariable<Double> rss_ov = new OutVariable<Double>();
		OutVariable<Double> ros_eq_ov = new OutVariable<Double>();
		OutVariable<Double> ros_t_ov = new OutVariable<Double>();
		OutVariable<Double> fros_ov = new OutVariable<Double>();
		OutVariable<Double> bros_ov = new OutVariable<Double>();
		OutVariable<Double> wsv_ov = new OutVariable<Double>();
		OutVariable<Double> raz_ov = new OutVariable<Double>();

		fuel.calculateROSValues(slopeValue * 0.01, SAZ, windSpeed, WAZ, bui,
				fmc, ffmc, FF, new WTime((long) (elapsedTime * 60), 
						new WTimeManager(new WorldLocation())), 
						new WTime((long) (elapsedTime * 60), 
						new WTimeManager(new WorldLocation())), flags, null, rss_ov, ros_eq_ov, ros_t_ov, frss_ov, fros_eq_ov, fros_ov,
				brss_ov, bros_eq_ov, bros_ov, wsv_ov, raz_ov);
		
		ros_eq = ros_eq_ov.value;
		ros_t = ros_t_ov.value;
		double fros_eq = fros_eq_ov.value;
		fros = fros_ov.value;
		double bros_eq = bros_eq_ov.value;
		bros = bros_ov.value;
		wsv = wsv_ov.value;
		raz = raz_ov.value;

		char ffd = 0;
		char bfd = 0;
		char hfd = 0;

		OutVariable<Double> cfb_ov = new OutVariable<Double>();
		OutVariable<Double> cfc_ov = new OutVariable<Double>();
		OutVariable<Double> rso_ov = new OutVariable<Double>();
		OutVariable<Double> csi_ov = new OutVariable<Double>();
		OutVariable<Double> sfc_ov = new OutVariable<Double>();
		OutVariable<Double> tfc_ov = new OutVariable<Double>();
		OutVariable<Double> ffi_ov = new OutVariable<Double>();
		fuel.calculateFCValues(ffmc, bui, fmc, fros, fros, flags, cfb_ov,
				cfc_ov, rso_ov, csi_ov, sfc_ov, tfc_ov, ffi_ov);
		cfb = cfb_ov.value;
		cfc = cfc_ov.value;
		rso = rso_ov.value;
		csi = csi_ov.value;
		sfc = sfc_ov.value;
		tfc = tfc_ov.value;
		ffi = ffi_ov.value;
		if (cfb >= 0.0) {
			if (cfb < 0.1)
				ffd = 'S';
			else if (cfb < 0.9)
				ffd = 'I';
			else
				ffd = 'C';
		}
		fuel.calculateFCValues(ffmc, bui, fmc, bros, bros, flags, cfb_ov,
				cfc_ov, rso_ov, csi_ov, sfc_ov, tfc_ov, ffi_ov);
		cfb = cfb_ov.value;
		cfc = cfc_ov.value;
		rso = rso_ov.value;
		csi = csi_ov.value;
		sfc = sfc_ov.value;
		tfc = tfc_ov.value;
		bfi = ffi_ov.value;
		if (cfb >= 0.0) {
			if (cfb < 0.1)
				bfd = 'S';
			else if (cfb < 0.9)
				bfd = 'I';
			else
				bfd = 'C';
		}
		fuel.calculateFCValues(ffmc, bui, fmc, ros_t, ros_t, flags, cfb_ov,
				cfc_ov, rso_ov, csi_ov, sfc_ov, tfc_ov, ffi_ov);
		cfb = cfb_ov.value;
		cfc = cfc_ov.value;
		rso = rso_ov.value;
		csi = csi_ov.value;
		sfc = sfc_ov.value;
		tfc = tfc_ov.value;
		hfi = ffi_ov.value;
		if (cfb >= 0.0) {
			if (cfb < 0.1)
				hfd = 'S';
			else if (cfb < 0.9)
				hfd = 'I';
			else if (cfb >= 0.9)
				hfd = 'C';
		}
		OutVariable<Double> area_ov = new OutVariable<Double>();
		OutVariable<Double> perimeter_ov = new OutVariable<Double>();
		fuel.calculateStatistics(ros_t, fros, bros, cfb, new WTime(
				(long) (elapsedTime * 60), new WTimeManager(new WorldLocation())), flags, area_ov, perimeter_ov);
		area = area_ov.value;
		perimeter = perimeter_ov.value;
		OutVariable<Double> distancehead_ov = new OutVariable<Double>();
		OutVariable<Double> distanceflank_ov = new OutVariable<Double>();
		OutVariable<Double> distanceback_ov = new OutVariable<Double>();
		fuel.calculateDistances(ros_t, fros, bros, cfb, new WTime(
				(long) (elapsedTime * 60), new WTimeManager(new WorldLocation())), flags, distancehead_ov,
				distanceflank_ov, distanceback_ov);
		distanceHead = distancehead_ov.value;
		distanceFlank = distanceflank_ov.value;
		distanceBack = distanceback_ov.value;

		raz = NORMALIZE_ANGLE_DEGREE(CARTESIAN_TO_COMPASS_DEGREE(RADIAN_TO_DEGREE(raz)));
		if (wsv == 0.0) {
			raz = 0.0;
		} else if (raz == 0.0) {
			raz = 360.0;
		}

		double LB;
		if (fros_eq > 0.0)
			LB = (ros_eq + bros_eq) / (2.0 * fros_eq);
		else
			LB = 0.0;
		lb = LB;

		isi = Fwi.isiFBP(ffmc, wsv, elapsedTime * 60);
		cfb *= 100.0;

		//
		// Build fire description string
		//
		headFireDescription = FBPFireDescription(hfd);
		flankFireDescription = FBPFireDescription(ffd);
		backFireDescription = FBPFireDescription(bfd);
		if (TranslationCallback.instance != null)
			fireDescription = TranslationCallback.instance.translate("ui.label.fire.head") + ": ";
		else
			fireDescription = "Head: ";
		
		if (cfbPossible)
			fireDescription += headFireDescription;
		else
			fireDescription += "Surface Fire";
		
		if (TranslationCallback.instance != null)
			fireDescription += "\r\n" + TranslationCallback.instance.translate("ui.label.fire.flank") + ": ";
		else
			fireDescription += "\r\nFlank: ";
		
		if (cfbPossible)
			fireDescription += flankFireDescription;
		else
			fireDescription += "Surface Fire";
		
		
		if (TranslationCallback.instance != null)
			fireDescription += "\r\n" + TranslationCallback.instance.translate("ui.label.fire.back") + ": ";
		else
			fireDescription += "\r\nBack: ";
		
		if (cfbPossible)
			fireDescription += backFireDescription;
		else
			fireDescription += "Surface Fire";
		
		if (!cfbPossible)
			cfb = 0;
		
	}

	//! @cond
	private String FBPFireDescription(char c) {
		switch (c) {
		case 'S':
			if (TranslationCallback.instance != null)
				return TranslationCallback.instance.translate("ui.label.fire.surface");
			else
				return "Surface Fire";
		case 'C':
			if (TranslationCallback.instance != null)
				return TranslationCallback.instance.translate("ui.label.fire.crown");
			else
				return "Crown Fire";
		case 'I':
			if (TranslationCallback.instance != null)
				return TranslationCallback.instance.translate("ui.label.fire.inter");
			else
				return "Intermittent Crowning";
		default:
			if (TranslationCallback.instance != null)
				return TranslationCallback.instance.translate("ui.label.fire.unknown");
			else
				return "Unknown";
		}
	}
	//! @endcond
}
