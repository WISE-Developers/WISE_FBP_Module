/**
 * WISE_FBP_Module: SFC.cpp
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

#if __has_include(<mathimf.h>)
#include <mathimf.h>
#else
#include <cmath>
#endif

#include "sfc.h"
#include "FBPFuel.h"
#include "doubleBuilder.h"
#include "str_printf.h"
#include "results.h"

#ifdef DEBUG
#include <assert.h>
#endif


namespace sfc {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::S1):
			val = FUELCOM_ATTRIBUTE_SFC_S1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S2):
			val = FUELCOM_ATTRIBUTE_SFC_S2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S3):
			val = FUELCOM_ATTRIBUTE_SFC_S3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz63):
			val = FUELCOM_ATTRIBUTE_SFC_NZ63_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz64):
			val = FUELCOM_ATTRIBUTE_SFC_NZ64_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz65):
			val = FUELCOM_ATTRIBUTE_SFC_NZ65_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz66):
			val = FUELCOM_ATTRIBUTE_SFC_NZ66_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1A):
			val = FUELCOM_ATTRIBUTE_SFC_O1A_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1B):
			val = FUELCOM_ATTRIBUTE_SFC_O1B_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz62):
			val = FUELCOM_ATTRIBUTE_SFC_NZ62_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz2):
			val = FUELCOM_ATTRIBUTE_SFC_NZ2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz15):
			val = FUELCOM_ATTRIBUTE_SFC_NZ15_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz32):
			val = FUELCOM_ATTRIBUTE_SFC_NZ32_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz33):
			val = FUELCOM_ATTRIBUTE_SFC_NZ33_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz44):
			val = FUELCOM_ATTRIBUTE_SFC_NZ44_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz30):
			val = FUELCOM_ATTRIBUTE_SFC_NZ30_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz45):
			val = FUELCOM_ATTRIBUTE_SFC_NZ45_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz46):
			val = FUELCOM_ATTRIBUTE_SFC_NZ46_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz53):
			val = FUELCOM_ATTRIBUTE_SFC_NZ53_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz40):
			val = FUELCOM_ATTRIBUTE_SFC_NZ40_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz41):
			val = FUELCOM_ATTRIBUTE_SFC_NZ41_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz43):
			val = FUELCOM_ATTRIBUTE_SFC_NZ43_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz47):
			val = FUELCOM_ATTRIBUTE_SFC_NZ47_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz50):
			val = FUELCOM_ATTRIBUTE_SFC_NZ50_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz56):
			val = FUELCOM_ATTRIBUTE_SFC_NZ56_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz57):
			val = FUELCOM_ATTRIBUTE_SFC_NZ57_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz58):
			val = FUELCOM_ATTRIBUTE_SFC_NZ58_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz51):
			val = FUELCOM_ATTRIBUTE_SFC_NZ51_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz52):
			val = FUELCOM_ATTRIBUTE_SFC_NZ52_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz55):
			val = FUELCOM_ATTRIBUTE_SFC_NZ55_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz70):
			val = FUELCOM_ATTRIBUTE_SFC_NZ70_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D2):
			val = FUELCOM_ATTRIBUTE_SFC_D2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C7):
			val = FUELCOM_ATTRIBUTE_SFC_C7_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C2):
			val = FUELCOM_ATTRIBUTE_SFC_C2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_SFC_M4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz67):
			val = FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C3):
			val = FUELCOM_ATTRIBUTE_SFC_C3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C4):
			val = FUELCOM_ATTRIBUTE_SFC_C4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C5):
			val = FUELCOM_ATTRIBUTE_SFC_C5_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C6):
			val = FUELCOM_ATTRIBUTE_SFC_C6_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz54):
			val = FUELCOM_ATTRIBUTE_SFC_NZ54_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz61):
			val = FUELCOM_ATTRIBUTE_SFC_NZ61_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz60):
			val = FUELCOM_ATTRIBUTE_SFC_NZ60_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C1):
			val = FUELCOM_ATTRIBUTE_SFC_C1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D1):
			val = FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz68):
			val = FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz71):
			val = FUELCOM_ATTRIBUTE_SFC_NZ71_DEFAULTS;
			break;

		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a no-argument constructor to initialize a SFC_C1 object
*/
SFC_C1::SFC_C1() : m_cache(16) { 
	m_p1 = -1.0;
	m_p2 = -1.0; 
	m_p3 = -1.0;
	m_p4 = -1.0;
	m_multiplier = 1.0;
}

/*
	This is a 1-argument constructor to initialize a SFC_C1 object by copying another SFC_C1 object
*/
SFC_C1::SFC_C1(const SFC_C1 & toCopy) : m_cache(16) {
	m_p1 = toCopy.m_p1;
	m_p2 = toCopy.m_p2;
	m_p3 = toCopy.m_p3;
	m_p4 = toCopy.m_p4;
	m_multiplier = toCopy.m_multiplier;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SFC_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_C1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_C1_DEFAULTS:			if ((m_p1 == 0.75) &&
															(m_p2 == 0.75) &&
															(m_p3 == 0.230) &&
															(m_p4 == 84.0) &&
															(m_multiplier == 1.0))
															return S_OK;
														return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_C1_CLR_DEFAULTS:		if ((m_p1 == 0.0) &&
															(m_p2 == 0.0) &&
															(m_p3 == 0.0) &&
															(m_p4 == 0.0) &&
															(m_multiplier == 0.0))
															return S_OK;
														return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_EQ9_ADDER:		*attribute = m_p1;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ9_MULT1:		*attribute = m_p2;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ9_MULT2:		*attribute = m_p3;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ9_FFMC_THRESHOLD:	*attribute = m_p4;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		*attribute = m_multiplier;	return S_OK;
	}
	return SFCAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SFC_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_C1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_C1_DEFAULTS:		m_p1 = 0.75;	// the equation is changed in Errata, equations 9a, 9b
								m_p2 = 0.75;
								m_p3 = 0.230;
								m_p4 = 84.0;
								m_multiplier = 1.0;
								m_cache.Clear();		// clear out the cache
								return S_OK;
		
		case FUELCOM_ATTRIBUTE_SFC_C1_CLR_DEFAULTS:	m_p1 = m_p2 = m_p3 = m_p4 = m_multiplier = 0.0;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ9_ADDER:		m_p1 = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ9_MULT1:		m_p2 = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ9_MULT2:		m_p3 = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ9_FFMC_THRESHOLD:	if (attribute < 0.0)		return E_INVALIDARG;
								m_p4 = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		m_multiplier = attribute;
								m_cache.Clear();
								return S_OK;
	}
	return SFCAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the SFC_C1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SFC_C1::Equals(const FuelAttribute *attribute) const {
	const SFC_C1 *a = dynamic_cast<const SFC_C1 *>(attribute);
	if (!a)
		return false;
	if (m_p1 != a->m_p1)					return false;
	if (m_p2 != a->m_p2)					return false;
	if (m_p3 != a->m_p3)					return false;
	if (m_p4 != a->m_p4)					return false;
	if (m_multiplier != a->m_multiplier)	return false;
	return true;
}

/*
	See the definition of SFC in the FuelAttribute header file
*/
double SFC_C1::SFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double FFMC, double /*BUI*/) const {
	{
		double *sfc, _sfc;
		if (sfc = m_cache.Retrieve(&FFMC, &_sfc))
			return *sfc;
	}
	{
		double m_sfc;

		weak_assert(m_p1 != -1.0);
		weak_assert(m_p2 != -1.0);
		weak_assert(m_p3 != -1.0);
		weak_assert(m_p4 != -1.0);
		weak_assert(m_multiplier != -1.0);

		if ((m_p1 == 0.0) && (m_p2 == 0.0) && (m_p3 == 0.0) && (m_p4 == 0.0) && (m_multiplier == 0.0))
			m_sfc = 0.0;
		else {
			if (FFMC > m_p4)
				m_sfc = m_p1 + m_p2 * sqrt(1.0 - exp(-m_p3 * (FFMC - m_p4)));	// equation 9a, August 04 paper
			else		
				m_sfc = m_p1 - m_p2 * sqrt(1.0 - exp(m_p3 * (FFMC - m_p4)));	// equation 9b, August 04 paper
			if (m_sfc < 0.0)
				m_sfc = 0.0;
			else if (m_sfc > 0.0)
				m_sfc *= m_multiplier;
		}
		m_cache.Store(&FFMC, &m_sfc);
		return m_sfc;
	}
}


WISE::FuelProto::SfcAttribute* SFC_C1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *attr = new WISE::FuelProto::SfcAttribute();
	attr->set_version(SFCAttribute::serialVersionUid(options));

	WISE::FuelProto::SfcC1 *msgRet = new WISE::FuelProto::SfcC1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SfcC1_Parms *msg = new WISE::FuelProto::SfcC1_Parms();
		msg->set_version(options.fileVersion());
		if (options.fileVersion() == 1) {
			std::string m_notes;
			msg->set_notes(m_notes);
		}
		msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p2(DoubleBuilder().withValue(m_p2).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p3(DoubleBuilder().withValue(m_p3).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p4(DoubleBuilder().withValue(m_p4).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_multiplier(DoubleBuilder().withValue(m_multiplier).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c1(msgRet);
	return attr;
}


SFC_C1 *SFC_C1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SfcC1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SfcC1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcC1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_C1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcC1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_C1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcC1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SfcC1_Parms &msg = msgRead->parms();

		if ((msg.version() != 1) && (msg.version() != 2)) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SfcC1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("SFC_C1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SfcC1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.version() == 1) {
			std::string m_notes;
			m_notes = msg.notes();
		}
		if (msg.has_p1())
			m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();
		if (msg.has_p2())
			m_p2 = DoubleBuilder().withProtobuf(msg.p2(), v2, "p2").getValue();
		if (msg.has_p3())
			m_p3 = DoubleBuilder().withProtobuf(msg.p3(), v2, "p3").getValue();
		if (msg.has_p4())
			m_p4 = DoubleBuilder().withProtobuf(msg.p4(), v2, "p4").getValue();
		if (msg.has_multiplier())
			m_multiplier = DoubleBuilder().withProtobuf(msg.multiplier(), v2, "multiplier").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("SFC_C1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SFC_C2 object
*/
SFC_C2::SFC_C2() : m_cache(16) {
	m_p1 = -1.0;
	m_p2 = -1.0;
	m_power = -1.0;
	m_multiplier = 1.0;
}

/*
	This is a 1-argument constructor to initialize a SFC_C2 object by copying another SFC_C2 object
*/
SFC_C2::SFC_C2(const SFC_C2 & toCopy) : m_cache(16) {
	m_p1 = toCopy.m_p1;
	m_p2 = toCopy.m_p2;
	m_power = toCopy.m_power;
	m_multiplier = toCopy.m_multiplier;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SFC_C2 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_C2::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_C2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_M4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ67_DEFAULTS:	if ((m_p1 == 5.0) &&
														(m_p2 == 0.0115) &&
														(m_power == 1.00) &&
														(m_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_C4_DEFAULTS:		if ((m_p1 == 5.0) &&
														(m_p2 == 0.0164) &&
														(m_power == 2.24) &&
														(m_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ54_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ61_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ69_DEFAULTS:	if ((m_p1 == 5.0) &&
														(m_p2 == 0.0149) &&
														(m_power == 2.48) &&
														(m_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_NZ60_DEFAULTS:	if ((m_p1 == 5.0) &&
														(m_p2 == 0.0149) &&
														(m_power == 2.48) &&
														(m_multiplier == 4.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ68_DEFAULTS:	if ((m_p1 == 1.5) &&
														(m_p2 == 0.0183) &&
														(m_power == 1.00) &&
														(m_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_EQ10_MULT1:		*attribute = m_p1;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ10_ADDER:		*attribute = m_p2;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ10_POWER:		*attribute = m_power;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		*attribute = m_multiplier;	return S_OK;
	}
	return SFCAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SFC_C2 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_C2::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_C2_DEFAULTS:	
		case FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_M4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ67_DEFAULTS:	m_p1 = 5.0;
													m_p2 = 0.0115;
													m_power = 1.00;
													m_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_C4_DEFAULTS:		m_p1 = 5.0;
													m_p2 = 0.0164;
													m_power = 2.24;
													m_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_C5_DEFAULTS:	
		case FUELCOM_ATTRIBUTE_SFC_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ54_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ61_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ69_DEFAULTS:	m_p1 = 5.0;
													m_p2 = 0.0149;
													m_power = 2.48;
													m_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ60_DEFAULTS:	m_p1 = 5.0;
													m_p2 = 0.0149;
													m_power = 2.48;
													m_multiplier = 4.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ68_DEFAULTS:	m_p1 = 1.5;
													m_p2 = 0.0183;
													m_power = 1.00;
													m_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ10_MULT1:		m_p1 = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ10_ADDER:		m_p2 = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ10_POWER:		m_power = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		m_multiplier = attribute;
								m_cache.Clear();
								return S_OK;
	}
	return SFCAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the SFC_C2 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SFC_C2::Equals(const FuelAttribute *attribute) const {
	const SFC_C2 *a = dynamic_cast<const SFC_C2 *>(attribute);
	if (!a)
		return false;
	if (m_p1 != a->m_p1)					return false;
	if (m_p2 != a->m_p2)					return false;
	if (m_power != a->m_power)				return false;
	if (m_multiplier != a->m_multiplier)	return false;
	return true;
}

/*
	See the definition of SFC in the FuelAttribute header file
*/
double SFC_C2::SFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double /*FFMC*/, double BUI) const {
	{
		double *sfc, _sfc;
		if (sfc = m_cache.Retrieve(&BUI, &_sfc))
			return *sfc;
	}
	{
		weak_assert(m_p1 != -1.0);
		weak_assert(m_p2 != -1.0);
		weak_assert(m_power != -1.0);
		weak_assert(m_multiplier != -1.0);
		double m_sfc = m_p1 * pow(1.0 - exp((0.0 - m_p2) * BUI), m_power);
		if (m_sfc > 0.0)
			m_sfc *= m_multiplier;	
						// equation 10, 11, 12, 16
		m_cache.Store(&BUI, &m_sfc);
		return m_sfc; 
	}
}


WISE::FuelProto::SfcAttribute* SFC_C2::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *attr = new WISE::FuelProto::SfcAttribute();
	attr->set_version(SFCAttribute::serialVersionUid(options));

	WISE::FuelProto::SfcC2 *msgRet = new WISE::FuelProto::SfcC2();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_M4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ67_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz67);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C6_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C6);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ54_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz54);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ61_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz61);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ69_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz69);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ60_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz60);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ68_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz68);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SfcC2_Parms *msg = new WISE::FuelProto::SfcC2_Parms();
		msg->set_version(options.fileVersion());
		if (options.fileVersion() == 1) {
			std::string m_notes;
			msg->set_notes(m_notes);
		}
		msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p2(DoubleBuilder().withValue(m_p2).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_power(DoubleBuilder().withValue(m_power).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_multiplier(DoubleBuilder().withValue(m_multiplier).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c2(msgRet);
	return attr;
}


SFC_C2 *SFC_C2::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SfcC2 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SfcC2 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcC2", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_C2: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcC2", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_C2: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcC2", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SfcC2_Parms &msg = msgRead->parms();

		if ((msg.version() != 1) && (msg.version() != 2)) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SfcC2.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("SFC_C2: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SfcC2.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.version() == 1) {
			std::string m_notes;
			m_notes = msg.notes();
		}
		if (msg.has_p1())
			m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();
		if (msg.has_p2())
			m_p2 = DoubleBuilder().withProtobuf(msg.p2(), v2, "p2").getValue();
		if (msg.has_power())
			m_power = DoubleBuilder().withProtobuf(msg.power(), v2, "power").getValue();
		if (msg.has_multiplier())
			m_multiplier = DoubleBuilder().withProtobuf(msg.multiplier(), v2, "multiplier").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("SFC_C2: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SFC_C7 object
*/
SFC_C7::SFC_C7() : m_cache(16) { 
	m_p1_f = -1.0; 
	m_p2_f = -1.0; 
	m_p3_f = -1.0; 
	m_p1_w = -1.0; 
	m_p2_w = -1.0; 
	m_ffc_multiplier = m_wfc_multiplier = m_sfc_multiplier = 1.0;
}

/*
	This is a 1-argument constructor to initialize a SFC_C7 object by copying another SFC_C7 object
*/
SFC_C7::SFC_C7(const SFC_C7 & toCopy) : m_cache(16) {
	m_p1_f = toCopy.m_p1_f;
	m_p2_f = toCopy.m_p2_f;
	m_p3_f = toCopy.m_p3_f;
	m_p1_w = toCopy.m_p1_w;
	m_p2_w = toCopy.m_p2_w;
	m_ffc_multiplier = toCopy.m_ffc_multiplier;
	m_wfc_multiplier = toCopy.m_wfc_multiplier;
	m_sfc_multiplier = toCopy.m_sfc_multiplier;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SFC_C7 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_C7::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {

		case FUELCOM_ATTRIBUTE_SFC_C7_DEFAULTS:		if ((m_p1_f == 2.0) &&
														(m_p2_f == 0.104) &&
														(m_p3_f == 70.0) &&
														(m_p1_w == 1.5) &&
														(m_p2_w == 0.0201) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 1.0) &&
														(m_ffc_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_EQ13_MULT1:		*attribute = m_p1_f;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ13_MULT2:		*attribute = m_p2_f;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ13_ADDER:		*attribute = m_p3_f;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ14_MULT1:		*attribute = m_p1_w;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ14_MULT2:		*attribute = m_p2_w;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		*attribute = m_sfc_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_WFC_MULTIPLIER:		*attribute = m_wfc_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_FFC_MULTIPLIER:		*attribute = m_ffc_multiplier;	return S_OK;
	}
	return SFCAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SFC_C7 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_C7::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_C7_DEFAULTS:		m_p1_f = 2.0;
								m_p2_f = 0.104;
								m_p3_f = 70.0;
								m_p1_w = 1.5;
								m_p2_w = 0.0201;
								m_sfc_multiplier = 1.0;
								m_wfc_multiplier = 1.0;
								m_ffc_multiplier = 1.0;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ13_MULT1:		m_p1_f = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ13_MULT2:		m_p2_f = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ13_ADDER:		m_p3_f = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ14_MULT1:		m_p1_w = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ14_MULT2:		m_p2_w = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		m_sfc_multiplier = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_WFC_MULTIPLIER:		m_wfc_multiplier = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_FFC_MULTIPLIER:		m_ffc_multiplier = attribute;
								m_cache.Clear();
								return S_OK;
	}
	return SFCAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the SFC_C7 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SFC_C7::Equals(const FuelAttribute *attribute) const {
	const SFC_C7 *a = dynamic_cast<const SFC_C7 *>(attribute);
	if (!a)
		return false;
	if (m_p1_f != a->m_p1_f)	return false;
	if (m_p2_f != a->m_p2_f)	return false;
	if (m_p3_f != a->m_p3_f)	return false;
	if (m_p1_w != a->m_p1_w)	return false;
	if (m_p2_w != a->m_p2_w)	return false;
	if (m_sfc_multiplier != a->m_sfc_multiplier)	return false;
	if (m_wfc_multiplier != a->m_wfc_multiplier)	return false;
	if (m_ffc_multiplier != a->m_ffc_multiplier)	return false;
	return true;
}

/*
	See the definition of SFC in the FuelAttribute header file
*/
double SFC_C7::SFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double FFMC, double BUI) const {
	key c_key;
	c_key.m_ffmc = FFMC;
	c_key.m_bui = BUI;
	{
		double *sfc, _sfc;
		if (sfc = m_cache.Retrieve(&c_key, &_sfc))
			return *sfc;
	}
	{
		weak_assert(m_p1_f != -1.0);
		weak_assert(m_p2_f != -1.0);
		weak_assert(m_p3_f != -1.0);
		weak_assert(m_p1_w != -1.0);
		weak_assert(m_p2_w != -1.0);
		double m_sfc;
		double ffc = m_p1_f * (1.0 - exp(-m_p2_f * (FFMC - m_p3_f)));
									// equation 13
		if (ffc < 0.0)
			ffc = 0.0;
		else if (ffc > 0.0)
			ffc *= m_ffc_multiplier;
		double wfc = m_p1_w * (1.0 - exp(-m_p2_w * BUI));	// equation 14
		if (wfc > 0.0)
			wfc *= m_wfc_multiplier;
		m_sfc = ffc + wfc;					// equation 15
		m_sfc *= m_sfc_multiplier;
		m_cache.Store(&c_key, &m_sfc);
		return m_sfc;
	}
}


WISE::FuelProto::SfcAttribute* SFC_C7::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *attr = new WISE::FuelProto::SfcAttribute();
	attr->set_version(SFCAttribute::serialVersionUid(options));

	WISE::FuelProto::SfcC7 *msgRet = new WISE::FuelProto::SfcC7();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SfcC7_Parms *msg = new WISE::FuelProto::SfcC7_Parms();
		msg->set_version(1);
		msg->set_allocated_p1f(DoubleBuilder().withValue(m_p1_f).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p2f(DoubleBuilder().withValue(m_p2_f).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p3f(DoubleBuilder().withValue(m_p3_f).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p1w(DoubleBuilder().withValue(m_p1_w).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p2w(DoubleBuilder().withValue(m_p2_w).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_ffcmultiplier(DoubleBuilder().withValue(m_ffc_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_wfcmultiplier(DoubleBuilder().withValue(m_wfc_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_sfcmultiplier(DoubleBuilder().withValue(m_sfc_multiplier).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c7(msgRet);
	return attr;
}


SFC_C7 *SFC_C7::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SfcC7 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SfcC7 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcC7", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_C2: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcC7", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_C2: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcC7", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SfcC7_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SfcC7.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("SFC_C2: Version is invalid");
		}
		
		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SfcC7.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_p1f())
			m_p1_f = DoubleBuilder().withProtobuf(msg.p1f(), v2, "p1F").getValue();
		if (msg.has_p2f())
			m_p2_f = DoubleBuilder().withProtobuf(msg.p2f(), v2, "p2F").getValue();
		if (msg.has_p3f())
			m_p3_f = DoubleBuilder().withProtobuf(msg.p3f(), v2, "p3F").getValue();
		if (msg.has_p1w())
			m_p1_w = DoubleBuilder().withProtobuf(msg.p1w(), v2, "p1W").getValue();
		if (msg.has_p2w())
			m_p2_w = DoubleBuilder().withProtobuf(msg.p2w(), v2, "p1W").getValue();
		if (msg.has_ffcmultiplier())
			m_ffc_multiplier = DoubleBuilder().withProtobuf(msg.ffcmultiplier(), v2, "ffcMultiplier").getValue();
		if (msg.has_wfcmultiplier())
			m_wfc_multiplier = DoubleBuilder().withProtobuf(msg.wfcmultiplier(), v2, "wfcMultiplier").getValue();
		if (msg.has_sfcmultiplier())
			m_sfc_multiplier = DoubleBuilder().withProtobuf(msg.sfcmultiplier(), v2, "sfcMultiplier").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("SFC_C2: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SFC_D2 object
*/
SFC_D2::SFC_D2() : SFC_C2() {
	m_threshold = 80.0;
	m_scale1 = 0.0;
	m_scale2 = 1.0;							// RWB: 051005: changed this modifier back to 1.0 after emails between Cordy and Mike Wotton
}

/*
	This is a 1-argument constructor to initialize a SFC_D2 object by copying another SFC_D2 object
*/
SFC_D2::SFC_D2(const SFC_D2 &toCopy) : SFC_C2(toCopy) {
	m_threshold = toCopy.m_threshold;
	m_scale1 = toCopy.m_scale1;
	m_scale2 = toCopy.m_scale2;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SFC_D2 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_D2::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_D2_DEFAULTS:		if ((m_p1 == 1.5) &&
														(m_p2 == 0.0183) &&
														(m_power == 1.00) &&
														(m_multiplier == 1.0) &&
														(m_threshold == 80.0) &&
														(m_scale1 == 0.0) &&
														(m_scale2 == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_D2_THRESHOLD:	*attribute = m_threshold;	return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_D2_SCALE1:		*attribute = m_scale1;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_D2_SCALE2:		*attribute = m_scale2;		return S_OK;
	}
	return SFC_C2::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SFC_D2 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_D2::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_D2_DEFAULTS:		m_p1 = 1.5;
								m_p2 = 0.0183;
								m_power = 1.00;
								m_multiplier = 1.0;
								m_threshold = 80.0;
								m_scale1 = 0.0;
								m_scale2 = 1.0;		// RWB: 051005: changed this modifier back to 1.0 after emails between Cordy and Mike Wotton
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_D2_THRESHOLD:	if (attribute < 0.0)		return E_INVALIDARG;
								m_threshold = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_D2_SCALE1:		if (attribute < 0.0)		return E_INVALIDARG;
								if (attribute > 2.0)		return E_INVALIDARG;
								m_scale1 = attribute;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_D2_SCALE2:		if (attribute < 0.0)		return E_INVALIDARG;
								if (attribute > 2.0)		return E_INVALIDARG;
								m_scale2 = attribute;
								m_cache.Clear();
								return S_OK;
	}
	return SFC_C2::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the SFC_D2 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SFC_D2::Equals(const FuelAttribute *attribute) const {
	const SFC_D2 *a = dynamic_cast<const SFC_D2 *>(attribute);
	if (!a)
		return false;
	if (m_p1 != a->m_p1)		return false;
	if (m_p2 != a->m_p2)		return false;
	if (m_power != a->m_power)	return false;
	if (m_multiplier != a->m_multiplier)	return false;
	if (m_threshold != a->m_threshold)	return false;
	if (m_scale1 != a->m_scale1)	return false;
	if (m_scale2 != a->m_scale2)	return false;
	return SFC_C2::Equals(attribute);
}

/*
	See the definition of SFC in the FuelAttribute header file
*/
double SFC_D2::SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const {
	double scale;
	if (BUI < m_threshold)	scale = m_scale1;
	else					scale = m_scale2;

	if (scale == 0.0)
		return 0.0;

	// equation 63 is applied in the following statement, just like D2, with any BE affect applied
	double sfc = SFC_C2::SFC(sa, flag, overrides, FFMC, BUI);
	return scale * sfc;
}


WISE::FuelProto::SfcAttribute* SFC_D2::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *attr = new WISE::FuelProto::SfcAttribute();
	attr->set_version(SFCAttribute::serialVersionUid(options));

	WISE::FuelProto::SfcD2 *msgRet = new WISE::FuelProto::SfcD2();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_D2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_M3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_M4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ67_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz67);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_C6_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C6);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ54_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz54);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ61_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz61);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ69_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz69);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ60_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz60);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_D1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ68_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz68);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SfcD2_Parms *msg = new WISE::FuelProto::SfcD2_Parms();
		msg->set_version(options.fileVersion());
		if (options.fileVersion() == 1) {
			std::string m_notes;
			msg->set_notes(m_notes);
		}
		msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p2(DoubleBuilder().withValue(m_p2).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_power(DoubleBuilder().withValue(m_power).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_multiplier(DoubleBuilder().withValue(m_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_threshold(DoubleBuilder().withValue(m_threshold).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_scale1(DoubleBuilder().withValue(m_scale1).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_scale2(DoubleBuilder().withValue(m_scale2).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_d2(msgRet);
	return attr;
}


SFC_D2 *SFC_D2::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SfcD2 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SfcD2 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcD2", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_D2: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcD2", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_D2: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcD2", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SfcD2_Parms &msg = msgRead->parms();

		if ((msg.version() != 1) && (msg.version() != 2)) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SfcD2.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("SFC_D2: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SfcD2.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.version() == 1) {
			std::string m_notes;
			m_notes = msg.notes();
		}
		if (msg.has_p1())
			m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();
		if (msg.has_p2())
			m_p2 = DoubleBuilder().withProtobuf(msg.p2(), v2, "p2").getValue();
		if (msg.has_power())
			m_power = DoubleBuilder().withProtobuf(msg.power(), v2, "power").getValue();
		if (msg.has_multiplier())
			m_multiplier = DoubleBuilder().withProtobuf(msg.multiplier(), v2, "multiplier").getValue();
		if (msg.has_threshold())
			m_threshold = DoubleBuilder().withProtobuf(msg.threshold(), v2, "threshold").getValue();
		if (msg.has_scale1())
			m_scale1 = DoubleBuilder().withProtobuf(msg.scale1(), v2, "scale1").getValue();
		if (msg.has_scale2())
			m_scale2 = DoubleBuilder().withProtobuf(msg.scale2(), v2, "scale2").getValue();

	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("SFC_D2: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SFC_M1 object
*/
SFC_M1::SFC_M1() { 
}

/*
	This is a 1-argument constructor to initialize a SFC_M1 object by copying another SFC_M1 object
*/
SFC_M1::SFC_M1(const SFC_M1 & /*toCopy*/)
{
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SFC_M1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_M1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	return SFCAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SFC_M1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_M1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	return SFCAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the SFC_M1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SFC_M1::Equals(const FuelAttribute *attribute) const {
	const SFC_M1 *a = dynamic_cast<const SFC_M1 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See the definition of SFC in the FuelAttribute header file
*/
double SFC_M1::SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const {
	double sfc_c2 , sfc_d1;
	flag = 0;

	boost::intrusive_ptr<ICWFGM_Fuel> c2, d1;
	sa->C2(c2);
	sa->D1(d1);

	if (c2)
		c2->SFC(FFMC, BUI, flag, overrides, &sfc_c2);
	else {
		weak_assert(false);
		sfc_c2 = 0.0;
	}
	if (d1)
		d1->SFC(FFMC, BUI, flag, overrides, &sfc_d1);
	else {
		weak_assert(false);
		sfc_d1 = 0.0;
	}

	double PC = sa->PC(overrides);
	double sfc = (PC * sfc_c2) + ((1.0 - PC) * sfc_d1);		// equation 17
	return sfc; 
}


WISE::FuelProto::SfcAttribute* SFC_M1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *attr = new WISE::FuelProto::SfcAttribute();
	attr->set_version(SFCAttribute::serialVersionUid(options));

	WISE::FuelProto::SfcM1 *msgRet = new WISE::FuelProto::SfcM1();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::SfcM1_Parms *msg = new WISE::FuelProto::SfcM1_Parms();
	msg->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_m1(msgRet);
	return attr;
}


SFC_M1 *SFC_M1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SfcM1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SfcM1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcM1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_M1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcM1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_M1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcM1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SfcM1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SfcM1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("SFC_M1: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.SfcM1.Parms", "parms");
	}
	else {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcM1", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(false);
		throw std::invalid_argument("SFC_M1: Incomplete initialization");
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SFC_O1 object
*/
SFC_O1::SFC_O1() { 
	m_fuel_load = -1.0;
}

/*
	This is a 1-argument constructor to initialize a SFC_O1 object by copying another SFC_O1 object
*/
SFC_O1::SFC_O1(const SFC_O1 & toCopy) {
	m_fuel_load = toCopy.m_fuel_load;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SFC_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_O1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SFC_O1A_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_O1B_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ62_DEFAULTS:	if (m_fuel_load == 0.35)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ15_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ31_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ32_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ33_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ44_DEFAULTS:	if (m_fuel_load == 0.2)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ30_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ45_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ46_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ53_DEFAULTS:	if (m_fuel_load == 0.8)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ40_DEFAULTS:	if (m_fuel_load == 0.4)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ41_DEFAULTS:	if (m_fuel_load == 0.3)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ43_DEFAULTS:	if (m_fuel_load == 2.0)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ47_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ50_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ56_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ57_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SFC_NZ58_DEFAULTS:	if (m_fuel_load == 1.0)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ51_DEFAULTS:	if (m_fuel_load == 3.0)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ52_DEFAULTS:	if (m_fuel_load == 2.5)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ55_DEFAULTS:	if (m_fuel_load == 1.5)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_SFC_NZ70_DEFAULTS:	if (m_fuel_load == 0.5)
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_FUELLOAD:
	case FUELCOM_ATTRIBUTE_GFL:					*attribute = m_fuel_load;
												return S_OK;
	}
	return SFCAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SFC_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_O1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_O1B_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ62_DEFAULTS:	m_fuel_load = 0.35;	// RWB: 020804: default changed to match FBP Note
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ15_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ31_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ32_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ33_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ44_DEFAULTS:	m_fuel_load = 0.2;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ30_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ45_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ46_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ53_DEFAULTS:	m_fuel_load = 0.8;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ40_DEFAULTS:	m_fuel_load = 0.4;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ41_DEFAULTS:	m_fuel_load = 0.3;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ43_DEFAULTS:	m_fuel_load = 2.0;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ47_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ50_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ56_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ57_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ58_DEFAULTS:	m_fuel_load = 1.0;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ51_DEFAULTS:	m_fuel_load = 3.0;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ52_DEFAULTS:	m_fuel_load = 2.5;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ55_DEFAULTS:	m_fuel_load = 1.5;
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ70_DEFAULTS:	m_fuel_load = 0.5;
													return S_OK;

		case FUELCOM_ATTRIBUTE_GFL:					if (attribute < 0.0)		return E_INVALIDARG;
													if (attribute > 5.0)		return E_INVALIDARG;
													m_fuel_load = attribute;
													return S_OK;
	}
	return SFCAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the SFC_O1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SFC_O1::Equals(const FuelAttribute *attribute) const {
	const SFC_O1 *a = dynamic_cast<const SFC_O1 *>(attribute);
	if (!a)
		return false;
	if (m_fuel_load != a->m_fuel_load)
		return false;
	return true;
}

/*
	See the definition of SFC in the FuelAttribute header file
*/
double SFC_O1::SFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* overrides, double /*FFMC*/, double /*BUI*/) const {
	PolymorphicAttribute gfl;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_GFL, gfl))) {
		double dgfl = std::get<double>(gfl);

		weak_assert(dgfl >= 0.0);
		weak_assert(dgfl <= 5.0);

		if (dgfl < 0.0)
			dgfl = 0.0;
		else if (dgfl > 5.0)
			dgfl = 5.0;

		return dgfl;
	}

	weak_assert(m_fuel_load >= 0.0);
	weak_assert(m_fuel_load <= 5.0);

	return m_fuel_load; 						// equation 18
}


WISE::FuelProto::SfcAttribute* SFC_O1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *attr = new WISE::FuelProto::SfcAttribute();
	attr->set_version(SFCAttribute::serialVersionUid(options));

	WISE::FuelProto::SfcO1 *msgRet = new WISE::FuelProto::SfcO1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_O1A_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_O1B_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1B);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ62_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz62);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ15_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz15);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ32_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz32);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ33_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz33);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ44_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz44);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ30_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz30);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ45_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz45);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ46_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz46);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ53_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz53);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ40_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz40);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ41_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz41);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ43_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz43);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ47_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz47);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ50_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz50);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ56_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz56);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ57_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz57);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ58_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz58);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ51_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz51);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ52_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz52);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ55_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz55);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ70_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz70);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SfcO1_Parms *msg = new WISE::FuelProto::SfcO1_Parms();
		msg->set_version(options.fileVersion());
		msg->set_allocated_fuelload(DoubleBuilder().withValue(m_fuel_load).forProtobuf(options.useVerboseFloats()));
		if (options.fileVersion() == 1) {
			std::string m_notes;
			msg->set_notes(m_notes);
		}
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_o1(msgRet);
	return attr;
}


SFC_O1 *SFC_O1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SfcO1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SfcO1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcO1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_O1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcO1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_O1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcO1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SfcO1_Parms &msg = msgRead->parms();

		if ((msg.version() != 1) && (msg.version() != 2)) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SfcO1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("SFC_O1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SfcO1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_fuelload())
			m_fuel_load = DoubleBuilder().withProtobuf(msg.fuelload(), v2, "fuelLoad").getValue();
		if (msg.version() == 1) {
			std::string m_notes;
			m_notes = msg.notes();
		}
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("SFC_O1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SFC_S1 object
*/
SFC_S1::SFC_S1() : m_cache(16) {
	m_p1_f = -1.0;
	m_p2_f = -1.0;
	m_p1_w = -1.0;
	m_p2_w = -1.0;
	m_ffc_multiplier = m_wfc_multiplier = m_sfc_multiplier = 1.0;
	m_ffc_bui_multiplier = m_wfc_bui_multiplier = 1.0;
}

/*
	This is a 1-argument constructor to initialize a SFC_S1 object by copying another SFC_S1 object
*/
SFC_S1::SFC_S1(const SFC_S1 & toCopy) : m_cache(16) {
	m_p1_f = toCopy.m_p1_f;
	m_p2_f = toCopy.m_p2_f;
	m_p1_w = toCopy.m_p1_w;
	m_p2_w = toCopy.m_p2_w;
	m_ffc_multiplier = toCopy.m_ffc_multiplier;
	m_wfc_multiplier = toCopy.m_wfc_multiplier;
	m_sfc_multiplier = toCopy.m_sfc_multiplier;
	m_ffc_bui_multiplier = toCopy.m_ffc_bui_multiplier;
	m_wfc_bui_multiplier = toCopy.m_wfc_bui_multiplier;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SFC_S1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_S1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_S1_DEFAULTS:		if ((m_p1_f == 4.0) &&
														(m_p2_f == 0.025) &&
														(m_p1_w == 4.0) &&
														(m_p2_w == 0.034) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 1.0) &&
														(m_ffc_multiplier == 1.0) &&
														(m_wfc_bui_multiplier == 1.0) &&
														(m_ffc_bui_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_S2_DEFAULTS:		if ((m_p1_f == 10.0) &&
														(m_p2_f == 0.013) &&
														(m_p1_w == 6.0) &&
														(m_p2_w == 0.060) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 1.0) &&
														(m_ffc_multiplier == 1.0) &&
														(m_wfc_bui_multiplier == 1.0) &&
														(m_ffc_bui_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_S3_DEFAULTS:		if ((m_p1_f == 12.0) &&
														(m_p2_f == 0.0166) &&
														(m_p1_w == 20.0) &&
														(m_p2_w == 0.0210) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 1.0) &&
														(m_ffc_multiplier == 1.0) &&
														(m_wfc_bui_multiplier == 1.0) &&
														(m_ffc_bui_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_NZ63_DEFAULTS:	if ((m_p1_f == 4.0) &&
														(m_p2_f == 0.025) &&
														(m_p1_w == 4.0) &&
														(m_p2_w == 0.034) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 2.5) &&
														(m_ffc_multiplier == 3.0) &&
														(m_wfc_bui_multiplier == 1.0) &&
														(m_ffc_bui_multiplier == 1.0))
														return S_OK;
													return S_FALSE;
		case FUELCOM_ATTRIBUTE_SFC_NZ64_DEFAULTS:	if ((m_p1_f == 4.0) &&
														(m_p2_f == 0.025) &&
														(m_p1_w == 4.0) &&
														(m_p2_w == 0.034) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 3.0) &&
														(m_ffc_multiplier == 4.5) &&
														(m_wfc_bui_multiplier == 1.0) &&
														(m_ffc_bui_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_NZ65_DEFAULTS:	if ((m_p1_f == 4.0) &&
														(m_p2_f == 0.025) &&
														(m_p1_w == 4.0) &&
														(m_p2_w == 0.034) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 2.0) &&
														(m_ffc_multiplier == 2.0) &&
														(m_wfc_bui_multiplier == 0.035) &&
														(m_ffc_bui_multiplier == 0.015))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_NZ66_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ71_DEFAULTS:	if ((m_p1_f == 4.0) &&
														(m_p2_f == 0.025) &&
														(m_p1_w == 4.0) &&
														(m_p2_w == 0.034) &&
														(m_sfc_multiplier == 1.0) &&
														(m_wfc_multiplier == 1.2) &&
														(m_ffc_multiplier == 1.5) &&
														(m_wfc_bui_multiplier == 1.0) &&
														(m_ffc_bui_multiplier == 1.0))
														return S_OK;
													return S_FALSE;

		case FUELCOM_ATTRIBUTE_SFC_EQ19_MULT1:		*attribute = m_p1_f;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ19_MULT2:		*attribute = m_p2_f;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ20_MULT1:		*attribute = m_p1_w;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_EQ20_MULT2:		*attribute = m_p2_w;		return S_OK;
		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		*attribute = m_sfc_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_WFC_MULTIPLIER:		*attribute = m_wfc_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_FFC_MULTIPLIER:		*attribute = m_ffc_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_WFC_BUI_MULTIPLIER:	*attribute = m_wfc_bui_multiplier; return S_OK;
		case FUELCOM_ATTRIBUTE_FFC_BUI_MULTIPLIER:	*attribute = m_ffc_bui_multiplier; return S_OK;

	}
	return SFCAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SFC_S1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SFC_S1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_SFC_S1_DEFAULTS:		m_p1_f = 4.0;
													m_p2_f = 0.025;
													m_p1_w = 4.0;
													m_p2_w = 0.034;
													m_sfc_multiplier = 1.0;
													m_wfc_multiplier = 1.0;
													m_ffc_multiplier = 1.0;
													m_wfc_bui_multiplier = 1.0;
													m_ffc_bui_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_S2_DEFAULTS:		m_p1_f = 10.0;
													m_p2_f = 0.013;
													m_p1_w = 6.0;
													m_p2_w = 0.060;
													m_sfc_multiplier = 1.0;
													m_wfc_multiplier = 1.0;
													m_ffc_multiplier = 1.0;
													m_wfc_bui_multiplier = 1.0;
													m_ffc_bui_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_S3_DEFAULTS:		m_p1_f = 12.0;
													m_p2_f = 0.0166;
													m_p1_w = 20.0;
													m_p2_w = 0.0210;
													m_sfc_multiplier = 1.0;
													m_wfc_multiplier = 1.0;
													m_ffc_multiplier = 1.0;
													m_wfc_bui_multiplier = 1.0;
													m_ffc_bui_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ63_DEFAULTS:	m_p1_f = 4.0;
													m_p2_f = 0.025;
													m_p1_w = 4.0;
													m_p2_w = 0.034;
													m_sfc_multiplier = 1.0;
													m_wfc_multiplier = 2.5;
													m_ffc_multiplier = 3.0;
													m_wfc_bui_multiplier = 1.0;
													m_ffc_bui_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ64_DEFAULTS:	m_p1_f = 4.0;
													m_p2_f = 0.025;
													m_p1_w = 4.0;
													m_p2_w = 0.034;
													m_sfc_multiplier = 1.0;
													m_wfc_multiplier = 3.0;
													m_ffc_multiplier = 4.5;
													m_wfc_bui_multiplier = 1.0;
													m_ffc_bui_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ65_DEFAULTS:	m_p1_f = 4.0;
													m_p2_f = 0.025;
													m_p1_w = 4.0;
													m_p2_w = 0.034;
													m_sfc_multiplier = 1.0;
													m_wfc_multiplier = 2.0;
													m_ffc_multiplier = 2.0;
													m_wfc_bui_multiplier = 0.035;
													m_ffc_bui_multiplier = 0.015;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_NZ66_DEFAULTS:
		case FUELCOM_ATTRIBUTE_SFC_NZ71_DEFAULTS:	m_p1_f = 4.0;
													m_p2_f = 0.025;
													m_p1_w = 4.0;
													m_p2_w = 0.034;
													m_sfc_multiplier = 1.0;
													m_wfc_multiplier = 1.2;
													m_ffc_multiplier = 1.5;
													m_wfc_bui_multiplier = 1.0;
													m_ffc_bui_multiplier = 1.0;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_MULTIPLIER:		m_sfc_multiplier = attribute;	
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_WFC_MULTIPLIER:		m_wfc_multiplier = attribute;	
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_FFC_MULTIPLIER:		m_ffc_multiplier = attribute;	
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_WFC_BUI_MULTIPLIER:	m_wfc_bui_multiplier = attribute; 
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_FFC_BUI_MULTIPLIER:	m_ffc_bui_multiplier = attribute;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ19_MULT1:		m_p1_f = attribute;
													m_cache.Clear();
													return S_OK;
								
		case FUELCOM_ATTRIBUTE_SFC_EQ19_MULT2:		m_p2_f = attribute;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ20_MULT1:		m_p1_w = attribute;
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_SFC_EQ20_MULT2:		m_p2_w = attribute;
													m_cache.Clear();
													return S_OK;
	}
	return SFCAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the SFC_S1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SFC_S1::Equals(const FuelAttribute *attribute) const {
	const SFC_S1 *a = dynamic_cast<const SFC_S1 *>(attribute);
	if (!a)
		return false;

	if (m_p1_f != a->m_p1_f)								return false;
	if (m_p2_f != a->m_p2_f)								return false;
	if (m_p1_w != a->m_p1_w)								return false;
	if (m_p2_w != a->m_p2_w)								return false;
	if (m_sfc_multiplier != a->m_sfc_multiplier)			return false;
	if (m_wfc_multiplier != a->m_wfc_multiplier)			return false;
	if (m_ffc_multiplier != a->m_ffc_multiplier)			return false;
	if (m_wfc_bui_multiplier != a->m_wfc_bui_multiplier)	return false;
	if (m_ffc_bui_multiplier != a->m_ffc_bui_multiplier)	return false;
	return true;
}

/*
	See the definition of SFC in the FuelAttribute header file
*/
double SFC_S1::SFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double /*FFMC*/, double BUI) const {
	{
		double *sfc, _sfc;
		if (sfc = m_cache.Retrieve(&BUI, &_sfc))
			return *sfc;
	}
	{
		weak_assert(m_p1_f != -1.0);
		weak_assert(m_p2_f != -1.0);
		weak_assert(m_p1_w != -1.0);
		weak_assert(m_p2_w != -1.0);
		double ffc = m_p1_f * (1.0 - exp(-m_p2_f * BUI * m_ffc_bui_multiplier));	// equation 19, 21, 23
		double wfc = m_p1_w * (1.0 - exp(-m_p2_w * BUI * m_wfc_bui_multiplier));	// equation 20, 22, 24

		ffc *= m_ffc_multiplier;
		wfc *= m_wfc_multiplier;

		double m_sfc = ffc + wfc;							// equation 25
		m_sfc *= m_sfc_multiplier;
		m_cache.Store(&BUI, &m_sfc);
		return m_sfc;
	}
}


WISE::FuelProto::SfcAttribute* SFC_S1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *attr = new WISE::FuelProto::SfcAttribute();
	attr->set_version(SFCAttribute::serialVersionUid(options));

	WISE::FuelProto::SfcS1 *msgRet = new WISE::FuelProto::SfcS1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ63_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz63);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ65_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz65);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ66_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz66);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SFC_NZ71_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz71);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SfcS1_Parms *msg = new WISE::FuelProto::SfcS1_Parms();
		msg->set_version(1);
		msg->set_allocated_p1f(DoubleBuilder().withValue(m_p1_f).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p2f(DoubleBuilder().withValue(m_p2_f).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p1w(DoubleBuilder().withValue(m_p1_w).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p2w(DoubleBuilder().withValue(m_p2_w).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_ffcmultiplier(DoubleBuilder().withValue(m_ffc_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_wfcmultiplier(DoubleBuilder().withValue(m_wfc_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_sfcmultiplier(DoubleBuilder().withValue(m_sfc_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_ffcbuimultiplier(DoubleBuilder().withValue(m_ffc_bui_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_wfcbuimultiplier(DoubleBuilder().withValue(m_wfc_bui_multiplier).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_s1(msgRet);
	return attr;
}


SFC_S1 *SFC_S1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SfcS1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SfcS1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcS1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_S1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcS1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFC_S1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcS1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SfcS1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SfcS1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("SFC_S1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SfcS1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_p1f())
			m_p1_f = DoubleBuilder().withProtobuf(msg.p1f(), v2, "p1F").getValue();
		if (msg.has_p2f())
			m_p2_f = DoubleBuilder().withProtobuf(msg.p2f(), v2, "p2F").getValue();
		if (msg.has_p1w())
			m_p1_w = DoubleBuilder().withProtobuf(msg.p1w(), v2, "p1W").getValue();
		if (msg.has_p2w())
			m_p2_w = DoubleBuilder().withProtobuf(msg.p2w(), v2, "p2W").getValue();
		if (msg.has_ffcmultiplier())
			m_ffc_multiplier = DoubleBuilder().withProtobuf(msg.ffcmultiplier(), v2, "ffcMultiplier").getValue();
		if (msg.has_wfcmultiplier())
			m_wfc_multiplier = DoubleBuilder().withProtobuf(msg.wfcmultiplier(), v2, "wfcMultiplier").getValue();
		if (msg.has_sfcmultiplier())
			m_sfc_multiplier = DoubleBuilder().withProtobuf(msg.sfcmultiplier(), v2, "sfcMultiplier").getValue();
		if (msg.has_ffcbuimultiplier())
			m_ffc_bui_multiplier = DoubleBuilder().withProtobuf(msg.ffcbuimultiplier(), v2, "ffcBuiMultiplier").getValue();
		if (msg.has_wfcbuimultiplier())
			m_wfc_bui_multiplier = DoubleBuilder().withProtobuf(msg.wfcbuimultiplier(), v2, "wfcBuiMultiplier").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("SFC_S1: Invalid default value");
		}
	}

	return this;
}
