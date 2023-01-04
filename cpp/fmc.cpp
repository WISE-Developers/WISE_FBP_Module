/**
 * WISE_FBP_Module: fmc.cpp
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

#include "angles.h"
#include "fmc.h"
#include "str_printf.h"
#include "results.h"


namespace fmc {
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
	This is a no-argument constructor to initialize a FMC_Calc object
*/
FMC_Calc::FMC_Calc() : m_cache(16) {
	m_day0 = -1;
}

/*
	This is a 1-argument constructor to initialize a FMC_Calc object by copying another FMC_Calc object
*/
FMC_Calc::FMC_Calc(const FMC_Calc & toCopy) : m_cache(16) {
	m_day0 = toCopy.m_day0;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a FMC_Calc and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FMC_Calc::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FMC_DAY0:		*attribute = m_day0;	return S_OK;
	}
	return FMCAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a FMC_Calc and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FMC_Calc::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FMC_DAY0:		if (attribute < -1.0)	return E_INVALIDARG;
												if (attribute > 365.0)	return E_INVALIDARG;
												if ((attribute - floor(attribute)) > 1e-5)	return E_INVALIDARG;
												m_day0 = (std::int16_t)attribute;
												m_cache.Clear();
												return S_OK;
	}
	return FMCAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the FMC_Calc object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool FMC_Calc::Equals(const FuelAttribute *attribute) const {
	const FMC_Calc *a = dynamic_cast<const FMC_Calc *>(attribute);
	if (!a)
		return false;
	if (m_day0 != a->m_day0)
		return false;
	return true;
}

/*
	See the definition of FMC in the FuelAttribute header file
*/
double FMC_Calc::FMC(double lat, double lon, double elev, std::uint16_t day, const CCWFGM_FuelOverrides* /*overrides*/) const {
	if (elev < 0.0)
		if (elev != -99.0) {
			weak_assert(false);
			elev = 0.0;
		}

	key c_key;
	c_key.m_lat = lat;
	c_key.m_lon = lon;
	c_key.m_elev = elev;
	c_key.m_day = day;
	{
		double *fmc, _fmc;
		if (fmc = m_cache.Retrieve(&c_key, &_fmc))
			return *fmc;
	}
	{
		double m_fmc_x;

		weak_assert(lat >= DEGREE_TO_RADIAN(-90.0));
		weak_assert(lat <= DEGREE_TO_RADIAN(90.0));
		weak_assert(lon >= DEGREE_TO_RADIAN(-180.0));
		weak_assert(lon <= DEGREE_TO_RADIAN(180.0));
		if (lat < 0.0) {
			day += 182;			// basic, simple correction for flipping from the southern hemisphere to the northern one
			if (day > 365)			// because we're dealing with Canada
				day -= 365;
		}
		if (lat < DEGREE_TO_RADIAN(42.0))
			lat = DEGREE_TO_RADIAN(42.0);
		else if (lat > DEGREE_TO_RADIAN(83.0))
			lat = DEGREE_TO_RADIAN(83.0);
		if (lon < DEGREE_TO_RADIAN(-141.0))
			lon = DEGREE_TO_RADIAN(-141.0);
		else if (lon > DEGREE_TO_RADIAN(-52.0))
			lon = DEGREE_TO_RADIAN(-52.0);

		lat = RADIAN_TO_DEGREE(lat);
		lon = RADIAN_TO_DEGREE(lon);

		if (lon < 0.0)
			lon = 0.0 - lon;

		double latn;						// normalized latitude
		std::uint16_t day0;						// julian day of minimum FMC
		if (m_day0 < 0) {
			if (elev < -98.0) {				// if elevation isn't specified...
				latn = 46.0 + 23.4 * exp(-0.0360 * (150.0 - lon));
									// equation 1
				day0 = (std::uint16_t)(0.5 + 151.0 * (lat / latn));
									// equation 2
			}
			else {					// otherwise, elev is considered a valid elevation
				latn = 43.0 + 33.7 * exp(-0.0351 * (150.0 - lon));
									// equation 3
				day0 = (std::uint16_t)(0.5 + 142.1 * (lat / latn) + 0.0172 * elev);
			}							// equation 4
		}
		else
			day0 = (std::uint16_t)m_day0;

		std::int16_t nd = (std::int16_t)(day - day0);				// number of days, equation 5
		if (nd < 0)
			nd = -nd;					// manually do abs

		if (nd < 30)
			m_fmc_x = 85.0 + 0.0189 * nd * nd;		// equation 6
		else if (nd < 50)
			m_fmc_x = 32.9 + 3.17 * nd - 0.0288 * nd * nd;	// equation 7
		else
			m_fmc_x = 120.0;				// equation 8
		m_cache.Store(&c_key, &m_fmc_x);
		return m_fmc_x;					// change from %age to actual value 
	}
}


WISE::FuelProto::FmcAttribute* FMC_Calc::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FmcAttribute *attr = new WISE::FuelProto::FmcAttribute();
	attr->set_version(FMCAttribute::serialVersionUid(options));

	WISE::FuelProto::FmcCalc_Parms *msg = new WISE::FuelProto::FmcCalc_Parms();
	msg->set_version(serialVersionUid(options));
	
	msg->set_day0(m_day0);

	WISE::FuelProto::FmcCalc *msgRet = new WISE::FuelProto::FmcCalc();
	msgRet->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_calc(msgRet);
	return attr;
}


FMC_Calc *FMC_Calc::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::FmcCalc *msgRead = dynamic_cast_assert<const WISE::FuelProto::FmcCalc *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FmcCalc", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FMC_Calc: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FmcCalc", name);
	auto v = vt.lock();

	if (msgRead->version() != 1) {
		if (v)
			v->add_child_validation("CWFGM.FuelProto.FmcCalc.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FMC_Calc: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	if (msgRead->has_parms()) {
		const WISE::FuelProto::FmcCalc_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FmcCalc.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("FMC_Calc: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.FmcCalc.Parms", "parms");

		m_day0 = msg.day0();
	}
	else {
		const WISE::FuelProto::FuelName &def = msgRead->default_();

		uint16_t val = fmc::GetDefaultValue(def);

		SetAttributeValue(val, 0.0);
	}

	return this;
}

/*
	This is a no-argument constructor to initialize a FMC_NoCalc object
*/
FMC_NoCalc::FMC_NoCalc() {
}

/*
	This is a 1-argument constructor to initialize a FMC_NoCalc object by copying another FMC_NoCalc object
*/
FMC_NoCalc::FMC_NoCalc(const FMC_NoCalc & /*toCopy*/) {
}

/*
	This is a method to check if the FMC_NoCalc object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool FMC_NoCalc::Equals(const FuelAttribute *attribute) const {
	const FMC_NoCalc *a = dynamic_cast<const FMC_NoCalc *>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See the definition of FMC in the FuelAttribute header file
*/
double FMC_NoCalc::FMC(double /*lat*/, double /*lon*/, double /*elev*/, std::uint16_t /*day*/, const CCWFGM_FuelOverrides* /*overrides*/) const {
	return 0.0;
}


WISE::FuelProto::FmcAttribute* FMC_NoCalc::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FmcAttribute *attr = new WISE::FuelProto::FmcAttribute();
	attr->set_version(FMCAttribute::serialVersionUid(options));

	WISE::FuelProto::FmcNoCalc_Parms *msg = new WISE::FuelProto::FmcNoCalc_Parms();
	msg->set_version(serialVersionUid(options));

	WISE::FuelProto::FmcNoCalc *msgRet = new WISE::FuelProto::FmcNoCalc();
	msgRet->set_version(1);
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_nocalc(msgRet);
	return attr;
}


FMC_NoCalc *FMC_NoCalc::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::FmcNoCalc *msgRead = dynamic_cast_assert<const WISE::FuelProto::FmcNoCalc *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FmcNoCalc", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FMC_NoCalc: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FmcNoCalc", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(false);
		throw ISerializeProto::DeserializeError("FMC_NoCalc: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FmcNoCalc", name);
	auto v = vt.lock();

	if (msgRead->has_parms()) {
		const WISE::FuelProto::FmcNoCalc_Parms &msg = msgRead->parms();

		if (msg.version() != 1) {
			if (v)
				v->add_child_validation("CWFGM.FuelProto.FmcNoCalc.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
			weak_assert(false);
			throw std::invalid_argument("FMC_NoCalc: Version is invalid");
		}

		if (v)
			v->add_child_validation("CWFGM.FuelProto.FmcNoCalc.Parms", "parms");
	}
	else {
		const WISE::FuelProto::FuelName &def = msgRead->default_();

		uint16_t val = fmc::GetDefaultValue(def);

		SetAttributeValue(val, 0.0);
	}

	return this;
}
