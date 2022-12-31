/**
 * WISE_FBP_Module: isf.cpp
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

#include "isf.h"
#include "FBPFuel.h"
#include "doubleBuilder.h"
#include "str_printf.h"
#include "results.h"

#ifdef DEBUG
#include <assert.h>
#endif


namespace isf {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::O1A):
			val = FUELCOM_ATTRIBUTE_ISF_O1A_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1B):
			val = FUELCOM_ATTRIBUTE_ISF_O1B_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS;
			break;

		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a method to get the isf_c1 value of type double and takes the following parameters:
		A 'a' value of type double
		A 'b' value of type double
		A 'c' value of type double
		A RSF value of type double
		A CF value of type double
*/
static double isf_c1(double a, double b, double c, double RSF, double CF) {
	double isf;
	if ((a != 0.0) && (b != 0.0) && (c != 0.0) && (RSF != 0.0)) {
								// avoid divide by zero's and unnecessary calc's 
		double temp = 1.0 - pow(RSF / a / CF, 1.0 / c);
		if (temp < 0.01)
			isf = 4.6051701859880913680359829093687 / b;		// ln(0.01) / -b : equation 41b & 43b, August 2004 article
		else
			isf = log(temp) / (-b);	// equation 41a & 43a, August 2004 article
	}
	else
		isf = 0.0;
	return isf; 
}

/*
	This is a no-argument constructor to initialize a ISF_C1 object
*/
ISF_C1::ISF_C1() { 
}

/*
	This is a 1-argument constructor to initialize a ISF_C1 object by copying another ISF_C1 object
*/
ISF_C1::ISF_C1(const ISF_C1 & /*toCopy*/) {
}

/*
	This is a method to check if the ISF_C1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool ISF_C1::Equals(const FuelAttribute *attribute) const {
	const ISF_C1 *a = dynamic_cast<const ISF_C1 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See the definition for this in isf.h
*/
double ISF_C1::ISF(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double RSF_C2, double /*RSF_D1*/, double /*SF*/, double /*ISZ*/) const {
	return isf_c1(sa->A(flag), sa->B(flag), sa->C(flag), RSF_C2, 1.0);
}


WISE::FuelProto::IsfAttribute* ISF_C1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::IsfAttribute *attr = new WISE::FuelProto::IsfAttribute();
	attr->set_version(ISFAttribute::serialVersionUid(options));

	WISE::FuelProto::IsfC1 *msgRet = new WISE::FuelProto::IsfC1();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::IsfC1_Parms *msg = new WISE::FuelProto::IsfC1_Parms();
	msg->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_c1(msgRet);
	return attr;
}


ISF_C1 *ISF_C1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::IsfC1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::IsfC1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfC1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("ISF_C1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfC1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("ISF_C1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.IsfC1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::IsfC1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.IsfC1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("ISF_C1: Version is invalid");
		}
	}
	else {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfC1", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw std::invalid_argument("ISF_C1: Incomplete initialization");
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a ISF_M1 object
*/
ISF_M1::ISF_M1() {
}

/*
	This is a 1-argument constructor to initialize a ISF_M1 object by copying another ISF_M1 object
*/
ISF_M1::ISF_M1(const ISF_M1 & /*toCopy*/) {
}

/*
	This is a method to check if the ISF_M1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool ISF_M1::Equals(const FuelAttribute *attribute) const {
	const ISF_M1 *a = dynamic_cast<const ISF_M1 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See the definition for this in isf.h
*/
double ISF_M1::ISF(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double RSF_C2, double RSF_D1, double SF, double ISZ) const {
								// parm is PC, the percentage (0-1) of the fuel type that is C1

	boost::intrusive_ptr<ICWFGM_Fuel> c2, d1;
	sa->C2(c2);
	sa->D1(d1);
	double PC = sa->PC(overrides);
	double c2Value, d1Value, newisf;
	if (c2)
		c2->ISF(RSF_C2, SF, ISZ, 0, overrides, &c2Value);
	else {

    #ifdef DEBUG
		weak_assert(0);
    #endif

		c2Value = 0.0;
	}
	if (d1)
		d1->ISF(RSF_D1, SF, ISZ, 0, overrides, &d1Value);
	else {

    #ifdef DEBUG
		weak_assert(0);
    #endif

		d1Value = 0.0;
	}
	newisf = PC * c2Value + (1.0 - PC) * d1Value;		// equation 42a, FBP note
	return newisf; 
}


WISE::FuelProto::IsfAttribute* ISF_M1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::IsfAttribute *attr = new WISE::FuelProto::IsfAttribute();
	attr->set_version(ISFAttribute::serialVersionUid(options));

	WISE::FuelProto::IsfM1 *msgRet = new WISE::FuelProto::IsfM1();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::IsfM1_Parms *msg = new WISE::FuelProto::IsfM1_Parms();
	msg->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_m1(msgRet);
	return attr;
}


ISF_M1 *ISF_M1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::IsfM1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::IsfM1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfM1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("ISF_M1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfM1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("ISF_M1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.IsfM1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::IsfM1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.IsfM1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("ISF_M1: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.IsfM1.Parms", "parms");
	}
	else {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfM1", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw std::invalid_argument("ISF_M1: Incomplete initialization");
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a ISF_M3M4 object
*/
ISF_M3M4::ISF_M3M4() {
	SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a ISF_M3M4 object by copying another ISF_M3M4 object
*/
ISF_M3M4::ISF_M3M4(const ISF_M3M4 & toCopy) {
	m_m_a = toCopy.m_m_a;
	m_m_b = toCopy.m_m_b;
	m_m_c = toCopy.m_m_c;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a ISF_M3M4 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT ISF_M3M4::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS:
		if ((m_m_a == 120.0) &&
				(m_m_b == 0.0572) &&
				(m_m_c == 1.4))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS:
		if ((m_m_a == 100.0) &&
				(m_m_b == 0.0404) &&
				(m_m_c == 1.48))
			return S_OK;
		return S_FALSE;

	case FUELCOM_ATTRIBUTE_M3M4_C2_A:
		*attribute = m_m_a;
		return S_OK;
	case FUELCOM_ATTRIBUTE_M3M4_C2_B:
		*attribute = m_m_b;
		return S_OK;
	case FUELCOM_ATTRIBUTE_M3M4_C2_C:
		*attribute = m_m_c;
		return S_OK;
	case FUELCOM_ATTRIBUTE_M4_D1_A:
	case FUELCOM_ATTRIBUTE_M4_D1_B:
	case FUELCOM_ATTRIBUTE_M4_D1_C:
		return S_FALSE;
	}
	return ISFAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a ISF_M3M4 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT ISF_M3M4::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS:		m_m_a = 120.0;
							m_m_b = 0.0572;
							m_m_c = 1.4;
							return S_OK;

	case FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS:		m_m_a = 100.0;
							m_m_b = 0.0404;
							m_m_c = 1.48;
							return S_OK;

	case FUELCOM_ATTRIBUTE_M3M4_C2_A:		m_m_a = attribute;
							return S_OK;

	case FUELCOM_ATTRIBUTE_M3M4_C2_B:		m_m_b = attribute;
							return S_OK;

	case FUELCOM_ATTRIBUTE_M3M4_C2_C:		m_m_c = attribute;
							return S_OK;

	case FUELCOM_ATTRIBUTE_M4_D1_A:
	case FUELCOM_ATTRIBUTE_M4_D1_B:
	case FUELCOM_ATTRIBUTE_M4_D1_C:
		return S_FALSE;
	}
	return ISFAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the ISF_M3M4 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool ISF_M3M4::Equals(const FuelAttribute *attribute) const {
	const ISF_M3M4 *a = dynamic_cast<const ISF_M3M4 *>(attribute);
	if (!a)
		return false;
	if (m_m_a != a->m_m_a)
		return false;
	if (m_m_b != a->m_m_b)
		return false;
	if (m_m_c != a->m_m_c)
		return false;
	return true;
}

/*
	See the definition for this in isf.h
*/
double ISF_M3M4::ISF(SpreadParmsAttribute *sa, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* overrides, double RSF_C2, double RSF_D1, double SF, double ISZ) const {
								// parm is PC, the percentage (0-1) of the fuel type that is C1
	weak_assert(m_m_a != -1.0);
	weak_assert(m_m_b != -1.0);
	weak_assert(m_m_c != -1.0);

	double c2_isf = isf_c1(m_m_a, m_m_b, m_m_c, RSF_C2, 1.0);			// equation 32, August 2004 article
	double d1_isf;

	boost::intrusive_ptr<ICWFGM_Fuel> d1;
	sa->D1(d1);

	if (d1)
		d1->ISF(RSF_D1, SF, ISZ, 0, overrides, &d1_isf);
	else {

    #ifdef DEBUG
		weak_assert(0);
    #endif

		d1_isf = 0.0;
	}

	double PDF = sa->PC(overrides);
 	double newisf = PDF * c2_isf + (1.0 - PDF) * d1_isf;			// equation 31, August 2004 article, equations 42b, 42c in the FBP update note
	return newisf;
}


WISE::FuelProto::IsfAttribute* ISF_M3M4::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::IsfAttribute *attr = new WISE::FuelProto::IsfAttribute();
	attr->set_version(ISFAttribute::serialVersionUid(options));

	WISE::FuelProto::IsfM3M4 *msgRet = new WISE::FuelProto::IsfM3M4();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput())
	{
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::IsfM3M4_Parms *msg = new WISE::FuelProto::IsfM3M4_Parms();
		msg->set_version(options.fileVersion());
		if (options.fileVersion() == 1) {
			std::string m_notes;
			msg->set_notes(m_notes);
		}
		msg->set_allocated_a(DoubleBuilder().withValue(m_m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_m_c).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_m3m4(msgRet);
	return attr;
}


ISF_M3M4 *ISF_M3M4::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::IsfM3M4 *msgRead = dynamic_cast_assert<const WISE::FuelProto::IsfM3M4 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfM3M4", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("ISF_M3M4: Protobuf object invalid");
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfM3M4", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw std::invalid_argument("ISF_M3M4: Version is invalid");
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.IsfM3M4", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::IsfM3M4_Parms &msg = msgRead->parms();
		if ((msg.version() != 1) && (msg.version() != 2)) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.IsfM3M4.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("ISF_M3M4: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.IsfM3M4.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.version() == 1) {
			std::string m_notes;
			m_notes = msg.notes();
		}
		if (msg.has_a())
			m_m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = isf::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("ISF_M3M4: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a ISF_O1 object
*/
ISF_O1::ISF_O1() { 
	m_threshold = 0.588;
	m_f1 = 0.005;
	m_f2 = 0.061;
	m_f3 = 0.176;
	m_f4 = 0.02;
}

/*
	This is a 1-argument constructor to initialize a ISF_O1 object by copying another ISF_O1 object
*/
ISF_O1::ISF_O1(const ISF_O1 & toCopy) {
	m_threshold = toCopy.m_threshold;
	m_f1 = toCopy.m_f1;
	m_f2 = toCopy.m_f2;
	m_f3 = toCopy.m_f3;
	m_f4 = toCopy.m_f4;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a ISF_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT ISF_O1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_ISF_O1A_DEFAULTS:
	case FUELCOM_ATTRIBUTE_ISF_O1B_DEFAULTS:	if ((m_threshold == 0.588) &&
													(m_f1 == 0.005) &&
													(m_f2 == 0.061) &&
													(m_f3 == 0.176) &&
													(m_f4 == 0.02))
													return S_OK;
												return S_FALSE;

		case FUELCOM_ATTRIBUTE_EQ35_THRESHOLD:		*attribute = m_threshold;	return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35A_MULT1:		*attribute = m_f1;		return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35A_MULT2:		*attribute = m_f2;		return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35B_ADDER:		*attribute = m_f3;		return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35B_MULT1:		*attribute = m_f4;		return S_OK;
	}
	return ISFAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a ISF_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT ISF_O1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_ISF_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_ISF_O1B_DEFAULTS:	m_threshold = 0.588;
								m_f1 = 0.005;
								m_f2 = 0.061;
								m_f3 = 0.176;
								m_f4 = 0.02;
								return S_OK;

		case FUELCOM_ATTRIBUTE_EQ35_THRESHOLD:		m_threshold = attribute;	return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35A_MULT1:		m_f1 = attribute;		return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35A_MULT2:		m_f2 = attribute;		return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35B_ADDER:		m_f3 = attribute;		return S_OK;
		case FUELCOM_ATTRIBUTE_EQ35B_MULT1:		m_f4 = attribute;		return S_OK;
	}
	return ISFAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the ISF_O1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool ISF_O1::Equals(const FuelAttribute *attribute) const {
	const ISF_O1 *a = dynamic_cast<const ISF_O1 *>(attribute);
	if (!a)
		return false;
	if (m_threshold != a->m_threshold)	return false;
	if (m_f1 != a->m_f1)		return false;
	if (m_f2 != a->m_f2)		return false;
	if (m_f3 != a->m_f3)		return false;
	if (m_f4 != a->m_f4)		return false;
	return true;
}

/*
	See the definition for this in isf.h
*/
double ISF_O1::ISF(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double RSF, double /*RSF_D1*/, double /*SF*/, double /*ISZ*/) const {
	// parm is C, the degree of curing for fuel types O1.
	double CF;
	double C = sa->CuringDegree(overrides);
	if (C < m_threshold)
		CF = m_f1 * (exp(m_f2 * C * 100.0) - 1.0);		// equation 35a, August 2004 article
	else	CF = m_f3 + m_f4 * ((C - m_threshold) * 100.0);		// equation 35b, August 2004 article

	if (CF == 0.0)
		return 0.0;
	else	return isf_c1(sa->A(flag), sa->B(flag), sa->C(flag), RSF, CF);
}


WISE::FuelProto::IsfAttribute* ISF_O1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::IsfAttribute *attr = new WISE::FuelProto::IsfAttribute();
	attr->set_version(ISFAttribute::serialVersionUid(options));

	WISE::FuelProto::IsfO1 *msgRet = new WISE::FuelProto::IsfO1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput())
	{
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_ISF_O1A_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_ISF_O1B_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1B);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::IsfO1_Parms *msg = new WISE::FuelProto::IsfO1_Parms();
		msg->set_version(1);
		msg->set_allocated_threshold(DoubleBuilder().withValue(m_threshold).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_f1(DoubleBuilder().withValue(m_f1).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_f2(DoubleBuilder().withValue(m_f2).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_f3(DoubleBuilder().withValue(m_f3).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_f4(DoubleBuilder().withValue(m_f4).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_o1(msgRet);
	return attr;
}


ISF_O1 *ISF_O1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::IsfO1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::IsfO1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfO1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("ISF_O1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfO1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("ISF_O1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.IsfO1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::IsfO1_Parms &msg = msgRead->parms();
		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.IsfO1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("ISF_O1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.OsfO1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_threshold())
			m_threshold = DoubleBuilder().withProtobuf(msg.threshold(), v2, "threshold").getValue();
		if (msg.has_f1())
			m_f1 = DoubleBuilder().withProtobuf(msg.f1(), v2, "f1").getValue();
		if (msg.has_f2())
			m_f2 = DoubleBuilder().withProtobuf(msg.f2(), v2, "f2").getValue();
		if (msg.has_f3())
			m_f3 = DoubleBuilder().withProtobuf(msg.f3(), v2, "f3").getValue();
		if (msg.has_f4())
			m_f4 = DoubleBuilder().withProtobuf(msg.f4(), v2, "f4").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = isf::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("ISF_O1: Invalid default value");
		}
	}

	return this;
}
