/**
 * WISE_FBP_Module: cfb.cpp
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

#include "cfb.h"
#include "doubleBuilder.h"
#include "str_printf.h"
#include "results.h"

#ifdef DEBUG
#include <assert.h>
#endif


namespace cfb {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::C1):
			val = FUELCOM_ATTRIBUTE_CFB_C1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C2):
			val = FUELCOM_ATTRIBUTE_CFB_C2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C3):
			val = FUELCOM_ATTRIBUTE_CFB_C3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C4):
			val = FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C5):
			val = FUELCOM_ATTRIBUTE_CFB_C5_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C6):
			val = FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C7):
			val = FUELCOM_ATTRIBUTE_CFB_C7_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D1):
			val = FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M1):
			val = FUELCOM_ATTRIBUTE_CFB_M1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M2):
			val = FUELCOM_ATTRIBUTE_CFB_M2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_CFB_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_CFB_M4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1A):
			val = FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1B):
			val = FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S1):
			val = FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S2):
			val = FUELCOM_ATTRIBUTE_CFB_S2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::S3):
			val = FUELCOM_ATTRIBUTE_CFB_S3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Non):
			val = FUELCOM_ATTRIBUTE_CFB_C1_DEFAULTS;
			break;

		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a no-argument constructor to initialize a CFB_C1 object
*/
CFB_C1::CFB_C1() : m_cache(16) { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C1_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a CFB_C1 object by copying another CFB_C1 object
*/
CFB_C1::CFB_C1(const CFB_C1 & toCopy) : m_cache(16) {
	m_csi_multiplier = toCopy.m_csi_multiplier;
	m_csi_cbh_exponent = toCopy.m_csi_cbh_exponent;
	m_csi_exp_adder = toCopy.m_csi_exp_adder;
	m_csi_exp_multiplier = toCopy.m_csi_exp_multiplier;
	m_csi_power = toCopy.m_csi_power;
	m_rso_div = toCopy.m_rso_div;
	m_cfb_exp = toCopy.m_cfb_exp;
	m_cfb_possible = toCopy.m_cfb_possible;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a CFB_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT CFB_C1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_CFB_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C7_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_S2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_S3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_NON_DEFAULTS:	if ((m_csi_multiplier == 0.001) &&
														(m_csi_cbh_exponent == 1.5) &&
														(m_csi_exp_adder == 460.0) &&
														(m_csi_exp_multiplier == 25.9) &&
														(m_csi_power == 1.5) &&
														(m_rso_div == 300.0) &&
														(m_cfb_exp == 0.23)) {
														if (m_cfb_possible != ((attributeKey == FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS) ||
															(attributeKey == FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS) ||
															(attributeKey == FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS) ||
															(attributeKey == FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS) ||
															(attributeKey == FUELCOM_ATTRIBUTE_CFB_S2_DEFAULTS) ||
															(attributeKey == FUELCOM_ATTRIBUTE_CFB_S3_DEFAULTS) ||
															(attributeKey == FUELCOM_ATTRIBUTE_CFB_NON_DEFAULTS)))
															return S_OK;
													}
													return S_FALSE;
		case FUELCOM_ATTRIBUTE_CFB_CSI_MULTIPLIER:	*attribute = m_csi_multiplier;				return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_CBH_EXPONENT:	*attribute = m_csi_cbh_exponent;			return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_EXP_ADDER:		*attribute = m_csi_exp_adder;				return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_EXP_MULTIPLIER:	*attribute = m_csi_exp_multiplier;			return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_CSI_POWER:		*attribute = m_csi_power;					return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_RSO_DIV:			*attribute = m_rso_div;						return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_EXP:				*attribute = m_cfb_exp;						return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_POSSIBLE:		*attribute = (m_cfb_possible) ? 1.0 : 0.0;	return S_OK;
	}
	return CFBAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a CFB_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT CFB_C1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_CFB_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_C7_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_M4_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_S2_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_S3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_CFB_NON_DEFAULTS:	m_csi_multiplier = 0.001;
													m_csi_cbh_exponent = 1.5;
													m_csi_exp_adder = 460.0;
													m_csi_exp_multiplier = 25.9;
													m_csi_power = 1.5;
													m_rso_div = 300.0;
													m_cfb_exp = 0.23;

													m_cfb_possible = (!((attributeKey == FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS) ||
														(attributeKey == FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS) ||
														(attributeKey == FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS) ||
														(attributeKey == FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS) ||
														(attributeKey == FUELCOM_ATTRIBUTE_CFB_S2_DEFAULTS) ||
														(attributeKey == FUELCOM_ATTRIBUTE_CFB_S3_DEFAULTS)));
													m_cache.Clear();
													return S_OK;

		case FUELCOM_ATTRIBUTE_CFB_CSI_MULTIPLIER:	m_csi_multiplier = attribute;						m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_CBH_EXPONENT:	m_csi_cbh_exponent = attribute;						m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_EXP_ADDER:		m_csi_exp_adder = attribute;						m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_EXP_MULTIPLIER:	m_csi_exp_multiplier = attribute;					m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_CSI_POWER:		m_csi_power = attribute;							m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_RSO_DIV:			m_rso_div = attribute;								m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_EXP:				m_cfb_exp = attribute;								m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_CFB_POSSIBLE:		m_cfb_possible = (attribute == 0.0) ? false : true;	m_cache.Clear();	return S_OK;
	}
	return CFBAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the CFB_C1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool CFB_C1::Equals(const FuelAttribute *attribute) const {
	const CFB_C1 *a = dynamic_cast<const CFB_C1 *>(attribute);
	if (!a)
		return false;
	if (m_csi_multiplier != a->m_csi_multiplier)			return false;
	if (m_csi_cbh_exponent != a->m_csi_cbh_exponent)		return false;
	if (m_csi_exp_adder != a->m_csi_exp_adder)				return false;
	if (m_csi_exp_multiplier != a->m_csi_exp_multiplier)	return false;
	if (m_csi_power != a->m_csi_power)						return false;
	if (m_rso_div != a->m_rso_div)							return false;
	if (m_cfb_exp != a->m_cfb_exp)							return false;
	if (m_cfb_possible != a->m_cfb_possible)				return false;
	return true;
}

/*
	See cfb.h for this definition
*/
double CFB_C1::CFB(double CBH, double FMC, double SFC, double ROS, double *rso, double *csi) const {
	key c_key;
	c_key.cbh = CBH;
	c_key.fmc = FMC;
	c_key.sfc = SFC;
	c_key.ros = ROS;
	{
		result *c_result, _c_result;
		if (c_result = m_cache.Retrieve(&c_key, &_c_result)) {
			*rso = c_result->rso;
			*csi = c_result->csi;
			return c_result->cfb;
		}
	}
	{
		result c_result;
		if (CBH == 0.0)
			c_result.csi = 0.0;
		else	c_result.csi = m_csi_multiplier * pow(CBH, m_csi_cbh_exponent) * pow(m_csi_exp_adder + m_csi_exp_multiplier * FMC, m_csi_power);
									// equation 56
		if (SFC == 0.0)
			c_result.rso = 0.0;
		else
			c_result.rso = c_result.csi / m_rso_div / SFC; 	// equation 57

		if (m_cfb_possible) {
			c_result.cfb = 1.0 - exp(-m_cfb_exp * (ROS - c_result.rso));
			// equation 58
			if (c_result.cfb < 0.0)
				c_result.cfb = 0.0;
		}
		else
			c_result.cfb = 0.0;
		m_cache.Store(&c_key, &c_result);
		*rso = c_result.rso;
		*csi = c_result.csi;
		return c_result.cfb;
	}
}


WISE::FuelProto::CfbAttribute* CFB_C1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::CfbAttribute *attr = new WISE::FuelProto::CfbAttribute();
	attr->set_version(CFBAttribute::serialVersionUid(options));

	WISE::FuelProto::CfbC1 *msgRet = new WISE::FuelProto::CfbC1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C5_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C5);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C6_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C6);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_C7_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C7);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_D1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_M4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1A_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_O1B_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1B);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_S1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S1);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_S2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S2);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_S3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::S3);
			serialized = true;
		}
		else if (GetAttributeValue(FUELCOM_ATTRIBUTE_CFB_NON_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Non);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::CfbC1_Parms *msg = new WISE::FuelProto::CfbC1_Parms();
		msg->set_version(1);
		msg->set_allocated_csimultiplier(DoubleBuilder().withValue(m_csi_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_csicbhexponent(DoubleBuilder().withValue(m_csi_cbh_exponent).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_csiexpadder(DoubleBuilder().withValue(m_csi_exp_adder).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_csiexpmultiplier(DoubleBuilder().withValue(m_csi_exp_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_csipower(DoubleBuilder().withValue(m_csi_power).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_rsodiv(DoubleBuilder().withValue(m_rso_div).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_cfbexp(DoubleBuilder().withValue(m_cfb_exp).forProtobuf(options.useVerboseFloats()));
		msg->set_cfbpossible(m_cfb_possible);
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c1(msgRet);
	return attr;
}


CFB_C1 *CFB_C1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::CfbC1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::CfbC1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CfbC1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("CFB_C1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CfbC1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("CFB_C1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.CfbC1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::CfbC1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.CfbC1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("CFB_C1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.CfbC1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_csimultiplier())
			m_csi_multiplier = DoubleBuilder().withProtobuf(msg.csimultiplier(), v2, "csiMultiplier").getValue();
		if (msg.has_csicbhexponent())
			m_csi_cbh_exponent = DoubleBuilder().withProtobuf(msg.csicbhexponent(), v2, "csiCbhExponent").getValue();
		if (msg.has_csiexpadder())
			m_csi_exp_adder = DoubleBuilder().withProtobuf(msg.csiexpadder(), v2, "csiExpAdder").getValue();
		if (msg.has_csiexpmultiplier())
			m_csi_exp_multiplier = DoubleBuilder().withProtobuf(msg.csiexpmultiplier(), v2, "csiExpMultiplier").getValue();
		if (msg.has_csipower())
			m_csi_power = DoubleBuilder().withProtobuf(msg.csipower(), v2, "csiPower").getValue();
		if (msg.has_rsodiv())
			m_rso_div = DoubleBuilder().withProtobuf(msg.rsodiv(), v2, "rsoDiv").getValue();
		if (msg.has_cfbexp())
			m_cfb_exp = DoubleBuilder().withProtobuf(msg.cfbexp(), v2, "cfbExp").getValue();
		m_cfb_possible = msg.cfbpossible();
	}
	else {
		const WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = cfb::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			weak_assert(0);
			throw std::invalid_argument("CFB_C1: Invalid default value");
		}
	}
	return this;
}


/*
	This is a no-argument constructor to initialize a CFB_D2 object
*/
CFB_D2::CFB_D2() {
}

/*
	This is a 1-argument constructor to initialize a CFB_D2 object by copying another CFB_D2 object
*/
CFB_D2::CFB_D2(const CFB_D2 & /*toCopy*/) {
}

/*
	This is a method to check if the CFB_D2 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool CFB_D2::Equals(const FuelAttribute *attribute) const {
	const CFB_D2 *a = dynamic_cast<const CFB_D2 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See cfb.h for this definition
*/
double CFB_D2::CFB(double /*CBH*/, double /*FMC*/, double /*SFC*/, double /*ROS*/, double *rso, double *csi) const {
	*rso = 0.0;
	*csi = 0.0;
	return 0.0;
}

WISE::FuelProto::CfbAttribute* CFB_D2::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::CfbAttribute *attr = new WISE::FuelProto::CfbAttribute();
	attr->set_version(CFBAttribute::serialVersionUid(options));

	WISE::FuelProto::CfbD2 *msgRet = new WISE::FuelProto::CfbD2();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::CfbD2_Parms *msg = new WISE::FuelProto::CfbD2_Parms();
	msg->set_version(1);

	msgRet->set_allocated_parms(msg);

	attr->set_allocated_d2(msgRet);
	return attr;
}


CFB_D2 *CFB_D2::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::CfbD2 *msgRead = dynamic_cast_assert<const WISE::FuelProto::CfbD2 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CfbD2", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("CFB_D2: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CfbD2", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("CFB_D2: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.CfbD2", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::CfbD2_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.CfbD2.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("CFB_D2: Version is invalid");
		}
	}
	else {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.CfbD2", name, validation::error_level::SEVERE, "Deserialize.Object:Incomplete", "parms");
		weak_assert(0);
		throw std::invalid_argument("CFB_D2: Incomplete initialization");
	}

	return this;
}
