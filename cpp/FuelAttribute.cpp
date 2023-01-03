/**
 * WISE_FBP_Module: FuelAttribute.cpp
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

#include "AccAlpha.h"
#include "rsi.h"
#include "SpreadParms.h"
#include "fmc.h"
#include "sfc.h"
#include "tfc.h"
#include "cfb.h"
#include "isf.h"
#include "lb.h"
#include "flame.h"
#include "ccwfgmFuel.pb.h"
#include "str_printf.h"
#include "results.h"


WISE::FuelProto::AccAlphaAttribute *AccAlphaAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::AccAlphaAttribute *msg = new WISE::FuelProto::AccAlphaAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


AccAlphaAttribute *AccAlphaAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::AccAlphaAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::AccAlphaAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.AccAlphaAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("AccAlphaAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.AccAlphaAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("AccAlphaAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.AccAlphaAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_ACC*>(defaults);

	AccAlphaAttribute *acc = nullptr;

	if (msg->has_alphaclosed()) {
		if (def->original && typeid(*def->original) == typeid(AccAlphaClosed)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->alphaclosed(), v, "alphaClosed");
		}
		else {
			acc = new AccAlphaClosed();
			acc = acc->deserialize(msg->alphaclosed(), v, "alphaClosed");
		}
	}
	if (msg->has_alphaopen()) {
		if (def->original && typeid(*def->original) == typeid(AccAlphaOpen)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->alphaopen(), v, "alphaOpen");
		}
		else {
			acc = new AccAlphaOpen();
			acc = acc->deserialize(msg->alphaopen(), v, "alphaOpen");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}


WISE::FuelProto::RsiAttribute *RSIAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *msg = new WISE::FuelProto::RsiAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


RSIAttribute *RSIAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::RsiAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::RsiAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("RSIAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("RSIAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_RSI*>(defaults);

	RSIAttribute *rsi = nullptr;
	if (msg->has_c1()) {
		if (def->original && typeid(*def->original) == typeid(RSI_C1)) {
			rsi = def->original;
			def->original = nullptr;
			rsi = rsi->deserialize(msg->c1(), v, "c1");
		}
		else {
			rsi = new RSI_C1();
			rsi = rsi->deserialize(msg->c1(), v, "c1");
		}
	}
	else if (msg->has_c6()) {
		if (def->original && typeid(*def->original) == typeid(RSI_C6)) {
			rsi = def->original;
			def->original = nullptr;
			rsi = rsi->deserialize(msg->c6(), v, "c6");
		}
		else {
			rsi = new RSI_C6();
			rsi = rsi->deserialize(msg->c6(), v, "c6");
		}
	}
	else if (msg->has_d2()) {
		if (def->original && typeid(*def->original) == typeid(RSI_D2)) {
			rsi = def->original;
			def->original = nullptr;
			rsi = rsi->deserialize(msg->d2(), v, "d2");
		}
		else {
			rsi = new RSI_D2();
			rsi = rsi->deserialize(msg->d2(), v, "d2");
		}
	}
	else if (msg->has_m1()) {
		if (def->original && typeid(*def->original) == typeid(RSI_M1)) {
			rsi = def->original;
			def->original = nullptr;
			return rsi->deserialize(msg->m1(), v, "m1");
		}
		else {
			rsi = new RSI_M1();
			return rsi->deserialize(msg->m1(), v, "m1");
		}
	}
	else if (msg->has_m3()) {
		if (def->original && typeid(*def->original) == typeid(RSI_M3)) {
			rsi = def->original;
			def->original = nullptr;
			rsi = rsi->deserialize(msg->m3(), v, "m3");
		}
		else {
			rsi = new RSI_M3();
			rsi = rsi->deserialize(msg->m3(), v, "m3");
		}
	}
	else if (msg->has_m4()) {
		if (def->original && typeid(*def->original) == typeid(RSI_M4)) {
			rsi = def->original;
			def->original = nullptr;
			rsi = rsi->deserialize(msg->m4(), v, "m4");
		}
		else {
			rsi = new RSI_M4();
			rsi = rsi->deserialize(msg->m4(), v, "m4");
		}
	}
	else if (msg->has_o1()) {
		if (def->original && typeid(*def->original) == typeid(RSI_O1)) {
			rsi = def->original;
			def->original = nullptr;
			rsi = rsi->deserialize(msg->o1(), v, "o1");
		}
		else {
			rsi = new RSI_O1();
			rsi = rsi->deserialize(msg->o1(), v, "o1");
		}
	}

	if (!rsi)
		weak_assert(false);
	return rsi;
}


WISE::FuelProto::SpreadParmsAttribute *SpreadParmsAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SpreadParmsAttribute *msg = new WISE::FuelProto::SpreadParmsAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


SpreadParmsAttribute *SpreadParmsAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::SpreadParmsAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::SpreadParmsAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SpreadParmsAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}
	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SpreadParmsAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SpreadParmsAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SpreadParmsAttribute", name);
	auto v = vt.lock();

	SpreadParmsAttribute *acc = nullptr;

	ISerializationData_SP *def = dynamic_cast<ISerializationData_SP *>(defaults);

	if (msg->has_c1()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_C1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
		else {
			acc = new SpreadParms_C1();
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
	}
	else if (msg->has_c6()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_C6)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c6(), v, "c6");
		}
		else {
			acc = new SpreadParms_C6();
			acc = acc->deserialize(msg->c6(), v, "c6");
		}
	}
	else if (msg->has_d1()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_D1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->d1(), v, "d1");
		}
		else {
			acc = new SpreadParms_D1();
			acc = acc->deserialize(msg->d1(), v, "d1");
		}
	}
	else if (msg->has_mixed()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_Mixed)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->mixed(), v, "mixed");
		}
		else {
			auto m = new SpreadParms_Mixed();
			acc = m;
	
			if (def) {
				m->SetC2(def->c2);
				m->SetD1(def->d1);
			}
	
			acc = acc->deserialize(msg->mixed(), v, "mixed");
		}
	}
	else if (msg->has_mixeddead()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_MixedDead)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->mixeddead(), v, "mixedDead");
		}
		else {
			auto m = new SpreadParms_MixedDead();
			acc = m;
	
			if (def) {
				m->SetC2(def->c2);
				m->SetD1(def->d1);
			}
	
			acc = acc->deserialize(msg->mixeddead(), v, "mixedDead");
		}
	}
	else if (msg->has_non()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_Non)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->non(), v, "non");
		}
		else {
			acc = new SpreadParms_Non();
			acc = acc->deserialize(msg->non(), v, "non");
		}
	}
	else if (msg->has_nz()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_NZ)) {
			acc = def->original;
			def->original = nullptr;
			return acc->deserialize(msg->nz(), v, "nz");
		}
		else {
			acc = new SpreadParms_NZ();
			acc = acc->deserialize(msg->nz(), v, "nz");
		}
	}
	else if (msg->has_o1()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_O1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
		else {
			acc = new SpreadParms_O1();
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
	}
	else if (msg->has_o1ab()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_O1ab)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->o1ab(), v, "o1ab");
		}
		else {
			acc = new SpreadParms_O1ab();
			acc = acc->deserialize(msg->o1ab(), v, "o1ab");
		}
	}
	else if (msg->has_s1()) {
		if (def->original && typeid(*def->original) == typeid(SpreadParms_S1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->s1(), v, "s1");
		}
		else {
			acc = new SpreadParms_S1();
			acc = acc->deserialize(msg->s1(), v, "s1");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}


WISE::FuelProto::FmcAttribute *FMCAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FmcAttribute *msg = new WISE::FuelProto::FmcAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


FMCAttribute *FMCAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::FmcAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::FmcAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FmcAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FMCAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FmcAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FMCAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FmcAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_FMC*>(defaults);

	FMCAttribute *acc = nullptr;

	if (msg->has_calc()) {
		if (def->original && typeid(*def->original) == typeid(FMC_Calc)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->calc(), v, "calc");
		}
		else {
			acc = new FMC_Calc();
			acc = acc->deserialize(msg->calc(), v, "calc");
		}
	}
	else if (msg->has_nocalc()) {
		if (def->original && typeid(*def->original) == typeid(FMC_NoCalc)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->nocalc(), v, "noCalc");
		}
		else {
			acc = new FMC_NoCalc();
			acc = acc->deserialize(msg->nocalc(), v, "noCalc");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}


WISE::FuelProto::SfcAttribute *SFCAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::SfcAttribute *msg = new WISE::FuelProto::SfcAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


SFCAttribute *SFCAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::SfcAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::SfcAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFCAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.SfcAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("SFCAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.SfcAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_SFC*>(defaults);

	SFCAttribute *acc = nullptr;

	if (msg->has_c1()) {
		if (def->original && typeid(*def->original) == typeid(SFC_C1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
		else {
			acc = new SFC_C1();
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
	}
	else if (msg->has_c2()) {
		if (def->original && typeid(*def->original) == typeid(SFC_C2)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c2(), v, "c2");
		}
		else {
			acc = new SFC_C2();
			acc = acc->deserialize(msg->c2(), v, "c2");
		}
	}
	else if (msg->has_c7()) {
		if (def->original && typeid(*def->original) == typeid(SFC_C7)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c7(), v, "c7");
		}
		else {
			acc = new SFC_C7();
			acc = acc->deserialize(msg->c7(), v, "c7");
		}
	}
	else if (msg->has_d2()) {
		if (def->original && typeid(*def->original) == typeid(SFC_D2)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->d2(), v, "d2");
		}
		else {
			acc = new SFC_D2();
			acc = acc->deserialize(msg->d2(), v, "d2");
		}
	}
	else if (msg->has_m1()) {
		if (def->original && typeid(*def->original) == typeid(SFC_M1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->m1(), v, "m1");
		}
		else {
			acc = new SFC_M1();
			acc = acc->deserialize(msg->m1(), v, "m1");
		}
	}
	else if (msg->has_o1()) {
		if (def->original && typeid(*def->original) == typeid(SFC_O1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
		else {
			acc = new SFC_O1();
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
	}
	else if (msg->has_s1()) {
		if (def->original && typeid(*def->original) == typeid(SFC_S1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->s1(), v, "s1");
		}
		else {
			acc = new SFC_S1();
			acc = acc->deserialize(msg->s1(), v, "s1");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}

WISE::FuelProto::TfcAttribute *TFCAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::TfcAttribute *msg = new WISE::FuelProto::TfcAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


TFCAttribute *TFCAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::TfcAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::TfcAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFCAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.TfcAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("TFCAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.TfcAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_TFC*>(defaults);

	TFCAttribute *acc = nullptr;

	if (msg->has_c1()) {
		if (def->original && typeid(*def->original) == typeid(TFC_C1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
		else {
			acc = new TFC_C1();
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
	}
	else if (msg->has_d2()) {
		if (def->original && typeid(*def->original) == typeid(TFC_D2)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->d2(), v, "d2");
		}
		else {
			acc = new TFC_D2();
			acc = acc->deserialize(msg->d2(), v, "d2");
		}
	}
	else if (msg->has_m1()) {
		if (def->original && typeid(*def->original) == typeid(TFC_M1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->m1(), v, "m1");
		}
		else {
			acc = new TFC_M1();
			acc = acc->deserialize(msg->m1(), v, "m1");
		}
	}
	else if (msg->has_o1()) {
		if (def->original && typeid(*def->original) == typeid(TFC_O1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
		else {
			acc = new TFC_O1();
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}


WISE::FuelProto::CfbAttribute *CFBAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::CfbAttribute *msg = new WISE::FuelProto::CfbAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


CFBAttribute *CFBAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::CfbAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::CfbAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CfbAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("CFBAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CfbAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("CFBAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.CfbAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_CFB*>(defaults);

	CFBAttribute *acc = nullptr;

	if (msg->has_c1()) {
		if (def->original && typeid(*def->original) == typeid(CFB_C1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
		else {
			acc = new CFB_C1();
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
	}
	else if (msg->has_d2()) {
		if (def->original && typeid(*def->original) == typeid(CFB_D2)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->d2(), v, "d2");
		}
		else {
			acc = new CFB_D2();
			acc = acc->deserialize(msg->d2(), v, "d2");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}


WISE::FuelProto::IsfAttribute *ISFAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::IsfAttribute *msg = new WISE::FuelProto::IsfAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


ISFAttribute *ISFAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::IsfAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::IsfAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("ISFAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.IsfAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("ISFAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.IsfAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_ISF*>(defaults);

	ISFAttribute *acc = nullptr;

	if (msg->has_c1()) {
		if (def->original && typeid(*def->original) == typeid(ISF_C1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
		else {
			acc = new ISF_C1();
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
	}
	else if (msg->has_m1()) {
		if (def->original && typeid(*def->original) == typeid(ISF_M1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->m1(), v, "m1");
		}
		else {
			acc = new ISF_M1();
			acc = acc->deserialize(msg->m1(), v, "m1");
		}
	}
	else if (msg->has_m3m4()) {
		if (def->original && typeid(*def->original) == typeid(ISF_M3M4)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->m3m4(), v, "m3m4");
		}
		else {
			acc = new ISF_M3M4();
			acc = acc->deserialize(msg->m3m4(), v, "m3m4");
		}
	}
	else if (msg->has_o1()) {
		if (def->original && typeid(*def->original) == typeid(ISF_O1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
		else {
			acc = new ISF_O1();
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}


WISE::FuelProto::LbAttribute *LBAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::LbAttribute *msg = new WISE::FuelProto::LbAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


LBAttribute *LBAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::LbAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::LbAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.LbAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("LBAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.LbAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("LBAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.LbAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_LB*>(defaults);

	LBAttribute *acc = nullptr;

	if (msg->has_c1()) {
		if (def->original && typeid(*def->original) == typeid(LB_C1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
		else {
			acc = new LB_C1();
			acc = acc->deserialize(msg->c1(), v, "c1");
		}
	}
	else if (msg->has_o1()) {
		if (def->original && typeid(*def->original) == typeid(LB_O1)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
		else {
			acc = new LB_O1();
			acc = acc->deserialize(msg->o1(), v, "o1");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}


WISE::FuelProto::FlameLengthAttribute *FlameLengthAttribute::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FlameLengthAttribute *msg = new WISE::FuelProto::FlameLengthAttribute();
	msg->set_version(serialVersionUid(options));
	return msg;
}


FlameLengthAttribute *FlameLengthAttribute::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) {
	const WISE::FuelProto::FlameLengthAttribute *msg = dynamic_cast_assert<const WISE::FuelProto::FlameLengthAttribute *>(&proto);
	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAttribute", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FlameLengthAttribute: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msg->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAttribute", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FlameLengthAttribute: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FlameLengthAttribute", name);
	auto v = vt.lock();

	auto def = dynamic_cast<ISerializationData_FL*>(defaults);

	FlameLengthAttribute *acc = nullptr;

	if (msg->has_alexander82()) {
		if (def->original && typeid(*def->original) == typeid(FlameLength_Alexander82)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->alexander82(), v, "alexander82");
		}
		else {
			acc = new FlameLength_Alexander82();
			acc = acc->deserialize(msg->alexander82(), v, "alexander82");
		}
	}
	else if (msg->has_alexander82tree()) {
		if (def->original && typeid(*def->original) == typeid(FlameLength_Alexander82_Tree)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->alexander82tree(), v, "alexander82Tree");
		}
		else {
			acc = new FlameLength_Alexander82_Tree();
			acc = acc->deserialize(msg->alexander82tree(), v, "alexander82Tree");
		}
	}
	else if (msg->has_other()) {
		if (def->original && typeid(*def->original) == typeid(FlameLength_Other)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->other(), v, "other");
		}
		else {
			acc = new FlameLength_Other();
			acc = acc->deserialize(msg->other(), v, "other");
		}
	}
	else if (msg->has_tree()) {
		if (def->original && typeid(*def->original) == typeid(FlameLength_Tree)) {
			acc = def->original;
			def->original = nullptr;
			acc = acc->deserialize(msg->tree(), v, "tree");
		}
		else {
			acc = new FlameLength_Tree();
			acc = acc->deserialize(msg->tree(), v, "tree");
		}
	}

	if (!acc)
		weak_assert(false);
	return acc;
}
