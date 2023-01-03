/**
 * WISE_FBP_Module: FBPFuel.cpp
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

#include "angles.h"
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
#include "str_printf.h"
#include "results.h"

#ifdef DEBUG
#include <assert.h>
#endif

using namespace CONSTANTS_NAMESPACE;

/*
	This is a no-argument constructor to initialize a FBPFuel object
	Refer to the constructors found in CWFGM_Fuel.cpp for valid values assigned to these member variables
*/
FBPFuel::FBPFuel() {
	memset(&m_defaultFuelType, 0, sizeof(m_defaultFuelType));
	m_fuelTypeModified = false;
	m_spread = nullptr;
	m_FMCCalculation = nullptr;
	m_SFCCalculation_Greenup = m_SFCCalculation = nullptr;
	m_TFCCalculation_Greenup = m_TFCCalculation = nullptr;
	m_RSICalculation_Greenup = m_RSICalculation = nullptr;
	m_ISFCalculation_Greenup = m_ISFCalculation = nullptr;
	m_AccAlphaCalculation = nullptr;
	m_LBCalculation = nullptr;
	m_CFBCalculation_Greenup = m_CFBCalculation = nullptr;
	m_FLCalculation = nullptr;

	m_AccelCustom = nullptr;
	m_FMCCustom = nullptr;
	m_SFCCustom = nullptr;
	m_TFCCustom = nullptr;
	m_CFBCustom = nullptr;
	m_RSICustom = nullptr;
	m_ISFCustom = nullptr;
	m_LBCustom = nullptr;

	m_fwi = new ICWFGM_FWI;
}

/*
	This is a 1-argument constructor to initialize a FBPFuel object by copying another FBPFuel object
*/
FBPFuel::FBPFuel(const FBPFuel & toCopy) {
	*this = toCopy;
}

/*
	This method copies the variables in the current FBPFuel object to another
	FBPFuel object
*/
FBPFuel &FBPFuel::operator=(const FBPFuel &toCopy) {
	if (this == &toCopy)
		return *this;
	m_defaultFuelType = toCopy.m_defaultFuelType;
	m_fuelTypeModified = toCopy.m_fuelTypeModified;

	if (m_spread)											delete m_spread;
	if (m_FMCCalculation)									delete m_FMCCalculation;
	if (m_SFCCalculation)									delete m_SFCCalculation;
	if (m_TFCCalculation)									delete m_TFCCalculation;
	if (m_RSICalculation)									delete m_RSICalculation;
	if (m_ISFCalculation)									delete m_ISFCalculation;
	if (m_AccAlphaCalculation)								delete m_AccAlphaCalculation;
	if (m_LBCalculation)									delete m_LBCalculation;
	if (m_CFBCalculation)									delete m_CFBCalculation;
	if (m_FLCalculation)									delete m_FLCalculation;

	if ((m_SFCCalculation_Greenup) && (m_SFCCalculation_Greenup != m_SFCCalculation))	delete m_SFCCalculation_Greenup;
	if ((m_TFCCalculation_Greenup) && (m_TFCCalculation_Greenup != m_TFCCalculation))	delete m_TFCCalculation_Greenup;
	if ((m_RSICalculation_Greenup) && (m_RSICalculation_Greenup != m_RSICalculation))	delete m_RSICalculation_Greenup;
	if ((m_CFBCalculation_Greenup) && (m_CFBCalculation_Greenup != m_CFBCalculation))	delete m_CFBCalculation_Greenup;
	if ((m_ISFCalculation_Greenup) && (m_ISFCalculation_Greenup != m_ISFCalculation))	delete m_ISFCalculation_Greenup;

	m_AccelCustom = nullptr;
	m_FMCCustom = nullptr;
	m_SFCCustom = nullptr;
	m_TFCCustom = nullptr;
	m_CFBCustom = nullptr;
	m_RSICustom = nullptr;
	m_ISFCustom = nullptr;
	m_LBCustom = nullptr;

	m_spread = (toCopy.m_spread) ? (SpreadParmsAttribute *)toCopy.m_spread->Clone() : nullptr;
	m_FMCCalculation = (toCopy.m_FMCCalculation) ? (FMCAttribute *)toCopy.m_FMCCalculation->Clone() : nullptr;
	m_SFCCalculation_Greenup = (toCopy.m_SFCCalculation_Greenup) ? (SFCAttribute *)toCopy.m_SFCCalculation_Greenup->Clone() : nullptr;
	m_SFCCalculation = (toCopy.m_SFCCalculation) ? (SFCAttribute *)toCopy.m_SFCCalculation->Clone() : nullptr;
	m_TFCCalculation_Greenup = (toCopy.m_TFCCalculation_Greenup) ? (TFCAttribute *)toCopy.m_TFCCalculation_Greenup->Clone() : nullptr;
	m_TFCCalculation = (toCopy.m_TFCCalculation) ? (TFCAttribute *)toCopy.m_TFCCalculation->Clone() : nullptr;
	m_RSICalculation_Greenup = (toCopy.m_RSICalculation_Greenup) ? (RSIAttribute *)toCopy.m_RSICalculation_Greenup->Clone() : nullptr;
	m_RSICalculation = (toCopy.m_RSICalculation) ? (RSIAttribute *)toCopy.m_RSICalculation->Clone() : nullptr;
	m_ISFCalculation_Greenup = (toCopy.m_ISFCalculation_Greenup) ? (ISFAttribute *)toCopy.m_ISFCalculation_Greenup->Clone() : nullptr;
	m_ISFCalculation = (toCopy.m_ISFCalculation) ? (ISFAttribute *)toCopy.m_ISFCalculation->Clone() : nullptr;
	m_AccAlphaCalculation = (toCopy.m_AccAlphaCalculation) ? (AccAlphaAttribute *)toCopy.m_AccAlphaCalculation->Clone() : nullptr;
	m_LBCalculation = (toCopy.m_LBCalculation) ? (LBAttribute *)toCopy.m_LBCalculation->Clone() : nullptr;
	m_CFBCalculation_Greenup = (toCopy.m_CFBCalculation_Greenup) ? (CFBAttribute *)toCopy.m_CFBCalculation_Greenup->Clone() : nullptr;
	m_CFBCalculation = (toCopy.m_CFBCalculation) ? (CFBAttribute *)toCopy.m_CFBCalculation->Clone() : nullptr;
	m_FLCalculation = (toCopy.m_FLCalculation) ? (FlameLengthAttribute *)toCopy.m_FLCalculation->Clone() : nullptr;

	weak_assert(m_spread != nullptr);
	weak_assert(m_FMCCalculation != nullptr);
	weak_assert(m_SFCCalculation_Greenup != nullptr);
	weak_assert(m_SFCCalculation != nullptr);
	weak_assert(m_TFCCalculation_Greenup != nullptr);
	weak_assert(m_TFCCalculation != nullptr);
	weak_assert(m_RSICalculation_Greenup != nullptr);
	weak_assert(m_RSICalculation != nullptr);
	weak_assert(m_ISFCalculation_Greenup != nullptr);
	weak_assert(m_ISFCalculation != nullptr);
	weak_assert(m_AccAlphaCalculation != nullptr);
	weak_assert(m_LBCalculation != nullptr);
	weak_assert(m_CFBCalculation_Greenup != nullptr);
	weak_assert(m_CFBCalculation != nullptr);
	weak_assert(m_FLCalculation != nullptr);

	m_AccelCustom = toCopy.m_AccelCustom;
	m_FMCCustom = toCopy.m_FMCCustom;
	m_SFCCustom = toCopy.m_SFCCustom;
	m_TFCCustom = toCopy.m_TFCCustom;
	m_CFBCustom = toCopy.m_CFBCustom;
	m_RSICustom = toCopy.m_RSICustom;
	m_ISFCustom = toCopy.m_ISFCustom;
	m_LBCustom = toCopy.m_LBCustom;

	if (!m_fwi)
		m_fwi = new ICWFGM_FWI;
	return *this;
}

/*
	This is a destructor method for a FBPFuel object
*/
FBPFuel::~FBPFuel() {
	if (m_spread)											delete m_spread;
	if (m_FMCCalculation)									delete m_FMCCalculation;
	if (m_SFCCalculation)									delete m_SFCCalculation;
	if (m_TFCCalculation)									delete m_TFCCalculation;
	if (m_RSICalculation)									delete m_RSICalculation;
	if (m_ISFCalculation)									delete m_ISFCalculation;
	if (m_AccAlphaCalculation)								delete m_AccAlphaCalculation;
	if (m_LBCalculation)									delete m_LBCalculation;
	if (m_CFBCalculation)									delete m_CFBCalculation;
	if (m_FLCalculation)									delete m_FLCalculation;

	if ((m_SFCCalculation_Greenup) && (m_SFCCalculation_Greenup != m_SFCCalculation))	delete m_SFCCalculation_Greenup;
	if ((m_TFCCalculation_Greenup) && (m_TFCCalculation_Greenup != m_TFCCalculation))	delete m_TFCCalculation_Greenup;
	if ((m_RSICalculation_Greenup) && (m_RSICalculation_Greenup != m_RSICalculation))	delete m_RSICalculation_Greenup;
	if ((m_CFBCalculation_Greenup) && (m_CFBCalculation_Greenup != m_CFBCalculation))	delete m_CFBCalculation_Greenup;
	if ((m_ISFCalculation_Greenup) && (m_ISFCalculation_Greenup != m_ISFCalculation))	delete m_ISFCalculation_Greenup;

	m_AccelCustom = nullptr;
	m_FMCCustom = nullptr;
	m_SFCCustom = nullptr;
	m_TFCCustom = nullptr;
	m_CFBCustom = nullptr;
	m_RSICustom = nullptr;
	m_ISFCustom = nullptr;
	m_LBCustom = nullptr;

	delete m_fwi;
}


template <class T>
bool compare_c(T &a, T &b) {
	if ((a) && (b)) {
		if (a != b)
			if (a->Equals(b) != S_OK)
				return false;
	}
	if (a != b)
		return false;
	return true;
}


template <class T>
bool compare_c1(T &a, T &b) {
	if ((a) && (b)) {
		if (a != b)
			if (a->Equals(b, false) != S_OK)
				return false;
	}
	if (a != b)
		return false;
	return true;
}

/*
	This is a method to check if the FBPFuel object is equal to a FBPFuel object and takes the following parameters:
		An attribute object of type FBPFuel
*/
bool FBPFuel::Equals(const FBPFuel &fuel) const {
	if (memcmp(&m_defaultFuelType, &fuel.m_defaultFuelType, sizeof(_GUID)))		return false;
	if (m_fuelTypeModified != fuel.m_fuelTypeModified)							return false;

	if (!compare_c(m_spread, fuel.m_spread))									return false;
	if (!compare_c(m_FMCCalculation, fuel.m_FMCCalculation))					return false;
	if (!compare_c(m_SFCCalculation_Greenup, fuel.m_SFCCalculation_Greenup))	return false;
	if (!compare_c(m_SFCCalculation, fuel.m_SFCCalculation))					return false;
	if (!compare_c(m_TFCCalculation_Greenup, fuel.m_TFCCalculation_Greenup))	return false;
	if (!compare_c(m_TFCCalculation, fuel.m_TFCCalculation))					return false;
	if (!compare_c(m_RSICalculation_Greenup, fuel.m_RSICalculation_Greenup))	return false;
	if (!compare_c(m_RSICalculation, fuel.m_RSICalculation))					return false;
	if (!compare_c(m_ISFCalculation_Greenup, fuel.m_ISFCalculation_Greenup))	return false;
	if (!compare_c(m_ISFCalculation, fuel.m_ISFCalculation))					return false;
	if (!compare_c(m_AccAlphaCalculation, fuel.m_AccAlphaCalculation))			return false;
	if (!compare_c(m_LBCalculation, fuel.m_LBCalculation))						return false;
	if (!compare_c(m_CFBCalculation_Greenup, fuel.m_CFBCalculation_Greenup))	return false;
	if (!compare_c(m_CFBCalculation, fuel.m_CFBCalculation))					return false;
	if (!compare_c(m_FLCalculation, fuel.m_FLCalculation))						return false;
	return true;
}


std::int32_t FBPFuel::serialVersionUid(const SerializeProtoOptions& options) const noexcept {
	return 1;
}


WISE::FuelProto::FbpFuel* FBPFuel::serialize(const SerializeProtoOptions& options) {
	return serialize(options, nullptr);
}


WISE::FuelProto::FbpFuel* FBPFuel::serialize(const SerializeProtoOptions& options, ISerializationData* userData) {
	FBPFuel* defaultFuel = nullptr;
	WISE::FuelProto::FuelName defaultFuelName = WISE::FuelProto::unset;
	if (userData) {
		SerializeFuelData* data = dynamic_cast<SerializeFuelData*>(userData);
		if (data) {
			defaultFuel = data->defaultFuel;
			defaultFuelName = (WISE::FuelProto::FuelName)data->defaultFuelType;
		}
	}
	bool verbose = options.useVerboseOutput() || defaultFuel == nullptr;

	WISE::FuelProto::FbpFuel *msg = new WISE::FuelProto::FbpFuel();
	msg->set_version(serialVersionUid(options));

	msg->set_defaultfueltype(defaultFuelName);

	if (m_spread != nullptr && (verbose || !m_spread->Equals(defaultFuel->m_spread)))
		msg->set_allocated_spread(m_spread->serialize(options));

	if (m_FMCCalculation != nullptr && (verbose || !m_FMCCalculation->Equals(defaultFuel->m_FMCCalculation)))
		msg->set_allocated_fmccalculation(m_FMCCalculation->serialize(options));

	if (m_SFCCalculation != nullptr && (verbose || !m_SFCCalculation->Equals(defaultFuel->m_SFCCalculation)))
		msg->set_allocated_sfccalculation(m_SFCCalculation->serialize(options));
	if (m_SFCCalculation_Greenup != nullptr && (verbose || !m_SFCCalculation_Greenup->Equals(defaultFuel->m_SFCCalculation_Greenup)))
		msg->set_allocated_sfccalculationgreenup(m_SFCCalculation_Greenup->serialize(options));

	if (m_TFCCalculation != nullptr && (verbose || !m_TFCCalculation->Equals(defaultFuel->m_TFCCalculation)))
		msg->set_allocated_tfccalculation(m_TFCCalculation->serialize(options));
	if (m_TFCCalculation_Greenup != nullptr && (verbose || !m_TFCCalculation_Greenup->Equals(defaultFuel->m_TFCCalculation_Greenup)))
		msg->set_allocated_tfccalculationgreenup(m_TFCCalculation_Greenup->serialize(options));

	if(m_RSICalculation != nullptr && (verbose || !m_RSICalculation->Equals(defaultFuel->m_RSICalculation)))
		msg->set_allocated_rsicalculation(m_RSICalculation->serialize(options));
	if (m_RSICalculation_Greenup != nullptr && (verbose || !m_RSICalculation_Greenup->Equals(defaultFuel->m_RSICalculation_Greenup)))
		msg->set_allocated_rsicalculationgreenup(m_RSICalculation_Greenup->serialize(options));

	if (m_ISFCalculation != nullptr && (verbose || !m_ISFCalculation->Equals(defaultFuel->m_ISFCalculation)))
		msg->set_allocated_isfcalculation(m_ISFCalculation->serialize(options));
	if (m_ISFCalculation_Greenup != nullptr && (verbose || !m_ISFCalculation_Greenup->Equals(defaultFuel->m_ISFCalculation_Greenup)))
		msg->set_allocated_isfcalculationgreenup(m_ISFCalculation_Greenup->serialize(options));

	if (m_AccAlphaCalculation != nullptr && (verbose || !m_AccAlphaCalculation->Equals(defaultFuel->m_AccAlphaCalculation)))
		msg->set_allocated_accalphacalculation(m_AccAlphaCalculation->serialize(options));

	if (m_LBCalculation != nullptr && (verbose || !m_LBCalculation->Equals(defaultFuel->m_LBCalculation)))
		msg->set_allocated_lbcalculation(m_LBCalculation->serialize(options));

	if (m_CFBCalculation != nullptr && (verbose || !m_CFBCalculation->Equals(defaultFuel->m_CFBCalculation)))
		msg->set_allocated_cfbcalculation(m_CFBCalculation->serialize(options));
	if (m_CFBCalculation_Greenup != nullptr && (verbose || !m_CFBCalculation_Greenup->Equals(defaultFuel->m_CFBCalculation_Greenup)))
		msg->set_allocated_cfbcalculationgreenup(m_CFBCalculation_Greenup->serialize(options));

	if (m_FLCalculation != nullptr && (verbose || !m_FLCalculation->Equals(defaultFuel->m_FLCalculation)))
		msg->set_allocated_flcalculation(m_FLCalculation->serialize(options));

	return msg;
}


FBPFuel *FBPFuel::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::FbpFuel *msgRead = dynamic_cast_assert<const WISE::FuelProto::FbpFuel *>(&proto);
	
	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FbpFuel", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FBPFuel: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FbpFuel", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		m_loadWarning += "FBPFuel: Version is invalid";
		throw ISerializeProto::DeserializeError("FBPFuel: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	try {
		WISE::FuelProto::FuelName fuelName = msgRead->defaultfueltype();

		auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FbpFuel", name);
		auto v = vt.lock();

		if (msgRead->has_spread()) {
			SpreadParmsAttribute tmp_spread;
			ISerializationData_SP def;
			if (m_spread) {
				m_spread->C2(def.c2);
				m_spread->D1(def.d1);
			}
			def.original = m_spread;
			m_spread = tmp_spread.deserialize(msgRead->spread(), v, "spread", &def);
			if (def.original)
				delete def.original;
		}

		if (msgRead->has_fmccalculation()) {
			FMCAttribute tmp_fmc;
			ISerializationData_FMC def;
			def.original = m_FMCCalculation;
			m_FMCCalculation = tmp_fmc.deserialize(msgRead->fmccalculation(), v, "fmcCalculation", &def);
			if (def.original)
				delete def.original;
		}

		if (msgRead->has_sfccalculation()) {
			SFCAttribute tmp_sfc;
			ISerializationData_SFC def;
			def.original = m_SFCCalculation;
			m_SFCCalculation = tmp_sfc.deserialize(msgRead->sfccalculation(), v, "sfcCalculation", &def);
			if (def.original)
				delete def.original;
		}
		if (msgRead->has_sfccalculationgreenup()) {
			SFCAttribute tmp_sfc;
			ISerializationData_SFC def;
			def.original = m_SFCCalculation_Greenup;
			m_SFCCalculation_Greenup = tmp_sfc.deserialize(msgRead->sfccalculationgreenup(), v, "sfcCalculationGreenup", &def);
			if (def.original)
				delete def.original;
			if (m_SFCCalculation_Greenup) {
				if (m_SFCCalculation_Greenup->Equals(m_SFCCalculation)) {
					delete m_SFCCalculation_Greenup;
					m_SFCCalculation_Greenup = m_SFCCalculation;
				}
			}
		}

		if (msgRead->has_tfccalculation()) {
			TFCAttribute tmp_tfc;
			ISerializationData_TFC def;
			def.original = m_TFCCalculation;
			m_TFCCalculation = tmp_tfc.deserialize(msgRead->tfccalculation(), v, "tfcCalculation", &def);
			if (def.original)
				delete def.original;
		}
		if (msgRead->has_tfccalculationgreenup()) {
			TFCAttribute tmp_tfc;
			ISerializationData_TFC def;
			def.original = m_TFCCalculation_Greenup;
			m_TFCCalculation_Greenup = tmp_tfc.deserialize(msgRead->tfccalculationgreenup(), v, "tfcCalculationGreenup", &def);
			if (def.original)
				delete def.original;
			if (m_TFCCalculation_Greenup) {
				if (m_TFCCalculation_Greenup->Equals(m_TFCCalculation)) {
					delete m_TFCCalculation_Greenup;
					m_TFCCalculation_Greenup = m_TFCCalculation;
				}
			}
		}

		if (msgRead->has_rsicalculation()) {
			RSIAttribute tmp_rsi;
			ISerializationData_RSI def;
			def.original = m_RSICalculation;
			m_RSICalculation = tmp_rsi.deserialize(msgRead->rsicalculation(), v, "rsiCalculation", &def);
			if (def.original)
				delete def.original;
		}
		if (msgRead->has_rsicalculationgreenup()) {
			RSIAttribute tmp_rsi;
			ISerializationData_RSI def;
			def.original = m_RSICalculation_Greenup;
			m_RSICalculation_Greenup = tmp_rsi.deserialize(msgRead->rsicalculationgreenup(), v, "rsiCalculationGreenup", &def);
			if (def.original)
				delete def.original;
			if (m_RSICalculation_Greenup) {
				if (m_RSICalculation_Greenup->Equals(m_RSICalculation)) {
					delete m_RSICalculation_Greenup;
					m_RSICalculation_Greenup = m_RSICalculation;
				}
			}
		}

		if (msgRead->has_isfcalculation()) {
			ISFAttribute tmp_isf;
			ISerializationData_ISF def;
			def.original = m_ISFCalculation;
			m_ISFCalculation = tmp_isf.deserialize(msgRead->isfcalculation(), v, "isfCalculation", &def);
			if (def.original)
				delete def.original;
		}
		if (msgRead->has_isfcalculationgreenup()) {
			ISFAttribute tmp_isf;
			ISerializationData_ISF def;
			def.original = m_ISFCalculation_Greenup;
			m_ISFCalculation_Greenup = tmp_isf.deserialize(msgRead->isfcalculationgreenup(), v, "isfCalculationGreenup", &def);
			if (def.original)
				delete def.original;
			if (m_ISFCalculation_Greenup) {
				if (m_ISFCalculation_Greenup->Equals(m_ISFCalculation)) {
					delete m_ISFCalculation_Greenup;
					m_ISFCalculation_Greenup = m_ISFCalculation;
				}
			}
		}

		if (msgRead->has_accalphacalculation()) {
			AccAlphaAttribute tmp_accalpha;
			ISerializationData_ACC def;
			def.original = m_AccAlphaCalculation;
			m_AccAlphaCalculation = tmp_accalpha.deserialize(msgRead->accalphacalculation(), v, "accAlphaCalculation", &def);
			if (def.original)
				delete def.original;
		}

		if (msgRead->has_lbcalculation()) {
			LBAttribute tmp_lb;
			ISerializationData_LB def;
			def.original = m_LBCalculation;
			m_LBCalculation = tmp_lb.deserialize(msgRead->lbcalculation(), v, "lbCalculation", &def);
			if (def.original)
				delete def.original;
		}

		if (msgRead->has_cfbcalculation()) {
			CFBAttribute tmp_cfb;
			ISerializationData_CFB def;
			def.original = m_CFBCalculation;
			m_CFBCalculation = tmp_cfb.deserialize(msgRead->cfbcalculation(), v, "cfbCalculation", &def);
			if (def.original)
				delete def.original;
		}
		if (msgRead->has_cfbcalculationgreenup()) {
			CFBAttribute tmp_cfb;
			ISerializationData_CFB def;
			def.original = m_CFBCalculation_Greenup;
			m_CFBCalculation_Greenup = tmp_cfb.deserialize(msgRead->cfbcalculationgreenup(), v, "cfbCalculationGreenup", &def);
			if (def.original)
				delete def.original;
			if (m_CFBCalculation_Greenup) {
				if (m_CFBCalculation_Greenup->Equals(m_CFBCalculation)) {
					delete m_CFBCalculation_Greenup;
					m_CFBCalculation_Greenup = m_CFBCalculation;
				}
			}
		}
		if (msgRead->has_flcalculation()) {
			FlameLengthAttribute tmp_fl;
			ISerializationData_FL def;
			def.original = m_FLCalculation;
			m_FLCalculation = tmp_fl.deserialize(msgRead->flcalculation(), v, "flCalculation", &def);
			if (def.original)
				delete def.original;
		}
	}
	catch (std::invalid_argument &ia) {
		m_loadWarning += ia.what();
		throw ia;
	}
	return this;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::SFC(double FFMC, double BUI, std::int16_t flag, const CCWFGM_FuelOverrides* overrides) {
	if ((!IsMixed()) && (!IsMixedDead()))
		if ((m_spread->A(flag) == 0.0) && (m_spread->B(flag) == 0.0) && (m_spread->C(flag) == 0.0))
			return 0.0;

	if (m_SFCCustom) {
		boost::intrusive_ptr<ICWFGM_Fuel> m_C2, m_D1;
		m_spread->C2(m_C2);
		m_spread->D1(m_D1);
		double m_pc = m_spread->PC(overrides);
		double SFC;
		m_SFCCustom->SFC((flag & USE_GREENUP) ? true : false, FFMC, BUI, m_C2, m_D1, m_pc, &SFC);
		return SFC;
	} else {
		if (!(flag & USE_GREENUP))
			return m_SFCCalculation->SFC(m_spread, flag, overrides, FFMC, BUI);
		else
			return m_SFCCalculation_Greenup->SFC(m_spread, flag, overrides, FFMC, BUI);
	}
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::TFC(double CFB, double SFC, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *CFC) {
	if (m_TFCCustom) {
		double m_pc = m_spread->PC(overrides);
		double m_cfl = m_spread->CFL(overrides);
		double TFC;
		m_TFCCustom->TFC((flag & USE_GREENUP) ? true : false, m_cfl, CFB, SFC, m_pc, CFC, &TFC);
		return TFC;
	} else {
		if (!(flag & USE_GREENUP))
			return m_TFCCalculation->TFC(m_spread, flag, overrides, CFB, SFC, CFC);
		else	
			return m_TFCCalculation_Greenup->TFC(m_spread, flag, overrides, CFB, SFC, CFC);
	}
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::ISF(double RSF_C2, double RSF_D1, double SF, double ISZ, std::int16_t flag, const CCWFGM_FuelOverrides* overrides) {

	double isf;
	if (m_ISFCustom) {
		boost::intrusive_ptr<ICWFGM_Fuel> m_C2, m_D1;
		m_spread->C2(m_C2);
		m_spread->D1(m_D1);
		double m_pc = m_spread->PC(overrides);
		double m_curingDegree = m_spread->CuringDegree(overrides);
		m_ISFCustom->ISF((flag & USE_GREENUP) ? true : false, m_spread->A(flag), m_spread->B(flag), m_spread->C(flag), RSF_C2, RSF_D1, SF, ISZ, m_C2, m_D1, m_curingDegree, m_pc, &isf);
	} else {
		if (!(flag & USE_GREENUP))
			isf = m_ISFCalculation->ISF(m_spread, flag, overrides, RSF_C2, RSF_D1, SF, ISZ);
		else
			isf = m_ISFCalculation_Greenup->ISF(m_spread, flag, overrides, RSF_C2, RSF_D1, SF, ISZ);
	}
	return isf;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::CFB(double FMC, double SFC, double RSS, double ROS, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *rso, double *csi) {
	double for_fros;
	if (m_RSICustom) {
		if (FAILED(m_RSICustom->For_FROS((flag & USE_GREENUP) ? true : false, RSS, ROS, 0.0, &for_fros)))
			return 0.0;
	}
	else {
		if (!(flag & USE_GREENUP))
			for_fros = m_RSICalculation->FOR_FROS(RSS, ROS, 0.0);
		else
			for_fros = m_RSICalculation_Greenup->FOR_FROS(RSS, ROS, 0.0);
	}

	if (m_CFBCustom) {
		double cfb;
		m_CFBCustom->CFB((flag & USE_GREENUP) ? true : false, m_spread->CBH(overrides), FMC, SFC, for_fros, rso, csi, &cfb);
		return cfb;
	}
	else {
		if (!(flag & USE_GREENUP))
			return m_CFBCalculation->CFB(m_spread->CBH(overrides), FMC, SFC, for_fros, rso, csi);
		else	
			return m_CFBCalculation_Greenup->CFB(m_spread->CBH(overrides), FMC, SFC, for_fros, rso, csi);
	}
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::FMC(double lat, double lon, double elev, std::uint16_t day, const CCWFGM_FuelOverrides* overrides) {
	double FMC;
	if (m_FMCCustom)
		m_FMCCustom->FMC(lat, lon, elev, day, overrides, &FMC);
	else
		FMC = m_FMCCalculation->FMC(lat, lon, elev, day, overrides);
	return FMC;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::RSI(double FFMC, double BUI, double FMC, double ISI, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *RSI_C2, double *RSI_D1) {
	double rsi;
	if (m_RSICustom) {
		boost::intrusive_ptr<ICWFGM_Fuel> m_C2, m_D1;
		m_spread->C2(m_C2);
		m_spread->D1(m_D1);
		double m_pc = m_spread->PC(overrides);

		m_RSICustom->RSI((flag & USE_GREENUP) ? true : false, m_spread->A(flag), m_spread->B(flag), m_spread->C(flag), ISI, FMC, BUI, FFMC, BE(BUI), m_spread->CuringDegree(overrides), m_C2, m_D1, m_pc, flag, overrides, RSI_C2, RSI_D1, &rsi);
	}
	else {
		if (!(flag & USE_GREENUP))
			rsi = m_RSICalculation->RSI(m_spread, flag, overrides, ISI, FMC, BUI, FFMC, BE(BUI), RSI_C2, RSI_D1);
		else	rsi = m_RSICalculation_Greenup->RSI(m_spread, flag, overrides, ISI, FMC, BUI, FFMC, BE(BUI), RSI_C2, RSI_D1);
	}
	return rsi;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::WSV(double GS, double SAZ, double WS, double WAZ, /*double ISI, double DeadWindISI,*/ double BUI, double FMC, double FFMC, double fF, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, const WTimeSpan &ffmc_t, double *raz) {
	double sf;						// slope factor, upslope
	if (!(flag & USE_SLOPE))
		GS = 0.0;					// - if slope is ignored, we will use zero.
								// this will force only the wind speed to be a factor in the ISI calculation
	if (GS >= 0.7)						// - else, ensure we aren't over the maximum. 
		GS = 0.7;					// equation 39b, FBP note - not really needed if we limited GS to a max of 0.6 but changed to this for

	sf = exp(3.533 * pow(GS, 1.2));				// equation 39a, FBP note

	if (!(flag & USE_WIND))
		WS = 0.0;					// - if wind is ignored, we will use zero. this will force only the slope
								// to be a factor in the ISI calculation

	double rsf_c2, rsf_d1;

	double DeadWindISI;

	m_fwi->ISI_FBP(FFMC, 0, (std::uint32_t)ffmc_t.GetTotalSeconds(), &DeadWindISI);
	RSI(FFMC, BUI, FMC, DeadWindISI, (flag & ~USE_BUI) | CALC_FOR_RSF, overrides, &rsf_c2, &rsf_d1);
	rsf_c2 *= sf;
	rsf_d1 *= sf;

	double isf = ISF(rsf_c2, rsf_d1, sf, DeadWindISI, flag, overrides);				// ISI, with zero wind upslope
								// either equation 41, 42 or 43, based on fuel type.

	double wse;						// slope equivalent of windspeed.

	if (!(flag & USE_SLOPE))
		wse = 0.0;					// RWB, Mac, June 20, 2000: if we aren't using slope, then just force wse
	else if (isf > 0.0) {					// to have to wind vector representing slope to be 0, otherwise actually
								// calculate it - we do this to 1.) help performance and 2.) ensure this
								// is correct regardless of whether slope was factored into the calculation
								// of FFMC, ISI, and later fF (done in FWICom)
		wse = log(isf / (0.208 * fF)) / 0.05039;	// equation 44
		if (wse > 40.0) {				// RWB: addition of equation 44b 050812
			double isiMAX = 2.496 * fF * 0.999;
			if (isf > isiMAX)
				isf = isiMAX;
				wse = 28.0 - log(1.0 - (isf / (2.496 * fF))) / 0.0818;
		}
	}
	else
		wse = 0.0;					// RWB: fix for ISF = 0.0 (can happen for mixed species when PC <= 0.0)

	double wsv;
	if (fabs(WS) <= 0.00000001 && fabs(wse) <= 0.0000001) {
		wsv = 0.0;
		*raz = COMPASS_TO_CARTESIAN_RADIAN(0.0);
	}
	else {
		double sin_waz, cos_waz, sin_saz, cos_saz;
		::sincos(WAZ, &sin_waz, &cos_waz);
		::sincos(SAZ, &sin_saz, &cos_saz);
		double wsx = WS * sin_waz + wse * sin_saz;	// wind in x-dir, equation 47, Dennis changed + into -
		double wsy = WS * cos_waz + wse * cos_saz;	// wind in y-dir, equation 48

		wsv = sqrt(wsx * wsx + wsy * wsy);		// net vectored wind speed, equation 49

		*raz = acos( wsy / wsv);			// spread direction azimuth, equation 50

		if (wsx < 0.0 )
			*raz = TwoPi<double>() - *raz;			// equation 51, Dennis Changed - into +, it works.
		*raz = COMPASS_TO_CARTESIAN_RADIAN(*raz);		// equations work in compass, we work in cartesian
	}
	return wsv;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::LB(double WSV, double RSS, double ROS_EQ, double BUI, double FMC, double FFMC, const WTimeSpan &t, std::int16_t flag, const CCWFGM_FuelOverrides* overrides) {
	double lb;
	if (m_LBCustom)
		m_LBCustom->LB(WSV, &lb);
	else 
		lb = m_LBCalculation->LB(WSV);

	if (flag & USE_ACCELERATION) {
		double rso, csi, sfc = SFC(FFMC, BUI, flag, overrides);
		double cfb = CFB(FMC, sfc, RSS, ROS_EQ, flag, overrides, &rso, &csi);
		double m_AccAlpha = ACC(cfb);
		lb = (lb - 1.0) * (1.0 - exp(m_AccAlpha * (double)t.GetTotalSeconds() / -60.0)) + 1.0;	// equation 81, August 2004 note
	}
	return lb;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::FROS(double ROS, double BROS, double LB) {
	double fros;
	if (LB > 0.0) {
		fros = (ROS + BROS) / (LB * 2.0);			// equation 89

		if (fros < 0.0)
			fros = 0.0;
	} else
		fros = 0.0;
	return fros;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::BROS(double WSV, double RSS, double ROS_EQ, double BUI, double FMC, double FFMC, double fF,
		const WTimeSpan &t, std::int16_t flag, const CCWFGM_FuelOverrides* overrides,
		ICWFGM_PercentileAttribute *RSIadjust, double *bros_eq, double *brss) {

	double b_fW = exp(-0.05039 * WSV);		// equation 75
	double bisi = b_fW * fF * 0.208;		// equation 76
	double bros_c2, bros_d1;
	*brss = RSI(FFMC, BUI, FMC, bisi, flag, overrides, &bros_c2, &bros_d1);

	if (RSIadjust) {
		double rsi1, rso, csi, cfb = CFB(FFMC, SFC(FFMC, BUI, flag, overrides), *brss, *brss, flag, overrides, &rso, &csi);
		HRESULT hr = RSIadjust->RSI(&this->m_defaultFuelType, *brss, cfb, &rsi1);
		if (SUCCEEDED(hr))
			*brss = rsi1;
	}

	if (m_RSICustom) {
		m_RSICustom->ROS((flag & USE_GREENUP) ? true : false, *brss, m_spread->CBH(overrides), bisi, FMC, SFC(FFMC, BUI, flag, overrides), bros_eq);
	}
	else {
		if (!(flag & USE_GREENUP))
			*bros_eq = m_RSICalculation->ROS(*brss, m_spread->CBH(overrides), bisi, FMC, SFC(FFMC, BUI, flag, overrides), m_CFBCalculation);
		else	*bros_eq = m_RSICalculation_Greenup->ROS(*brss, m_spread->CBH(overrides), bisi, FMC, SFC(FFMC, BUI, flag, overrides), m_CFBCalculation_Greenup);
	}

	double bros = *bros_eq;
	if (flag & USE_ACCELERATION) {
		double rso, csi, sfc = SFC(FFMC, BUI, flag, overrides);
		double cfb = CFB(FMC, sfc, RSS, ROS_EQ, flag, overrides, &rso, &csi);
		double m_AccAlpha = ACC(cfb);
		bros *= 1.0 - exp(m_AccAlpha * ((double)t.GetTotalSeconds() / -60.0));
	}
	return bros;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::ROS(double WSV, double BUI, double FMC, double FFMC, const WTimeSpan &t,
    const WTimeSpan &ffmc_t, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, ICWFGM_PercentileAttribute *RSIadjust, double *ros_eq, double *rss) {
	double isi;

	m_fwi->ISI_FBP(FFMC, WSV, (std::uint32_t)ffmc_t.GetTotalSeconds(), &isi);

	// rate of spread, using wind and slope input.
	double ros_c2, ros_d1;
	*rss = RSI(FFMC, BUI, FMC, isi, flag, overrides, &ros_c2, &ros_d1);	

	if (RSIadjust) {
		double rsi1, rso, csi, cfb = CFB(FFMC, SFC(FFMC, BUI, flag, overrides), *rss, *rss, flag, overrides, &rso, &csi);
		HRESULT hr = RSIadjust->RSI(&this->m_defaultFuelType, *rss, cfb, &rsi1);
		if (SUCCEEDED(hr))
			*rss = rsi1;
	}

	if (*rss < 0)
		*rss = 0;
								// at this point, we should have the final rate of spread for everything
								// except c6, where the variable ros now actually contains RSS, which is
								// 'surface fire spread rate (c6)'.

	double ros;
	if (m_RSICustom) {
		m_RSICustom->ROS((flag & USE_GREENUP) ? true : false, *rss, m_spread->CBH(overrides), isi, FMC, SFC(FFMC, BUI, flag, overrides), &ros);
	}
	else {
		if (!(flag & USE_GREENUP))
			ros = m_RSICalculation->ROS(*rss, m_spread->CBH(overrides), isi, FMC, SFC(FFMC, BUI, flag, overrides), m_CFBCalculation);
		else	ros = m_RSICalculation_Greenup->ROS(*rss, m_spread->CBH(overrides), isi, FMC, SFC(FFMC, BUI, flag, overrides), m_CFBCalculation_Greenup);
	}
	*ros_eq = ros;

	if (flag & USE_ACCELERATION) {
		double rso, csi, sfc = SFC(FFMC, BUI, flag, overrides);
		double cfb = CFB(FMC, sfc, *rss, *ros_eq, flag, overrides, &rso, &csi);
		double m_AccAlpha = ACC(cfb);
		ros *= 1.0 - exp( m_AccAlpha * ((double)t.GetTotalSeconds() / -60.0));
	}

	return ros;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::ACC(double cfb) {
	double m_AccAlpha;
	if (m_AccelCustom)
		m_AccelCustom->Acceleration(cfb, &m_AccAlpha);
	else
		m_AccAlpha = m_AccAlphaCalculation->AccAlpha(cfb);
	return m_AccAlpha;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides) {
	double fl;
	weak_assert(m_FLCalculation);
	fl = m_FLCalculation->FlameLength(height, CFB, fi, overrides);
	return fl;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::BE(double BUI) {
	double be = exp(50.0 * log(m_spread->Q()) * (1.0 / BUI - 1.0 / m_spread->BUI0()));
								// equation 54
	if (be > m_spread->MaxBE())	
		be = m_spread->MaxBE();					// from p34 devel &struct of CFBP system

	return be;
}

/*
	See FBPFuel.h for this definition
*/
double FBPFuel::FI(double TFC, double ROS, std::int16_t /*flag*/) {
								// equation 69, can be fros or bros too.
	return 300.0 * TFC * ROS;
}

/*
	See FBPFuel.h for this definition
*/
void FBPFuel::CalculateFCValues(double FFMC, double BUI, double FMC, double RSS, double ROS, short flag,
		const CCWFGM_FuelOverrides* overrides, double* cfb, double* cfc, double *rso, double *csi, double* sfc, double* tfc, double *fi) {
	*sfc = SFC(FFMC, BUI, flag, overrides);
	*cfb = CFB(FMC, *sfc, RSS, ROS, flag, overrides, rso, csi);
	*tfc = TFC(*cfb, *sfc, flag, overrides, cfc);
	double for_fros;
	if (m_RSICustom)
		m_RSICustom->For_FROS((flag & USE_GREENUP) ? true : false, RSS, ROS, *cfb, &for_fros);
	else 
		for_fros = m_RSICalculation->FOR_FROS(RSS, ROS, *cfb);
	*fi = FI(*tfc, for_fros, flag);
}


#define sq(A) ((A) * (A))
/*
	See FBPFuel.h for this definition
*/
void FBPFuel::CalculateDistances(double ROS, double FROS, double BROS, double _CFB,
		const WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
		double *dhead, double *dflank, double *dback) {
	double alpha = ACC(_CFB);

	*dhead = *dflank = *dback = 0.0;

	// if (FROS == 0), there really is no ellipse, thus we can safely return 0
	if (FROS == 0.0)
		return;

	double t = (double)time.GetTotalSeconds() / 60.0;
	double LB_t;

	double LB = (ROS + BROS) / (2.0 * FROS);

	if (flag & USE_ACCELERATION) { // use eqn 71
		if (alpha > 0.0) {
			LB_t = (LB - 1) * (1 - exp(-alpha*t)) + 1;
		}
		else {
			LB_t = 0.0;
		}
	}
	else {
		// from eqn 89
		LB_t = LB;
	}

	if (LB_t > 0.0) {
		if (flag & USE_ACCELERATION) {
		// eqn 71
			if (alpha > 0.0) {
				*dhead	= ROS*(t + (exp(-alpha * t) - 1.0)  / alpha);
				*dback	= BROS*(t + (exp(-alpha * t) - 1.0) / alpha);
			}
		}
		else {
		// eqn 89
			*dhead	= ROS * t;
			*dback	= BROS * t;
		}
		if (LB_t > 0.0)
			*dflank = (*dhead + *dback) / (2.0 * LB_t);
	}
}

void FBPFuel::CalculateROSTheta(double ROS, double FROS, double BROS, double RAZ, double Theta, double* rosTheta) {
	// implements equation 94 out of the FBP update article
	double theta = fabs(Theta - RAZ);
	if (theta == 0.0) {
		*rosTheta = FROS;
		return;
	}
	if (theta == CONSTANTS_NAMESPACE::Pi<double>()) {
		*rosTheta = BROS;
		return;
	}
	if (theta == CONSTANTS_NAMESPACE::HalfPi<double>())
		theta -= CONSTANTS_NAMESPACE::dPi<double>();
	double cost = cos(theta);
	double sint = sin(theta);
	double twocost = 2.0 * cost;
	double cost2 = cost * cost;
	double sint2 = sint * sint;
	double sum_ros = ROS + BROS;
	double ROSt = (ROS - BROS) / twocost + sum_ros / twocost * (
		(FROS * cost * sqrt(FROS * FROS * cost2 + (ROS * BROS) * sint2) - (sq(ROS) - sq(BROS)) / 4.0 * sint2)
		/
		(sq(FROS) * cost2 + sq(sum_ros) * 0.25 * sint2)
		);
	*rosTheta = ROSt;
}

/*
	See FBPFuel.h for this definition
*/
void FBPFuel::CalculateStatistics(double ROS, double FROS, double BROS, double _CFB,
		const WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
		double *area, double *perimeter) {
	double alpha = ACC(_CFB);

	*area = 0.0;
	*perimeter = 0.0;

	if (FROS == 0.0)
		return;

	double t = (double)time.GetTotalSeconds() / 60.0;
	double Dt, LB_t;

	double LB = (ROS + BROS) / (2.0 * FROS);

	if (flag & USE_ACCELERATION) { // use eqn 71
		if (alpha > 0.0) {
			Dt = (ROS + BROS) * (t + (exp(-alpha * t) - 1.0) / alpha);
			LB_t = (LB - 1) * (1 - exp(-alpha*t)) + 1;
		}
		else {
			Dt = 0.0;
			LB_t = 0.0;
		}
	} else {
		// from eqn 89
		Dt = (ROS + BROS) * t;
		LB_t = LB;
	}

	if (LB_t > 0.0) {
	// eqn 87
		*perimeter = Pi<double>() * (Dt / 2.0) * (1.0 + (1.0 / LB_t)) * (1.0 + sq((LB_t - 1.0) / (2.0 * (LB_t + 1.0))));

	// eqn 86
		*area = (Pi<double>() / (4.0 * LB_t) * sq(Dt)) / 10000;
	}
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::CalculateValues( double GS, double SAZ, double WS, double WAZ, double BUI, double FMC, double FFMC, double fF,
    const WTimeSpan &t, const WTimeSpan &ffmc_t, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, ICWFGM_PercentileAttribute *RSIadjust,
		double *rss, double *ros_eq, double *ros, double *frss, double *fros_eq, double *fros, double *brss, double *bros_eq, double *bros, double *lb,
		double *wsv, double *raz) {

#ifdef DEBUG
	weak_assert(m_SFCCalculation);
	weak_assert(m_TFCCalculation);
	weak_assert(m_RSICalculation);
	weak_assert(m_ISFCalculation);
	weak_assert(m_AccAlphaCalculation);
	weak_assert(m_LBCalculation);
	weak_assert(m_CFBCalculation);
	weak_assert(m_SFCCalculation_Greenup);
	weak_assert(m_TFCCalculation_Greenup);
	weak_assert(m_RSICalculation_Greenup);
	weak_assert(m_CFBCalculation_Greenup);
	weak_assert(m_ISFCalculation_Greenup);
#endif

	if (GS < 0.0) {
		flag &= (~(USE_SLOPE));
		GS = 0.0;
		SAZ = 0.0;
	}
	else
		SAZ = COMPASS_TO_CARTESIAN_RADIAN(SAZ);		// we expect them in radians, cartesian, but all the math from FBP
	WAZ = COMPASS_TO_CARTESIAN_RADIAN(WAZ);			// wants them in radians, compass
	*wsv = WSV(GS, SAZ, WS, WAZ, BUI, FMC, FFMC, fF, flag, overrides, ffmc_t, raz);
	*ros = ROS(*wsv, BUI, FMC, FFMC, t, ffmc_t, flag, overrides, RSIadjust, ros_eq, rss);

	*bros = BROS(*wsv, *rss, *ros_eq, BUI, FMC, FFMC, fF, t, flag, overrides, RSIadjust, bros_eq, brss);

	double _lb;
	if (!lb)
		lb = &_lb;
	_lb = LB(*wsv, *rss, *ros_eq, BUI, FMC, FFMC, t, flag & (~(USE_ACCELERATION)), overrides);
	*frss = FROS(*rss, *brss, _lb);
	
	*fros_eq = FROS(*ros_eq, *bros_eq, _lb);
	
	*lb = LB(*wsv, *rss, *ros_eq, BUI, FMC, FFMC, t, flag, overrides);	// this is actually (conditionally) LBt

	*fros = FROS(*ros, *bros, *lb);

	return true;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsNonFuel() const {
	if (m_fuelTypeModified)
		return false;
	SpreadParms_Non *s = dynamic_cast<SpreadParms_Non *>(m_spread);
	if (s)
		return true;
	return false;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsConifer() const {
	if (m_fuelTypeModified)
		return false;
	SpreadParms_C1 *s = dynamic_cast<SpreadParms_C1 *>(m_spread);
	if (s)
		return true;
	return false;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsDeciduous() const {
	if (m_fuelTypeModified)
		return false;
	SpreadParms_D1 *s = dynamic_cast<SpreadParms_D1 *>(m_spread);
	if (s)
		return true;
	return false;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsMixed() const {
	if (m_fuelTypeModified)
		return false;
	SpreadParms_Mixed *s = dynamic_cast<SpreadParms_Mixed *>(m_spread);
	if (s)
		return true;
	return false;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsGrass() const {
	if (m_fuelTypeModified)
		return false;
	{
		SpreadParms_O1 *s = dynamic_cast<SpreadParms_O1 *>(m_spread);
		if (s)
			return true;
	}
	{
		SpreadParms_O1ab *ss = dynamic_cast<SpreadParms_O1ab *>(m_spread);
		if (ss)
			return true;
	}
	return false;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsMixedDead() const {
	if (m_fuelTypeModified)
		return false;
	SpreadParms_MixedDead *s = dynamic_cast<SpreadParms_MixedDead *>(m_spread);
	if (s)
		return true;
	return false;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsSlash() const {
	if (m_fuelTypeModified)
		return false;
	SpreadParms_S1 *s = dynamic_cast<SpreadParms_S1 *>(m_spread);
	if (s)
		return true;
	return false;
}

/*
	See FBPFuel.h for this definition
*/
bool FBPFuel::IsC6() const {
	if (m_fuelTypeModified)
		return false;
	SpreadParms_C6 *s = dynamic_cast<SpreadParms_C6 *>(m_spread);
	if (s)
		return true;
	return false;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a FBPFuel and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FBPFuel::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	HRESULT hr = E_UNEXPECTED;
	std::uint16_t key = attributeKey & (~(FUELCOM_ATTRIBUTE_GREENUP_MODIFIER));
	std::uint16_t greenup = attributeKey & FUELCOM_ATTRIBUTE_GREENUP_MODIFIER;

	switch (key) {
	case FUELCOM_FUEL_MODIFIED:
							*attribute = m_fuelTypeModified;
							return S_OK;

		case FUELCOM_ATTRIBUTE_M3M4_C2_A:
		case FUELCOM_ATTRIBUTE_M3M4_C2_B:
		case FUELCOM_ATTRIBUTE_M3M4_C2_C:
		case FUELCOM_ATTRIBUTE_M4_D1_A:
		case FUELCOM_ATTRIBUTE_M4_D1_B:
		case FUELCOM_ATTRIBUTE_M4_D1_C:
		case FUELCOM_ATTRIBUTE_EQ35_THRESHOLD:
		case FUELCOM_ATTRIBUTE_EQ35A_MULT1:
		case FUELCOM_ATTRIBUTE_EQ35A_MULT2:
		case FUELCOM_ATTRIBUTE_EQ35B_ADDER:
		case FUELCOM_ATTRIBUTE_EQ35B_MULT1:
						if (greenup) {
							HRESULT hr1 = E_UNEXPECTED, hr2 = E_UNEXPECTED;
							if (m_RSICalculation_Greenup)
								hr1 = m_RSICalculation_Greenup->GetAttributeValue(key, attribute);
							if (m_ISFCalculation_Greenup)
								hr2 = m_ISFCalculation_Greenup->GetAttributeValue(key, attribute);
							if (SUCCEEDED(hr1))
								hr = hr1;
							else
								hr = hr2;
							return hr;
						} else {
							HRESULT hr1 = E_UNEXPECTED, hr2 = E_UNEXPECTED;
							if (m_RSICalculation)
								hr1 = m_RSICalculation->GetAttributeValue(key, attribute);
							if (m_ISFCalculation)
								hr2 = m_ISFCalculation->GetAttributeValue(key, attribute);
							if (SUCCEEDED(hr1))
								hr = hr1;
							else
								hr = hr2;
							return hr;
						}
	}

	if ((key >= FUELCOM_ATTRIBUTE_SPREAD_START) && (key < FUELCOM_ATTRIBUTE_SPREAD_END)) {
		if ((IsGrass()) && (key == FUELCOM_ATTRIBUTE_FUELLOAD)) {
			if (greenup)
				hr = m_SFCCalculation_Greenup->GetAttributeValue(key, attribute);
			else
				hr = m_SFCCalculation->GetAttributeValue(key, attribute);
		}
		else
			hr = m_spread->GetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_SFC_START) && (key < FUELCOM_ATTRIBUTE_SFC_END)) {
		if (greenup)
			hr = m_SFCCalculation_Greenup->GetAttributeValue(key, attribute);
		else
			hr = m_SFCCalculation->GetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_RSI_START) && (key < FUELCOM_ATTRIBUTE_RSI_END)) {
		if (greenup)
			hr = m_RSICalculation_Greenup->GetAttributeValue(key, attribute);
		else
			hr = m_RSICalculation->GetAttributeValue(key, attribute);
	}
		
	else if ((key >= FUELCOM_ATTRIBUTE_LB_START) && (key < FUELCOM_ATTRIBUTE_LB_END)) {
		hr = m_LBCalculation->GetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_ISF_START) && (key < FUELCOM_ATTRIBUTE_ISF_END)) {
		if (greenup)
			hr = m_ISFCalculation_Greenup->GetAttributeValue(key, attribute);
		else
			hr = m_ISFCalculation->GetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_CFB_START) && (key < FUELCOM_ATTRIBUTE_CFB_END)) {
		if (greenup)
			hr = m_CFBCalculation_Greenup->GetAttributeValue(key, attribute);
		else
			hr = m_CFBCalculation->GetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_ACCEL_START) && (key < FUELCOM_ATTRIBUTE_ACCEL_END)) {
		hr = m_AccAlphaCalculation->GetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_FMC_START) && (key < FUELCOM_ATTRIBUTE_FMC_END)) {
		hr = m_FMCCalculation->GetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_FLAMELENGTH_START) && (key < FUELCOM_ATTRIBUTE_FLAMELENGTH_END)) {
		hr = m_FLCalculation->GetAttributeValue(key, attribute);
	}

	return hr;
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a FBPFuel and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FBPFuel::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	HRESULT hr = E_INVALIDARG;
	std::uint16_t key = attributeKey & (~(FUELCOM_ATTRIBUTE_GREENUP_MODIFIER));
	std::uint16_t greenup = attributeKey & FUELCOM_ATTRIBUTE_GREENUP_MODIFIER;

	switch (key) {
	case FUELCOM_FUEL_MODIFIED:
						m_fuelTypeModified = (attribute) ? true : false;
						return S_OK;

	case FUELCOM_ATTRIBUTE_M3M4_C2_A:
		case FUELCOM_ATTRIBUTE_M3M4_C2_B:
		case FUELCOM_ATTRIBUTE_M3M4_C2_C:
		case FUELCOM_ATTRIBUTE_M4_D1_A:
		case FUELCOM_ATTRIBUTE_M4_D1_B:
		case FUELCOM_ATTRIBUTE_M4_D1_C:
		case FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_EQ35_THRESHOLD:
		case FUELCOM_ATTRIBUTE_EQ35A_MULT1:
		case FUELCOM_ATTRIBUTE_EQ35A_MULT2:
		case FUELCOM_ATTRIBUTE_EQ35B_ADDER:
		case FUELCOM_ATTRIBUTE_EQ35B_MULT1:
						if (greenup) {
							HRESULT hr1 = E_UNEXPECTED, hr2 = E_UNEXPECTED;
							if (m_RSICalculation_Greenup)
								hr1 = m_RSICalculation_Greenup->SetAttributeValue(key, attribute);
							if (m_ISFCalculation_Greenup)
								hr2 = m_ISFCalculation_Greenup->SetAttributeValue(key, attribute);
							if (SUCCEEDED(hr1))
								hr = hr1;
							else
								hr = hr2;
							return hr;
						} else {
							HRESULT hr1 = E_UNEXPECTED, hr2 = E_UNEXPECTED;
							if (m_RSICalculation)
								hr1 = m_RSICalculation->SetAttributeValue(key, attribute);
							if (m_ISFCalculation)
								hr2 = m_ISFCalculation->SetAttributeValue(key, attribute);
							if (SUCCEEDED(hr1))
								hr = hr1;
							else
								hr = hr2;
							return hr;
						}
	}

	if ((key >= FUELCOM_ATTRIBUTE_SPREAD_START) && (key < FUELCOM_ATTRIBUTE_SPREAD_END)) {
		if ((IsGrass()) && (key == FUELCOM_ATTRIBUTE_FUELLOAD)) {
			if (greenup)
				hr = m_SFCCalculation_Greenup->SetAttributeValue(key, attribute);
			else
				hr = m_SFCCalculation->SetAttributeValue(key, attribute);
		}
		else
			hr = m_spread->SetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_SFC_START) && (key < FUELCOM_ATTRIBUTE_SFC_END)) {
		if (greenup)
			hr = m_SFCCalculation_Greenup->SetAttributeValue(key, attribute);
		else
			hr = m_SFCCalculation->SetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_RSI_START) && (key < FUELCOM_ATTRIBUTE_RSI_END)) {
		if (greenup)
			hr = m_RSICalculation_Greenup->SetAttributeValue(key, attribute);
		else
			hr = m_RSICalculation->SetAttributeValue(key, attribute);
	}
		
	else if ((key >= FUELCOM_ATTRIBUTE_LB_START) && (key < FUELCOM_ATTRIBUTE_LB_END)) {
		hr = m_LBCalculation->SetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_ISF_START) && (key < FUELCOM_ATTRIBUTE_ISF_END)) {
		if (greenup)
			hr = m_ISFCalculation_Greenup->SetAttributeValue(key, attribute);
		else
			hr = m_ISFCalculation->SetAttributeValue(key, attribute);
	}
		
	else if ((key >= FUELCOM_ATTRIBUTE_CFB_START) && (key < FUELCOM_ATTRIBUTE_CFB_END)) {
		if (greenup)
			hr = m_CFBCalculation_Greenup->SetAttributeValue(key, attribute);
		else
			hr = m_CFBCalculation->SetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_ACCEL_START) && (key < FUELCOM_ATTRIBUTE_ACCEL_END)) {
		hr = m_AccAlphaCalculation->SetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_FMC_START) && (key < FUELCOM_ATTRIBUTE_FMC_END)) {
		hr = m_FMCCalculation->SetAttributeValue(key, attribute);
	}

	else if ((key >= FUELCOM_ATTRIBUTE_FLAMELENGTH_START) && (key < FUELCOM_ATTRIBUTE_FLAMELENGTH_END)) {
		hr = m_FLCalculation->SetAttributeValue(key, attribute);
	}

#ifdef DEBUG
	weak_assert(SUCCEEDED(hr));
#endif

	return hr;
}

/*
	This is a method to get the equation used in a FBPFuel and takes the following parameters:
		An equation key value of type uint16
		An equation value of type double
*/
HRESULT FBPFuel::GetEquation(std::uint16_t equationKey, std::uint16_t *equation) const {
	switch (equationKey) {
		case FUELCOM_EQUATION_FMC:			if (!m_FMCCalculation) { *equation = 0;  return E_FAIL; }			*equation = m_FMCCalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_SFC:			if (!m_SFCCalculation) { *equation = 0;  return E_FAIL; }			*equation = m_SFCCalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_SFC_GREENUP:	if (!m_SFCCalculation_Greenup) { *equation = 0;  return E_FAIL; }	*equation = m_SFCCalculation_Greenup->GetExternalDefinition();		break;
		case FUELCOM_EQUATION_TFC:			if (!m_TFCCalculation) { *equation = 0;  return E_FAIL; }			*equation = m_TFCCalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_TFC_GREENUP:	if (!m_TFCCalculation_Greenup) { *equation = 0;  return E_FAIL; }	*equation = m_TFCCalculation_Greenup->GetExternalDefinition();		break;
		case FUELCOM_EQUATION_RSI:			if (!m_RSICalculation) { *equation = 0;  return E_FAIL; }			*equation = m_RSICalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_RSI_GREENUP:	if (!m_RSICalculation_Greenup) { *equation = 0;  return E_FAIL; }	*equation = m_RSICalculation_Greenup->GetExternalDefinition();		break;
		case FUELCOM_EQUATION_ISF:			if (!m_ISFCalculation) { *equation = 0;  return E_FAIL; }			*equation = m_ISFCalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_ISF_GREENUP:	if (!m_ISFCalculation_Greenup) { *equation = 0;  return E_FAIL; }	*equation = m_ISFCalculation_Greenup->GetExternalDefinition();		break;
		case FUELCOM_EQUATION_CFB:			if (!m_CFBCalculation) { *equation = 0;  return E_FAIL; }			*equation = m_CFBCalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_CFB_GREENUP:	if (!m_CFBCalculation_Greenup) { *equation = 0;  return E_FAIL; }	*equation = m_CFBCalculation_Greenup->GetExternalDefinition();		break;
		case FUELCOM_EQUATION_ACCEL:		if (!m_AccAlphaCalculation) { *equation = 0;  return E_FAIL; }		*equation = m_AccAlphaCalculation->GetExternalDefinition();			break;
		case FUELCOM_EQUATION_LB:			if (!m_LBCalculation) { *equation = 0;  return E_FAIL; }			*equation = m_LBCalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_FLAMELENGTH:	if (!m_FLCalculation) { *equation = 0;  return E_FAIL; }			*equation = m_FLCalculation->GetExternalDefinition();				break;
		case FUELCOM_EQUATION_SPREADPARMS:	if (!m_spread) { *equation = 0; return E_FAIL; }					*equation = m_spread->GetExternalDefinition();						break;
		default:				*equation = 0;
			
    #ifdef DEBUG
							weak_assert(false);
    #endif

							return E_INVALIDARG;
	}
	return S_OK;
}


struct class_conversion_table {
	std::uint16_t m_equation;
	const std::type_info *m_class;
} conv_table[] = {
	{ FUELCOM_EQUATION_SELECTION_FMC_CALC,		&typeid(FMC_Calc) },
	{ FUELCOM_EQUATION_SELECTION_FMC_NOCALC,	&typeid(FMC_NoCalc) },

	{ FUELCOM_EQUATION_SELECTION_SFC_C1,		&typeid(SFC_C1) },
	{ FUELCOM_EQUATION_SELECTION_SFC_C2,		&typeid(SFC_C2) },
	{ FUELCOM_EQUATION_SELECTION_SFC_C7,		&typeid(SFC_C7) },
	{ FUELCOM_EQUATION_SELECTION_SFC_D2,		&typeid(SFC_D2) },
	{ FUELCOM_EQUATION_SELECTION_SFC_M1,		&typeid(SFC_M1) },
	{ FUELCOM_EQUATION_SELECTION_SFC_O1,		&typeid(SFC_O1) },
	{ FUELCOM_EQUATION_SELECTION_SFC_S1,		&typeid(SFC_S1) },

	{ FUELCOM_EQUATION_SELECTION_TFC_C1,		&typeid(TFC_C1) },
	{ FUELCOM_EQUATION_SELECTION_TFC_D2,		&typeid(TFC_D2) },
	{ FUELCOM_EQUATION_SELECTION_TFC_M1,		&typeid(TFC_M1) },
	{ FUELCOM_EQUATION_SELECTION_TFC_O1,		&typeid(TFC_O1) },

	{ FUELCOM_EQUATION_SELECTION_RSI_C1,		&typeid(RSI_C1) },
	{ FUELCOM_EQUATION_SELECTION_RSI_C6,		&typeid(RSI_C6) },
	{ FUELCOM_EQUATION_SELECTION_RSI_D2,		&typeid(RSI_D2) },
	{ FUELCOM_EQUATION_SELECTION_RSI_M1,		&typeid(RSI_M1) },
	{ FUELCOM_EQUATION_SELECTION_RSI_M3,		&typeid(RSI_M3) },
	{ FUELCOM_EQUATION_SELECTION_RSI_M4,		&typeid(RSI_M4) },
	{ FUELCOM_EQUATION_SELECTION_RSI_O1,		&typeid(RSI_O1) },
	{ FUELCOM_EQUATION_SELECTION_RSI_CONSTANT,	&typeid(RSI_Constant) },

	{ FUELCOM_EQUATION_SELECTION_ISF_C1,		&typeid(ISF_C1) },
	{ FUELCOM_EQUATION_SELECTION_ISF_M1,		&typeid(ISF_M1) },
	{ FUELCOM_EQUATION_SELECTION_ISF_M3M4,		&typeid(ISF_M3M4) },
	{ FUELCOM_EQUATION_SELECTION_ISF_O1,		&typeid(ISF_O1) },

	{ FUELCOM_EQUATION_SELECTION_CFB_C1,		&typeid(CFB_C1) },
	{ FUELCOM_EQUATION_SELECTION_CFB_D2,		&typeid(CFB_D2) },

	{ FUELCOM_EQUATION_SELECTION_ACCEL_CLOSED,	&typeid(AccAlphaClosed) },
	{ FUELCOM_EQUATION_SELECTION_ACCEL_OPEN,	&typeid(AccAlphaOpen) },

	{ FUELCOM_EQUATION_SELECTION_LB_C1,			&typeid(LB_C1) },
	{ FUELCOM_EQUATION_SELECTION_LB_O1,			&typeid(LB_O1) },

	{ FUELCOM_EQUATION_SELECTION_FLAMELENGTH_TREE,				&typeid(FlameLength_Tree) },
	{ FUELCOM_EQUATION_SELECTION_FLAMELENGTH_OTHER,				&typeid(FlameLength_Other) },
	{ FUELCOM_EQUATION_SELECTION_FLAMELENGTH_ALEXANDER82,		&typeid(FlameLength_Alexander82) },
	{ FUELCOM_EQUATION_SELECTION_FLAMELENGTH_ALEXANDER82_TREE,	&typeid(FlameLength_Alexander82_Tree) },

	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_S1,				&typeid(SpreadParms_S1) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_C1,				&typeid(SpreadParms_C1) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_C6,				&typeid(SpreadParms_C6) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1,				&typeid(SpreadParms_O1) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1AB,				&typeid(SpreadParms_O1ab) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXED,				&typeid(SpreadParms_Mixed) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXEDDEAD,			&typeid(SpreadParms_MixedDead) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_NON,				&typeid(SpreadParms_Non) },
	{ FUELCOM_EQUATION_SELECTION_SPREADPARMS_NZ,				&typeid(SpreadParms_NZ) },

	{ 0,										nullptr }
};

/*
	This is a method to set the equation used in a FBPFuel and takes the following parameters:
		An equation key value of type uint16
		An equation value of type double
*/
HRESULT FBPFuel::SetEquation(std::uint16_t equationKey, std::uint16_t equation) {
	std::uint16_t current;
	HRESULT hr;
	if (FAILED(hr = GetEquation(equationKey, &current))) {
		if (hr != E_FAIL) {
			
#ifdef DEBUG
			weak_assert(false);
#endif

			return E_INVALIDARG;
		}
	}

	if (current == equation)
		return FUELCOM_SUCCESS_NO_CHANGE;

	struct class_conversion_table *t = conv_table;
	while (t->m_equation) {
		if (t->m_equation == equation)
			break;
		t++;
	}
	if (!t->m_equation) {
			
#ifdef DEBUG
		weak_assert(false);
#endif

		return E_INVALIDARG;
	}

	switch (equationKey) {
		case FUELCOM_EQUATION_SPREADPARMS:
							if ((equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_S1) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_C1) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_C6) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1AB) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXED) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXEDDEAD) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_NON) &&
								(equation != FUELCOM_EQUATION_SELECTION_SPREADPARMS_NZ)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_FMC:		
							if ((equation != FUELCOM_EQUATION_SELECTION_FMC_CALC) &&
								(equation != FUELCOM_EQUATION_SELECTION_FMC_NOCALC)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_SFC:		
		case FUELCOM_EQUATION_SFC_GREENUP:
							if ((equation != FUELCOM_EQUATION_SELECTION_SFC_C1) &&
								(equation != FUELCOM_EQUATION_SELECTION_SFC_C2) &&
								(equation != FUELCOM_EQUATION_SELECTION_SFC_C7) &&
								(equation != FUELCOM_EQUATION_SELECTION_SFC_D2) &&
								(equation != FUELCOM_EQUATION_SELECTION_SFC_M1) &&
								(equation != FUELCOM_EQUATION_SELECTION_SFC_O1) &&
								(equation != FUELCOM_EQUATION_SELECTION_SFC_S1)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_TFC:
		case FUELCOM_EQUATION_TFC_GREENUP:
							if ((equation != FUELCOM_EQUATION_SELECTION_TFC_C1) &&
								(equation != FUELCOM_EQUATION_SELECTION_TFC_D2) &&
								(equation != FUELCOM_EQUATION_SELECTION_TFC_M1) &&
								(equation != FUELCOM_EQUATION_SELECTION_TFC_O1)) {
		
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_RSI:
		case FUELCOM_EQUATION_RSI_GREENUP:
							if ((equation != FUELCOM_EQUATION_SELECTION_RSI_C1) &&
								(equation != FUELCOM_EQUATION_SELECTION_RSI_C6) &&
								(equation != FUELCOM_EQUATION_SELECTION_RSI_D2) &&
								(equation != FUELCOM_EQUATION_SELECTION_RSI_M1) &&
								(equation != FUELCOM_EQUATION_SELECTION_RSI_M3) &&
								(equation != FUELCOM_EQUATION_SELECTION_RSI_M4) &&
								(equation != FUELCOM_EQUATION_SELECTION_RSI_O1) &&
								(equation != FUELCOM_EQUATION_SELECTION_RSI_CONSTANT)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_ISF:		
		case FUELCOM_EQUATION_ISF_GREENUP:
							if ((equation != FUELCOM_EQUATION_SELECTION_ISF_C1) &&
								(equation != FUELCOM_EQUATION_SELECTION_ISF_M1) &&
								(equation != FUELCOM_EQUATION_SELECTION_ISF_M3M4) &&
								(equation != FUELCOM_EQUATION_SELECTION_ISF_O1)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_CFB:
		case FUELCOM_EQUATION_CFB_GREENUP:
							if ((equation != FUELCOM_EQUATION_SELECTION_CFB_C1) &&
								(equation != FUELCOM_EQUATION_SELECTION_CFB_D2)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_ACCEL:
							if ((equation != FUELCOM_EQUATION_SELECTION_ACCEL_CLOSED) &&
								(equation != FUELCOM_EQUATION_SELECTION_ACCEL_OPEN)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_LB:
							if ((equation != FUELCOM_EQUATION_SELECTION_LB_C1) &&
								(equation != FUELCOM_EQUATION_SELECTION_LB_O1)) {
			
#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;

		case FUELCOM_EQUATION_FLAMELENGTH:
							if ((equation != FUELCOM_EQUATION_SELECTION_FLAMELENGTH_ALEXANDER82) &&
								(equation != FUELCOM_EQUATION_SELECTION_FLAMELENGTH_ALEXANDER82_TREE) &&
								(equation != FUELCOM_EQUATION_SELECTION_FLAMELENGTH_OTHER) &&
								(equation != FUELCOM_EQUATION_SELECTION_FLAMELENGTH_TREE)) {

#ifdef DEBUG
								weak_assert(false);
#endif

								return E_INVALIDARG;
							}
							break;
		default:
			
#ifdef DEBUG
							weak_assert(false);
#endif

							return E_INVALIDARG;
	}

	FuelAttribute *fa = nullptr;
	switch (equation) {
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_S1: fa = new SpreadParms_S1(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_C1: fa = new SpreadParms_C1(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_C6: fa = new SpreadParms_C6(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1: fa = new SpreadParms_O1(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1AB: fa = new SpreadParms_O1ab(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXED: fa = new SpreadParms_Mixed(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXEDDEAD: fa = new SpreadParms_MixedDead(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_NON: fa = new SpreadParms_Non(); break;
		case FUELCOM_EQUATION_SELECTION_SPREADPARMS_NZ: fa = new SpreadParms_NZ(); break;

		case FUELCOM_EQUATION_SELECTION_FMC_CALC:		fa = new FMC_Calc(); break;
		case FUELCOM_EQUATION_SELECTION_FMC_NOCALC:		fa = new FMC_NoCalc(); break;

		case FUELCOM_EQUATION_SELECTION_SFC_C1:			fa = new SFC_C1(); break;
		case FUELCOM_EQUATION_SELECTION_SFC_C2:			fa = new SFC_C2(); break;
		case FUELCOM_EQUATION_SELECTION_SFC_C7:			fa = new SFC_C7(); break;
		case FUELCOM_EQUATION_SELECTION_SFC_D2:			fa = new SFC_D2(); break;
		case FUELCOM_EQUATION_SELECTION_SFC_M1:			fa = new SFC_M1(); break;
		case FUELCOM_EQUATION_SELECTION_SFC_O1:			fa = new SFC_O1(); break;
		case FUELCOM_EQUATION_SELECTION_SFC_S1:			fa = new SFC_S1(); break;

		case FUELCOM_EQUATION_SELECTION_TFC_C1:			fa = new TFC_C1(); break;
		case FUELCOM_EQUATION_SELECTION_TFC_D2:			fa = new TFC_D2(); break;
		case FUELCOM_EQUATION_SELECTION_TFC_M1:			fa = new TFC_M1(); break;
		case FUELCOM_EQUATION_SELECTION_TFC_O1:			fa = new TFC_O1(); break;

		case FUELCOM_EQUATION_SELECTION_RSI_C1:			fa = new RSI_C1(); break;
		case FUELCOM_EQUATION_SELECTION_RSI_C6:			fa = new RSI_C6(); break;
		case FUELCOM_EQUATION_SELECTION_RSI_D2:			fa = new RSI_D2(); break;
		case FUELCOM_EQUATION_SELECTION_RSI_M1:			fa = new RSI_M1(); break;
		case FUELCOM_EQUATION_SELECTION_RSI_M3:			fa = new RSI_M3(); break;
		case FUELCOM_EQUATION_SELECTION_RSI_M4:			fa = new RSI_M4(); break;
		case FUELCOM_EQUATION_SELECTION_RSI_O1:			fa = new RSI_O1(); break;
		case FUELCOM_EQUATION_SELECTION_RSI_CONSTANT:	fa = new RSI_Constant(); break;

		case FUELCOM_EQUATION_SELECTION_ISF_C1:			fa = new ISF_C1(); break;
		case FUELCOM_EQUATION_SELECTION_ISF_M1:			fa = new ISF_M1(); break;
		case FUELCOM_EQUATION_SELECTION_ISF_M3M4:		fa = new ISF_M3M4(); break;
		case FUELCOM_EQUATION_SELECTION_ISF_O1:			fa = new ISF_O1(); break;

		case FUELCOM_EQUATION_SELECTION_CFB_C1:			fa = new CFB_C1(); break;
		case FUELCOM_EQUATION_SELECTION_CFB_D2:			fa = new CFB_D2(); break;

		case FUELCOM_EQUATION_SELECTION_ACCEL_CLOSED:	fa = new AccAlphaClosed(); break;
		case FUELCOM_EQUATION_SELECTION_ACCEL_OPEN:		fa = new AccAlphaOpen(); break;

		case FUELCOM_EQUATION_SELECTION_LB_C1:			fa = new LB_C1(); break;
		case FUELCOM_EQUATION_SELECTION_LB_O1:			fa = new LB_O1(); break;
	}

	switch (equationKey) {
	case FUELCOM_EQUATION_SPREADPARMS:
							if (m_spread)
								delete m_spread;
							m_spread = (SpreadParmsAttribute *)fa;
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_FMC:
							if (m_FMCCalculation)
								delete m_FMCCalculation;	
							m_FMCCalculation = (FMCAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_SFC:	
							if ((m_SFCCalculation) && (m_SFCCalculation != m_SFCCalculation_Greenup))
								delete m_SFCCalculation;	
							m_SFCCalculation = (SFCAttribute *)fa;
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_SFC_GREENUP:	
							if ((m_SFCCalculation_Greenup) && (m_SFCCalculation != m_SFCCalculation_Greenup))
								delete m_SFCCalculation_Greenup;
							m_SFCCalculation_Greenup = (SFCAttribute *)fa;
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_TFC:			
							if ((m_TFCCalculation) && (m_TFCCalculation != m_TFCCalculation_Greenup))
								delete m_TFCCalculation;
							m_TFCCalculation = (TFCAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_TFC_GREENUP:	
							if ((m_TFCCalculation_Greenup) && (m_TFCCalculation != m_TFCCalculation_Greenup))
								delete m_TFCCalculation_Greenup;
							m_TFCCalculation_Greenup = (TFCAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_RSI:			
							if ((m_RSICalculation) && (m_RSICalculation != m_RSICalculation_Greenup))
								delete m_RSICalculation;
							m_RSICalculation = (RSIAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_RSI_GREENUP:	
							if ((m_RSICalculation_Greenup) && (m_RSICalculation != m_RSICalculation_Greenup))
								delete m_RSICalculation_Greenup;
							m_RSICalculation_Greenup = (RSIAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_ISF:			
							if ((m_ISFCalculation) && (m_ISFCalculation != m_ISFCalculation_Greenup))
								delete m_ISFCalculation;
							m_ISFCalculation = (ISFAttribute *)fa;
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_ISF_GREENUP:	
							if ((m_ISFCalculation_Greenup) && (m_ISFCalculation != m_ISFCalculation_Greenup))
								delete m_ISFCalculation_Greenup;
							m_ISFCalculation_Greenup = (ISFAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_CFB:			
							if ((m_CFBCalculation) && (m_CFBCalculation != m_CFBCalculation_Greenup))
								delete m_CFBCalculation;	
							m_CFBCalculation = (CFBAttribute *)fa;		
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_CFB_GREENUP:
							if ((m_CFBCalculation_Greenup) && (m_CFBCalculation != m_CFBCalculation_Greenup))
								delete m_CFBCalculation_Greenup;
							m_CFBCalculation_Greenup = (CFBAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_ACCEL:
							if (m_AccAlphaCalculation)
								delete m_AccAlphaCalculation;	
							m_AccAlphaCalculation = (AccAlphaAttribute *)fa;
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;

		case FUELCOM_EQUATION_LB:	
							if (m_LBCalculation)
								delete m_LBCalculation;	
							m_LBCalculation = (LBAttribute *)fa;	
#ifdef _DEBUG
							fa = nullptr;
#endif
											break;

		case FUELCOM_EQUATION_FLAMELENGTH:	if (m_FLCalculation)
												delete m_FLCalculation;
											m_FLCalculation = (FlameLengthAttribute *)fa;
#ifdef _DEBUG
							fa = nullptr;
#endif
							break;
	}

#ifdef _DEBUG
	weak_assert(!fa);
#endif

	m_fuelTypeModified = true;
	return S_OK;
}

/*
	See FBPFuel.h for this definition
*/
void FBPFuel::SetC2(boost::intrusive_ptr<ICWFGM_Fuel> &newVal) {
	SpreadParms_Mixed *sa = dynamic_cast<SpreadParms_Mixed *>(m_spread);
	SpreadParms_MixedDead *sd = dynamic_cast<SpreadParms_MixedDead *>(m_spread);

	if ((sa) || (sd)) {
		SpreadParms_Mixed *m = (SpreadParms_Mixed *)m_spread;
		m->SetC2(newVal);
	}
}

/*
	See FBPFuel.h for this definition
*/
void FBPFuel::SetD1(boost::intrusive_ptr<ICWFGM_Fuel> &newVal) {
	SpreadParms_Mixed *sa = dynamic_cast<SpreadParms_Mixed *>(m_spread);
	SpreadParms_MixedDead *sd = dynamic_cast<SpreadParms_MixedDead *>(m_spread);

	if ((sa) || (sd)) {
		SpreadParms_Mixed *m = (SpreadParms_Mixed *)m_spread;
		m->SetD1(newVal);
	}
}

/*
	See FBPFuel.h for this definition
*/
void FBPFuel::GetC2(boost::intrusive_ptr<ICWFGM_Fuel> *newVal) const {
	SpreadParms_Mixed *sa = dynamic_cast<SpreadParms_Mixed *>(m_spread);
	SpreadParms_MixedDead *sd = dynamic_cast<SpreadParms_MixedDead *>(m_spread);

	if ((sa) || (sd)) {
		SpreadParms_Mixed *m = (SpreadParms_Mixed *)m_spread;
		m->C2(*newVal);
	}
}

/*
	See FBPFuel.h for this definition
*/
void FBPFuel::GetD1(boost::intrusive_ptr<ICWFGM_Fuel> *newVal) const {
	SpreadParms_Mixed *sa = dynamic_cast<SpreadParms_Mixed *>(m_spread);
	SpreadParms_MixedDead *sd = dynamic_cast<SpreadParms_MixedDead *>(m_spread);

	if ((sa) || (sd)) {
		SpreadParms_Mixed *m = (SpreadParms_Mixed *)m_spread;
		m->D1(*newVal);
	}
}


#define DEFINE_GUID1(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_C1, 0xB92D1311, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_C2, 0xB92D1314, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_C3, 0xB92D1315, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_C4, 0xB92D1316, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_C5, 0xB92D1317, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_C6, 0xB92D1318, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_C7, 0xB92D1319, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_D1, 0xB92D1320, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_D2, 0xB92D1331, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_D1D2, 0xB92D1332, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_M1, 0xB92D1321, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_M2, 0xB92D1322, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_M1M2, 0xB92D1333, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_M3, 0xB92D1323, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_M4, 0xB92D1324, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_M3M4, 0xB92D1334, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_S1, 0xB92D1327, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_S2, 0xB92D1328, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel, 0xB92D1330, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_S3, 0xB92D1329, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_O1b, 0xB92D1326, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_O1a, 0xB92D1325, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_O1ab, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x80);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_Non, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xD7, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ1, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x01);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ2, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x02);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ3, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x03);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ4, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x04);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ5, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x05);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ6, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x06);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ10, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x10);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ11, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x11);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ12, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x12);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ13, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x13);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ14, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x14);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ15, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x15);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ16, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x16);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ20, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x20);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ21, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x21);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ22, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x22);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ30, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x30);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ31, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x31);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ32, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x32);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ33, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x33);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ40, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x40);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ41, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x41);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ43, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x43);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ44, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x44);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ45, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x45);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ46, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x46);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ47, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x47);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ50, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x50);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ51, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x51);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ52, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x52);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ53, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x53);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ54, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x54);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ55, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x55);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ56, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x56);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ57, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x57);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ58, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x58);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ60, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x60);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ61, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x61);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ62, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x62);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ63, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x63);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ64, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x64);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ65, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x65);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ66, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x66);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ67, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x67);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ68, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x68);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ69, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x69);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ70, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x70);
DEFINE_GUID1(_GUID, CLSID_CWFGM_Fuel_NZ71, 0xB92D1341, 0x1D20, 0x11D4, 0xBC, 0xE8, 0x00, 0xA0, 0x83, 0x3B, 0x17, 0x71);
