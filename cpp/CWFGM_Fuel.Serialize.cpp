/**
 * WISE_FBP_Module: CWFGM_Fuel.Serialize.cpp
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

#if !defined(__INTEL_COMPILER) && !defined(__INTEL_LLVM_COMPILER) && defined(_MSC_VER)
#pragma managed(push, off)
#endif

#include "FBPFuel.h"

#include "CWFGM_Fuel_Shared.h"
#include "WTime.h"
#include "results.h"
#include "GridCom_ext.h"

#ifdef DEBUG
#include <cassert>
#endif

#if !defined(__INTEL_COMPILER) && !defined(__INTEL_LLVM_COMPILER) && defined(_MSC_VER)
#pragma managed(pop)
#endif


struct _fuelMap {
	const _GUID *guid;
	const WISE::FuelProto::FuelName protoName;
	const char* name;
};


const static struct _fuelMap fuelMap[]{
	{ &CLSID_CWFGM_Fuel_C1, WISE::FuelProto::FuelName::C1, "C1" },
	{ &CLSID_CWFGM_Fuel_C2, WISE::FuelProto::FuelName::C2, "C2" },
	{ &CLSID_CWFGM_Fuel_C3, WISE::FuelProto::FuelName::C3, "C3" },
	{ &CLSID_CWFGM_Fuel_C4, WISE::FuelProto::FuelName::C4, "C4"  },
	{ &CLSID_CWFGM_Fuel_C5, WISE::FuelProto::FuelName::C5, "C5"  },
	{ &CLSID_CWFGM_Fuel_C6, WISE::FuelProto::FuelName::C6, "C6"  },
	{ &CLSID_CWFGM_Fuel_C7, WISE::FuelProto::FuelName::C7, "C7"  },

	{ &CLSID_CWFGM_Fuel_D1, WISE::FuelProto::FuelName::D1, "D1" },
	{ &CLSID_CWFGM_Fuel_D2, WISE::FuelProto::FuelName::D2, "D2" },
	{ &CLSID_CWFGM_Fuel_D1D2, WISE::FuelProto::FuelName::D1D2, "D1D2" },

	{ &CLSID_CWFGM_Fuel_M1, WISE::FuelProto::FuelName::M1, "M1" },
	{ &CLSID_CWFGM_Fuel_M2, WISE::FuelProto::FuelName::M2, "M2" },
	{ &CLSID_CWFGM_Fuel_M1M2, WISE::FuelProto::FuelName::M1M2, "M1M2" },

	{ &CLSID_CWFGM_Fuel_M3, WISE::FuelProto::FuelName::M3, "M3" },
	{ &CLSID_CWFGM_Fuel_M4, WISE::FuelProto::FuelName::M4, "M4" },
	{ &CLSID_CWFGM_Fuel_M3M4, WISE::FuelProto::FuelName::M3M4, "M3M4" },

	{ &CLSID_CWFGM_Fuel_S1, WISE::FuelProto::FuelName::S1, "S1" },
	{ &CLSID_CWFGM_Fuel_S2, WISE::FuelProto::FuelName::S2, "S2" },
	{ &CLSID_CWFGM_Fuel_S3, WISE::FuelProto::FuelName::S3, "S3" },

	{ &CLSID_CWFGM_Fuel_O1a, WISE::FuelProto::FuelName::O1A, "O1A"  },
	{ &CLSID_CWFGM_Fuel_O1b, WISE::FuelProto::FuelName::O1B, "O1B"  },
	{ &CLSID_CWFGM_Fuel_O1ab, WISE::FuelProto::FuelName::O1AB, "O1AB"  },

	{ &CLSID_CWFGM_Fuel_Non, WISE::FuelProto::FuelName::Non, "Non" },

	{ &CLSID_CWFGM_Fuel_NZ2, WISE::FuelProto::FuelName::Nz2, "Nz2" },

	{ &CLSID_CWFGM_Fuel_NZ15, WISE::FuelProto::FuelName::Nz15, "Nz15" },

	{ &CLSID_CWFGM_Fuel_NZ30, WISE::FuelProto::FuelName::Nz30, "Nz30" },
	{ &CLSID_CWFGM_Fuel_NZ31, WISE::FuelProto::FuelName::Nz31, "Nz31" },
	{ &CLSID_CWFGM_Fuel_NZ32, WISE::FuelProto::FuelName::Nz32, "Nz32" },
	{ &CLSID_CWFGM_Fuel_NZ33, WISE::FuelProto::FuelName::Nz33, "Nz33" },

	{ &CLSID_CWFGM_Fuel_NZ40, WISE::FuelProto::FuelName::Nz40, "Nz40" },
	{ &CLSID_CWFGM_Fuel_NZ41, WISE::FuelProto::FuelName::Nz41, "Nz41" },
	{ &CLSID_CWFGM_Fuel_NZ43, WISE::FuelProto::FuelName::Nz43, "Nz43" },
	{ &CLSID_CWFGM_Fuel_NZ44, WISE::FuelProto::FuelName::Nz44, "Nz44" },
	{ &CLSID_CWFGM_Fuel_NZ45, WISE::FuelProto::FuelName::Nz45, "Nz45" },
	{ &CLSID_CWFGM_Fuel_NZ46, WISE::FuelProto::FuelName::Nz46, "Nz46" },
	{ &CLSID_CWFGM_Fuel_NZ47, WISE::FuelProto::FuelName::Nz47, "Nz47" },

	{ &CLSID_CWFGM_Fuel_NZ50, WISE::FuelProto::FuelName::Nz50, "Nz50" },
	{ &CLSID_CWFGM_Fuel_NZ51, WISE::FuelProto::FuelName::Nz51, "Nz51" },
	{ &CLSID_CWFGM_Fuel_NZ52, WISE::FuelProto::FuelName::Nz52, "Nz52" },
	{ &CLSID_CWFGM_Fuel_NZ53, WISE::FuelProto::FuelName::Nz53, "Nz53" },
	{ &CLSID_CWFGM_Fuel_NZ54, WISE::FuelProto::FuelName::Nz54, "Nz54" },
	{ &CLSID_CWFGM_Fuel_NZ55, WISE::FuelProto::FuelName::Nz55, "Nz55" },
	{ &CLSID_CWFGM_Fuel_NZ56, WISE::FuelProto::FuelName::Nz56, "Nz56" },
	{ &CLSID_CWFGM_Fuel_NZ57, WISE::FuelProto::FuelName::Nz57, "Nz57" },
	{ &CLSID_CWFGM_Fuel_NZ58, WISE::FuelProto::FuelName::Nz58, "Nz58" },

	{ &CLSID_CWFGM_Fuel_NZ60, WISE::FuelProto::FuelName::Nz60, "Nz60" },
	{ &CLSID_CWFGM_Fuel_NZ61, WISE::FuelProto::FuelName::Nz61, "Nz61" },
	{ &CLSID_CWFGM_Fuel_NZ62, WISE::FuelProto::FuelName::Nz62, "Nz62" },
	{ &CLSID_CWFGM_Fuel_NZ63, WISE::FuelProto::FuelName::Nz63, "Nz63" },
	{ &CLSID_CWFGM_Fuel_NZ64, WISE::FuelProto::FuelName::Nz64, "Nz64" },
	{ &CLSID_CWFGM_Fuel_NZ65, WISE::FuelProto::FuelName::Nz65, "Nz65" },
	{ &CLSID_CWFGM_Fuel_NZ66, WISE::FuelProto::FuelName::Nz66, "Nz66" },
	{ &CLSID_CWFGM_Fuel_NZ67, WISE::FuelProto::FuelName::Nz67, "Nz67" },
	{ &CLSID_CWFGM_Fuel_NZ68, WISE::FuelProto::FuelName::Nz68, "Nz68" },
	{ &CLSID_CWFGM_Fuel_NZ69, WISE::FuelProto::FuelName::Nz69, "Nz69" },

	{ &CLSID_CWFGM_Fuel_NZ70, WISE::FuelProto::FuelName::Nz70, "Nz70" },
	{ &CLSID_CWFGM_Fuel_NZ71, WISE::FuelProto::FuelName::Nz71, "Nz71" },

	{ nullptr, WISE::FuelProto::FuelName::unset, ""}
};


const char* ICWFGM_FBPFuel::FuelNameToChar(WISE::FuelProto::FuelName fuelname) {
	const _fuelMap* f = fuelMap;
	while (f->guid) {
		if (fuelname == f->protoName)
			return f->name;
		f++;
	}
	return "";
}


const char* ICWFGM_FBPFuel::GUIDToChar(_GUID fuelguid) {
	const _fuelMap* f = fuelMap;
	while (f->guid) {
		if (!memcmp(&fuelguid, f->guid, sizeof(_GUID)))
			return f->name;
		f++;
	}
	return "";
}


const _GUID* ICWFGM_FBPFuel::FuelNameToGUID(WISE::FuelProto::FuelName fuelname) {
	const _fuelMap* f = fuelMap;
	while (f->guid) {
		if (fuelname == f->protoName)
			return f->guid;
		f++;
	}
	return f->guid;
}


WISE::FuelProto::FuelName ICWFGM_FBPFuel::GUIDToFuelName(_GUID fuelguid) {
	const _fuelMap* f = fuelMap;
	while (f->guid) {
		if (!memcmp(&fuelguid, f->guid, sizeof(_GUID)))
			return f->protoName;
		f++;
	}
	return WISE::FuelProto::FuelName::unset;
}


std::int32_t CCWFGM_Fuel::serialVersionUid(const SerializeProtoOptions& options) const noexcept {
	return options.fileVersion();
}


google::protobuf::Message* CCWFGM_Fuel::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::CcwfgmFuel *msg = new WISE::FuelProto::CcwfgmFuel();
	msg->set_version(options.fileVersion());										// 2 adds default specification, color, name, fbp name, comments, flags from the wrapper object in Project, though
																					// serialization of those items remain in Project
	_GUID clsID;
	GetCLSID(&clsID);

	const _fuelMap *f = nullptr;

	if (!options.useVerboseOutput()) {
		f = fuelMap;
		while (f->guid) {
			if (!memcmp(&clsID, f->guid, sizeof(_GUID)))
				break;
			f++;
		}
	}

	if (f && f->guid) {
		msg->set_readonly(f->protoName);
	}
	else {
		GetDefaultCLSID(&clsID);
		SerializeFuelData fuelData;
		boost::intrusive_ptr<ICWFGM_Fuel> fuel0;
		FromCLSID(clsID, &fuel0);
		if (fuel0)
			fuelData.defaultFuel = &dynamic_cast<CCWFGM_Fuel*>(fuel0.get())->m_fuel;
		else
			fuelData.defaultFuel = nullptr;

		f = fuelMap;
		while (f->guid) {
			if (!memcmp(&clsID, f->guid, sizeof(_GUID)))
				break;
			f++;
		}
		if (f->guid)
			fuelData.defaultFuelType = f->protoName;
		else
			fuelData.defaultFuelType = WISE::FuelProto::unset;

		WISE::FuelProto::CcwfgmFuel_FuelData *data = new WISE::FuelProto::CcwfgmFuel_FuelData();
		msg->set_allocated_data(data);
		data->set_name(m_name);
		data->set_allocated_fuel(dynamic_cast<WISE::FuelProto::FbpFuel *>(m_fuel.serialize(options, &fuelData)));
		if (options.clearDirty())
			m_bRequiresSave = false;
	}
	return msg;
}


CCWFGM_Fuel *CCWFGM_Fuel::deserializeFuel(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::CcwfgmFuel *msg = dynamic_cast_assert<const WISE::FuelProto::CcwfgmFuel *>(&proto);

	if (!msg) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CcwfgmFuel", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("CWFGM.FuelProto.CwfgmFuel: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}
	if ((msg->version() != 1) && (msg->version() != 2)) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CcwfgmFuel", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("CWFGM.FuelProto.CwfgmFuel: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.CcwfgmFuel", name);
	auto v = vt.lock();

	if (msg->msg_case() == WISE::FuelProto::CcwfgmFuel::MsgCase::kReadonly) {
		WISE::FuelProto::FuelName fn = msg->readonly();
		const _fuelMap *f = fuelMap;
		while (f->guid) {
			if (fn == f->protoName)
				break;
			f++;
		}

		if (f->guid) {
			boost::intrusive_ptr<ICWFGM_Fuel> val;
			FromCLSID(*f->guid, &val);
			ICWFGM_Fuel *ptr = val.detach();
			if (!ptr) {
				/// <summary>
				/// The COM object could not be instantiated.
				/// </summary>
				/// <type>internal</type>
				if (v)
					v->add_child_validation("CWFGM.FuelProto.CcwfgmFuel", "readonly", validation::error_level::SEVERE, validation::id::cannot_allocate, "CLSID_CWFGM_Fuel");
			}
			CCWFGM_Fuel *retval = dynamic_cast<CCWFGM_Fuel *>(ptr);
			return retval;
		}
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.CcwfgmFuel", "readonly", validation::error_level::SEVERE, validation::id::enum_invalid, "CLSID_CWFGM_Fuel");
		}
	}
	else if (msg->msg_case() == WISE::FuelProto::CcwfgmFuel::MsgCase::kData) {
		boost::intrusive_ptr<ICWFGM_Fuel> val;

		WISE::FuelProto::FuelName fn = msg->data().fuel().defaultfueltype();
		const _fuelMap *f = fuelMap;
		while (f->guid) {
			if (fn == f->protoName)
				break;
			f++;
		}

		if (f->guid) {
			boost::intrusive_ptr<ICWFGM_Fuel> def_val;
			FromCLSID(*f->guid, &def_val);
			if (def_val.get())
				def_val->Mutate(&val);
			else {
				if (v)
					v->add_child_validation("CWFGM.FuelProto.CcwfgmFuel", "defaultFuelType", validation::error_level::SEVERE, validation::id::enum_invalid, "CLSID_CWFGM_Fuel");
			}
		}

		if (val.get()) {
			ICWFGM_Fuel *ptr = val.detach();
			CCWFGM_Fuel *retval = dynamic_cast<CCWFGM_Fuel *>(ptr);
			if (retval) {
				if (!msg->data().name().length()) {
					if (v)
						/// <summary>
						/// The scenario's name (to identify the output) is missing.
						/// </summary>
						/// <type>user</type>
						v->add_child_validation("string", "name", validation::error_level::SEVERE, validation::id::missing_name, msg->data().name());
				}
				retval->m_name = msg->data().name();
				retval->m_fuel.deserialize(msg->data().fuel(), v, "fuel");
			}
			return retval;
		}
	}
	weak_assert(false);
	return nullptr;
}
