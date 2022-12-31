/**
 * WISE_FBP_Module: lb.cpp
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

#if __has_include(<mathimf.h>)
#include <mathimf.h>
#else
#include <cmath>
#endif

#include "lb.h"
#include "doubleBuilder.h"
#include "str_printf.h"
#include "results.h"


namespace lb {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::C1):
			val = FUELCOM_ATTRIBUTE_LB_C1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C2):
			val = FUELCOM_ATTRIBUTE_LB_C2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C3):
			val = FUELCOM_ATTRIBUTE_LB_C3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C4):
			val = FUELCOM_ATTRIBUTE_LB_C4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C5):
			val = FUELCOM_ATTRIBUTE_LB_C5_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C6):
			val = FUELCOM_ATTRIBUTE_LB_C6_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C7):
			val = FUELCOM_ATTRIBUTE_LB_C7_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D1):
			val = FUELCOM_ATTRIBUTE_LB_D1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D2):
			val = FUELCOM_ATTRIBUTE_LB_D2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M1):
			val = FUELCOM_ATTRIBUTE_LB_M1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M2):
			val = FUELCOM_ATTRIBUTE_LB_M2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_LB_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_LB_M4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1A):
			val = FUELCOM_ATTRIBUTE_LB_O1A_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1B):
			val = FUELCOM_ATTRIBUTE_LB_O1B_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S1):
			val = FUELCOM_ATTRIBUTE_LB_S1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S2):
			val = FUELCOM_ATTRIBUTE_LB_S2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S3):
			val = FUELCOM_ATTRIBUTE_LB_S3_DEFAULTS;
			break;

		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a no-argument constructor to initialize a LB_C1 object
*/
LB_C1::LB_C1() : m_cache(16) { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_LB_C1_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a LB_C1 object by copying another LB_C1 object
*/
LB_C1::LB_C1(const LB_C1 & toCopy) : m_cache(16) {
	m_init = toCopy.m_init;
	m_multiplier = toCopy.m_multiplier;
	m_exp_multiplier = toCopy.m_exp_multiplier;
	m_power = toCopy.m_power;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a LB_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT LB_C1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_LB_C1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_C6_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_C7_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_D1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_D2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_M1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_M2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_M3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_M4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_S1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_S2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_LB_S3_DEFAULTS:		if ((m_init == 1.0) &&
													(m_multiplier == 8.729) &&
													(m_exp_multiplier == 0.030) &&
													(m_power == 2.155))
													return S_OK;
												return S_FALSE;

		case FUELCOM_ATTRIBUTE_LB_INIT:			*attribute = m_init;			return S_OK;
		case FUELCOM_ATTRIBUTE_LB_MULTIPLIER:		*attribute = m_multiplier;		return S_OK;
		case FUELCOM_ATTRIBUTE_LB_EXP_MULTIPLIER:	*attribute = m_exp_multiplier;		return S_OK;
		case FUELCOM_ATTRIBUTE_LB_POWER:		*attribute = m_power;			return S_OK;
	}
	return LBAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a LB_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT LB_C1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_LB_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_C2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_C4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_C7_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_D2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_M2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_M4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_S2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_S3_DEFAULTS:		m_init = 1.0;
								m_multiplier = 8.729;
								m_exp_multiplier = 0.030;
								m_power = 2.155;
													m_cache.Clear();
													return S_OK;
		case FUELCOM_ATTRIBUTE_LB_INIT:			m_init = attribute;		m_cache.Clear();return S_OK;
		case FUELCOM_ATTRIBUTE_LB_MULTIPLIER:		m_multiplier = attribute;	m_cache.Clear();return S_OK;
		case FUELCOM_ATTRIBUTE_LB_EXP_MULTIPLIER:	m_exp_multiplier = attribute;	m_cache.Clear();return S_OK;
		case FUELCOM_ATTRIBUTE_LB_POWER:		m_power = attribute;		m_cache.Clear();return S_OK;
	}
	return LBAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the LB_C1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool LB_C1::Equals(const FuelAttribute *attribute) const {
	const LB_C1 *a = dynamic_cast<const LB_C1 *>(attribute);
	if (!a)
		return false;
	if (m_init != a->m_init)						return false;
	if (m_multiplier != a->m_multiplier)			return false;
	if (m_exp_multiplier != a->m_exp_multiplier)	return false;
	if (m_power != a->m_power)						return false;
	return true;
}

/*
	This is a method to get the value of LB which is of type double and takes the following parameters:
		A WSV value of type double
*/
double LB_C1::LB(double WSV) const {
	{
		double *lb, _lb;
		if (lb = m_cache.Retrieve(&WSV, &_lb))
			return *lb;
	}
	{
		double lb = m_init + m_multiplier * pow(1.0 - exp((0.0 - m_exp_multiplier) * WSV), m_power);	// equation 79
		m_cache.Store(&WSV, &lb);
		return lb; 
	}
}


WISE::FuelProto::LbAttribute* LB_C1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::LbAttribute *attr = new WISE::FuelProto::LbAttribute();
	attr->set_version(LBAttribute::serialVersionUid(options));

	WISE::FuelProto::LbC1 *msgRet = new WISE::FuelProto::LbC1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput())
	{
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_C6_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C6);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_D1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_D2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_M1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_M2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_M3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_M4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::LbC1_Parms *msg = new WISE::FuelProto::LbC1_Parms();
		msg->set_version(1);
		msg->set_allocated_init(DoubleBuilder().withValue(m_init).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_multiplier(DoubleBuilder().withValue(m_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_expmultiplier(DoubleBuilder().withValue(m_exp_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_power(DoubleBuilder().withValue(m_power).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c1(msgRet);
	return attr;
}


LB_C1 *LB_C1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::LbC1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::LbC1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.LbC1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("LB_C1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.LbC1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("LB_C1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.LbC1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::LbC1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.LbC1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("LB_C1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.LbC1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_init())
			m_init = DoubleBuilder().withProtobuf(msg.init(), v2, "init").getValue();
		if (msg.has_multiplier())
			m_multiplier = DoubleBuilder().withProtobuf(msg.multiplier(), v2, "multiplier").getValue();
		if (msg.has_expmultiplier())
			m_exp_multiplier = DoubleBuilder().withProtobuf(msg.expmultiplier(), v2, "expMultiplier").getValue();
		if (msg.has_power())
			m_power = DoubleBuilder().withProtobuf(msg.power(), v2, "power").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = lb::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("LB_C1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a LB_O1 object
*/
LB_O1::LB_O1() : m_cache(16) { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_LB_O1A_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a LB_O1 object by copying another LB_O1 object
*/
LB_O1::LB_O1(const LB_O1 & toCopy) : m_cache(16) {
	m_init = toCopy.m_init;
	m_power = toCopy.m_power;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a LB_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT LB_O1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_LB_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_O1B_DEFAULTS:	if ((m_init == 1.1) &&
													(m_power == 0.464))
													return S_OK;
												return S_FALSE;
		case FUELCOM_ATTRIBUTE_LB_INIT:			*attribute = m_init;			return S_OK;
		case FUELCOM_ATTRIBUTE_LB_POWER:		*attribute = m_power;			return S_OK;
	}
	return LBAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a LB_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT LB_O1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_LB_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_LB_O1B_DEFAULTS:		m_init = 1.1;
								m_power = 0.464;
								m_cache.Clear();			return S_OK;
		case FUELCOM_ATTRIBUTE_LB_INIT:			m_init = attribute;	m_cache.Clear();return S_OK;
		case FUELCOM_ATTRIBUTE_LB_POWER:		m_power = attribute;	m_cache.Clear();return S_OK;
	}
	return LBAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the LB_O1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool LB_O1::Equals(const FuelAttribute *attribute) const {
	const LB_O1 *a = dynamic_cast<const LB_O1 *>(attribute);
	if (!a)
		return false;
	if (m_init != a->m_init)						return false;
	if (m_power != a->m_power)						return false;
	return true;
}

/*
	This is a method to get the value of LB which is of type double and takes the following parameters:
		A WSV value of type double
*/
double LB_O1::LB(double WSV) const { 
	{
		double *lb, _lb;
		if (lb = m_cache.Retrieve(&WSV, &_lb))
			return *lb;
	}
	{
		double lb = (WSV < 1.0) ? 1.0 : m_init * pow(WSV, m_power);	// equations 80, 81
		m_cache.Store(&WSV, &lb);									// now equations 80a, 80b in the August 2004 article
		return lb; 
	}
}


WISE::FuelProto::LbAttribute* LB_O1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::LbAttribute *attr = new WISE::FuelProto::LbAttribute();
	attr->set_version(LBAttribute::serialVersionUid(options));

	WISE::FuelProto::LbO1 *msgRet = new WISE::FuelProto::LbO1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_O1A_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_LB_O1B_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1B);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::LbO1_Parms *msg = new WISE::FuelProto::LbO1_Parms();
		msg->set_version(1);
		msg->set_allocated_init(DoubleBuilder().withValue(m_init).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_power(DoubleBuilder().withValue(m_power).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_o1(msgRet);
	return attr;
}


LB_O1 *LB_O1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::LbO1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::LbO1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.LbO1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("LB_O1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.LbO1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("LB_O1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.LbO1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::LbO1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.LbO1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("LB_O1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(valid, "CWFGM.FuelProto.LbO1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_init())
			m_init = DoubleBuilder().withProtobuf(msg.init(), v2, "init").getValue();
		if (msg.has_power())
			m_power = DoubleBuilder().withProtobuf(msg.power(), v2, "power").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = lb::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("LB_O1: Invalid default value");
		}
	}

	return this;
}
