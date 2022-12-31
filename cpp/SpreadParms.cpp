/**
 * WISE_FBP_Module: SpreadParms.cpp
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

#include "FBPFuel.h"
#include "SpreadParms.h"
#include "CWFGM_Fuel_Shared.h"
#include "doubleBuilder.h"
#include "str_printf.h"
#include "results.h"

#ifdef DEBUG
#include <cassert>
#endif


namespace sp {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::M1):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M2):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_M2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_M4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz54):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ54_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz69):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ69_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz2):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz15):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz30):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz31):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz32):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz33):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz40):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz41):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz43):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz44):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz46):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz50):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz53):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz62):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz63):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz64):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz65):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1A):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1B):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1AB):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_O1AB_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S1):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S2):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S3):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz57):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ57_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz58):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz56):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ56_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C1):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C2):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C3):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C4):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C5):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C7):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz45):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ45_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz47):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ47_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz51):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ51_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz52):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ52_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz55):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ55_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D1):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_D1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D2):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_D2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz68):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ68_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C6):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_C6_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz60):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ60_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz66):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ66_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz67):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ67_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz71):
			val = FUELCOM_ATTRIBUTE_SPREADPARMS_NZ71_DEFAULTS;
			break;


		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a no-argument constructor to initialize a SpreadParms_S1 object
*/
SpreadParms_S1::SpreadParms_S1() {
	m_a = -1.0;
	m_b = -1.0;
	m_c = -1.0;
	m_q = -1.0;
	m_bui0 = -1.0;
	m_max_be = -1.0;
}

/*
	This is a no-argument constructor to initialize a SpreadParms_C1 object
	which extends the SpreadParms_S1 constructor
*/
SpreadParms_C1::SpreadParms_C1() : SpreadParms_S1() {
	m_height = -1.0;
	m_cbh = -1.0;
	m_cfl = -1.0;
}

/*
	This is a 1-argument constructor to initialize a SpreadParms_S1 object by copying another SpreadParms_S1 object
*/
SpreadParms_S1::SpreadParms_S1(const SpreadParms_S1 &toCopy) {
	m_a = toCopy.m_a;
	m_b = toCopy.m_b;
	m_c = toCopy.m_c;
	m_q = toCopy.m_q;
	m_bui0 = toCopy.m_bui0;
	m_max_be = toCopy.m_max_be;
}

/*
	This is a 1-argument constructor to initialize a SpreadParms_C1 object by copying another SpreadParms_C1 object.
	This method extends the SpreadParms_S1 copy constructor
*/
SpreadParms_C1::SpreadParms_C1(const SpreadParms_C1 &toCopy) : SpreadParms_S1(toCopy) {
	m_height = toCopy.m_height;
	m_cbh = toCopy.m_cbh;
	m_cfl = toCopy.m_cfl;
}

/*
	This is a method to check if the SpreadParms_S1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SpreadParms_S1::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_S1 *a = dynamic_cast<const SpreadParms_S1 *>(attribute);
	if (!a)
		return false;
	if (m_a != a->m_a)						return false;
	if (m_b != a->m_b)						return false;
	if (m_c != a->m_c)						return false;
	if (m_q != a->m_q)						return false;
	if (m_bui0 != a->m_bui0)				return false;
	if (m_max_be != a->m_max_be)			return false;
	return true;
}

/*
	This is a method to check if the SpreadParms_C1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SpreadParms_C1::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_C1 *a = dynamic_cast<const SpreadParms_C1 *>(attribute);
	if (!a)
		return false;
	if (!SpreadParms_S1::Equals(attribute))
		return false;
	if (m_height != a->m_height)			return false;
	if (m_cbh != a->m_cbh)					return false;
	if (m_cfl != a->m_cfl)					return false;
	return true;
}


bool SpreadParms_C6::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_C6 *a = dynamic_cast<const SpreadParms_C6 *>(attribute);
	if (!a)
		return false;
	return SpreadParms_C1::Equals(attribute);
}


bool SpreadParms_D1::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_D1 *a = dynamic_cast<const SpreadParms_D1 *>(attribute);
	if (!a)
		return false;
	return SpreadParms_C1::Equals(attribute);
}


bool SpreadParms_NZ::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_NZ *a = dynamic_cast<const SpreadParms_NZ *>(attribute);
	if (!a)
		return false;
	return SpreadParms_C1::Equals(attribute);
}

/*
	See the definitions for these in SpreadParms.h
*/
double SpreadParms_S1::A(std::int16_t flag) const { return m_a; }
double SpreadParms_S1::B(std::int16_t flag) const { return m_b; }
double SpreadParms_S1::C(std::int16_t flag) const { return m_c; }
double SpreadParms_S1::Q() const { return m_q; }
double SpreadParms_S1::BUI0() const { return m_bui0; }
double SpreadParms_S1::MaxBE() const { return m_max_be; }
double SpreadParms_C1::Height(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute height;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_TREE_HEIGHT, height)))
		return std::get<double>(height);
	return m_height;
}
double SpreadParms_C1::CBH(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute cbh;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_CBH, cbh)))
		return std::get<double>(cbh);
	return m_cbh;
}
double SpreadParms_C1::CFL(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute cfl;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_CFL, cfl)))
		return std::get<double>(cfl);
	return m_cfl;
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_C1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsC1 *msgRet = new WISE::FuelProto::SpreadParmsC1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput())
	{
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ70_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz70);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsC1_Parms *msg = new WISE::FuelProto::SpreadParmsC1_Parms();
		msg->set_version(1);
		msg->set_allocated_a(DoubleBuilder().withValue(m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_height(DoubleBuilder().withValue(m_height).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cbh(DoubleBuilder().withValue(m_cbh).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cfl(DoubleBuilder().withValue(m_cfl).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c1(msgRet);
	return attr;
}


SpreadParms_C1 *SpreadParms_C1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsC1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsC1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsC1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_C1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsC1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_C1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsC1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsC1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsC1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_C1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsC1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_a())
			m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_height())
			m_height = DoubleBuilder().withProtobuf(msg.height(), v2, "height").getValue();
		if (msg.has_cbh())
			m_cbh = DoubleBuilder().withProtobuf(msg.cbh(), v2, "cbh").getValue();
		if (msg.has_cfl())
			m_cfl = DoubleBuilder().withProtobuf(msg.cfl(), v2, "cfl").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_C1: Invalid default value");
		}
	}

	return this;
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_S1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsS1 *msgRet = new WISE::FuelProto::SpreadParmsS1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsS1_Parms *msg = new WISE::FuelProto::SpreadParmsS1_Parms();
		msg->set_version(1);
		msg->set_allocated_a(DoubleBuilder().withValue(m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_s1(msgRet);
	return attr;
}


SpreadParms_S1 *SpreadParms_S1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsS1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsS1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsS1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_S1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsS1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_S1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsS1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsS1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsS1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_S1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsS1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_a())
			m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_S1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SpreadParms_O1 object
	which extends the SpreadParms_S1 constructor
*/
SpreadParms_O1::SpreadParms_O1() : SpreadParms_S1() {
	m_curingDegree = -1.0;
}

/*
	This is a 1-argument constructor to initialize a SpreadParms_O1 object by copying another SpreadParms_O1 object.
	This extends the SpreadParms_S1 copy constructor
*/
SpreadParms_O1::SpreadParms_O1(const SpreadParms_O1 &toCopy) : SpreadParms_S1(toCopy) {
	m_curingDegree = toCopy.m_curingDegree;
}

/*
	This is a method to check if the SpreadParms_O1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SpreadParms_O1::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_O1 *a = dynamic_cast<const SpreadParms_O1 *>(attribute);
	if (!a)
		return false;
	if (!SpreadParms_S1::Equals(attribute))
		return false;
	if (m_curingDegree != a->m_curingDegree)return false;
	return true;
}

/*
	See the definition for this in SpreadParms.h
*/
double SpreadParms_O1::CuringDegree(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute degree;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_CURINGDEGREE, degree))) {
		double d = std::get<double>(degree);

		weak_assert(d >= 0.0);
		weak_assert(d <= 1.0);

		if (d < 0.0)
			d = 0.0;
		else if (d > 1.0)
			d = 1.0;

		return d;
	}
	return m_curingDegree;
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_O1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsO1 *msgRet = new WISE::FuelProto::SpreadParmsO1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz15);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz30);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz31);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz32);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz33);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz40);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz41);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz43);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz44);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz46);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz50);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz53);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz62);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz63);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz65);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1B);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsO1_Parms *msg = new WISE::FuelProto::SpreadParmsO1_Parms();
		msg->set_version(1);
		msg->set_allocated_a(DoubleBuilder().withValue(m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_curingdegree(DoubleBuilder().withValue(m_curingDegree).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_o1(msgRet);
	return attr;
}


SpreadParms_O1 *SpreadParms_O1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsO1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsO1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsO1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_O1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsO1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_O1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsO1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsO1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsO1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_O1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsO1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_a())
			m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_curingdegree())
			m_curingDegree = DoubleBuilder().withProtobuf(msg.curingdegree(), v2, "curingDegree").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_O1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SpreadParms_O1ab object
	which extends the SpreadParms_O1 constructor
*/
SpreadParms_O1ab::SpreadParms_O1ab() : SpreadParms_O1() {
	m_o1ab_standing_a = -1.0;
	m_o1ab_standing_b = -1.0;
	m_o1ab_standing_c = -1.0;
}

/*
	This is a 1-argument constructor to initialize a SpreadParms_O1ab object by copying another SpreadParms_O1ab object.
	This extends the SpreadParms_O1 copy constructor
*/
SpreadParms_O1ab::SpreadParms_O1ab(const SpreadParms_O1ab &toCopy) : SpreadParms_O1(toCopy) {
	m_o1ab_standing_a = toCopy.m_o1ab_standing_a;
	m_o1ab_standing_b = toCopy.m_o1ab_standing_b;
	m_o1ab_standing_c = toCopy.m_o1ab_standing_c;
}

/*
	This is a method to check if the SpreadParms_O1ab object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SpreadParms_O1ab::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_O1ab *a = dynamic_cast<const SpreadParms_O1ab *>(attribute);
	if (!a)
		return false;
	if (m_o1ab_standing_a != a->m_o1ab_standing_a)						return false;
	if (m_o1ab_standing_b != a->m_o1ab_standing_b)						return false;
	if (m_o1ab_standing_c != a->m_o1ab_standing_c)						return false;
	return SpreadParms_O1::Equals(attribute);
}

/*
	See the definition for this in SpreadParms.h
*/
double SpreadParms_O1ab::A(std::int16_t flag) const {
	if (flag & USE_GRASSPHENOLOGY)
		return m_o1ab_standing_a;
	return m_a;
}

/*
	See the definition for this in SpreadParms.h
*/
double SpreadParms_O1ab::B(std::int16_t flag) const {
	if (flag & USE_GRASSPHENOLOGY)
		return m_o1ab_standing_b;
	return m_b;
}

/*
	See the definition for this in SpreadParms.h
*/
double SpreadParms_O1ab::C(std::int16_t flag) const {
	if (flag & USE_GRASSPHENOLOGY)
		return m_o1ab_standing_c;
	return m_c;
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_O1ab::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsO1ab *msgRet = new WISE::FuelProto::SpreadParmsO1ab();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz15);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz30);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz31);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz32);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz33);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz40);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz41);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz43);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz44);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz46);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz50);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz53);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz62);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz63);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz65);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1B);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsO1ab_Parms *msg = new WISE::FuelProto::SpreadParmsO1ab_Parms();
		msg->set_version(1);
		msg->set_allocated_a(DoubleBuilder().withValue(m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_curingdegree(DoubleBuilder().withValue(m_curingDegree).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_o1abstandinga(DoubleBuilder().withValue(m_o1ab_standing_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_o1abstandingb(DoubleBuilder().withValue(m_o1ab_standing_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_o1abstandingc(DoubleBuilder().withValue(m_o1ab_standing_c).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_o1ab(msgRet);
	return attr;
}


SpreadParms_O1ab *SpreadParms_O1ab::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsO1ab *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsO1ab *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsO1ab", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_O1ab: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsO1ab", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_O1ab: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsO1ab", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsO1ab_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsO1ab.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_O1ab: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsO1ab.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_a())
			m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_curingdegree())
			m_curingDegree = DoubleBuilder().withProtobuf(msg.curingdegree(), v2, "curingDegree").getValue();
		if (msg.has_o1abstandinga())
			m_o1ab_standing_a = DoubleBuilder().withProtobuf(msg.o1abstandinga(), v2, "o1AbstandingA").getValue();
		if (msg.has_o1abstandingb())
			m_o1ab_standing_b = DoubleBuilder().withProtobuf(msg.o1abstandingb(), v2, "o1AbstandingB").getValue();
		if (msg.has_o1abstandingc())
			m_o1ab_standing_c = DoubleBuilder().withProtobuf(msg.o1abstandingc(), v2, "o1AbstandingC").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_O1ab: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a SpreadParms_Mixed object
*/
SpreadParms_Mixed::SpreadParms_Mixed() {
	m_q = -1.0;
	m_bui0 = -1.0;
	m_max_be = -1.0;
	m_height = -1.0;
	m_cbh = -1.0;
	m_cfl = -1.0;
	m_pc = 0.5;
}

/*
	This is a 1-argument constructor to initialize a SpreadParms_Mixed object by copying another SpreadParms_Mixed object
*/
SpreadParms_Mixed::SpreadParms_Mixed(const SpreadParms_Mixed &toCopy) {
	m_q = toCopy.m_q;
	m_bui0 = toCopy.m_bui0;
	m_max_be = toCopy.m_max_be;
	m_height = toCopy.m_height;
	m_cbh = toCopy.m_cbh;
	m_cfl = toCopy.m_cfl;
	m_pc = toCopy.m_pc;

#ifdef _DEBUG
	weak_assert(toCopy.m_C2);
	weak_assert(toCopy.m_D1);
#endif

	toCopy.m_C2->Mutate(&m_C2);
	toCopy.m_D1->Mutate(&m_D1);

#ifdef _DEBUG
	weak_assert(m_C2);
	weak_assert(m_D1);
#endif
}

/*
	This is a method to check if the SpreadParms_Mixed object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SpreadParms_Mixed::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_Mixed *a = dynamic_cast<const SpreadParms_Mixed *>(attribute);
	if (!a)
		return false;
	if (m_q != a->m_q)						return false;
	if (m_bui0 != a->m_bui0)				return false;
	if (m_max_be != a->m_max_be)			return false;
	if (m_height != a->m_height)			return false;
	if (m_cbh != a->m_cbh)					return false;
	if (m_cfl != a->m_cfl)					return false;
	if (m_pc != a->m_pc)					return false;
	return true;
}


bool SpreadParms_MixedDead::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_MixedDead *a = dynamic_cast<const SpreadParms_MixedDead *>(attribute);
	if (!a)
		return false;
	return SpreadParms_Mixed::Equals(attribute);
}

/*
	See the definitions for these in SpreadParms.h
*/
double SpreadParms_Mixed::Q() const { return m_q; }
double SpreadParms_Mixed::BUI0() const { return m_bui0; }
double SpreadParms_Mixed::MaxBE() const { return m_max_be; }
double SpreadParms_Mixed::Height(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute height;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_TREE_HEIGHT, height)))
		return std::get<double>(height);
	return m_height;
}


double SpreadParms_Mixed::CBH(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute cbh;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_CBH, cbh)))
		return std::get<double>(cbh);	return m_cbh;
}


double SpreadParms_Mixed::CFL(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute cfl;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_CFL, cfl)))
		return std::get<double>(cfl);
	return m_cfl;
}


double SpreadParms_Mixed::PC(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute pc;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_PC, pc))) {
		double d = std::get<double>(pc);

		weak_assert(d >= 0.0);
		weak_assert(d <= 1.0);

		if (d < 0.0)
			d = 0.0;
		else if (d > 1.0)
			d = 1.0;

		return d;
	}
	return m_pc;
}


void SpreadParms_Mixed::C2(boost::intrusive_ptr<ICWFGM_Fuel> &c2) { c2 = m_C2; }


void SpreadParms_Mixed::D1(boost::intrusive_ptr<ICWFGM_Fuel> &d1) { d1 = m_D1; }


void SpreadParms_Mixed::SetC2(boost::intrusive_ptr<ICWFGM_Fuel> &c2) { m_C2 = c2; }


void SpreadParms_Mixed::SetD1(boost::intrusive_ptr<ICWFGM_Fuel> &d1) { m_D1 = d1; }


double SpreadParms_MixedDead::PC(const CCWFGM_FuelOverrides* overrides) const {
	PolymorphicAttribute pc;
	if ((overrides) && (overrides->RetrieveOverride(FUELCOM_ATTRIBUTE_PDF, pc))) {
		double d = std::get<double>(pc);

		weak_assert(d >= 0.0);
		weak_assert(d <= 1.0);

		if (d < 0.0)
			d = 0.0;
		else if (d > 1.0)
			d = 1.0;

		return d;
	}
	return m_pc;
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_Mixed::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsMixed *msgRet = new WISE::FuelProto::SpreadParmsMixed();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		WISE::FuelProto::SpreadParmsMixed_DefaultParms *msgDef = nullptr;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixed_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::M1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M2_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixed_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::M2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ54_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixed_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::Nz54);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ69_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixed_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::Nz69);
			serialized = true;
		}

		if ((msgDef) && (m_pc != 0.5)) {
			msgDef->set_allocated_pc(DoubleBuilder().withValue(m_pc * 100.0).forProtobuf(options.useVerboseFloats()));
		}

#ifdef _DEBUG
		if (!msgDef)
			weak_assert(0);
#endif
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsMixed_Parms *msg = new WISE::FuelProto::SpreadParmsMixed_Parms();
		msg->set_version(1);
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_height(DoubleBuilder().withValue(m_height).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cbh(DoubleBuilder().withValue(m_cbh).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cfl(DoubleBuilder().withValue(m_cfl).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_pc(DoubleBuilder().withValue(m_pc * 100.0).forProtobuf(options.useVerboseFloats()));

		ICWFGM_Fuel *c2 = m_C2.get();
		if (c2) {
			CCWFGM_Fuel *cc2 = dynamic_cast<CCWFGM_Fuel *>(c2);
			if (cc2)
				msg->set_allocated_c2(dynamic_cast_assert<WISE::FuelProto::CcwfgmFuel *>(cc2->serialize(options)));
		}

		ICWFGM_Fuel *d1 = m_D1.get();
		if (d1) {
			CCWFGM_Fuel *dd1 = dynamic_cast<CCWFGM_Fuel *>(d1);
			if (dd1)
				msg->set_allocated_d1(dynamic_cast_assert<WISE::FuelProto::CcwfgmFuel *>(dd1->serialize(options)));
		}
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_mixed(msgRet);
	return attr;
}


SpreadParms_Mixed *SpreadParms_Mixed::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsMixed *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsMixed *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsMixed", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_Mixed: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsMixed", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_Mixed: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsMixed", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsMixed_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsMixed.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_Mixed: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsMixed.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_height())
			m_height = DoubleBuilder().withProtobuf(msg.height(), v2, "height").getValue();
		if (msg.has_cbh())
			m_cbh = DoubleBuilder().withProtobuf(msg.cbh(), v2, "cbh").getValue();
		if (msg.has_cfl())
			m_cfl = DoubleBuilder().withProtobuf(msg.cfl(), v2, "cfl").getValue();
		if (msg.has_pc())
			m_pc = DoubleBuilder().withProtobuf(msg.pc(), v2, "pc").getValue() * 0.01;

		if (msg.has_c2()) {
			CCWFGM_Fuel *p = CCWFGM_Fuel::deserializeFuel(msg.c2(), v2, "c2");
			if (p)
				m_C2 = p;
		}

		if (msg.has_d1()) {
			CCWFGM_Fuel *p = CCWFGM_Fuel::deserializeFuel(msg.d1(), v2, "d1");
			if (p)
				m_D1 = p;
		}
	}
	else if (msgRead->has_default_()) {
		const WISE::FuelProto::SpreadParmsMixed_DefaultParms &msgDef(msgRead->default_());
		WISE::FuelProto::FuelName def = msgDef.default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_Mixed: Invalid default value");
		}

		if (msgDef.has_pc())
			m_pc = msgDef.pc().value() * 0.01;
	}

	weak_assert(m_C2);
	weak_assert(m_D1);

	return this;
}

/*
	This is a no-argument constructor to initialize a SpreadParms_Non object
*/
SpreadParms_Non::SpreadParms_Non() {
}

/*
	This is a 1-argument constructor to initialize a SpreadParms_Non object by copying another SpreadParms_Non object
*/
SpreadParms_Non::SpreadParms_Non(const SpreadParms_Non &toCopy) {
}

/*
	This is a method to check if the SpreadParms_Non object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool SpreadParms_Non::Equals(const FuelAttribute *attribute) const {
	const SpreadParms_Non *a = dynamic_cast<const SpreadParms_Non *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_Non and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_Non::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_A:
	case FUELCOM_ATTRIBUTE_B:
	case FUELCOM_ATTRIBUTE_C:
	case FUELCOM_ATTRIBUTE_MAXBE:
	case FUELCOM_ATTRIBUTE_CBH:
	case FUELCOM_ATTRIBUTE_CFL:
	case FUELCOM_ATTRIBUTE_FUELLOAD:
	case FUELCOM_ATTRIBUTE_TREE_HEIGHT:
		*attribute = 0.0;
		return S_OK;

	case FUELCOM_ATTRIBUTE_Q:
	case FUELCOM_ATTRIBUTE_BUI0:
		*attribute = 1.0;
		return S_OK;
	}
	return SpreadParmsAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	See the definitions for these in SpreadParms.h
*/
double SpreadParms_Non::A(std::int16_t flag) const { return 0.0; }
double SpreadParms_Non::B(std::int16_t flag) const { return 0.0; }
double SpreadParms_Non::C(std::int16_t flag) const { return 0.0; }
double SpreadParms_Non::Q() const { return 1.0; }
double SpreadParms_Non::BUI0() const { return 1.0; }
double SpreadParms_Non::MaxBE() const { return 0.0; }
double SpreadParms_Non::Height(const CCWFGM_FuelOverrides* /*overrides*/) const { return 0.0; }
double SpreadParms_Non::CBH(const CCWFGM_FuelOverrides* /*overrides*/) const { return 0.0; }
double SpreadParms_Non::CFL(const CCWFGM_FuelOverrides* /*overrides*/) const { return 0.0; }
double SpreadParms_Non::CuringDegree(const CCWFGM_FuelOverrides* /*overrides*/) const { return 0.0; }


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_Non::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsNon *msgRet = new WISE::FuelProto::SpreadParmsNon();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::SpreadParmsNon_Parms *msg = new WISE::FuelProto::SpreadParmsNon_Parms();
	msg->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_non(msgRet);
	return attr;
}


SpreadParms_Non *SpreadParms_Non::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsNon *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsNon *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsNon", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_Non: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsNon", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_Non: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsNon", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsNon_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsNon.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_Non: Version is invalid");
		}
	}
	else {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsNon", name, validation::error_level::SEVERE, "Deserialize.Object:Incomplete", "parms");
		weak_assert(0);
		throw std::invalid_argument("SpreadParms_Non: Incomplete initialization");
	}

	return this;
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_S1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_S1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS:
		if ((m_a == 75.0) &&
			(m_b == 0.0297) &&
			(m_c == 1.3) &&
			(m_q == 0.75) &&
			(m_bui0 == 38.0) &&
			(m_max_be == 1.460))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS:
		if ((m_a == 40.0) &&
			(m_b == 0.0438) &&
			(m_c == 1.7) &&
			(m_q == 0.75) &&
			(m_bui0 == 63.0) &&
			(m_max_be == 1.256))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS:
		if ((m_a == 55.0) &&
			(m_b == 0.0829) &&
			(m_c == 3.2) &&
			(m_q == 0.75) &&
			(m_bui0 == 31.0) &&
			(m_max_be == 1.590))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_A:
		*attribute = m_a;
		return S_OK;

	case FUELCOM_ATTRIBUTE_B:
		*attribute = m_b;
		return S_OK;

	case FUELCOM_ATTRIBUTE_C:
		*attribute = m_c;
		return S_OK;

	case FUELCOM_ATTRIBUTE_Q:
		*attribute = m_q;
		return S_OK;

	case FUELCOM_ATTRIBUTE_MAXBE:
		*attribute = m_max_be;
		return S_OK;

	case FUELCOM_ATTRIBUTE_BUI0:
		*attribute = m_bui0;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CBH:
		*attribute = 0.0;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CFL:
	case FUELCOM_ATTRIBUTE_FUELLOAD:
		*attribute = 0.0;
		return S_OK;

	case FUELCOM_ATTRIBUTE_TREE_HEIGHT:
		*attribute = 0.0;
		return S_OK;
	}
	return SpreadParmsAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_C1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ70_DEFAULTS:
		if ((m_a == 90.0) &&
			(m_b == 0.0649) &&
			(m_c == 4.5) &&
			(m_q == 0.90) &&
			(m_bui0 == 72.0) &&
			(m_max_be == 1.076) &&
			(m_height == 10.0) &&
			(m_cbh == 2.0) &&
			(m_cfl == 0.75))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
		if ((m_a == 110.0) &&
			(m_b == 0.0282) &&
			(m_c == 1.5) &&
			(m_q == 0.70) &&
			(m_bui0 == 64.0) &&
			(m_max_be == 1.321) &&
			(m_height == 7.0) &&
			(m_cbh == 3.0) &&
			(m_cfl == 0.80))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
		if ((m_a == 110.0) &&
			(m_b == 0.0444) &&
			(m_c == 3.0) &&
			(m_q == 0.75) &&
			(m_bui0 == 62.0) &&
			(m_max_be == 1.261) &&
			(m_height == 18.0) &&
			(m_cbh == 8.0) &&
			(m_cfl == 1.15))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
		if ((m_a == 110.0) &&
			(m_b == 0.0293) &&
			(m_c == 1.5) &&
			(m_q == 0.80) &&
			(m_bui0 == 66.0) &&
			(m_max_be == 1.184) &&
			(m_height == 10.0) &&
			(m_cbh == 4.0) &&
			(m_cfl == 1.20))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
		if ((m_a == 30.0) &&
			(m_b == 0.0697) &&
			(m_c == 4.0) &&
			(m_q == 0.80) &&
			(m_bui0 == 56.0) &&
			(m_max_be == 1.220) &&
			(m_height == 25.0) &&
			(m_cbh == 18.0) &&
			(m_cfl == 1.20))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		if ((m_a == 45.0) &&
			(m_b == 0.0305) &&
			(m_c == 2.0) &&
			(m_q == 0.85) &&
			(m_bui0 == 106.0) &&
			(m_max_be == 1.134) &&
			(m_height == 20.0) &&
			(m_cbh == 10.0) &&
			(m_cfl == 0.50))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_CBH:
		*attribute = m_cbh;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CFL:
	case FUELCOM_ATTRIBUTE_FUELLOAD:
		*attribute = m_cfl;
		return S_OK;

	case FUELCOM_ATTRIBUTE_TREE_HEIGHT:
		*attribute = m_height;
		return S_OK;
	}
	return SpreadParms_S1::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_C6 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_C6::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C6_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ60_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ66_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ67_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ71_DEFAULTS:
		if ((m_a == 30.0) &&
			(m_b == 0.0800) &&
			(m_c == 3.0) &&
			(m_q == 0.80) &&
			(m_bui0 == 62.0) &&
			(m_max_be == 1.197) &&
			(m_height == 14.0) &&
			(m_cbh == 7.0) &&
			(m_cfl == 1.80))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ61_DEFAULTS:
		if ((m_a == 30.0) &&
			(m_b == 0.0800) &&
			(m_c == 3.0) &&
			(m_q == 0.80) &&
			(m_bui0 == 62.0) &&
			(m_max_be == 1.197) &&
			(m_height == 14.0) &&
			(m_cbh == 7.0) &&
			(m_cfl == 1.20))
			return S_OK;
		return S_FALSE;
	}
	return SpreadParms_C1::GetAttributeValue(attributeKey, attribute);
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_C6::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsC6 *msgRet = new WISE::FuelProto::SpreadParmsC6();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C6_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ70_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz70);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ60_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz60);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ66_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz66);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ67_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz67);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ71_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz71);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsC6_Parms *msg = new WISE::FuelProto::SpreadParmsC6_Parms();
		msg->set_version(1);
		msg->set_allocated_a(DoubleBuilder().withValue(m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_height(DoubleBuilder().withValue(m_height).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cbh(DoubleBuilder().withValue(m_cbh).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cfl(DoubleBuilder().withValue(m_cfl).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c6(msgRet);
	return attr;
}


SpreadParms_C6 *SpreadParms_C6::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsC6 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsC6 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsC6", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_C6: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsC6", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_C6: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsC6", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsC6_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsC6.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_C6: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsC6.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_a())
			m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_height())
			m_height = DoubleBuilder().withProtobuf(msg.height(), v2, "height").getValue();
		if (msg.has_cbh())
			m_cbh = DoubleBuilder().withProtobuf(msg.cbh(), v2, "cbh").getValue();
		if (msg.has_cfl())
			m_cfl = DoubleBuilder().withProtobuf(msg.cfl(), v2, "cfl").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_C6: Invalid default value");
		}
	}

	return this;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_D1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_D1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_D1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_D2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ68_DEFAULTS:
		if ((m_a == 30.0) &&
			(m_b == 0.0232) &&
			(m_c == 1.6) &&
			(m_q == 0.90) &&
			(m_bui0 == 32.0) &&
			(m_max_be == 1.179) &&
			(m_height == -1.0) &&
			(m_cbh == 0.0) &&
			(m_cfl == 0.0))
			return S_OK;
		return S_FALSE;
	}
	return SpreadParms_C1::GetAttributeValue(attributeKey, attribute);
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_D1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsD1 *msgRet = new WISE::FuelProto::SpreadParmsD1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_D1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_D2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ68_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz68);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ70_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz70);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsD1_Parms *msg = new WISE::FuelProto::SpreadParmsD1_Parms();
		msg->set_version(1);
		msg->set_allocated_a(DoubleBuilder().withValue(m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_height(DoubleBuilder().withValue(m_height).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cbh(DoubleBuilder().withValue(m_cbh).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cfl(DoubleBuilder().withValue(m_cfl).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_d1(msgRet);
	return attr;
}


SpreadParms_D1 *SpreadParms_D1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsD1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsD1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsD1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_D1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsD1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_D1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsD1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsD1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsD1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_D1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsD1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_a())
			m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_height())
			m_height = DoubleBuilder().withProtobuf(msg.height(), v2, "height").getValue();
		if (msg.has_cbh())
			m_cbh = DoubleBuilder().withProtobuf(msg.cbh(), v2, "cbh").getValue();
		if (msg.has_cfl())
			m_cfl = DoubleBuilder().withProtobuf(msg.cfl(), v2, "cfl").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_D1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_NZ and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_NZ::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ45_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ47_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ51_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ52_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ55_DEFAULTS:
		if ((m_a == 82.0) &&
			(m_b == 0.1) &&
			(m_c == 1.5) &&
			(m_q == 1.0) &&
			(m_bui0 == 1.0) &&
			(m_max_be == 1.184) &&
			(m_height == 10.0) &&
			(m_cbh == 4.0) &&
			(m_cfl == 1.2))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ56_DEFAULTS:
		if ((m_a == 74.0) &&
			(m_b == 0.1) &&
			(m_c == 1.5) &&
			(m_q == 1.0) &&
			(m_bui0 == 1.0) &&
			(m_max_be == 1.184) &&
			(m_height == 10.0) &&
			(m_cbh == 4.0) &&
			(m_cfl == 1.2))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ57_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ58_DEFAULTS:
		if ((m_a == 41.0) &&
			(m_b == 0.1) &&
			(m_c == 1.5) &&
			(m_q == 1.0) &&
			(m_bui0 == 1.0) &&
			(m_max_be == 1.184) &&
			(m_height == 10.0) &&
			(m_cbh == 4.0) &&
			(m_cfl == 1.2))
			return S_OK;
		return S_FALSE;

	}
	return SpreadParms_C1::GetAttributeValue(attributeKey, attribute);
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_NZ::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsNz *msgRet = new WISE::FuelProto::SpreadParmsNz();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz64);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ70_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz70);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ45_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz45);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ47_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz47);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ51_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz51);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ52_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz52);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ55_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz55);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ56_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz56);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ57_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz57);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ58_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz58);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsNz_Parms *msg = new WISE::FuelProto::SpreadParmsNz_Parms();
		msg->set_version(1);
		msg->set_allocated_a(DoubleBuilder().withValue(m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_height(DoubleBuilder().withValue(m_height).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cbh(DoubleBuilder().withValue(m_cbh).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cfl(DoubleBuilder().withValue(m_cfl).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_nz(msgRet);
	return attr;
}


SpreadParms_NZ *SpreadParms_NZ::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsNz *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsNz *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsNz", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_NZ: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsNz", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_NZ: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsNz", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsNz_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsNz.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_NZ: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsNz.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_a())
			m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_height())
			m_height = DoubleBuilder().withProtobuf(msg.height(), v2, "height").getValue();
		if (msg.has_cbh())
			m_cbh = DoubleBuilder().withProtobuf(msg.cbh(), v2, "cbh").getValue();
		if (msg.has_cfl())
			m_cfl = DoubleBuilder().withProtobuf(msg.cfl(), v2, "cfl").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_NZ: Invalid default value");
		}
	}

	return this;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_O1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS:
		if ((m_a == 190.0) &&
			(m_b == 0.0310) &&
			(m_c == 1.4) &&
			(m_q == 1.00) &&
			(m_bui0 == 1.0) &&
			(m_max_be == 1.000) &&
			(m_curingDegree == 0.6))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS:
		if ((m_a == 250.0) &&
			(m_b == 0.0350) &&
			(m_c == 1.7) &&
			(m_q == 1.00) &&
			(m_bui0 == 1.0) &&
			(m_max_be == 1.000) &&
			(m_curingDegree == 0.6))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_O1AB_MATTED_A:
	case FUELCOM_ATTRIBUTE_O1AB_STANDING_A:
		*attribute = m_a;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_MATTED_B:
	case FUELCOM_ATTRIBUTE_O1AB_STANDING_B:
		*attribute = m_b;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_MATTED_C:
	case FUELCOM_ATTRIBUTE_O1AB_STANDING_C:
		*attribute = m_c;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CURINGDEGREE:
		*attribute = m_curingDegree;
		return S_OK;
	}
	return SpreadParms_S1::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_O1ab and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_O1ab::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS:
		if (!((m_a == 190.0) &&
			(m_b == 0.0310) &&
			(m_c == 1.4)))
			return S_FALSE;
		break;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS:
		if (!((m_o1ab_standing_a == 250.0) &&
			(m_o1ab_standing_b == 0.0350) &&
			(m_o1ab_standing_c == 1.7)))
			return S_FALSE;
		break;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1AB_DEFAULTS:
		if ((m_a == 190.0) &&
			(m_b == 0.0310) &&
			(m_c == 1.4) &&
			(m_o1ab_standing_a == 250.0) &&
			(m_o1ab_standing_b == 0.0350) &&
			(m_o1ab_standing_c == 1.7) &&
			(m_q == 1.00) &&
			(m_bui0 == 1.0) &&
			(m_max_be == 1.000) &&
			(m_curingDegree == 0.6))
			return S_OK;
		return S_FALSE;


	case FUELCOM_ATTRIBUTE_O1AB_STANDING_A:
		*attribute = m_o1ab_standing_a;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_STANDING_B:
		*attribute = m_o1ab_standing_b;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_STANDING_C:
		*attribute = m_o1ab_standing_c;
		return S_OK;
	}
	return SpreadParms_O1::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_Mixed and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_Mixed::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ54_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ69_DEFAULTS:
		if ((m_q == 0.80) &&
			(m_bui0 == 50.0) &&
			(m_max_be == 1.250) &&
			(m_height == 13.0) &&
			(m_cbh == 6.0) &&
			(m_cfl == 0.80))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_Q:
		*attribute = m_q;
		return S_OK;

	case FUELCOM_ATTRIBUTE_MAXBE:
		*attribute = m_max_be;
		return S_OK;

	case FUELCOM_ATTRIBUTE_BUI0:
		*attribute = m_bui0;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CBH:
		*attribute = m_cbh;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CFL:
	case FUELCOM_ATTRIBUTE_FUELLOAD:
		*attribute = m_cfl;
		return S_OK;

	case FUELCOM_ATTRIBUTE_TREE_HEIGHT:
		*attribute = m_height;
		return S_OK;

	case FUELCOM_ATTRIBUTE_PC:
		*attribute = m_pc;
		return S_OK;
	}
	return SpreadParmsAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a SpreadParms_MixedDead and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_MixedDead::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_PC:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_M3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M4_DEFAULTS:
		if ((m_q == 0.80) &&
			(m_bui0 == 50.0) &&
			(m_max_be == 1.250) &&
			(m_height == 10.0) &&
			(m_cbh == 6.0) &&
			(m_cfl == 0.80))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_PDF:
		*attribute = m_pc;
		return S_OK;
	}
	return SpreadParms_Mixed::GetAttributeValue(attributeKey, attribute);
}


WISE::FuelProto::SpreadParmsAttribute* SpreadParms_MixedDead::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *attr = new WISE::FuelProto::SpreadParmsAttribute();
	attr->set_version(SpreadParmsAttribute::serialVersionUid(options));

	WISE::FuelProto::SpreadParmsMixedDead *msgRet = new WISE::FuelProto::SpreadParmsMixedDead();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		WISE::FuelProto::SpreadParmsMixedDead_DefaultParms *msgDef = nullptr;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M3_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixedDead_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_M4_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixedDead_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ54_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixedDead_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::Nz54);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_SPREADPARMS_NZ69_DEFAULTS, &value) == S_OK) {
			msgDef = new WISE::FuelProto::SpreadParmsMixedDead_DefaultParms();
			msgRet->set_allocated_default_(msgDef);
			msgDef->set_default_(WISE::FuelProto::FuelName::Nz69);
			serialized = true;
		}

		if ((msgDef) && (m_pc != 0.5)) {
			msgDef->set_allocated_pdf(DoubleBuilder().withValue(m_pc * 100.0).forProtobuf(options.useVerboseFloats()));
		}

#ifdef _DEBUG
		if (!msgDef)
			weak_assert(0);
#endif

	}

	if (!serialized) {
		WISE::FuelProto::SpreadParmsMixedDead_Parms *msg = new WISE::FuelProto::SpreadParmsMixedDead_Parms();
		msg->set_version(1);
		msg->set_allocated_q(DoubleBuilder().withValue(m_q).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_bui0(DoubleBuilder().withValue(m_bui0).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_maxbe(DoubleBuilder().withValue(m_max_be).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_height(DoubleBuilder().withValue(m_height).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cbh(DoubleBuilder().withValue(m_cbh).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cfl(DoubleBuilder().withValue(m_cfl).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_pdf(DoubleBuilder().withValue(m_pc * 100.0).forProtobuf(options.useVerboseFloats()));

		ICWFGM_Fuel *c2 = m_C2.get();
		if (c2) {
			CCWFGM_Fuel *cc2 = dynamic_cast<CCWFGM_Fuel *>(c2);
			if (cc2)
				msg->set_allocated_c2(dynamic_cast_assert<WISE::FuelProto::CcwfgmFuel *>(cc2->serialize(options)));
		}
		ICWFGM_Fuel *d1 = m_D1.get();
		if (d1) {
			CCWFGM_Fuel *dd1 = dynamic_cast<CCWFGM_Fuel *>(d1);
			if (dd1)
				msg->set_allocated_d1(dynamic_cast_assert<WISE::FuelProto::CcwfgmFuel *>(dd1->serialize(options)));
		}
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_mixeddead(msgRet);
	return attr;
}


SpreadParms_MixedDead *SpreadParms_MixedDead::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::SpreadParmsMixedDead *msgRead = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsMixedDead *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsMixedDead", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_MixedDead: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsMixedDead", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("SpreadParms_MixedDead: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsMixedDead", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::SpreadParmsMixedDead_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.SpreadParmsMixedDead.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_MixedDead: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.SpreadParmsMixedDead.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_q())
			m_q = DoubleBuilder().withProtobuf(msg.q(), v2, "q").getValue();
		if (msg.has_bui0())
			m_bui0 = DoubleBuilder().withProtobuf(msg.bui0(), v2, "bui0").getValue();
		if (msg.has_maxbe())
			m_max_be = DoubleBuilder().withProtobuf(msg.maxbe(), v2, "maxBe").getValue();
		if (msg.has_height())
			m_height = DoubleBuilder().withProtobuf(msg.height(), v2, "height").getValue();
		if (msg.has_cbh())
			m_cbh = DoubleBuilder().withProtobuf(msg.cbh(), v2, "cbh").getValue();
		if (msg.has_cfl())
			m_cfl = DoubleBuilder().withProtobuf(msg.cfl(), v2, "cfl").getValue();
		if (msg.has_pdf())
			m_pc = DoubleBuilder().withProtobuf(msg.pdf(), v2, "pdf").getValue() * 0.01;

		if (msg.has_c2()) {
			CCWFGM_Fuel *p = CCWFGM_Fuel::deserializeFuel(msg.c2(), v2, "c2");
			if (p)
				m_C2 = p;
		}

		if (msg.has_d1()) {
			CCWFGM_Fuel *p = CCWFGM_Fuel::deserializeFuel(msg.d1(), v2, "d1");
			if (p)
				m_D1 = p;
		}
	}
	else if (msgRead->has_default_()) {
		const WISE::FuelProto::SpreadParmsMixedDead_DefaultParms &msgDef(msgRead->default_());
		WISE::FuelProto::FuelName def = msgDef.default_();

		uint16_t val = sp::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, "Deserialize.Enum:Invalid", std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("SpreadParms_MixedDead: Invalid default value");
		}

		if (msgDef.has_pdf())
			m_pc = msgDef.pdf().value() * 0.01;
	}

	weak_assert(m_C2);
	weak_assert(m_D1);

	return this;
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_S1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_S1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ64_DEFAULTS:
		m_a = 75.0;
		m_b = 0.0297;
		m_c = 1.3;
		m_q = 0.75;
		m_bui0 = 38.0;
		m_max_be = 1.460;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS:
		m_a = 40.0;
		m_b = 0.0438;
		m_c = 1.7;
		m_q = 0.75;
		m_bui0 = 63.0;
		m_max_be = 1.256;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS:
		m_a = 55.0;
		m_b = 0.0829;
		m_c = 3.2;
		m_q = 0.75;
		m_bui0 = 31.0;
		m_max_be = 1.590;
		return S_OK;

	case FUELCOM_ATTRIBUTE_A:
		m_a = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_B:
		m_b = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_C:
		m_c = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_Q:
		m_q = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_MAXBE:
		if (attribute < 0.0)					break;
		if (attribute > 2.0)					break;
		m_max_be = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_BUI0:
		if (attribute < 0.0)					break;
		if (attribute > 200.0)					break;
		m_bui0 = attribute;
		return S_OK;
	}
	return SpreadParmsAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_C1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ70_DEFAULTS:
		m_a = 90.0;
		m_b = 0.0649;
		m_c = 4.5;
		m_q = 0.90;
		m_bui0 = 72.0;
		m_max_be = 1.076;
		m_height = 10.0;
		m_cbh = 2.0;
		m_cfl = 0.75;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
		m_a = 110.0;
		m_b = 0.0282;
		m_c = 1.5;
		m_q = 0.70;
		m_bui0 = 64.0;
		m_max_be = 1.321;
		m_height = 7.0;
		m_cbh = 3.0;
		m_cfl = 0.80;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
		m_a = 110.0;
		m_b = 0.0444;
		m_c = 3.0;
		m_q = 0.75;
		m_bui0 = 62.0;
		m_max_be = 1.261;
		m_height = 18.0;
		m_cbh = 8.0;
		m_cfl = 1.15;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
		m_a = 110.0;
		m_b = 0.0293;
		m_c = 1.5;
		m_q = 0.80;
		m_bui0 = 66.0;
		m_max_be = 1.184;
		m_height = 10.0;
		m_cbh = 4.0;
		m_cfl = 1.20;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
		m_a = 30.0;
		m_b = 0.0697;
		m_c = 4.0;
		m_q = 0.80;
		m_bui0 = 56.0;
		m_max_be = 1.220;
		m_height = 25.0;
		m_cbh = 18.0;
		m_cfl = 1.20;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		m_a = 45.0;
		m_b = 0.0305;
		m_c = 2.0;
		m_q = 0.85;
		m_bui0 = 106.0;
		m_max_be = 1.134;
		m_height = 20.0;
		m_cbh = 10.0;
		m_cfl = 0.50;
		return S_OK;

	case FUELCOM_ATTRIBUTE_TREE_HEIGHT:
		if ((attribute < 0.0) &&
			(attribute != -1.0))				break;
		if (attribute > 50.0)					break;
		m_height = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CBH:
		if (attribute < 0.0)					break;
		if (attribute > 50.0)					break;
		m_cbh = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CFL:
		if (attribute < 0.0)					break;
		if (attribute > 5.0)					break;
		m_cfl = attribute;
		return S_OK;
	}
	return SpreadParms_S1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_C6 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_C6::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_C6_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ60_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ66_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ67_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ71_DEFAULTS:
		m_a = 30.0;
		m_b = 0.0800;
		m_c = 3.0;
		m_q = 0.80;
		m_bui0 = 62.0;
		m_max_be = 1.197;
		m_height = 14.0;
		m_cbh = 7.0;
		m_cfl = 1.80;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ61_DEFAULTS:
		m_a = 30.0;
		m_b = 0.0800;
		m_c = 3.0;
		m_q = 0.80;
		m_bui0 = 62.0;
		m_max_be = 1.197;
		m_height = 14.0;
		m_cbh = 7.0;
		m_cfl = 1.20;
		return S_OK;
	}
	return SpreadParms_C1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_D1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_D1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_D1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_D2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ68_DEFAULTS:
		m_a = 30.0;
		m_b = 0.0232;
		m_c = 1.6;
		m_q = 0.90;
		m_bui0 = 32.0;
		m_max_be = 1.179;
		m_height = -1.0;
		m_cbh = 0.0;
		m_cfl = 0.0;
		return S_OK;
	}
	return SpreadParms_C1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_NZ and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_NZ::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_C7_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ45_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ47_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ51_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ52_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ55_DEFAULTS:
		m_a = 82.0;
		m_b = 0.1;
		m_c = 1.5;
		m_q = 1.0;
		m_bui0 = 1.0;
		m_max_be = 1.184;
		m_height = 10.0;
		m_cbh = 4.0;
		m_cfl = 1.2;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ56_DEFAULTS:
		m_a = 74.0;
		m_b = 0.1;
		m_c = 1.5;
		m_q = 1.0;
		m_bui0 = 1.0;
		m_max_be = 1.184;
		m_height = 10.0;
		m_cbh = 4.0;
		m_cfl = 1.2;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ57_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ58_DEFAULTS:
		m_a = 41.0;
		m_b = 0.1;
		m_c = 1.5;
		m_q = 1.0;
		m_bui0 = 1.0;
		m_max_be = 1.184;
		m_height = 10.0;
		m_cbh = 4.0;
		m_cfl = 1.2;
		return S_OK;
	}
	return SpreadParms_C1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_O1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_S3_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS:
		m_a = 190.0;
		m_b = 0.0310;
		m_c = 1.4;
		m_q = 1.00;
		m_bui0 = 1.0;
		m_max_be = 1.000;
		m_curingDegree = 0.6;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS:
		m_a = 250.0;
		m_b = 0.0350;
		m_c = 1.7;
		m_q = 1.00;
		m_bui0 = 1.0;
		m_max_be = 1.000;
		m_curingDegree = 0.6;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_MATTED_A:
	case FUELCOM_ATTRIBUTE_O1AB_STANDING_A:
		m_a = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_MATTED_B:
	case FUELCOM_ATTRIBUTE_O1AB_STANDING_B:
		m_b = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_MATTED_C:
	case FUELCOM_ATTRIBUTE_O1AB_STANDING_C:
		m_c = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CURINGDEGREE:
		if (attribute < 0.0)					{ weak_assert(0);  break; }
		if (attribute > 1.0)					{ weak_assert(0);  break; }
		m_curingDegree = attribute;
		return S_OK;
	}
	return SpreadParms_S1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_O1ab and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_O1ab::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ31_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ32_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ33_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ40_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ41_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ15_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ30_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ43_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ44_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ46_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ50_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ53_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ62_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ63_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ65_DEFAULTS:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1A_DEFAULTS:
		m_a = 190.0;
		m_b = 0.0310;
		m_c = 1.4;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1B_DEFAULTS:
		m_o1ab_standing_a = 250.0;
		m_o1ab_standing_b = 0.0350;
		m_o1ab_standing_c = 1.7;
		return S_OK;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_O1AB_DEFAULTS:
		m_a = 190.0;
		m_b = 0.0310;
		m_c = 1.4;
		m_o1ab_standing_a = 250.0;
		m_o1ab_standing_b = 0.0350;
		m_o1ab_standing_c = 1.7;
		m_q = 1.00;
		m_bui0 = 1.0;
		m_max_be = 1.000;
		m_curingDegree = 0.6;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_STANDING_A:
		m_o1ab_standing_a = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_STANDING_B:
		m_o1ab_standing_b = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_O1AB_STANDING_C:
		m_o1ab_standing_c = attribute;
		return S_OK;
	}
	return SpreadParms_O1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_Mixed and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_Mixed::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ54_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_NZ69_DEFAULTS:
		m_q = 0.80;
		m_bui0 = 50.0;
		m_max_be = 1.250;
		m_height = 13.0;
		m_cbh = 6.0;
		m_cfl = 0.80;
		return S_OK;

	case FUELCOM_ATTRIBUTE_Q:
		m_q = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_MAXBE:
		if (attribute < 0.0)					break;
		if (attribute > 2.0)					break;
		m_max_be = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_BUI0:
		if (attribute < 0.0)					break;
		if (attribute > 200.0)					break;
		m_bui0 = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_TREE_HEIGHT:
		if ((attribute < 0.0) &&
			(attribute != -1.0))				break;
		if (attribute > 50.0)					break;
		m_height = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CBH:
		if (attribute < 0.0)					break;
		if (attribute > 50.0)					break;
		m_cbh = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_CFL:
		if (attribute < 0.0)					break;
		if (attribute > 5.0)					break;
		m_cfl = attribute;
		return S_OK;

	case FUELCOM_ATTRIBUTE_PC:
		if (attribute < 0.0)					break;
		if (attribute > 1.0)					break;
		m_pc = attribute;
		return S_OK;
	}
	return SpreadParmsAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a SpreadParms_MixedDead and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT SpreadParms_MixedDead::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_PC:
		return E_UNEXPECTED;

	case FUELCOM_ATTRIBUTE_SPREADPARMS_M3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_SPREADPARMS_M4_DEFAULTS:
		m_q = 0.80;
		m_bui0 = 50.0;
		m_max_be = 1.250;
		m_height = 10.0;
		m_cbh = 6.0;
		m_cfl = 0.80;
		return S_OK;

	case FUELCOM_ATTRIBUTE_PDF:
		if (attribute < 0.0)					break;
		if (attribute > 1.0)					break;
		m_pc = attribute;
		return S_OK;
	}
	return SpreadParms_Mixed::SetAttributeValue(attributeKey, attribute);
}
