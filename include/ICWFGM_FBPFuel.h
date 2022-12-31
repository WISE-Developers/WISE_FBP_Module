/**
 * WISE_FBP_Module: ICWFGM_FBPFuel.h
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

#include "ICWFGM_Fuel.h"


// done this way to avoid some files that can't be compiled as Cxx17
namespace CWFGM {
	namespace FuelProto {
		enum FuelName : int;
	}
};

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(push, 8)
#endif

/*
	Declaration for the ICWFGM_AccelAttribute class

	Method list:
		No argument constructor
		Acceleration with a return type HRESULT that takes the following parameters:
			A CFB value of type double
			An acceleration of type double
*/
class FUELCOM_API ICWFGM_AccelAttribute {
public:
	ICWFGM_AccelAttribute();
	virtual ~ICWFGM_AccelAttribute() { }

	virtual NO_THROW HRESULT Acceleration(double CFB, double *Accel) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_AccelAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_AccelAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};

/*
	Declaration for the ICWFGM_FMCAttribute class

	Method list:
		No argument constructor
		FMC (initial spread rate without BUI effect) with a return type HRESULT that takes the following parameters:
			A latitude value of type double
			A longitude value of type double
			A elevation value of type double
			A julian_day value of type uint16_t
			A FMC value of type double
*/
class FUELCOM_API ICWFGM_FMCAttribute {
public:
	ICWFGM_FMCAttribute();
	virtual ~ICWFGM_FMCAttribute() { }

	virtual NO_THROW HRESULT FMC(double latitide, double longitude, double elevation,
			std::uint16_t julian_day, const CCWFGM_FuelOverrides* overrides, double *FMC) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_FMCAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_FMCAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};

/*
	Declaration for the ICWFGM_SFCAttribute class

	Method list:
		No argument constructor
		SFC (total surface fuel consumption) with a return type HRESULT that takes the following parameters:
			A greenup value of type boolean
			A FFMC value of type double
			A BUI value of type double
			A C2 value of type ICWFGM_Fuel
			A D1 value of type ICWFGM_Fuel
			A PC value of type double
			A SFC value of type double
*/
class FUELCOM_API ICWFGM_SFCAttribute {
public:
	ICWFGM_SFCAttribute();
	virtual ~ICWFGM_SFCAttribute() { }

	virtual NO_THROW HRESULT SFC(bool greenup, double FFMC, double BUI,
		boost::intrusive_ptr<ICWFGM_Fuel> &C2, boost::intrusive_ptr<ICWFGM_Fuel> &D1,
		double PC, double *SFC) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_SFCAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_SFCAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};

/*
	Declaration for the ICWFGM_TFCAttribute class

	Method list:
		No argument constructor
		TFC (total fuel consumption) with a return type HRESULT that takes the following parameters:
			A greenup value of type boolean
			A CFL value of type double
			A CFB value of type double
			A SFC value of type double
			A PC value of type double
			A CFC value of type double
			A TFC value of type double
*/
class FUELCOM_API ICWFGM_TFCAttribute {
public:
	ICWFGM_TFCAttribute();
	virtual ~ICWFGM_TFCAttribute() { }

	virtual NO_THROW HRESULT TFC(bool greenup, double CFL, double CFB,
		double SFC, double PC, double *CFC, double *TFC) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_TFCAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_TFCAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};

/*
	Declaration for the ICWFGM_RSIAttribute class

	Method list:
		No argument constructor
		RSI (initial spread rate without BUI effect) with a return type HRESULT that takes the following parameters:
			A greenup value of type boolean
			A 'a' value of type double
			A 'b' value of type double
			A 'c' value of type double
			A ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A 'C' value of type double
			A C2 value of type ICWFGM_Fuel
			A D1 value of type ICWFGM_Fuel
			A PC value of type double
			A flags value of type uint16
			A RSI_C2 value of type double
			A RSI_D1 value of type double
			A RSI value of type double
		ROS (final spread rate) with a return type of HRESULT that takes the following parameters
			A greenup value of type bool
			A RSI value of type double
			A CBH value of type double
			A ISI value of type double
			A FMC value of type double
			A SFC value of type double
			A ROS value of type double
		For_FROS (flank fire spread rate) with a return type of HRESULT that takes the following parameters
			A greenup value of type bool
			A RSS value of type double
			A ROS value of type double
			A CFB value of type double
			A For_FROS value of type double
*/
class FUELCOM_API ICWFGM_RSIAttribute {
public:
	ICWFGM_RSIAttribute();
	virtual ~ICWFGM_RSIAttribute() { }

	virtual NO_THROW HRESULT RSI(bool greenup, double a, double b, double c,
			double ISI, double FMC, double BUI, double FFMC, double BE, double C,
			boost::intrusive_ptr<ICWFGM_Fuel> &C2, boost::intrusive_ptr<ICWFGM_Fuel> &D1,
			double PC, std::uint16_t flags, const CCWFGM_FuelOverrides* overrides,
			double *RSI_C2, double *RSI_D1, double *RSI) = 0;

	virtual NO_THROW HRESULT ROS(bool greenup, double RSI, double CBH,
			double ISI, double FMC, double SFC, double *ROS) = 0;

	virtual NO_THROW HRESULT For_FROS(bool greenup, double RSS, double ROS, double CFB, double *For_FROS) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_RSIAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_RSIAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};

/*
	Declaration for the ICWFGM_CFBAttribute class

	Method list:
		No argument constructor
		CFB (crown fraction burned) with a return type HRESULT that takes the following parameters:
			A greenup value of type boolean
			A CBH value of type double
			A FMC value of type double
			A SFC value of type double
			A ROS value of type double
			A RSO value of type double
			A CSI value of type double
			A CFB value of type double
*/
class FUELCOM_API ICWFGM_CFBAttribute {
public:
	ICWFGM_CFBAttribute();
	virtual ~ICWFGM_CFBAttribute() { }

	virtual NO_THROW HRESULT CFB(bool greenup, double CBH, double FMC, double SFC,
			double ROS, double *RSO, double *CSI, double *CFB) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_CFBAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_CFBAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};

/*
	Declaration for the ICWFGM_LBAttribute class

	Method list:
		No argument constructor
		LB (length-to-breadth ratio) with a return type HRESULT that takes the following parameters:
			A WSV value of type double
			A LB value of type double
*/
class FUELCOM_API ICWFGM_LBAttribute {
public:
	ICWFGM_LBAttribute();
	virtual ~ICWFGM_LBAttribute() { }

	virtual NO_THROW HRESULT LB(double WSV, double *LB) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_LBAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_LBAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};

};

/*
	Declaration for the ICWFGM_ISFAttribute class

	Method list:
		No argument constructor
		ISF (ISI with zero wind upslope) with a return type HRESULT that takes the following parameters:
			A greenup value of type bool
					A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
			A 'b' value of type double
			A 'c' value of type double
			A RFC_C2 value of type double
			A RFC_D1 value of type double
			A SF value of type double
			A ISZ value of type double
			A C2 value of type ICWFGM_Fuel
			A D1 value of type ICWFGM_Fuel
			A 'C' value of type double
			A PC value of type double
			A ISF value of type double
*/
class FUELCOM_API ICWFGM_ISFAttribute {
public:
	ICWFGM_ISFAttribute();
	virtual ~ICWFGM_ISFAttribute() { }

	virtual NO_THROW HRESULT ISF(bool greenup, double a, double b, double c,
			double RFC_C2, double RFC_D1, double SF, double ISZ,
			boost::intrusive_ptr<ICWFGM_Fuel> &C2, boost::intrusive_ptr<ICWFGM_Fuel> &D1,
			double C, double PC, double *ISF) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_ISFAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_ISFAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};

};

/*
	Declaration for the ICWFGM_DBHAttribute class

	Method list:
		No argument constructor
		DBH with a return type HRESULT that takes the following parameters:
			A height value of type double
			A dbh value of type double
*/
class FUELCOM_API ICWFGM_DBHAttribute {
public:
	ICWFGM_DBHAttribute();
	virtual ~ICWFGM_DBHAttribute() { }

	virtual NO_THROW HRESULT DBH(double height, double *dbh) = 0;

private:
	mutable boost::atomic<long> __boost_ref_cnt;		// this variable and the below methods deal with the necessary implementations for the boost intrusive_ptr<> template
														// to deal with automatic clean-up of this object when no other clients retain a reference to it any longer.  This is
														// a way of dealing with automatic garbage collection in C++ that's a good migration from the Microsoft ATL/COM
														// infrastructure that we're migrating away from.
public:
	friend inline void intrusive_ptr_add_ref(const ICWFGM_DBHAttribute *f) { f->__boost_ref_cnt.fetch_add(1, boost::memory_order_relaxed); };
	friend inline void intrusive_ptr_release(const ICWFGM_DBHAttribute *f) {
		if (f->__boost_ref_cnt.fetch_sub(1, boost::memory_order_release) == 1) {
			boost::atomic_thread_fence(boost::memory_order_acquire);
			delete f;
		}
	};
};


/** Interface CWFGM FBPFuel

ICWFGM_FBPFuel defines properties and methods to modify and examine various aspects of the fuel type.
*/
class FUELCOM_API ICWFGM_FBPFuel : public ICWFGM_Fuel {
public:
	/**
	Set the fuel type name
	\param newVal New name for the fuel type
	*/
	virtual NO_THROW HRESULT put_Name(const std::string &newVal) = 0;

	/**
	This property is used only for M-1, M-2 fuel types.  They define extra parameters that are needed for those fuel types.  For any other fuel types, these parameters are unused.  C-2 and D-1 are pointers to ICWFGM_Fuel objects which represent the appropriate fuel type.\n
	If the fuel type is not mixed (or modified), then attempts to get or set these parameters will result in a returned error code.\n
	Retrieval of C-2 or D-1 pointer values does not modify the COM reference counter for either of these objects.  Assignment will increment the reference counter for the new object and decrement the reference counter for the old object.
	\param pVal	When retrieving the property.
	\param newVal	When setting the property.
	*/
	virtual NO_THROW HRESULT get_C2(boost::intrusive_ptr<ICWFGM_Fuel> *pVal) const = 0;

	virtual NO_THROW HRESULT put_C2(const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) = 0;

	/**
	This property is used only for M-1, M-2 fuel types.  They define extra parameters that are needed for those fuel types.  For any other fuel types, these parameters are unused.  C-2 and D-1 are pointers to ICWFGM_Fuel objects which represent the appropriate fuel type.\n
	If the fuel type is not mixed (or modified), then attempts to get or set these parameters will result in a returned error code.\n
	Retrieval of C-2 or D-1 pointer values does not modify the COM reference counter for either of these objects.  Assignment will increment the reference counter for the new object and decrement the reference counter for the old object.
	\param pVal	When retrieving the property.
	\param newVal	When setting the property.
	*/
	virtual NO_THROW HRESULT get_D1(boost::intrusive_ptr<ICWFGM_Fuel> *pVal) const = 0;

	virtual NO_THROW HRESULT put_D1(const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) = 0;

	/**
	Sets the default CLSID. Typically this value identifies the original read-only fuel type used to create/clone the fuel type, but can be used to store any value (because this value is unused by this COM DLL).
	\param clsID	return value for CLSID
	*/
	virtual NO_THROW HRESULT SetDefaultCLSID(_GUID *clsId) = 0;

	/**
	Given a request for a specific type of equation, retrieves the index for the specific equation (set) used for a particular calculation.
	\param equationKey	One of the following values, as defined in FuelCOM_ext.h
	<ul>
	<li> FUELCOM_EQUATION_FMC
	<li> FUELCOM_EQUATION_SFC
	<li> FUELCOM_EQUATION_SFC_GREENUP
	<li> FUELCOM_EQUATION_TFC
	<li> FUELCOM_EQUATION_TFC_GREENUP
	<li> FUELCOM_EQUATION_RSI
	<li> FUELCOM_EQUATION_RSI_GREENUP
	<li> FUELCOM_EQUATION_ISF
	<li> FUELCOM_EQUATION_ISF_GREENUP
	<li> FUELCOM_EQUATION_CFB
	<li> FUELCOM_EQUATION_CFB_GREENUP
	<li> FUELCOM_EQUATION_ACCEL
	<li> FUELCOM_EQUATION_LB
	</ul>
	\param equation	Index of the requested equation.  Refer to the following table for equation indices and what they refer to.
	*/
	virtual NO_THROW HRESULT GetEquation(std::uint16_t equationKey, std::uint16_t *equation) const = 0;

	/**
	Requests to change a specific equation defining part of the operations for the fuel type. If the request matches the type of the current equation, then nothing is performed. Once a given equation format has been chosen, virtually any coefficient or attribute of that equation (set) can be modified using the method SetAttribute.
	\param equationKey	One of the following values, as defined in FuelCOM_ext.h
	<ul>
	<li> FUELCOM_EQUATION_FMC
	<li> FUELCOM_EQUATION_SFC
	<li> FUELCOM_EQUATION_SFC_GREENUP
	<li> FUELCOM_EQUATION_TFC
	<li> FUELCOM_EQUATION_TFC_GREENUP
	<li> FUELCOM_EQUATION_RSI
	<li> FUELCOM_EQUATION_RSI_GREENUP
	<li> FUELCOM_EQUATION_ISF
	<li> FUELCOM_EQUATION_ISF_GREENUP
	<li> FUELCOM_EQUATION_CFB
	<li> FUELCOM_EQUATION_CFB_GREENUP
	<li> FUELCOM_EQUATION_ACCEL
	<li> FUELCOM_EQUATION_LB
	</ul>
	\param equation	The index identifying the equation to be set.  Refer to the following table for equestion indices and what they refer to.
	*/
	virtual NO_THROW HRESULT SetEquation(std::uint16_t equationKey, std::uint16_t equation) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_Accel(boost::intrusive_ptr<ICWFGM_AccelAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_Accel(const boost::intrusive_ptr<ICWFGM_AccelAttribute> &newVal) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_FMC(boost::intrusive_ptr<ICWFGM_FMCAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_FMC(const boost::intrusive_ptr<ICWFGM_FMCAttribute> &newVal) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_SFC(boost::intrusive_ptr<ICWFGM_SFCAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_SFC(const boost::intrusive_ptr<ICWFGM_SFCAttribute> &newVal) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_TFC(boost::intrusive_ptr<ICWFGM_TFCAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_TFC(const boost::intrusive_ptr<ICWFGM_TFCAttribute> &newVal) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_CFB(boost::intrusive_ptr<ICWFGM_CFBAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_CFB(const boost::intrusive_ptr<ICWFGM_CFBAttribute> &newVal) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_RSI(boost::intrusive_ptr<ICWFGM_RSIAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_RSI(const boost::intrusive_ptr<ICWFGM_RSIAttribute> &newVal) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_ISF(boost::intrusive_ptr<ICWFGM_ISFAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_ISF(const boost::intrusive_ptr<ICWFGM_ISFAttribute> &newVal) = 0;

	virtual NO_THROW HRESULT get_CustomEquation_LB(boost::intrusive_ptr<ICWFGM_LBAttribute> *pVal) const = 0;

	virtual NO_THROW HRESULT put_CustomEquation_LB(const boost::intrusive_ptr<ICWFGM_LBAttribute> &newVal) = 0;

	static const char* FuelNameToChar(WISE::FuelProto::FuelName fuelname);
	static const char* GUIDToChar(_GUID fuelguid);
	static const _GUID* FuelNameToGUID(WISE::FuelProto::FuelName fuelname);
	static WISE::FuelProto::FuelName GUIDToFuelName(_GUID fuelguid);
};


// We need to uniquely identify each fuel type class for purposes of class serialization and class instantiation via class factories.
// To make life simple in the C++ world, I'm just simply re-using the V6 GUID's and doing a basic table lookup for a class factory.
// For use outside this DLL library, I've declared these as external, even though the definitions will remain in this DLL.
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_C1;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_C2;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_C3;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_C4;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_C5;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_C6;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_C7;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_D1;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_D2;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_D1D2;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_M1;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_M2;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_M1M2;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_M3;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_M4;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_M3M4;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_S1;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_S2;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_S3;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_O1b;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_O1a;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_O1ab;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_Non;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ2;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ15;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ30;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ31;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ32;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ33;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ40;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ41;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ43;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ44;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ45;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ46;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ47;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ50;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ51;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ52;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ53;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ54;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ55;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ56;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ57;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ58;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ60;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ61;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ62;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ63;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ64;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ65;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ66;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ67;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ68;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ69;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ70;
extern "C" FUELCOM_API const _GUID CLSID_CWFGM_Fuel_NZ71;

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(pop)
#endif
