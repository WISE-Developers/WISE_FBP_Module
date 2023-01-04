/**
 * WISE_FBP_Module: tfc.cpp
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

#include "tfc.h"
#include "FBPFuel.h"
#include "str_printf.h"
#include "results.h"


namespace tfc {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a no-argument constructor to initialize a TFC_C1 object
*/
TFC_C1::TFC_C1() { 
}

/*
	This is a 1-argument constructor to initialize a TFC_C1 object by copying another TFC_C1 object
*/
TFC_C1::TFC_C1(const TFC_C1 & /*toCopy*/)
{
}

/*
	This is a destructor method for a TFC_C1 object
*/
TFC_C1::~TFC_C1() {
}

/*
	This is a method to check if the TFC_C1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool TFC_C1::Equals(const FuelAttribute *attribute) const {
	const TFC_C1 *a = dynamic_cast<const TFC_C1 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See tfc.h for this definition
*/
double TFC_C1::TFC(SpreadParmsAttribute *sa, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* overrides, double CFB, double SFC, double *CFC) const {
	*CFC = sa->CFL(overrides) * CFB;			// equation 66
	double tfc = SFC + (*CFC);		// equation 67
	return tfc; 
}


WISE::FuelProto::TfcAttribute* TFC_C1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::TfcAttribute *attr = new WISE::FuelProto::TfcAttribute();
	attr->set_version(TFCAttribute::serialVersionUid(options));

	WISE::FuelProto::TfcC1_Parms *msg = new WISE::FuelProto::TfcC1_Parms();
	msg->set_version(serialVersionUid(options));

	WISE::FuelProto::TfcC1 *msgRet = new WISE::FuelProto::TfcC1();
	msgRet->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_c1(msgRet);
	return attr;
}


TFC_C1 *TFC_C1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::TfcC1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::TfcC1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcC1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_C1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcC1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_C1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.TfcC1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::TfcC1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.TfcC1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("TFC_C1: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.TfcC1.Parms", "parms");
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = tfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("TFC_C1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a TFC_D2 object
*/
TFC_D2::TFC_D2() {
}

/*
	This is a 1-argument constructor to initialize a TFC_D2 object by copying another TFC_D2 object
*/
TFC_D2::TFC_D2(const TFC_D2 & /*toCopy*/)
{
}

/*
	This is a method to check if the TFC_D2 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool TFC_D2::Equals(const FuelAttribute *attribute) const {
	const TFC_D2 *a = dynamic_cast<const TFC_D2 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See tfc.h for this definition
*/
double TFC_D2::TFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double /*CFB*/, double SFC, double* CFC) const {
	*CFC = 0.0;
	return SFC;
}


WISE::FuelProto::TfcAttribute* TFC_D2::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::TfcAttribute *attr = new WISE::FuelProto::TfcAttribute();
	attr->set_version(TFCAttribute::serialVersionUid(options));

	WISE::FuelProto::TfcD2_Parms *msg = new WISE::FuelProto::TfcD2_Parms();
	msg->set_version(serialVersionUid(options));

	WISE::FuelProto::TfcD2 *msgRet = new WISE::FuelProto::TfcD2();
	msgRet->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_d2(msgRet);
	return attr;
}


TFC_D2 *TFC_D2::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::TfcD2 *msgRead = dynamic_cast_assert<const WISE::FuelProto::TfcD2 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcD2", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_D2: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcD2", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_D2: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.TfcD2", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::TfcD2_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.TfcD2.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("TFC_D2: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.TfcD2.Parms", "parms");
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = tfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("TFC_D2: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a TFC_M1 object
*/
TFC_M1::TFC_M1() { 
}

/*
	This is a 1-argument constructor to initialize a TFC_M1 object by copying another TFC_M1 object
*/
TFC_M1::TFC_M1(const TFC_M1 & /*toCopy*/)
{
}

/*
	This is a method to check if the TFC_M1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool TFC_M1::Equals(const FuelAttribute *attribute) const {
	const TFC_M1 *a = dynamic_cast<const TFC_M1 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See tfc.h for this definition
*/
double TFC_M1::TFC(SpreadParmsAttribute *sa, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* overrides, double CFB, double SFC, double *CFC) const {
	*CFC = sa->CFL(overrides) * CFB * sa->PC(overrides);			// equation 66 ( with mods for m1, m2 )
	double tfc = SFC + (*CFC);		// equation 67
	return tfc; 
}


WISE::FuelProto::TfcAttribute* TFC_M1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::TfcAttribute *attr = new WISE::FuelProto::TfcAttribute();
	attr->set_version(TFCAttribute::serialVersionUid(options));

	WISE::FuelProto::TfcM1_Parms *msg = new WISE::FuelProto::TfcM1_Parms();
	msg->set_version(serialVersionUid(options));

	WISE::FuelProto::TfcM1 *msgRet = new WISE::FuelProto::TfcM1();
	msgRet->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_m1(msgRet);
	return attr;
}


TFC_M1 *TFC_M1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::TfcM1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::TfcM1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcM1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_M1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcM1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_M1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.TfcM1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::TfcM1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.TfcM1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("TFC_M1: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.TfcM1.Parms", "parms");
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = tfc::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(false);
			throw std::invalid_argument("TFC_M1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a TFC_O1 object
*/
TFC_O1::TFC_O1() { 
}

/*
	This is a 1-argument constructor to initialize a TFC_O1 object by copying another TFC_O1 object
*/
TFC_O1::TFC_O1(const TFC_O1 & /*toCopy*/)
{
}

/*
	This is a method to check if the TFC_O1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool TFC_O1::Equals(const FuelAttribute *attribute) const {
	const TFC_O1 *a = dynamic_cast<const TFC_O1 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See tfc.h for this definition
*/
double TFC_O1::TFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double /*CFB*/, double SFC, double* CFC) const {
	*CFC = 0.0;
	return SFC; 
}


WISE::FuelProto::TfcAttribute* TFC_O1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::TfcAttribute *attr = new WISE::FuelProto::TfcAttribute();
	attr->set_version(TFCAttribute::serialVersionUid(options));

	WISE::FuelProto::TfcO1_Parms *msg = new WISE::FuelProto::TfcO1_Parms();
	msg->set_version(serialVersionUid(options));

	WISE::FuelProto::TfcO1 *msgRet = new WISE::FuelProto::TfcO1();
	msgRet->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_o1(msgRet);
	return attr;
}


TFC_O1 *TFC_O1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::TfcO1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::TfcO1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcO1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_O1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcO1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFC_O1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.TfcO1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::TfcO1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.TfcO1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("TFC_O1: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.TfcO1.Parms", "parms");
	}
	else {
		const WISE::FuelProto::FuelName &def = msgRead->default_();

		uint16_t val = tfc::GetDefaultValue(def);

		SetAttributeValue(val, 0.0);
	}

	return this;
}
