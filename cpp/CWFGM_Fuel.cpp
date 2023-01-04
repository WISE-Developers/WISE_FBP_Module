/**
 * WISE_FBP_Module: CWFGM_Fuel.cpp
 * Copyright (C) 2023  WISE
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "fmc.h"
#include "sfc.h"
#include "tfc.h"
#include "isf.h"
#include "rsi.h"
#include "lb.h"
#include "cfb.h"
#include "AccAlpha.h"
#include "flame.h"
#include "SpreadParms.h"
#include "FBPFuel.h"

#include "CWFGM_Fuel_Shared.h"

#include "WTime.h"
#include "results.h"
#include "GridCom_ext.h"
#include "ccwfgmFuel.pb.h"

#ifdef DEBUG
#include <assert.h>
#endif

/*
	This is a no-argument constructor to initialize a ICWFGM_Fuel object
*/
ICWFGM_Fuel::ICWFGM_Fuel() : ICWFGM_CommonBase() {
}

/*
	This is a destructor method for a ICWFGM_Fuel object
*/
ICWFGM_Fuel::~ICWFGM_Fuel() {
}


bool CCWFGM_FuelOverrides::AddOverride(const std::uint16_t option, const PolymorphicAttribute value) {
	auto it = overrides.begin();
	while (it != overrides.end()) {
		if (it->key == option) {
			it->value = value;
			return true;
		}
		++it;
	}
	entry e;
	e.key = option;
	e.value = value;
	overrides.push_back(e);
	return true;
}


bool CCWFGM_FuelOverrides::RemoveOverride(const std::uint16_t option) {
	auto it = overrides.begin();
	while (it != overrides.end()) {
		if (it->key == option) {
			overrides.erase(it);
			return true;
		}
		++it;
	}
	return false;
}


bool CCWFGM_FuelOverrides::ContainsOverride(const std::uint16_t option) const {
	auto it = overrides.begin();
	while (it != overrides.end()) {
		if (it->key == option) {
			return true;
		}
		++it;
	}
	return false;
}


bool CCWFGM_FuelOverrides::RetrieveOverride(const std::uint16_t option, PolymorphicAttribute& value) const {
	auto it = overrides.begin();
	while (it != overrides.end()) {
		if (it->key == option) {
			value = it->value;
			return true;
		}
		++it;
	}
	return false;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_PercentileAttribute object
*/
ICWFGM_PercentileAttribute::ICWFGM_PercentileAttribute() {
}


/*
	This is a no-argument constructor to initialize a ICWFGM_AccelAttribute object
*/
ICWFGM_AccelAttribute::ICWFGM_AccelAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_FMCAttribute object
*/
ICWFGM_FMCAttribute::ICWFGM_FMCAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_SFCAttribute object
*/
ICWFGM_SFCAttribute::ICWFGM_SFCAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_TFCAttribute object
*/
ICWFGM_TFCAttribute::ICWFGM_TFCAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_RSIAttribute object
*/
ICWFGM_RSIAttribute::ICWFGM_RSIAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_CFBAttribute object
*/
ICWFGM_CFBAttribute::ICWFGM_CFBAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_LBAttribute object
*/
ICWFGM_LBAttribute::ICWFGM_LBAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_ISFAttribute object
*/
ICWFGM_ISFAttribute::ICWFGM_ISFAttribute() {
	__boost_ref_cnt = 0;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel object
*/
CCWFGM_Fuel::CCWFGM_Fuel() {
	m_bRequiresSave = false;

	m_name.clear();
//	memset(&m_fuel.m_defaultFuelType, 0, ((char *)&m_fuel.m_CFBCalculation_Greenup) - ((char *)&m_fuel.m_defaultFuelType) + sizeof(m_fuel.m_CFBCalculation_Greenup));
}

/*
	This is a 1-argument constructor to initialize a CCWFGM_Fuel object by copying another CCWFGM_Fuel object
*/
CCWFGM_Fuel::CCWFGM_Fuel(const CCWFGM_Fuel &toCopy) : m_fuel(toCopy.m_fuel) {
	m_bRequiresSave = false;

	m_name = toCopy.m_name;
}


HRESULT CCWFGM_Fuel::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel::FromCLSID(const _GUID &guid, boost::intrusive_ptr<ICWFGM_Fuel> *pVal) {
	if (!pVal)
		return E_INVALIDARG;

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_C1, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_C1());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_C2, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_C2());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_C3, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_C3());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_C4, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_C4());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_C5, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_C5());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_C6, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_C6());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_C7, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_C7());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_D1, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_D1());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_D2, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_D2());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_D1D2, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_D1D2());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_M1, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_M1());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_M2, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_M2());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_M1M2, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_M1M2());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_M3, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_M3());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_M4, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_M4());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_M3M4, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_M3M4());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_S1, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_S1());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_S2, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_S2());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_S3, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_S3());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_O1a, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_O1a());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_O1b, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_O1b());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_O1ab, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_O1ab());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_Non, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_Non());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ2, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ2());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ15, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ15());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ30, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ30());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ31, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ31());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ32, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ32());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ33, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ33());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ40, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ40());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ41, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ41());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ43, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ43());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ44, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ44());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ45, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ45());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ46, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ46());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ47, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ47());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ50, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ50());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ51, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ51());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ52, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ52());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ53, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ53());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ54, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ54());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ55, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ55());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ56, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ56());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ57, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ57());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ58, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ58());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ60, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ60());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ61, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ61());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ62, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ62());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ63, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ63());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ64, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ64());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ65, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ65());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ66, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ66());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ67, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ67());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ68, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ68());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ69, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ69());
		return S_OK;
	}

	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ70, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ70());
		return S_OK;
	}
	if (!memcmp(&guid, &CLSID_CWFGM_Fuel_NZ71, sizeof(_GUID))) {
		pVal->reset(new CCWFGM_Fuel_NZ71());
		return S_OK;
	}

	return E_FAIL;
}

/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_Readonly object
*/
CCWFGM_Fuel_Readonly::CCWFGM_Fuel_Readonly() : CCWFGM_Fuel() {
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_C1 object
*/
CCWFGM_Fuel_C1::CCWFGM_Fuel_C1() : CCWFGM_Fuel_Readonly() {
	m_name = "C-1 Spruce-Lichen Woodland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_C1;

	m_fuel.m_spread = new SpreadParms_C1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS, 0.0);

	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C1_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_C1::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_C1();
	return S_OK;
}


HRESULT CCWFGM_Fuel_C1::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C1, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_C1::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C1, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_C2 object
*/
CCWFGM_Fuel_C2::CCWFGM_Fuel_C2() : CCWFGM_Fuel_Readonly() {
	m_name = "C-2 Boreal Spruce";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_C2;

	m_fuel.m_spread = new SpreadParms_C1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS, 0.0);

	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C2_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C2_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_C2::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_C2();
	return S_OK;
}


HRESULT CCWFGM_Fuel_C2::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C2, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_C2::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C2, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_C3 object
*/
CCWFGM_Fuel_C3::CCWFGM_Fuel_C3() : CCWFGM_Fuel_Readonly() {
	m_name = "C-3 Mature Jack or Lodgepole Pine";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_C3;

	m_fuel.m_spread = new SpreadParms_C1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C3_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1() ;
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1() ;
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C3_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_C3::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_C3();
	return S_OK;
}


HRESULT CCWFGM_Fuel_C3::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C3, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_C3::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C3, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_C4 object
*/
CCWFGM_Fuel_C4::CCWFGM_Fuel_C4() : CCWFGM_Fuel_Readonly() {
	m_name = "C-4 Immature Jack or Lodgepole Pine";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_C4;

	m_fuel.m_spread = new SpreadParms_C1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C4_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_C4::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_C4();
	return S_OK;
}


HRESULT CCWFGM_Fuel_C4::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C4, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_C4::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C4, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_C5 object
*/
CCWFGM_Fuel_C5::CCWFGM_Fuel_C5() : CCWFGM_Fuel_Readonly() {
	m_name = "C-5 Red and White Pine";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_C5;

	m_fuel.m_spread = new SpreadParms_C1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C5_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C5_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_C5::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_C5();
	return S_OK;
}


HRESULT CCWFGM_Fuel_C5::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C5, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_C5::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C5, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_C6 object
*/
CCWFGM_Fuel_C6::CCWFGM_Fuel_C6() : CCWFGM_Fuel_Readonly() {
	m_name = "C-6 Conifer Plantation";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_C6;

	m_fuel.m_spread = new SpreadParms_C6();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C6_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C6_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C6() ;
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1() ;
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_C6::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_C6();
	return S_OK;
}


HRESULT CCWFGM_Fuel_C6::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C6, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_C6::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C6, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_C7 object
*/
CCWFGM_Fuel_C7::CCWFGM_Fuel_C7() : CCWFGM_Fuel_Readonly() {
	m_name = "C-7 Ponderosa Pine / Douglas Fir";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_C7;

	m_fuel.m_spread = new SpreadParms_C1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C7();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C7_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C7_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_C7::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_C7();
	return S_OK;
}


HRESULT CCWFGM_Fuel_C7::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C7, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_C7::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_C7, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_D1 object
*/
CCWFGM_Fuel_D1::CCWFGM_Fuel_D1() : CCWFGM_Fuel_Readonly() {
	m_name = "D-1 Leafless Aspen";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_D1;

	m_fuel.m_spread = new SpreadParms_D1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_D1_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_D1::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_D1();
	return S_OK;
}


HRESULT CCWFGM_Fuel_D1::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_D1, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_D1::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_D1, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_D2 object
*/
CCWFGM_Fuel_D2::CCWFGM_Fuel_D2() : CCWFGM_Fuel_Readonly() {
	m_name = "D-2 Green Aspen (with BUI Thresholding)";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_D2;

	m_fuel.m_spread = new SpreadParms_D1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_D2_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_D2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_D2_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_D2();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_D2();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_D2();
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_D2::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_D2();
	return S_OK;
}


HRESULT CCWFGM_Fuel_D2::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_D2, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_D2::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_D2, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_D1D2 object
*/
CCWFGM_Fuel_D1D2::CCWFGM_Fuel_D1D2() : CCWFGM_Fuel_Readonly() {
	m_name = "D-1/D-2 Aspen";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_D1D2;

	m_fuel.m_spread = new SpreadParms_D1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_D1_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS, 0.0);
	m_fuel.m_SFCCalculation_Greenup = new SFC_D2();
	m_fuel.m_SFCCalculation_Greenup->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_D2_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_TFCCalculation_Greenup = new TFC_D2();
	m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_RSICalculation_Greenup = new RSI_D2();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS, 0.0);
	m_fuel.m_CFBCalculation_Greenup = new CFB_D2();
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_D1D2::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_D1D2();
	return S_OK;
}


HRESULT CCWFGM_Fuel_D1D2::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_D1D2, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_D1D2::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_D1D2, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_M1 object
*/
CCWFGM_Fuel_M1::CCWFGM_Fuel_M1() : CCWFGM_Fuel_Readonly() {
	m_name = "M-1 Boreal Mixedwood - Leafless";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_M1;

	SpreadParms_Mixed *m = new SpreadParms_Mixed();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS, 0.0);
	// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c2(new CCWFGM_Fuel_C2()), cc2;
	if (FAILED(c2->Mutate(&cc2))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc2);
	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_M1();
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_M1();
	m_fuel.m_RSICalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR, 1.0);
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_M1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M1_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_M1::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_M1();
	return S_OK;
}


HRESULT CCWFGM_Fuel_M1::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M1, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_M1::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M1, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_M2 object
*/
CCWFGM_Fuel_M2::CCWFGM_Fuel_M2() : CCWFGM_Fuel_Readonly() {
	m_name = "M-2 Boreal Mixedwood - Green";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_M2;

	SpreadParms_Mixed *m = new SpreadParms_Mixed();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M2_DEFAULTS, 0.0);
	// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c2(new CCWFGM_Fuel_C2()), cc2;
	if (FAILED(c2->Mutate(&cc2))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc2);
	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_M1();
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_M1();
	m_fuel.m_RSICalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR, 0.2);
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_M1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M2_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_M2::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_M2();
	return S_OK;
}


HRESULT CCWFGM_Fuel_M2::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M2, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_M2::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M2, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_M1M2 object
*/
CCWFGM_Fuel_M1M2::CCWFGM_Fuel_M1M2() : CCWFGM_Fuel_Readonly() {
	m_name = "M-1/M-2 Boreal Mixedwood";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_M1M2;

	SpreadParms_Mixed *m = new SpreadParms_Mixed();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS, 0.0);
	// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c2(new CCWFGM_Fuel_C2()), cc2;
	if (FAILED(c2->Mutate(&cc2))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc2);
	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_M1();
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation = new RSI_M1();
	m_fuel.m_RSICalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR, 1.0);
	m_fuel.m_RSICalculation_Greenup = new RSI_M1();
	m_fuel.m_RSICalculation_Greenup->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR, 0.2);
	m_fuel.m_ISFCalculation = new ISF_M1();
	m_fuel.m_ISFCalculation_Greenup = new ISF_M1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();	
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M1_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_M1M2::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_M1M2();
	return S_OK;
}


HRESULT CCWFGM_Fuel_M1M2::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M1M2, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_M1M2::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M1M2, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_M3 object
*/
CCWFGM_Fuel_M3::CCWFGM_Fuel_M3() : CCWFGM_Fuel_Readonly() {
	m_name = "M-3 Dead Balsam Fir / Mixedwood - Leafless";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_M3;

	SpreadParms_Mixed *m = new SpreadParms_MixedDead();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M3_DEFAULTS, 0.0);
	// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c2(new CCWFGM_Fuel_C2()), cc2;
	if (FAILED(c2->Mutate(&cc2))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc2);
	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_M3();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation= new ISF_M3M4();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M3_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_M3::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_M3();
	return S_OK;
}


HRESULT CCWFGM_Fuel_M3::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M3, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_M3::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M3, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_M4 object
*/
CCWFGM_Fuel_M4::CCWFGM_Fuel_M4() : CCWFGM_Fuel_Readonly() {
	m_name = "M-4 Dead Balsam Fir / Mixedwood - Green";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_M4;

	SpreadParms_Mixed *m = new SpreadParms_MixedDead();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M4_DEFAULTS, 0.0);
	// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c2(new CCWFGM_Fuel_C2()), cc2;
	if (FAILED(c2->Mutate(&cc2))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc2);
	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_M4_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_M4();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation= new ISF_M3M4();
	m_fuel.m_ISFCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS, 0.0);
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_M4::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_M4();
	return S_OK;
}


HRESULT CCWFGM_Fuel_M4::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M4, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_M4::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M4, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_M3M4 object
*/
CCWFGM_Fuel_M3M4::CCWFGM_Fuel_M3M4() : CCWFGM_Fuel_Readonly() {
	m_name = "M-3/M-4 Dead Balsam Fir / Mixedwood";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_M3M4;

	SpreadParms_Mixed *m = new SpreadParms_MixedDead();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M3_DEFAULTS, 0.0);
// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c2(new CCWFGM_Fuel_C2()), cc2;
	if (FAILED(c2->Mutate(&cc2))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc2);
	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation = new RSI_M3();
	m_fuel.m_RSICalculation_Greenup = new RSI_M4();
	m_fuel.m_ISFCalculation= new ISF_M3M4();
	m_fuel.m_ISFCalculation_Greenup = new ISF_M3M4();
	m_fuel.m_ISFCalculation_Greenup->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS, 0.0);
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M3_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_M3M4::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_M3M4();
	return S_OK;
}


HRESULT CCWFGM_Fuel_M3M4::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M3M4, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_M3M4::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_M3M4, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_O1a object
*/
CCWFGM_Fuel_O1a::CCWFGM_Fuel_O1a() : CCWFGM_Fuel_Readonly() {
	m_name = "O-1a Matted Grass";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_O1a;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_O1A_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_O1a::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_O1a();
	return S_OK;
}


HRESULT CCWFGM_Fuel_O1a::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_O1a, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_O1a::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_O1a, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_O1b object
*/
CCWFGM_Fuel_O1b::CCWFGM_Fuel_O1b() : CCWFGM_Fuel_Readonly() {
	m_name = "O-1b Standing Grass";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_O1b;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_O1B_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_O1b::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_O1b();
	return S_OK;
}


HRESULT CCWFGM_Fuel_O1b::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_O1b, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_O1b::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_O1b, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_O1ab object
*/
CCWFGM_Fuel_O1ab::CCWFGM_Fuel_O1ab() {
	m_name = "O-1a/O-1b Grass";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_O1ab;

	m_fuel.m_spread = new SpreadParms_O1ab();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_O1AB_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_O1A_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_O1ab::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_O1ab();
	return S_OK;
}


HRESULT CCWFGM_Fuel_O1ab::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_O1ab, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_O1ab::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_O1ab, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_S1 object
*/
CCWFGM_Fuel_S1::CCWFGM_Fuel_S1() : CCWFGM_Fuel_Readonly() {
	m_name = "S-1 Jack or Lodgepole Pine Slash";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_S1;

	m_fuel.m_spread = new SpreadParms_S1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_S1_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_S1::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_S1();
	return S_OK;
}


HRESULT CCWFGM_Fuel_S1::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_S1, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_S1::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_S1, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_S2 object
*/
CCWFGM_Fuel_S2::CCWFGM_Fuel_S2() : CCWFGM_Fuel_Readonly() {
	m_name = "S-2 White Spruce / Balsam Slash";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_S2;

	m_fuel.m_spread = new SpreadParms_S1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_S2_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_S2_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_S2::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_S2();
	return S_OK;
}


HRESULT CCWFGM_Fuel_S2::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_S2, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_S2::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_S2, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_S3 object
*/
CCWFGM_Fuel_S3::CCWFGM_Fuel_S3() : CCWFGM_Fuel_Readonly() {
	m_name = "S-3 Coastal Cedar / Hemlock / Douglas-Fir Slash";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_S3;

	m_fuel.m_spread = new SpreadParms_S1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_S3_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_S3_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_S3::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_S3();
	return S_OK;
}


HRESULT CCWFGM_Fuel_S3::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_S3, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_S3::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_S3, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_Non object
*/
CCWFGM_Fuel_Non::CCWFGM_Fuel_Non() : CCWFGM_Fuel_Readonly() {
	m_name = "Non-fuel";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_Non;

	m_fuel.m_spread = new SpreadParms_Non();
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C1_CLR_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_NON_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_Non::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_Non();
	return S_OK;
}


HRESULT CCWFGM_Fuel_Non::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_Non, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_Non::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_Non, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ2 object
*/
CCWFGM_Fuel_NZ2::CCWFGM_Fuel_NZ2() {
	m_name = "NZ-2 Urban Parkland/Open Space";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ2;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ2_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ2::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ2();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ2::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ2, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ2::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ2, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ15 object
*/
CCWFGM_Fuel_NZ15::CCWFGM_Fuel_NZ15() {
	m_name = "NZ-15 Alpine Grass/Herbfield";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ15;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ15_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ15::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ15();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ15::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ15, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ15::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ15, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ30 object
*/
CCWFGM_Fuel_NZ30::CCWFGM_Fuel_NZ30() {
	m_name = "NZ-30 Short-rotation Cropland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ30;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ30_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ30::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ30();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ30::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ30, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ30::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ30, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ31 object
*/
CCWFGM_Fuel_NZ31::CCWFGM_Fuel_NZ31() {
	m_name = "NZ-31 Vineyard";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ31;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ31_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ31::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ31();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ31::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ31, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ31::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ31, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ32 object
*/
CCWFGM_Fuel_NZ32::CCWFGM_Fuel_NZ32() {
	m_name = "NZ-32 Orchard and Other Perennial Crops";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ32;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ32_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ32::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ32();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ32::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ32, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ32::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ32, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ33 object
*/
CCWFGM_Fuel_NZ33::CCWFGM_Fuel_NZ33() {
	m_name = "NZ-33 Orchard Vineyard and Other Perennial Crops";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ33;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ33_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ33::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ33();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ33::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ33, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ33::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ33, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ40 object
*/
CCWFGM_Fuel_NZ40::CCWFGM_Fuel_NZ40() {
	m_name = "NZ-40 High Producing Exotic Grassland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ40;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ40_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ40::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ40();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ40::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ40, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ40::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ40, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ41 object
*/
CCWFGM_Fuel_NZ41::CCWFGM_Fuel_NZ41() {
	m_name = "NZ-41 Low Producing Grassland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ41;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ41_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ41::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ41();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ41::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ41, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ41::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ41, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ43 object
*/
CCWFGM_Fuel_NZ43::CCWFGM_Fuel_NZ43() {
	m_name = "NZ-43 Tall Tussock Grassland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ43;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ43_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ43::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ43();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ43::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ43, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ43::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ43, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ44 object
*/
CCWFGM_Fuel_NZ44::CCWFGM_Fuel_NZ44() {
	m_name = "NZ-44 Depleted Grassland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ44;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ44_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ44::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ44();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ44::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ44, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ44::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ44, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ45 object
*/
CCWFGM_Fuel_NZ45::CCWFGM_Fuel_NZ45() {
	m_name = "NZ-45 Herbaceous Freshwater Vegetation";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ45;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ45_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ45_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ45::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ45();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ45::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ45, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ45::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ45, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ46 object
*/
CCWFGM_Fuel_NZ46::CCWFGM_Fuel_NZ46() {
	m_name = "NZ-46 Herbaceous Saline Vegetation";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ46;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ46_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ46::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ46();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ46::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ46, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ46::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ46, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ47 object
*/
CCWFGM_Fuel_NZ47::CCWFGM_Fuel_NZ47() {
	m_name = "NZ-47 Flaxland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ47;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ47_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ47_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ47::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ47();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ47::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ47, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ47::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ47, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ50 object
*/
CCWFGM_Fuel_NZ50::CCWFGM_Fuel_NZ50() {
	m_name = "NZ-50 Fernland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ50;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ50_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ50::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ50();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ50::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ50, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ50::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ50, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ51 object
*/
CCWFGM_Fuel_NZ51::CCWFGM_Fuel_NZ51() {
	m_name = "NZ-51 Gorse and/or Broom";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ51;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ51_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ51_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ51::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ51();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ51::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ51, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ51::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ51, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ52 object
*/
CCWFGM_Fuel_NZ52::CCWFGM_Fuel_NZ52() {
	m_name = "NZ-52 Manuka and/or Kanuka";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ52;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ52_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ52_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ52::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ52();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ52::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ52, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ52::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ52, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ53 object
*/
CCWFGM_Fuel_NZ53::CCWFGM_Fuel_NZ53() {
	m_name = "NZ-53 Matagouri";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ53;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ53_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ53::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ53();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ53::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ53, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ53::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ53, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ54 object
*/
CCWFGM_Fuel_NZ54::CCWFGM_Fuel_NZ54() {
	m_name = "NZ-54 Broadleafed Indigenous Hardwoods";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ54;

	SpreadParms_Mixed *m = new SpreadParms_Mixed();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ54_DEFAULTS, 0.0);
	// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c5(new CCWFGM_Fuel_C5()), cc5;
	if (FAILED(c5->Mutate(&cc5))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc5);

	cc5->SetAttribute(FUELCOM_ATTRIBUTE_A, 30.0);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_B, 0.0697);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_C, 4.0);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_Q, 0.8);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_BUI0, 50.0);

	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);

	dd1->SetAttribute(FUELCOM_ATTRIBUTE_A, 30.0);
	dd1->SetAttribute(FUELCOM_ATTRIBUTE_B, 0.0232);
	dd1->SetAttribute(FUELCOM_ATTRIBUTE_C, 1.6);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ54_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_M1();
	m_fuel.m_RSICalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR, 0.2);
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_M1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M2_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ54::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ54();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ54::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ54, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ54::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ54, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ55 object
*/
CCWFGM_Fuel_NZ55::CCWFGM_Fuel_NZ55() {
	m_name = "NZ-55 Sub Alpine Shrubland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ55;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ55_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ55_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ55::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ55();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ55::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ55, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ55::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ55, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ56 object
*/
CCWFGM_Fuel_NZ56::CCWFGM_Fuel_NZ56() {
	m_name = "NZ-56 Mixed Exotic Shrubland";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ56;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ56_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ56_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ56::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ56();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ56::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ56, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ56::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ56, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ57 object
*/
CCWFGM_Fuel_NZ57::CCWFGM_Fuel_NZ57() {
	m_name = "NZ-57 Grey Scrub";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ57;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ57_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ57_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ57::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ57();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ57::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ57, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ57::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ57, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ58 object
*/
CCWFGM_Fuel_NZ58::CCWFGM_Fuel_NZ58() {
	m_name = "NZ-58 Matagouri or Grey Scrub";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ58;

	m_fuel.m_spread = new SpreadParms_NZ();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ58_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ58_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ58::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ58();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ58::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ58, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ58::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ58, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ60 object
*/
CCWFGM_Fuel_NZ60::CCWFGM_Fuel_NZ60() {
	m_name = "NZ-60 Minor Shelterbelts";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ60;

	m_fuel.m_spread = new SpreadParms_C6();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ60_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ60_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C6();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ60::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ60();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ60::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ60, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ60::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ60, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ61 object
*/
CCWFGM_Fuel_NZ61::CCWFGM_Fuel_NZ61() {
	m_name = "NZ-61 Major Shelterbelts";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ61;

	m_fuel.m_spread = new SpreadParms_C6();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ61_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ61_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C6();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ61::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ61();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ61::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ61, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ61::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ61, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ62 object
*/
CCWFGM_Fuel_NZ62::CCWFGM_Fuel_NZ62() {
	m_name = "NZ-62 Afforestation (not imaged)";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ62;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ62_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ62::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ62();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ62::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ62, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ62::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ62, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ63 object
*/
CCWFGM_Fuel_NZ63::CCWFGM_Fuel_NZ63() {
	m_name = "NZ-63 Afforestation (imaged post LCDB1)";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ63;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ63_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ63::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ63();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ63::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ63, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ63::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ63, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ64 object
*/
CCWFGM_Fuel_NZ64::CCWFGM_Fuel_NZ64() {
	m_name = "NZ-64 Forest - Harvested";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ64;

	m_fuel.m_spread = new SpreadParms_S1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ64_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ64::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ64();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ64::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ64, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ64::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ64, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ65 object
*/
CCWFGM_Fuel_NZ65::CCWFGM_Fuel_NZ65() {
	m_name = "NZ-65 Pine Forest - Open Canopy";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ65;

	m_fuel.m_spread = new SpreadParms_O1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ65_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_O1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_O1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_O1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_O1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82();
}


HRESULT CCWFGM_Fuel_NZ65::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ65();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ65::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ65, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ65::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ65, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ66 object
*/
CCWFGM_Fuel_NZ66::CCWFGM_Fuel_NZ66() {
	m_name = "NZ-66 Pine Forest - Closed Canopy";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ66;

	m_fuel.m_spread = new SpreadParms_C6();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ66_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ66_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C6();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ66::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ66();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ66::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ66, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ66::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ66, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ67 object
*/
CCWFGM_Fuel_NZ67::CCWFGM_Fuel_NZ67() {
	m_name = "NZ-67 Other Exotic Forest";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ67;

	m_fuel.m_spread = new SpreadParms_C6();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ67_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ67_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C6();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ67::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ67();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ67::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ67, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ67::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ67, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ68 object
*/
CCWFGM_Fuel_NZ68::CCWFGM_Fuel_NZ68() {
	m_name = "NZ-68 Deciduous Hardwoods";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ68;

	m_fuel.m_spread = new SpreadParms_D1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ68_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel
	m_fuel.m_FMCCalculation = new FMC_NoCalc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ68_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C1();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ68::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ68();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ68::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ68, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ68::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ68, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ69 object
*/
CCWFGM_Fuel_NZ69::CCWFGM_Fuel_NZ69() {
	m_name = "NZ-69 Indigenous Forest";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ69;

	SpreadParms_Mixed *m = new SpreadParms_Mixed();
	m_fuel.m_spread = m;
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ69_DEFAULTS, 0.0);
	// parameters for M1,2
	boost::intrusive_ptr<ICWFGM_Fuel> c5(new CCWFGM_Fuel_C5()), cc5;
	if (FAILED(c5->Mutate(&cc5))) // these are read/writes even though M1 is only read-only - done on purpose to make the UI
		throw std::runtime_error("Mutate");
	m->SetC2(cc5);

	cc5->SetAttribute(FUELCOM_ATTRIBUTE_A, 30.0);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_B, 0.0697);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_C, 4.0);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_Q, 0.8);
	cc5->SetAttribute(FUELCOM_ATTRIBUTE_BUI0, 50.0);

	boost::intrusive_ptr<ICWFGM_Fuel> d1(new CCWFGM_Fuel_D1()), dd1;
	if (FAILED(d1->Mutate(&dd1)))
		throw std::runtime_error("Mutate");
	m->SetD1(dd1);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_C2();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ69_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_M1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_M1();
	m_fuel.m_RSICalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR, 0.2);
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_M1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M2_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ69::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ69();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ69::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ69, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ69::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ69, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ70 object
*/
CCWFGM_Fuel_NZ70::CCWFGM_Fuel_NZ70() {
	m_name = "NZ-70 Mangrove";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ70;

	m_fuel.m_spread = new SpreadParms_C1();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ70_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_O1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ70_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_Constant();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaOpen();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ70::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ70();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ70::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ70, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ70::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ70, sizeof(_GUID));
	return S_OK;
}


/*
	This is a no-argument constructor to initialize a CCWFGM_Fuel_NZ71 object
*/
CCWFGM_Fuel_NZ71::CCWFGM_Fuel_NZ71() {
	m_name = "NZ-71 Exotic Forest";
	m_fuel.m_defaultFuelType = CLSID_CWFGM_Fuel_NZ71;

	m_fuel.m_spread = new SpreadParms_C6();
	m_fuel.m_spread->SetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ71_DEFAULTS, 0.0);
	// fuel type-specific calculation engines for the FBPfuel 
	m_fuel.m_FMCCalculation = new FMC_Calc();
	m_fuel.m_SFCCalculation_Greenup = m_fuel.m_SFCCalculation = new SFC_S1();
	m_fuel.m_SFCCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ71_DEFAULTS, 0.0);
	m_fuel.m_TFCCalculation_Greenup = m_fuel.m_TFCCalculation = new TFC_C1();
	m_fuel.m_RSICalculation_Greenup = m_fuel.m_RSICalculation = new RSI_C6();
	m_fuel.m_ISFCalculation_Greenup = m_fuel.m_ISFCalculation = new ISF_C1();
	m_fuel.m_AccAlphaCalculation = new AccAlphaClosed();
	m_fuel.m_LBCalculation = new LB_C1();
	m_fuel.m_CFBCalculation_Greenup = m_fuel.m_CFBCalculation = new CFB_C1();
	m_fuel.m_CFBCalculation->SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS, 0.0);
	m_fuel.m_FLCalculation = new FlameLength_Alexander82_Tree();
}


HRESULT CCWFGM_Fuel_NZ71::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	*newFuel = new CCWFGM_Fuel_NZ71();
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ71::GetDefaultCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ71, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_NZ71::GetCLSID(_GUID *clsID) const {
	memcpy(clsID, &CLSID_CWFGM_Fuel_NZ71, sizeof(_GUID));
	return S_OK;
}
