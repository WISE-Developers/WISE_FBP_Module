/**
 * WISE_FBP_Module: RSI.cpp
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

#include "rsi.h"
#include "FBPFuel.h"
#include "doubleBuilder.h"
#include "str_printf.h"
#include "results.h"

#include <assert.h>


namespace rsi {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::C6):
			val = FUELCOM_ATTRIBUTE_RSI_C6_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D2):
			val = FUELCOM_ATTRIBUTE_RSI_D2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::O1A):
			val = FUELCOM_ATTRIBUTE_RSI_O1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::Nz70):
			val = FUELCOM_ATTRIBUTE_RSI_NZ70_DEFAULTS;
			break;

		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	See the definition for this in rsi.h
*/
double RSI_StdCalc::_rsi(double a, double b, double c, double ISI) const {
	if (a == 0.0)
		return 0.0;					// for non-fuels - just short-cut calculation of rsi
	key c_key;
	c_key.a = a;
	c_key.b = b;
	c_key.c = c;
	c_key.ISI = ISI;
	{
		double *rsi, _rsi;
		if (rsi = m_cache.Retrieve(&c_key, &_rsi))
			return *rsi;
	}
	{
		double rsi;
		double tempBasic = 1.0 - exp((0.0 - b) * ISI);
		if (tempBasic < 0.0)
			tempBasic = 0.0;
		double tempPower = pow(tempBasic, c);
		rsi = a * tempPower;	// equation 26
		m_cache.Store(&c_key, &rsi);
		return rsi;
	}
}

/*
	This is a no-argument constructor to initialize a RSI_C1 object
*/
RSI_C1::RSI_C1() { 
}

/*
	This is a 1-argument constructor to initialize a RSI_C1 object by copying another RSI_C1 object
*/
RSI_C1::RSI_C1(const RSI_C1 & /*toCopy*/) {
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_C1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	return RSIAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_C1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_C1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	return RSIAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_C1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_C1::Equals(const FuelAttribute *attribute) const {
	const RSI_C1 *a = dynamic_cast<const RSI_C1 *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See the definition for this in rsi.h
*/
double RSI_C1::RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double /*FMC*/, double /*BUI*/, double /*FFMC*/, double BE,
    double *rsi_c2, double *rsi_d1) const {
	double rsi = _rsi(sa->A(flag), sa->B(flag), sa->C(flag), ISI);
	if (flag & USE_BUI) 
		rsi *= BE;
	*rsi_d1 = *rsi_c2 = rsi;
	return rsi;
}


WISE::FuelProto::RsiAttribute* RSI_C1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiC1 *msgRet = new WISE::FuelProto::RsiC1();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::RsiC1_Parms *msg = new WISE::FuelProto::RsiC1_Parms();
	msg->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_c1(msgRet);
	return attr;
}


RSI_C1 *RSI_C1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiC1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiC1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiC1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_C1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiC1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_C1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiC1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiC1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiC1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_C1: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.RsiC1.Parms", "parms");
	}
	else {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiC1", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw std::invalid_argument("RSI_C1: Incomplete initialization");
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a RSI_C6 object
*/
RSI_C6::RSI_C6() { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_C6_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a RSI_C6 object by copying another RSI_C6 object
*/
RSI_C6::RSI_C6(const RSI_C6 & toCopy) : RSI_C1(toCopy) {
	m_fme_multiplier = toCopy.m_fme_multiplier;
	m_fme_pow_adder = toCopy.m_fme_pow_adder;
	m_fme_pow_multiplier = toCopy.m_fme_pow_multiplier;
	m_fme_div_adder = toCopy.m_fme_div_adder;
	m_fme_div_multiplier = toCopy.m_fme_div_multiplier;
	m_fme_power = toCopy.m_fme_power;
	m_rsc_multiplier = toCopy.m_rsc_multiplier;
	m_rsc_exp_multiplier = toCopy.m_rsc_exp_multiplier;
	m_fme_avg = toCopy.m_fme_avg;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_C6 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/

HRESULT RSI_C6::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_ROS_EQ61_MULT1:		*attribute = m_fme_multiplier;		return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_MULT2:		*attribute = m_fme_pow_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_MULT3:		*attribute = m_fme_div_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_ADDER1:		*attribute = m_fme_pow_adder;		return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_ADDER2:		*attribute = m_fme_div_adder;		return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_POWER:		*attribute = m_fme_power;		return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ64_MULT1:		*attribute = m_rsc_multiplier;		return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ64_MULT2:		*attribute = m_rsc_exp_multiplier;	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ64_FMEAVG:		*attribute = m_fme_avg;			return S_OK;
		case FUELCOM_ATTRIBUTE_RSI_C6_DEFAULTS:
													if ((m_fme_multiplier == 1000.0) &&
														(m_fme_pow_adder == 1.5) &&
														(m_fme_pow_multiplier == 0.00275) &&
														(m_fme_div_adder == 460.0) &&
														(m_fme_div_multiplier == 25.9) &&
														(m_fme_power == 4.0) &&
														(m_rsc_multiplier == 60.0) &&
														(m_rsc_exp_multiplier == 0.0497) &&
														(m_fme_avg == 0.778))					// actual value given on pp37, CFBP system booklet.
														return S_OK;
													return S_FALSE;
	}
	return RSI_C1::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_C6 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_C6::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_ROS_EQ61_MULT1:		m_fme_multiplier = attribute;		m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_MULT2:		m_fme_pow_multiplier = attribute;	m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_MULT3:		m_fme_div_multiplier = attribute;	m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_ADDER1:		m_fme_pow_adder = attribute;		m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_ADDER2:		m_fme_div_adder = attribute;		m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ61_POWER:		m_fme_power = attribute;		m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ64_MULT1:		m_rsc_multiplier = attribute;		m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ64_MULT2:		m_rsc_exp_multiplier = attribute;	m_cache.Clear();	return S_OK;
		case FUELCOM_ATTRIBUTE_ROS_EQ64_FMEAVG:		if (attribute <= 0.0)			return E_INVALIDARG;
								m_fme_avg = attribute;			m_cache.Clear();	return S_OK;

		case FUELCOM_ATTRIBUTE_RSI_C6_DEFAULTS:
								m_fme_multiplier = 1000.0;
								m_fme_pow_adder = 1.5;
								m_fme_pow_multiplier = 0.00275;
								m_fme_div_adder = 460.0;
								m_fme_div_multiplier = 25.9;
								m_fme_power = 4.0;

								m_rsc_multiplier = 60.0;
								m_rsc_exp_multiplier = 0.0497;

								m_fme_avg = 0.778;					// actual value given on pp37, CFBP system booklet.
								m_cache.Clear();	
								return S_OK;
	}
	return RSI_C1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_C6 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_C6::Equals(const FuelAttribute *attribute) const {
	const RSI_C6 *a = dynamic_cast<const RSI_C6 *>(attribute);
	if (!a)
		return false;
	if (m_fme_multiplier != a->m_fme_multiplier)			return false;
	if (m_fme_pow_adder != a->m_fme_pow_adder)				return false;
	if (m_fme_pow_multiplier != a->m_fme_pow_multiplier)	return false;
	if (m_fme_div_adder != a->m_fme_div_adder)				return false;
	if (m_fme_div_multiplier != a->m_fme_div_multiplier)	return false;
	if (m_fme_power != a->m_fme_power)						return false;
	if (m_rsc_multiplier != a->m_rsc_multiplier)			return false;
	if (m_rsc_exp_multiplier != a->m_rsc_exp_multiplier)	return false;
	if (m_fme_avg != a->m_fme_avg)							return false;
	return RSI_C1::Equals(attribute);
}

/*
	See the definition for this in rsi.h
*/
double RSI_C6::RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const {
	// C6 is a special case for RSI.
	// equation 63 is applied in the following statement. 
	*rsi_d1 = *rsi_c2 = RSI_C1::RSI(sa, flag, overrides, ISI, FMC, BUI, FFMC, BE, rsi_c2, rsi_d1);
	return *rsi_c2;
}

/*
	See the definition for this in rsi.h
*/
double RSI_C6::ROS(double RSI, double CBH, double ISI, double FMC, double SFC, CFBAttribute* cfb) const { 
	// C6 is a special case for RSI.
	double fme = m_fme_multiplier * pow(m_fme_pow_adder - m_fme_pow_multiplier * FMC, m_fme_power) /
	    (m_fme_div_adder + m_fme_div_multiplier * FMC);		// equation 61

	// cfb should now be calculated, based on this rsi.
	double rsc = m_rsc_multiplier * (1.0 - exp(-m_rsc_exp_multiplier * ISI)) * fme / m_fme_avg;
									// equation 64

	double rso, csi;
	double ros = RSI + cfb->CFB(CBH, FMC, SFC, RSI, &rso, &csi) * (rsc - RSI);	// equation 65

	// BE effect was applied inside of the RSI_C1::RSI() call above.
	return ros;
}

/*
	See the definition for this in rsi.h
*/
double RSI_C6::FOR_FROS(double RSS, double ROS, double CFB) const {
	if (CFB > 0.0)
		return ROS;
	return RSS;
}


WISE::FuelProto::RsiAttribute* RSI_C6::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiC6 *msgRet = new WISE::FuelProto::RsiC6();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_C6_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::C6);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::RsiC6_Parms *msg = new WISE::FuelProto::RsiC6_Parms();
		msg->set_version(1);
		msg->set_allocated_fmemultiplier(DoubleBuilder().withValue(m_fme_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_fmepowadder(DoubleBuilder().withValue(m_fme_pow_adder).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_fmepowmultiplier(DoubleBuilder().withValue(m_fme_pow_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_fmedivadder(DoubleBuilder().withValue(m_fme_div_adder).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_fmedivmultiplier(DoubleBuilder().withValue(m_fme_div_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_fmepower(DoubleBuilder().withValue(m_fme_power).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_rscmultiplier(DoubleBuilder().withValue(m_rsc_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_rscexpmultiplier(DoubleBuilder().withValue(m_rsc_exp_multiplier).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_fmeavg(DoubleBuilder().withValue(m_fme_avg).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_c6(msgRet);
	return attr;
}


RSI_C6 *RSI_C6::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiC6 *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiC6 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiC6", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_C6: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiC6", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_C6: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiC6", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiC6_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiC6.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_C6: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.RsiC6.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_fmemultiplier())
			m_fme_multiplier = DoubleBuilder().withProtobuf(msg.fmemultiplier(), v2, "fmeMultiplier").getValue();
		if (msg.has_fmepowadder())
			m_fme_pow_adder = DoubleBuilder().withProtobuf(msg.fmepowadder(), v2, "fmePowAdder").getValue();
		if (msg.has_fmepowmultiplier())
			m_fme_pow_multiplier = DoubleBuilder().withProtobuf(msg.fmepowmultiplier(), v2, "fmePowMultiplier").getValue();
		if (msg.has_fmedivadder())
			m_fme_div_adder = DoubleBuilder().withProtobuf(msg.fmedivadder(), v2, "fmeCivAdder").getValue();
		if (msg.has_fmedivmultiplier())
			m_fme_div_multiplier = DoubleBuilder().withProtobuf(msg.fmedivmultiplier(), v2, "fmeDivmMltiplier").getValue();
		if (msg.has_fmepower())
			m_fme_power = DoubleBuilder().withProtobuf(msg.fmepower(), v2, "fmePower").getValue();
		if (msg.has_rscmultiplier())
			m_rsc_multiplier = DoubleBuilder().withProtobuf(msg.rscmultiplier(), v2, "rscMultiplier").getValue();
		if (msg.has_rscexpmultiplier())
			m_rsc_exp_multiplier = DoubleBuilder().withProtobuf(msg.rscexpmultiplier(), v2, "rscExpMultiplier").getValue();
		if (msg.has_fmeavg())
			m_fme_avg = DoubleBuilder().withProtobuf(msg.fmeavg(), v2, "fmeAvg").getValue();
	}
	else {

		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = rsi::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("RSI_C6: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a RSI_D2 object
*/
RSI_D2::RSI_D2() {
	SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_D2_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a RSI_D2 object by copying another RSI_D2 object
*/
RSI_D2::RSI_D2(const RSI_D2 & toCopy) : RSI_C1(toCopy) {
	m_threshold = toCopy.m_threshold;
	m_scale1 = toCopy.m_scale1;
	m_scale2 = toCopy.m_scale2;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_D2 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_D2::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_D2_DEFAULTS:
												if ((m_threshold == 80.0) &&
													(m_scale1 == 0.0) &&
													(m_scale2 == 0.2))
													return S_OK;
													return S_FALSE;
		case FUELCOM_ATTRIBUTE_RSI_D2_THRESHOLD:*attribute = m_threshold;	return S_OK;
		case FUELCOM_ATTRIBUTE_RSI_D2_SCALE1:		*attribute = m_scale1;		return S_OK;
		case FUELCOM_ATTRIBUTE_RSI_D2_SCALE2:		*attribute = m_scale2;		return S_OK;
	}
	return RSI_C1::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_D2 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_D2::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_D2_DEFAULTS:
								m_threshold = 80.0;
								m_scale1 = 0.0;
								m_scale2 = 0.2;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_RSI_D2_THRESHOLD:	if (attribute < 0.0)		return E_INVALIDARG;
								m_threshold = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_RSI_D2_SCALE1:		if (attribute < 0.0)		return E_INVALIDARG;
								if (attribute > 2.0)		return E_INVALIDARG;
								m_scale1 = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_RSI_D2_SCALE2:		if (attribute < 0.0)		return E_INVALIDARG;
								if (attribute > 2.0)		return E_INVALIDARG;
								m_scale2 = attribute;
								m_cache.Clear();	
								return S_OK;
	}
	return RSI_C1::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_D2 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_D2::Equals(const FuelAttribute *attribute) const {
	const RSI_D2 *a = dynamic_cast<const RSI_D2 *>(attribute);
	if (!a)
		return false;
	if (m_threshold != a->m_threshold)	return false;
	if (m_scale1 != a->m_scale1)		return false;
	if (m_scale2 != a->m_scale2)		return false;
	return RSI_C1::Equals(attribute);
}

/*
	See the definition for this in rsi.h
*/
double RSI_D2::RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const {
	double scale;
	if (BUI < m_threshold)
		scale = m_scale1;
	else
		scale = m_scale2;
	if (scale == 0.0) {
		*rsi_d1 = *rsi_c2 = 0.0;
		return *rsi_c2;
	}
	// equation 63 is applied in the following statement, just like D2, with any BE affect applied
	double rsi = RSI_C1::RSI(sa, flag, overrides, ISI, FMC, BUI, FFMC, BE, rsi_c2, rsi_d1);
	
	if (flag & CALC_FOR_RSF) {
		*rsi_d1 = *rsi_c2 = rsi;
	} else {
		*rsi_d1 = *rsi_c2 = scale * rsi;		// RWB: 120805: this scale factor is only applied to calculate RSI, not to calculate RSF
	}
	return *rsi_c2;
}


WISE::FuelProto::RsiAttribute* RSI_D2::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiD2 *msgRet = new WISE::FuelProto::RsiD2();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput())
	{
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_D2_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::D2);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::RsiD2_Parms *msg = new WISE::FuelProto::RsiD2_Parms();
		msg->set_version(1);
		msg->set_allocated_threshold(DoubleBuilder().withValue(m_threshold).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_scale1(DoubleBuilder().withValue(m_scale1).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_scale2(DoubleBuilder().withValue(m_scale2).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_d2(msgRet);
	return attr;
}


RSI_D2 *RSI_D2::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiD2 *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiD2 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiD2", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_D2: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiD2", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_D2: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiD2", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiD2_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiD2.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_D2: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.RsiD2.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_threshold())
			m_threshold = DoubleBuilder().withProtobuf(msg.threshold(), v2, "threshold").getValue();
		if (msg.has_scale1())
			m_scale1 = DoubleBuilder().withProtobuf(msg.scale1(), v2, "scale1").getValue();
		if (msg.has_scale2())
			m_scale2 = DoubleBuilder().withProtobuf(msg.scale2(), v2, "scale2").getValue();

	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = rsi::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("RSI_D2: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a RSI_M1 object
*/
RSI_M1::RSI_M1() { 
	m_p1 = -1.0;
}

/*
	This is a 1-argument constructor to initialize a RSI_M1 object by copying another RSI_M1 object
*/
RSI_M1::RSI_M1(const RSI_M1 & toCopy) {
	m_p1 = toCopy.m_p1;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_M1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_M1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR:		*attribute = m_p1;	return S_OK;
	}
	return RSIAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_M1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_M1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR:		if (attribute < 0.0)	return E_INVALIDARG;
								if (attribute > 1.0)	return E_INVALIDARG;
								m_p1 = attribute;
								return S_OK;
	}
	return RSIAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_M1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_M1::Equals(const FuelAttribute *attribute) const {
	const RSI_M1 *a = dynamic_cast<const RSI_M1 *>(attribute);
	if (!a)
		return false;
	if (m_p1 != a->m_p1)	return false;
	return true;
}

/*
	See the definition for this in rsi.h
*/
double RSI_M1::RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const {
// originally we don't omit the BUI effect, but according to Mike's codes, 
// we don't apply BUI effect when calculating C-2 and D-1's ROS separately, Dennis Yuan, Oct.12,2004
	std::int16_t f = flag & (~(USE_BUI));

	boost::intrusive_ptr<ICWFGM_Fuel> c2, d1;
	sa->C2(c2);
	sa->D1(d1);
	if (c2)
		c2->RSI(FFMC, BUI, FMC, ISI, f, overrides, rsi_c2);	
	else {
		weak_assert(0);
		*rsi_c2 = 0.0;
	}
	if (d1)
		d1->RSI(FFMC, BUI, FMC, ISI, f, overrides, rsi_d1);
	else {
		weak_assert(0);
		*rsi_d1 = 0.0;
	}

	double PC = sa->PC(overrides);
	double rsi = PC * (*rsi_c2) + m_p1 * (1.0 - PC) * (*rsi_d1);	// equation 27, 28
	if (flag & USE_BUI)
		rsi *= BE;
	return rsi;
}


WISE::FuelProto::RsiAttribute* RSI_M1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiM1 *msgRet = new WISE::FuelProto::RsiM1();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::RsiM1_Parms *msg = new WISE::FuelProto::RsiM1_Parms();
	msg->set_version(1);
	msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_m1(msgRet);
	return attr;
}


RSI_M1 *RSI_M1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiM1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiM1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiM1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_M1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiM1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_M1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiM1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiM1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiM1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_M1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.RsiM1.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_p1())
			m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();
	}
	else {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiM1", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_M1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a RSI_M3 object
*/
RSI_M3::RSI_M3() { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a RSI_M3 object by copying another RSI_M3 object
*/
RSI_M3::RSI_M3(const RSI_M3 & toCopy) {
	m_m_a = toCopy.m_m_a;
	m_m_b = toCopy.m_m_b;
	m_m_c = toCopy.m_m_c;
	m_p = toCopy.m_p;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_M3 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_M3::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS:
												if ((m_m_a == 120.0) &&
													(m_m_b == 0.0572) &&
													(m_m_c == 1.4) &&
													(m_p == 1.0))
													return S_OK;
												return S_FALSE;

		case FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR:		*attribute = m_p;	return S_OK;
		case FUELCOM_ATTRIBUTE_M3M4_C2_A:		*attribute = m_m_a;	return S_OK;
		case FUELCOM_ATTRIBUTE_M3M4_C2_B:		*attribute = m_m_b;	return S_OK;
		case FUELCOM_ATTRIBUTE_M3M4_C2_C:		*attribute = m_m_c;	return S_OK;
	}
	return RSIAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_M3 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_M3::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS:
								m_m_a = 120.0;
								m_m_b = 0.0572;
								m_m_c = 1.4;
								m_p = 1.0;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR:		if (attribute < 0.0)	return E_INVALIDARG;
								if (attribute > 1.0)	return E_INVALIDARG;
								m_p = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M3M4_C2_A:		m_m_a = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M3M4_C2_B:		m_m_b = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M3M4_C2_C:		m_m_c = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M4_D1_A:
		case FUELCOM_ATTRIBUTE_M4_D1_B:
		case FUELCOM_ATTRIBUTE_M4_D1_C:
		case FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS: return S_FALSE;
	}
	return RSIAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_M3 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_M3::Equals(const FuelAttribute *attribute) const {
	const RSI_M3 *a = dynamic_cast<const RSI_M3 *>(attribute);
	if (!a)
		return false;
	if (m_p != a->m_p)		return false;
	if (m_m_a != a->m_m_a)	return false;
	if (m_m_b != a->m_m_b)	return false;
	if (m_m_c != a->m_m_c)	return false;
	return true;
}

/*
	See the definition for this in rsi.h
*/
double RSI_M3::RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const {
	double m3_rsi = _rsi(m_m_a, m_m_b, m_m_c, ISI);			// equation 30, August 2004 article

	boost::intrusive_ptr<ICWFGM_Fuel> d1;
	sa->D1(d1);

	double d1_rsi;
	if (d1)
		d1->RSI(FFMC, BUI, FMC, ISI, 0, overrides, &d1_rsi);
	else {
		weak_assert(0);
		d1_rsi = 0.0;
	}
	*rsi_c2 = m3_rsi;
	*rsi_d1 = d1_rsi;

	double PC = sa->PC(overrides);
	double newrsi = PC * m3_rsi + m_p * (1.0 - PC) * d1_rsi;			// equation 29, August 2004 article
											// PC is a synonym for PDF here
	if (flag & USE_BUI) 
		newrsi *= BE;
	return newrsi;
}


WISE::FuelProto::RsiAttribute* RSI_M3::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiM3 *msgRet = new WISE::FuelProto::RsiM3();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M3);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::RsiM3_Parms *msg = new WISE::FuelProto::RsiM3_Parms();
		msg->set_version(options.fileVersion());
		if (options.fileVersion() == 1) {
			std::string m_notes;
			msg->set_notes(m_notes);
		}
		msg->set_allocated_a(DoubleBuilder().withValue(m_m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p(DoubleBuilder().withValue(m_p).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_m3(msgRet);
	return attr;
}


RSI_M3 *RSI_M3::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiM3 *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiM3 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiM3", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_M3: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiM3", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_M3: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiM3", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiM3_Parms &msg = msgRead->parms();

		if ((msg.version() != 1) && (msg.version() != 2)) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiM3.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_M3: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.RsiM3.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.version() != 1) {
			std::string m_notes;
			m_notes = msg.notes();
		}

		if (msg.has_a())
			m_m_a = DoubleBuilder().withProtobuf(msg.a(), v2, "a").getValue();
		if (msg.has_b())
			m_m_b = DoubleBuilder().withProtobuf(msg.b(), v2, "b").getValue();
		if (msg.has_c())
			m_m_c = DoubleBuilder().withProtobuf(msg.c(), v2, "c").getValue();
		if (msg.has_p())
			m_p = DoubleBuilder().withProtobuf(msg.p(), v2, "p").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = rsi::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("RSI_M3: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a RSI_M4 object
*/
RSI_M4::RSI_M4() { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a RSI_M4 object by copying another RSI_M4 object
*/
RSI_M4::RSI_M4(const RSI_M4 & toCopy) {
	m_m_a = toCopy.m_m_a;
	m_m_b = toCopy.m_m_b;
	m_m_c = toCopy.m_m_c;
	m_d1_a = toCopy.m_d1_a;
	m_d1_b = toCopy.m_d1_b;
	m_d1_c = toCopy.m_d1_c;
	m_p = toCopy.m_p;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_M4 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_M4::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS:
												if ((m_m_a == 100.0) &&
													(m_m_b == 0.0404) &&
													(m_m_c == 1.48) &&
													(m_d1_a == 30.0) &&
													(m_d1_b == 0.0232) &&
													(m_d1_c == 1.6) &&
													(m_p == 0.2))
													return S_OK;
												return S_FALSE;

		case FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR:		*attribute = m_p;	return S_OK;
		case FUELCOM_ATTRIBUTE_M3M4_C2_A:		*attribute = m_m_a;	return S_OK;
		case FUELCOM_ATTRIBUTE_M3M4_C2_B:		*attribute = m_m_b;	return S_OK;
		case FUELCOM_ATTRIBUTE_M3M4_C2_C:		*attribute = m_m_c;	return S_OK;
		case FUELCOM_ATTRIBUTE_M4_D1_A:			*attribute = m_d1_a;	return S_OK;
		case FUELCOM_ATTRIBUTE_M4_D1_B:			*attribute = m_d1_b;	return S_OK;
		case FUELCOM_ATTRIBUTE_M4_D1_C:			*attribute = m_d1_c;	return S_OK;
		case FUELCOM_ATTRIBUTE_RSI_M3_DEFAULTS: return S_FALSE;
	}
	return RSIAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_M4 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_M4::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS:
								m_m_a = 100.0;
								m_m_b = 0.0404;
								m_m_c = 1.48;
								m_d1_a = 30.0;
								m_d1_b = 0.0232;
								m_d1_c = 1.6;
								m_p = 0.2;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_RSI_MIX_FACTOR:		if (attribute < 0.0)	return E_INVALIDARG;
								if (attribute > 1.0)	return E_INVALIDARG;
								m_p = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M3M4_C2_A:		m_m_a = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M3M4_C2_B:		m_m_b = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M3M4_C2_C:		m_m_c = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M4_D1_A:			m_d1_a = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M4_D1_B:			m_d1_b = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_M4_D1_C:			m_d1_c = attribute;
								m_cache.Clear();	
								return S_OK;
	}
	return RSIAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_M4 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_M4::Equals(const FuelAttribute *attribute) const {
	const RSI_M4 *a = dynamic_cast<const RSI_M4 *>(attribute);
	if (!a)
		return false;
	if (m_p != a->m_p)		return false;
	if (m_m_a != a->m_m_a)		return false;
	if (m_m_b != a->m_m_b)		return false;
	if (m_m_c != a->m_m_c)		return false;
	if (m_d1_a != a->m_d1_a)		return false;
	if (m_d1_b != a->m_d1_b)		return false;
	if (m_d1_c != a->m_d1_c)		return false;
	return true;
}

/*
	See the definition for this in rsi.h
*/
double RSI_M4::RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double /*FMC*/, double /*BUI*/, double /*FFMC*/, double BE, double *rsi_c2, double *rsi_d1) const {
	double PC = sa->PC(overrides);
	double m4_rsi = _rsi(m_m_a, m_m_b, m_m_c, ISI);			// equation 32, August 2004 article
	double d1_rsi = _rsi(m_d1_a, m_d1_b, m_d1_c, ISI);
	double newrsi = PC * m4_rsi + m_p * (1.0 - PC) * d1_rsi;			// equation 31, August 2004 article
											// PC is a synonym for PDF here
	*rsi_c2 = m4_rsi;
	*rsi_d1 = d1_rsi;

	if (flag & USE_BUI) 
		newrsi *= BE;
	return newrsi;
}


WISE::FuelProto::RsiAttribute* RSI_M4::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiM4 *msgRet = new WISE::FuelProto::RsiM4();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_M4_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::M4);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::RsiM4_Parms *msg = new WISE::FuelProto::RsiM4_Parms();
		msg->set_version(options.fileVersion());
		if (options.fileVersion() == 1) {
			std::string m_notes;
			msg->set_notes(m_notes);
		}
		msg->set_allocated_a(DoubleBuilder().withValue(m_m_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_b(DoubleBuilder().withValue(m_m_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_c(DoubleBuilder().withValue(m_m_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_d1a(DoubleBuilder().withValue(m_d1_a).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_d1b(DoubleBuilder().withValue(m_d1_b).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_d1c(DoubleBuilder().withValue(m_d1_c).forProtobuf(options.useVerboseFloats()));
		msg->set_allocated_p(DoubleBuilder().withValue(m_p).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_m4(msgRet);
	return attr;
}


RSI_M4 *RSI_M4::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiM4 *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiM4 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiM4", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_M4: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiM4", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_M4: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiM4", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiM4_Parms &msg = msgRead->parms();

		if ((msg.version() != 1) && (msg.version() != 2)) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiM4.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_M4: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.RsiM4.Parms", "parms");
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
		if (msg.has_d1a())
			m_d1_a = DoubleBuilder().withProtobuf(msg.d1a(), v2, "d1A").getValue();
		if (msg.has_d1b())
			m_d1_b = DoubleBuilder().withProtobuf(msg.d1b(), v2, "d1B").getValue();
		if (msg.has_d1c())
			m_d1_c = DoubleBuilder().withProtobuf(msg.d1c(), v2, "d1C").getValue();
		if (msg.has_p())
			m_p = DoubleBuilder().withProtobuf(msg.p(), v2, "p").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();
		
		uint16_t val = rsi::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("RSI_M4: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a RSI_O1 object
*/
RSI_O1::RSI_O1() { 
	SetAttributeValue(FUELCOM_ATTRIBUTE_RSI_O1_DEFAULTS, 0.0);
}

/*
	This is a 1-argument constructor to initialize a RSI_O1 object by copying another RSI_O1 object
*/
RSI_O1::RSI_O1(const RSI_O1 & toCopy) {
	m_threshold = toCopy.m_threshold;
	m_f1 = toCopy.m_f1;
	m_f2 = toCopy.m_f2;
	m_f3 = toCopy.m_f3;
	m_f4 = toCopy.m_f4;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_O1::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_O1_DEFAULTS:
												if ((m_threshold == 0.588) &&
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
	return RSIAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_O1 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_O1::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_RSI_O1_DEFAULTS:
								m_threshold = 0.588;
								m_f1 = 0.005;
								m_f2 = 0.061;
								m_f3 = 0.176;
								m_f4 = 0.02;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_EQ35_THRESHOLD:		if (attribute < 0.0)		return E_INVALIDARG;
								if (attribute > 1.0)		return E_INVALIDARG;
								m_threshold = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_EQ35A_MULT1:		m_f1 = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_EQ35A_MULT2:		m_f2 = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_EQ35B_ADDER:		m_f3 = attribute;
								m_cache.Clear();	
								return S_OK;

		case FUELCOM_ATTRIBUTE_EQ35B_MULT1:		m_f4 = attribute;
								m_cache.Clear();	
								return S_OK;
	}
	return RSIAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_O1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_O1::Equals(const FuelAttribute *attribute) const {
	const RSI_O1 *a = dynamic_cast<const RSI_O1 *>(attribute);
	if (!a)
		return false;
	if (m_threshold != a->m_threshold)	return false;
	if (m_f1 != a->m_f1)	return false;
	if (m_f2 != a->m_f2)	return false;
	if (m_f3 != a->m_f3)	return false;
	if (m_f4 != a->m_f4)	return false;
	return true;
}

/*
	See the definition for this in rsi.h
*/
double RSI_O1::RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double /*FMC*/, double /*BUI*/, double /*FFMC*/, double BE, double *rsi_c2, double *rsi_d1) const {
	double CF;

	weak_assert(m_f1 != -1.0);
	weak_assert(m_f2 != -1.0);
	weak_assert(m_f3 != -1.0);
	weak_assert(m_f4 != -1.0);
	weak_assert(m_threshold != -1.0);

	double C = sa->CuringDegree(overrides);
	if (C < m_threshold)
		CF = m_f1 * (exp(m_f2 * C * 100.0) - 1.0);		// equation 35a, August 2004 article
	else
		CF = m_f3 + m_f4 * ((C - m_threshold) * 100.0);		// equation 35b, August 2004 article

	double rsi2 = _rsi(sa->A(flag), sa->B(flag), sa->C(flag), ISI) * CF;

	if (flag & USE_BUI)
		rsi2 *= BE;

 	*rsi_c2 = *rsi_d1 = rsi2;
	return rsi2;
}


WISE::FuelProto::RsiAttribute* RSI_O1::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiO1 *msgRet = new WISE::FuelProto::RsiO1();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_O1_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::O1A);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::RsiO1_Parms *msg = new WISE::FuelProto::RsiO1_Parms();
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


RSI_O1 *RSI_O1::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiO1 *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiO1 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiO1", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_O1: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiO1", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_O1: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiO1", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiO1_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiO1.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_O1: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.RsiO1.Parms", "parms");
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

		uint16_t val = rsi::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("RSI_O1: Invalid default value");
		}
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a RSI_Constant object
*/
RSI_Constant::RSI_Constant() {
	m_rsi = 0.0;
}

/*
	This is a 1-argument constructor to initialize a RSI_Constant object by copying another RSI_Constant object
*/
RSI_Constant::RSI_Constant(const RSI_Constant & toCopy) {
	m_rsi = toCopy.m_rsi;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a RSI_Constant and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_Constant::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_RSI_NZ70_DEFAULTS:	if (m_rsi == (5.0 / 60.0))
													return S_OK;
												return S_FALSE;

	case FUELCOM_ATTRIBUTE_RSI_CONSTANT_RSI:	*attribute = m_rsi;		return S_OK;
	}
	return RSIAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a RSI_Constant and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT RSI_Constant::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
	case FUELCOM_ATTRIBUTE_RSI_NZ70_DEFAULTS:	m_rsi = 5.0 / 60.0;
												return S_OK;

	case FUELCOM_ATTRIBUTE_RSI_CONSTANT_RSI:	if (attribute < 0.0)		return E_INVALIDARG;
												m_rsi = attribute;
												return S_OK;
	}
	return RSIAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the RSI_Constant object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool RSI_Constant::Equals(const FuelAttribute *attribute) const {
	const RSI_Constant *a = dynamic_cast<const RSI_Constant *>(attribute);
	if (!a)
		return false;
	if (m_rsi != a->m_rsi)	return false;
	return true;
}

/*
	See the definition for this in rsi.h
*/
double RSI_Constant::RSI(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* overrides, double /*ISI*/, double /*FMC*/, double /*BUI*/, double /*FFMC*/, double /*BE*/, double *rsi_c2, double *rsi_d1) const {
	*rsi_c2 = *rsi_d1 = m_rsi;
	return m_rsi;
}


WISE::FuelProto::RsiAttribute* RSI_Constant::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::RsiAttribute *attr = new WISE::FuelProto::RsiAttribute();
	attr->set_version(RSIAttribute::serialVersionUid(options));

	WISE::FuelProto::RsiConstant *msgRet = new WISE::FuelProto::RsiConstant();
	msgRet->set_version(serialVersionUid(options));

	bool serialized = false;

	if (!options.useVerboseOutput()) {
		double value;
		if (GetAttributeValue(FUELCOM_ATTRIBUTE_RSI_NZ70_DEFAULTS, &value) == S_OK) {
			msgRet->set_default_(WISE::FuelProto::FuelName::Nz70);
			serialized = true;
		}
	}

	if (!serialized) {
		WISE::FuelProto::RsiConstant_Parms *msg = new WISE::FuelProto::RsiConstant_Parms();
		msg->set_version(1);
		msg->set_allocated_rsi(DoubleBuilder().withValue(m_rsi).forProtobuf(options.useVerboseFloats()));
		msgRet->set_allocated_parms(msg);
	}

	attr->set_allocated_constant(msgRet);
	return attr;
}


RSI_Constant *RSI_Constant::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::RsiConstant *msgRead = dynamic_cast_assert<const WISE::FuelProto::RsiConstant *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiConstant", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_Constant: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.RsiConstant", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("RSI_Constant: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.RsiConstant", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::RsiConstant_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.RsiConstant.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(0);
			throw std::invalid_argument("RSI_Constant: Version is invalid");
		}

		auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.RsiConstant.Parms", "parms");
		auto v2 = vt2.lock();

		if (msg.has_rsi())
			m_rsi = DoubleBuilder().withProtobuf(msg.rsi(), v2, "rsi").getValue();
	}
	else {
		WISE::FuelProto::FuelName def = msgRead->default_();

		uint16_t val = rsi::GetDefaultValue(def);

		if (val != (uint16_t)-1)
			SetAttributeValue(val, 0.0);
		else {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FuelName", "default", validation::error_level::WARNING, validation::id::enum_invalid, std::to_string(val));
			weak_assert(0);
			throw std::invalid_argument("RSI_Constant: Invalid default value");
		}
	}

	return this;
}
