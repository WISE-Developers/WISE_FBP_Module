/**
 * WISE_FBP_Module: AccAlpha.cpp
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

#include "AccAlpha.h"
#include "doubleBuilder.h"
#include "results.h"


namespace aac {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::C1):
			val = FUELCOM_ATTRIBUTE_ACCEL_C1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C2):
			val = FUELCOM_ATTRIBUTE_ACCEL_C2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C3):
			val = FUELCOM_ATTRIBUTE_ACCEL_C3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C4):
			val = FUELCOM_ATTRIBUTE_ACCEL_C4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C5):
			val = FUELCOM_ATTRIBUTE_ACCEL_C5_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C6):
			val = FUELCOM_ATTRIBUTE_ACCEL_C6_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C7):
			val = FUELCOM_ATTRIBUTE_ACCEL_C7_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D1):
			val = FUELCOM_ATTRIBUTE_ACCEL_D1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M1):
			val = FUELCOM_ATTRIBUTE_ACCEL_M1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M2):
			val = FUELCOM_ATTRIBUTE_ACCEL_M2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_ACCEL_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_ACCEL_M4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1A):
			val = FUELCOM_ATTRIBUTE_ACCEL_O1A_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1B):
			val = FUELCOM_ATTRIBUTE_ACCEL_O1B_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S1):
			val = FUELCOM_ATTRIBUTE_ACCEL_S1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S2):
			val = FUELCOM_ATTRIBUTE_ACCEL_S2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S3):
			val = FUELCOM_ATTRIBUTE_ACCEL_S3_DEFAULTS;
			break;

		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a no-argument constructor to initialize a AccAlphaClosed object
*/
AccAlphaClosed::AccAlphaClosed() : m_cache(16) { 
	m_init = 0.115;
	m_multiplier = 18.8;
	m_power = 2.5;
	m_exp_multiplier = 8.0;
} 

/*
	This is a 1-argument constructor to initialize a AccAlphaClosed object by copying another AccAlphaClosed object
*/
AccAlphaClosed::AccAlphaClosed(const AccAlphaClosed &toCopy) : m_cache(16) {
	m_init = toCopy.m_init;
	m_multiplier = toCopy.m_multiplier;
	m_power = toCopy.m_power;
	m_exp_multiplier = toCopy.m_exp_multiplier;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a AccAlphaClosed and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT AccAlphaClosed::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_ACCEL_C2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_C3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_C4_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_C5_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_C6_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_C7_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_D1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_M1_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_M2_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_M3_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ACCEL_M4_DEFAULTS:	if ((m_init == 0.115) &&
													(m_multiplier == 18.8) &&
													(m_power == 2.5) &&
													(m_exp_multiplier == 8.0))
													return S_OK;
												return S_FALSE;

		case FUELCOM_ATTRIBUTE_ACCEL_INIT:		*attribute = m_init;		return S_OK;
		case FUELCOM_ATTRIBUTE_ACCEL_MULTIPLIER:	*attribute = m_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_ACCEL_POWER:		*attribute = m_power;		return S_OK;
		case FUELCOM_ATTRIBUTE_ACCEL_EXP_MULTIPLIER:	*attribute = m_exp_multiplier;	return S_OK;
	}
	return AccAlphaAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a AccAlphaClosed and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT AccAlphaClosed::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_ACCEL_C2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_C4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_C7_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_M2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_M4_DEFAULTS:	m_init = 0.115;
								m_multiplier = 18.8;
								m_power = 2.5;
								m_exp_multiplier = 8.0;
								m_cache.Clear();
								return S_OK;

		case FUELCOM_ATTRIBUTE_ACCEL_INIT:		m_init = attribute;		m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ACCEL_MULTIPLIER:	m_multiplier = attribute;	m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ACCEL_POWER:		m_power = attribute;		m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ACCEL_EXP_MULTIPLIER:	m_exp_multiplier = attribute;	m_cache.Clear();	return S_OK;
	}
	return AccAlphaAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the AccAlphaClosed object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool AccAlphaClosed::Equals(const FuelAttribute *attribute) const {
	const AccAlphaClosed *a = dynamic_cast<const AccAlphaClosed *>(attribute);
	if (!a)
		return false;
	if (m_init != a->m_init)						return false;
	if (m_multiplier != a->m_multiplier)			return false;
	if (m_power != a->m_power)						return false;
	if (m_exp_multiplier != a->m_exp_multiplier)	return false;
	return true;
}

/*
	See AccAlpha.h for this definition
*/
double AccAlphaClosed::AccAlpha(double CFB) const {
	double *a, aa;
	if (a = m_cache.Retrieve(&CFB, &aa))
		return *a;
	aa = m_init - m_multiplier * pow(CFB, m_power) * exp((0.0 - m_exp_multiplier) * CFB);	// equation 72
	m_cache.Store(&CFB, &aa);
	return aa; 
}

WISE::FuelProto::AccAlphaAttribute* AccAlphaClosed::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::AccAlphaAttribute *attr = new WISE::FuelProto::AccAlphaAttribute();
	attr->set_version(AccAlphaAttribute::serialVersionUid(options));

	WISE::FuelProto::AccAlphaClosed *msgRet = new WISE::FuelProto::AccAlphaClosed();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C6_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C6);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_D1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_M1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_M2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_M3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_M4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::AccAlphaClosed_Parms *msg = new WISE::FuelProto::AccAlphaClosed_Parms();
		msg->set_version(1);
		msg->set_allocated_init(DoubleBuilder().withValue(m_init).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_multiplier(DoubleBuilder().withValue(m_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_power(DoubleBuilder().withValue(m_power).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_expmultiplier(DoubleBuilder().withValue(m_exp_multiplier).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}
	
	attr->set_allocated_alphaclosed(msgRet);
	return attr;
}


AccAlphaClosed *AccAlphaClosed::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::AccAlphaClosed *msgRead = dynamic_cast_assert<const WISE::FuelProto::AccAlphaClosed *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.AccAlphaClosed", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("AccAlphaClosed: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CcwfgmFuel", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("AccAlphaClosed: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.AccAlphaClosed", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::AccAlphaClosed_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.AccAlphaClosed.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("AccAlphaClosed: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.AccAlphaClosed.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_init())
			m_init = DoubleBuilder().withProtobuf(msg.init(), v2, "init").getValue();
		if (msg.has_multiplier())
			m_multiplier = DoubleBuilder().withProtobuf(msg.multiplier(), v2, "multiplier").getValue();
		if (msg.has_power())
			m_power = DoubleBuilder().withProtobuf(msg.power(), v2, "power").getValue();
		if (msg.has_expmultiplier())
			m_exp_multiplier = DoubleBuilder().withProtobuf(msg.expmultiplier(), v2, "expMultiplier").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = aac::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
		}
	}
	return this;
}

/*
	This is a no-argument constructor to initialize a AccAlphaOpen object
*/
AccAlphaOpen::AccAlphaOpen() { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C1_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a AccAlphaOpen object by copying another AccAlphaOpen object
*/
AccAlphaOpen::AccAlphaOpen(const AccAlphaOpen & toCopy) {
	m_init = toCopy.m_init;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a AccAlphaOpen and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT AccAlphaOpen::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_ACCEL_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_O1B_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_S2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_S3_DEFAULTS:	if (m_init == 0.115)
														return S_OK;
													return S_FALSE;
		case FUELCOM_ATTRIBUTE_ACCEL_INIT:			*attribute = m_init;
													return S_OK;
	}
	return AccAlphaAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a AccAlphaOpen and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT AccAlphaOpen::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_ACCEL_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_O1B_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_S2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ACCEL_S3_DEFAULTS:	m_init = 0.115;
								return S_OK;

		case FUELCOM_ATTRIBUTE_ACCEL_INIT:		m_init = attribute;		return S_OK;
	}
	return AccAlphaAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the AccAlphaOpen object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool AccAlphaOpen::Equals(const FuelAttribute *attribute) const {
	const AccAlphaOpen *a = dynamic_cast<const AccAlphaOpen *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See AccAlpha.h for this definition
*/
double AccAlphaOpen::AccAlpha(double /*CFB*/) const { 
	return m_init;
}

WISE::FuelProto::AccAlphaAttribute* AccAlphaOpen::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::AccAlphaAttribute *attr = new WISE::FuelProto::AccAlphaAttribute();
	attr->set_version(AccAlphaAttribute::serialVersionUid(options));

	WISE::FuelProto::AccAlphaOpen *msgRet = new WISE::FuelProto::AccAlphaOpen();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_O1A_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_O1B_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1B);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ACCEL_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::AccAlphaOpen_Parms *msg = new WISE::FuelProto::AccAlphaOpen_Parms();
		msg->set_version(1);
		msg->set_allocated_init(DoubleBuilder().withValue(m_init).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_alphaopen(msgRet);
	return attr;
}


AccAlphaOpen *AccAlphaOpen::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::AccAlphaOpen *msgRead = dynamic_cast_assert<const WISE::FuelProto::AccAlphaOpen *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.AccAlphaOpen", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("AccAlphaOpen: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}
	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.AccAlphaOpen", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("AccAlphaOpen: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.AccAlphaOpen", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::AccAlphaOpen_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.AccAlphaOpen.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("AccAlphaOpen: Version is invalid");
		}
		
		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.AccAlphaOpen.Parms", "Parms");
		auto v2 = vt2.lock();

		if (msg.has_init())
			m_init = DoubleBuilder().withProtobuf(msg.init(), v2, "init").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = aac::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
		}
	}
	return this;
}
