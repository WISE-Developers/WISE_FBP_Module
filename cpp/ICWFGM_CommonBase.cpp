/**
 * WISE_FBP_Module: ICWFGM_CommonBase.cpp
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

#include "ICWFGM_CommonBase.h"
#include "ISerializeProto.h"

#include "WTime.h"

#include <gsl/gsl_util>

#ifdef DEBUG
#include <assert.h>
#endif



HRESULT VariantToBoolean_(const PolymorphicAttribute& varIn, bool* retval) {
	if (std::holds_alternative<bool>(varIn))
		*retval = std::get<bool>(varIn);

	else if (std::holds_alternative<std::int32_t>(varIn))
		*retval = std::get<std::int32_t>(varIn) ? true : false;

	else if (std::holds_alternative<std::int64_t>(varIn))
		*retval = std::get<std::int64_t>(varIn) ? true : false;

	else if (std::holds_alternative<std::uint32_t>(varIn))
		*retval = std::get<std::uint32_t>(varIn) ? true : false;

	else if (std::holds_alternative<std::uint64_t>(varIn))
		*retval = std::get<std::uint64_t>(varIn) ? true : false;

	else {
		weak_assert(false);
		*retval = false;
		return E_INVALIDARG;
	}

	return S_OK;
}

HRESULT VariantToInt16_(const PolymorphicAttribute& varIn, std::int16_t* retval) {
	if (std::holds_alternative<bool>(varIn))
		*retval = gsl::narrow_cast<std::int16_t>(std::get<bool>(varIn) ? 1 : 0);

	else if (std::holds_alternative<double>(varIn))
		*retval = gsl::narrow_cast<std::int16_t>(std::get<double>(varIn));

	else if (std::holds_alternative<std::int32_t>(varIn))
		*retval = gsl::narrow_cast<std::int16_t>(std::get<std::int32_t>(varIn));

	else if (std::holds_alternative<std::int64_t>(varIn))
		*retval = gsl::narrow_cast<std::int16_t>(std::get<std::int64_t>(varIn));

	else if (std::holds_alternative<std::uint32_t>(varIn))
		*retval = gsl::narrow_cast<std::int16_t>(std::get<std::uint32_t>(varIn));

	else if (std::holds_alternative<std::uint64_t>(varIn))
		*retval = gsl::narrow_cast<std::int16_t>(std::get<std::uint64_t>(varIn));

	else {
		weak_assert(false);
		*retval = 0;
		return E_INVALIDARG;
	}

	return S_OK;
}

HRESULT VariantToInt32_(const PolymorphicAttribute& varIn, std::int32_t* retval) {
	if (std::holds_alternative<std::int32_t>(varIn))
		*retval = std::get<std::int32_t>(varIn);

	else if (std::holds_alternative<bool>(varIn))
		*retval = std::get<bool>(varIn) ? 1 : 0;

	else if (std::holds_alternative<double>(varIn))
		*retval = gsl::narrow_cast<std::int32_t>(std::get<double>(varIn));

	else if (std::holds_alternative<std::int64_t>(varIn))
		*retval = gsl::narrow_cast<std::int32_t>(std::get<std::int64_t>(varIn));

	else if (std::holds_alternative<std::uint32_t>(varIn))
		*retval = gsl::narrow_cast<std::int32_t>(std::get<std::uint32_t>(varIn));

	else if (std::holds_alternative<std::uint64_t>(varIn))
		*retval = gsl::narrow_cast<std::int32_t>(std::get<std::uint64_t>(varIn));

	else {
		weak_assert(false);
		*retval = 0;
		return E_INVALIDARG;
	}

	return S_OK;
}

HRESULT VariantToInt64_(const PolymorphicAttribute& varIn, std::int64_t* retval) {
	if (std::holds_alternative<std::int64_t>(varIn))
		*retval = std::get<std::int64_t>(varIn);

	else if (std::holds_alternative<bool>(varIn))
		*retval = std::get<bool>(varIn) ? 1LL : 0LL;

	else if (std::holds_alternative<double>(varIn))
		*retval = gsl::narrow_cast<std::int64_t>(std::get<double>(varIn));

	else if (std::holds_alternative<std::int32_t>(varIn))
		*retval = gsl::narrow_cast<std::int64_t>(std::get<std::int32_t>(varIn));

	else if (std::holds_alternative<std::uint32_t>(varIn))
		*retval = gsl::narrow_cast<std::int64_t>(std::get<std::uint32_t>(varIn));

	else if (std::holds_alternative<std::uint64_t>(varIn))
		*retval = gsl::narrow_cast<std::int64_t>(std::get<std::uint64_t>(varIn));

	else {
		weak_assert(false);
		*retval = 0;
		return E_INVALIDARG;
	}

	return S_OK;
}

HRESULT VariantToTimeSpan_(const PolymorphicAttribute& varIn, HSS_Time::WTimeSpan* retval)
{
	if (std::holds_alternative<HSS_Time::WTimeSpan>(varIn))
		*retval = std::get<HSS_Time::WTimeSpan>(varIn);

	else {
		std::int64_t var;
		if (SUCCEEDED(VariantToInt64_(varIn, &var)))
			*retval = HSS_Time::WTimeSpan(var);
		else {
			weak_assert(false);
			*retval = HSS_Time::WTimeSpan(0);
			return E_INVALIDARG;
		}
	}

	return S_OK;
}

HRESULT VariantToTime_(const PolymorphicAttribute& varIn, HSS_Time::WTime* retval)
{
	if (std::holds_alternative<HSS_Time::WTime>(varIn))
		retval->SetTime(std::get<HSS_Time::WTime>(varIn));

	return S_OK;
}

HRESULT VariantToUInt16_(const PolymorphicAttribute& varIn, std::uint16_t* retval) {
	if (std::holds_alternative<bool>(varIn))
		*retval = gsl::narrow_cast<std::uint16_t>(std::get<bool>(varIn) ? 1U : 0U);

	else if (std::holds_alternative<double>(varIn))
		*retval = gsl::narrow_cast<std::uint16_t>(std::get<double>(varIn));

	else if (std::holds_alternative<std::int32_t>(varIn))
		*retval = gsl::narrow_cast<std::uint16_t>(std::get<std::int32_t>(varIn));

	else if (std::holds_alternative<std::int64_t>(varIn))
		*retval = gsl::narrow_cast<std::uint16_t>(std::get<std::int64_t>(varIn));

	else if (std::holds_alternative<std::uint32_t>(varIn))
		*retval = gsl::narrow_cast<std::uint16_t>(std::get<std::uint32_t>(varIn));

	else if (std::holds_alternative<std::uint64_t>(varIn))
		*retval = gsl::narrow_cast<std::uint16_t>(std::get<std::uint64_t>(varIn));

	else {
		weak_assert(false);
		*retval = 0;
		return E_INVALIDARG;
	}

	return S_OK;
}

HRESULT VariantToUInt32_(const PolymorphicAttribute& varIn, std::uint32_t* retval) {
	if (std::holds_alternative<std::uint32_t>(varIn))
		*retval = std::get<std::uint32_t>(varIn);

	else if (std::holds_alternative<bool>(varIn))
		*retval = std::get<bool>(varIn) ? 1U : 0U;

	else if (std::holds_alternative<double>(varIn))
		*retval = gsl::narrow_cast<std::uint32_t>(std::get<double>(varIn));

	else if (std::holds_alternative<std::int32_t>(varIn))
		*retval = gsl::narrow_cast<std::uint32_t>(std::get<std::int32_t>(varIn));

	else if (std::holds_alternative<std::int64_t>(varIn))
		*retval = gsl::narrow_cast<std::uint32_t>(std::get<std::int64_t>(varIn));

	else if (std::holds_alternative<std::uint64_t>(varIn))
		*retval = gsl::narrow_cast<std::uint32_t>(std::get<std::uint64_t>(varIn));

	else {
		weak_assert(false);
		*retval = 0;
		return E_INVALIDARG;
	}

	return S_OK;
}

HRESULT VariantToUInt64_(const PolymorphicAttribute& varIn, std::uint64_t* retval) {
	if (std::holds_alternative<std::uint64_t>(varIn))
		*retval = std::get<std::uint64_t>(varIn);

	else if (std::holds_alternative<bool>(varIn))
		*retval = std::get<bool>(varIn) ? 1ULL : 0ULL;

	else if (std::holds_alternative<double>(varIn))
		*retval = gsl::narrow_cast<std::uint64_t>(std::get<double>(varIn));

	else if (std::holds_alternative<std::int32_t>(varIn))
		*retval = gsl::narrow_cast<std::uint64_t>(std::get<std::int32_t>(varIn));

	else if (std::holds_alternative<std::int64_t>(varIn))
		*retval = gsl::narrow_cast<std::uint64_t>(std::get<std::int64_t>(varIn));

	else if (std::holds_alternative<std::uint32_t>(varIn))
		*retval = gsl::narrow_cast<std::uint64_t>(std::get<std::uint32_t>(varIn));

	else {
		weak_assert(false);
		*retval = 0;
		return E_INVALIDARG;
	}

	return S_OK;
}

HRESULT VariantToDouble_(const PolymorphicAttribute& varIn, double* pdblRet) {
	if (std::holds_alternative<double>(varIn))
		*pdblRet = std::get<double>(varIn);

	else if (std::holds_alternative<std::int32_t>(varIn))
		*pdblRet = gsl::narrow_cast<double>(std::get<std::int32_t>(varIn));

	else if (std::holds_alternative<std::int64_t>(varIn))
		*pdblRet = gsl::narrow_cast<double>(std::get<std::int64_t>(varIn));

	else if (std::holds_alternative<std::uint32_t>(varIn))
		*pdblRet = gsl::narrow_cast<double>(std::get<std::uint32_t>(varIn));

	else if (std::holds_alternative<std::uint64_t>(varIn))
		*pdblRet = gsl::narrow_cast<double>(std::get<std::uint64_t>(varIn));

	else {
		weak_assert(false);
		*pdblRet = 0.0;
		return E_INVALIDARG;
	}

	return S_OK;
}


/*
	This is a no-argument constructor to initialize a ICWFGM_CommonBase object
*/
ICWFGM_CommonBase::ICWFGM_CommonBase() {
	__boost_ref_cnt = 0;
}

/*
	This is a destructor method for a ICWFGM_CommonBase object
*/
ICWFGM_CommonBase::~ICWFGM_CommonBase() {
}

/*
	This is a method to get the user data from the ICWFGM_CommonBase
	object and store it in the passed PolymorphicUserData object
*/
HRESULT ICWFGM_CommonBase::get_UserData(PolymorphicUserData *pVal) const {
	if (!pVal)
		return E_POINTER;

	*pVal = m_userData;
	return S_OK;
}

/*
	This is a method to set the user data in the ICWFGM_CommonBase
	object with the passed PolymorphicUserData object
*/
HRESULT ICWFGM_CommonBase::put_UserData(const PolymorphicUserData &newVal) {
	m_userData = newVal;
	return S_OK;
}


ISerializeProto::DeserializeError::DeserializeError(const std::string& message) :
	logic_error(message)
{
}


ISerializeProto::DeserializeError::DeserializeError(const std::string& message, std::uint32_t hr_) :
	logic_error(message)
{
	hr = hr_;
}
