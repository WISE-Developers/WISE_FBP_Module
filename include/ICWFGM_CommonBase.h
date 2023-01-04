/**
 * WISE_FBP_Module: ICWFGM_CommonBase.h
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

#pragma once

#include "FuelConfig.h"
#include "hssconfig/config.h"
#include "boost_ll_config.h"

#include <string>
#include <boost/intrusive_ptr.hpp>
#include <boost/atomic.hpp>
#include <variant>
#include "WTime.h"

#define __FuelCom_h__

#include "types.h"
#ifndef E_POINTER
#define E_POINTER                        0x80004003L
#endif
#ifndef E_INVALIDARG
#define E_INVALIDARG                     0x80070057L
#endif
#ifndef E_UNEXPECTED
#define E_UNEXPECTED					 0x8000FFFFL
#endif

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(push, 8)
#endif


typedef std::variant<std::monostate, bool, double, std::string, HSS_Time::WTimeSpan, HSS_Time::WTime, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t> PolymorphicAttribute;
typedef std::variant<std::monostate, std::uint64_t, void *> PolymorphicUserData;

template<typename T>
T GetPolymorphicAttributeData(const PolymorphicAttribute& attr, T&& def) {
	try {
		return std::get<T>(attr);
	}
	catch (std::bad_variant_access&) {
		weak_assert(false);
		return def;
	}
}

HRESULT FUELCOM_API VariantToBoolean_(const PolymorphicAttribute& varIn, bool* retval);
HRESULT FUELCOM_API VariantToInt16_(const PolymorphicAttribute& varIn, std::int16_t* retval);
HRESULT FUELCOM_API VariantToInt32_(const PolymorphicAttribute& varIn, std::int32_t* retval);
HRESULT FUELCOM_API VariantToInt64_(const PolymorphicAttribute& varIn, std::int64_t* retval);
HRESULT FUELCOM_API VariantToTimeSpan_(const PolymorphicAttribute& varIn, HSS_Time::WTimeSpan* retval);
HRESULT FUELCOM_API VariantToTime_(const PolymorphicAttribute& varIn, HSS_Time::WTime* retval);
HRESULT FUELCOM_API VariantToUInt16_(const PolymorphicAttribute& varIn, std::uint16_t* retval);
HRESULT FUELCOM_API VariantToUInt32_(const PolymorphicAttribute& varIn, std::uint32_t* retval);
HRESULT FUELCOM_API VariantToUInt64_(const PolymorphicAttribute& varIn, std::uint64_t* retval);
HRESULT FUELCOM_API VariantToDouble_(const PolymorphicAttribute& varIn, double* pdblRet);


/* ALL classes that were originally COM/ATL classes (for now) inherit from this common base class.  The intent here is 3-fold:
// 1.) All of these objects (for now) must deal with garbage collection in a way that's similar to Microsoft's COM/ATL classes.
//	   Here, I've chosen the BOOST intrusive_ptr<> template class which will delete itself when all known references disappear.
//	   This solution is cross-platform and doesn't require introducing clean-up code where we used to have COM objects.
// 2.) THis was missing from COM/ATL but we built our own abtractions to fake a copy construction.  In the COM world, we built
//     routiens to simply serialize to memory, then back into a new object.  Here, the Clone() method serves to duplicate 'this'
//     without the client code knowning or caring what type of object, 'this' is.
// 3.) UserData is still required so long as we have to fake inheritance to the client code like we did in V6.  This may serve
//     to be useful for other client libraries but hopefully in the future, we can clean up this fake inheritance that we used
//     to abstract away COM/ATL from the original MFC Prometheus GUI.
*/
class FUELCOM_API ICWFGM_CommonBase {
public:
	ICWFGM_CommonBase();
	virtual ~ICWFGM_CommonBase();

	virtual NO_THROW HRESULT Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newObject) const = 0;

	/**
	This property is unused by the fuel object, and is available for exclusive use by the client code.  It is a variant value to ensure
	that the client code can store a pointer value (if it chooses) for use in manual subclassing this object.  This value is not loaded or
	saved during serialization operations, and it is the responsibility of the client code to manage any value or object stored here.
	Access to this property is not thread-safe.
	\param pVal value

	\retval S_OK	Successful
	*/
	NO_THROW HRESULT get_UserData(PolymorphicUserData *pVal) const;

	/**
	This property is unused by the fuel object, and is available for exclusive use by the client code.  It is a variant value to ensure
	that the client code can store a pointer value (if it chooses) for use in manual subclassing this object.  This value is not loaded or
	saved during serialization operations, and it is the responsibility of the client code to manage any value or object stored here.
	Access to this property is not thread-safe.
	\param newVal value

	\retval S_OK	Successful
	*/
	NO_THROW HRESULT put_UserData(const PolymorphicUserData &newVal);

private:
	PolymorphicUserData m_userData;

	// http://www.boost.org/doc/libs/1_62_0/doc/html/atomic/usage_examples.html
private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_CommonBase *f) {
		f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed);
	};
	friend inline void intrusive_ptr_release(const ICWFGM_CommonBase *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(pop)
#endif
