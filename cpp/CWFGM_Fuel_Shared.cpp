/**
 * WISE_FBP_Module: CWFGM_Fuel_Shared.cpp
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

#include "FBPFuel.h"
#include "dbh.h"

#include "CWFGM_Fuel_Shared.h"

#include "WTime.h"
#include "results.h"
#include "GridCom_ext.h"
#include "semaphore.h"

using namespace HSS_Time;

/*
	Refer to the documentation in CWFGM_Fuel_Shared.h for each of these functions
*/
HRESULT CCWFGM_Fuel::get_Name(std::string *pVal) const {
	if (!pVal)						return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_name;
	return S_OK;
}

HRESULT CCWFGM_Fuel::MT_Lock(bool exclusive, std::uint16_t obtain) {
	if (obtain == (std::uint16_t)-1) {
		std::int64_t state = m_mt_lock.CurrentState();
		if (!state)
			return SUCCESS_STATE_OBJECT_UNLOCKED;
		if (state < 0)
			return SUCCESS_STATE_OBJECT_LOCKED_WRITE;
		if (state >= 1000000LL)
			return SUCCESS_STATE_OBJECT_LOCKED_SCENARIO;
		return SUCCESS_STATE_OBJECT_LOCKED_READ;
	}
	else if (obtain) {
		if (exclusive)
			m_mt_lock.Lock_Write();
		else
			m_mt_lock.Lock_Read(1000000LL);
	}
	else {
		if (exclusive)
			m_mt_lock.Unlock();
		else
			m_mt_lock.Unlock(1000000LL);
	}

	return S_OK;
}


HRESULT CCWFGM_Fuel::Equals(const boost::intrusive_ptr<ICWFGM_Fuel> &fuel, bool compareName) const {
	if (!fuel)
		return E_FAIL;
	CCWFGM_Fuel *fbp = dynamic_cast<CCWFGM_Fuel *>(fuel.get());
	if (!fbp)
		return S_FALSE;

	CRWThreadSemaphoreEngage engage(fbp->m_mt_lock, SEM_FALSE);
	CRWThreadSemaphoreEngage engage2(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	if (compareName)
		if (m_name != fbp->m_name)
			return S_FALSE;
	if (!m_fuel.Equals(fbp->m_fuel))
		return S_FALSE;
	return S_OK;
}


HRESULT CCWFGM_Fuel::Clone(boost::intrusive_ptr<ICWFGM_CommonBase> *newFuel) const {
	if (!newFuel)
		return E_POINTER;
	HRESULT hr = 0;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	try {
		boost::intrusive_ptr<CCWFGM_Fuel> nf(new CCWFGM_Fuel());
		nf->m_name = m_name;
		nf->m_fuel = m_fuel;
		*newFuel = nf;
	}
	catch (std::exception &e) {
		hr = E_FAIL;
	}
	return hr;
}


CCWFGM_Fuel &CCWFGM_Fuel::operator=(const CCWFGM_Fuel &toCopy) {
	if (this == &toCopy)
		return *this;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)&toCopy)->m_mt_lock, SEM_FALSE);
	CRWThreadSemaphoreEngage engage2(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_TRUE);

	try {
		boost::intrusive_ptr<CCWFGM_Fuel> nf(new CCWFGM_Fuel());
		nf->m_name = m_name;
		nf->m_fuel = m_fuel;
	}
	catch (std::exception &e) {
	}
	return *this;
}


HRESULT CCWFGM_Fuel::Mutate(boost::intrusive_ptr<ICWFGM_Fuel> *newFuel) const {
	if (!newFuel)
		return E_POINTER;
	HRESULT hr = 0;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	try {
		boost::intrusive_ptr<CCWFGM_Fuel> nf(new CCWFGM_Fuel());
		nf->m_name = m_name;
		nf->m_fuel = m_fuel;
		*newFuel = nf;
	}
	catch (std::exception &e) {
		hr = E_FAIL;
	}
	return hr;
}


HRESULT CCWFGM_Fuel_Readonly::put_Name(const std::string & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel::put_Name(const std::string &pVal) {
	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)								return ERROR_SCENARIO_SIMULATION_RUNNING;

	m_name = pVal;
	m_bRequiresSave = true;
	return S_OK;
}


HRESULT CCWFGM_Fuel::GetEquation(std::uint16_t equationKey, std::uint16_t *equation) const {
	if (!equation)						return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	return m_fuel.GetEquation(equationKey, equation);
}


HRESULT CCWFGM_Fuel_Readonly::SetEquation(std::uint16_t /*equationKey*/, std::uint16_t /*equation*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel::SetEquation(std::uint16_t equationKey, std::uint16_t equation) {
	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	HRESULT hr = m_fuel.SetEquation(equationKey, equation);
	if (SUCCEEDED(hr))
		m_bRequiresSave = true;
	return hr;
}


HRESULT CCWFGM_Fuel::GetAttribute(std::uint16_t attributeKey, PolymorphicAttribute *value) const {
	if (!value)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	switch (attributeKey) {
	case CWFGM_ATTRIBUTE_LOAD_WARNING:
		if (m_fuel.m_loadWarning.length()) {
			std::string cstr = m_name;
			cstr += ":\n";
			cstr += m_fuel.m_loadWarning;
			cstr += "\n";
			std::string str = cstr;
			*value = str;
			return S_OK;
		}
		return S_FALSE;
	}
	double dvalue;
	HRESULT hr = m_fuel.GetAttributeValue(attributeKey, &dvalue);
	*value = dvalue;
	return hr;
}


HRESULT CCWFGM_Fuel_Readonly::SetAttribute(std::uint16_t /*attributeKey*/, const PolymorphicAttribute & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel::SetAttribute(std::uint16_t attributeKey, const PolymorphicAttribute &newVal) {
	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	double dval;
	HRESULT hr;
	if (FAILED(hr = VariantToDouble_(newVal, &dval)))
		return hr;
	hr = m_fuel.SetAttributeValue(attributeKey, dval);
	if (SUCCEEDED(hr))
		m_bRequiresSave = true;
	return hr;
}


HRESULT CCWFGM_Fuel::get_C2(boost::intrusive_ptr<ICWFGM_Fuel> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	m_fuel.GetC2(pVal);
	return S_OK;
}


HRESULT CCWFGM_Fuel_Readonly::put_C2(const boost::intrusive_ptr<ICWFGM_Fuel> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel::put_C2(const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) {
	if ((!m_fuel.IsMixed()) && (!m_fuel.IsModified()))
		return E_UNEXPECTED;
	if (!newVal)
		return E_POINTER;

	ICWFGM_Fuel *a = dynamic_cast<ICWFGM_Fuel *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	boost::intrusive_ptr<ICWFGM_Fuel> c2;
	m_fuel.GetC2(&c2);
	if (newVal != c2) {
		m_fuel.SetC2((boost::intrusive_ptr<ICWFGM_Fuel> &)newVal);
		m_bRequiresSave = true;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_D1(boost::intrusive_ptr<ICWFGM_Fuel> *pVal) const {
	if (!pVal)						return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	m_fuel.GetD1(pVal);
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_Accel(boost::intrusive_ptr<ICWFGM_AccelAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_AccelCustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_FMC(boost::intrusive_ptr<ICWFGM_FMCAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_FMCCustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_SFC(boost::intrusive_ptr<ICWFGM_SFCAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_SFCCustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_TFC(boost::intrusive_ptr<ICWFGM_TFCAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_TFCCustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_CFB(boost::intrusive_ptr<ICWFGM_CFBAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_CFBCustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_RSI(boost::intrusive_ptr<ICWFGM_RSIAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_RSICustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_ISF(boost::intrusive_ptr<ICWFGM_ISFAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_ISFCustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel::get_CustomEquation_LB(boost::intrusive_ptr<ICWFGM_LBAttribute> *pVal) const {
	if (!pVal)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*pVal = m_fuel.m_LBCustom;
	return S_OK;
}


HRESULT CCWFGM_Fuel_Readonly::put_D1(const boost::intrusive_ptr<ICWFGM_Fuel> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_Accel(const boost::intrusive_ptr<ICWFGM_AccelAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_FMC(const boost::intrusive_ptr<ICWFGM_FMCAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_SFC(const boost::intrusive_ptr<ICWFGM_SFCAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_TFC(const boost::intrusive_ptr<ICWFGM_TFCAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_CFB(const boost::intrusive_ptr<ICWFGM_CFBAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_RSI(const boost::intrusive_ptr<ICWFGM_RSIAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_ISF(const boost::intrusive_ptr<ICWFGM_ISFAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel_Readonly::put_CustomEquation_LB(const boost::intrusive_ptr<ICWFGM_LBAttribute> & /*newVal*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel::put_D1(const boost::intrusive_ptr<ICWFGM_Fuel> &newVal) {
	if ((!m_fuel.IsMixed()) && (!m_fuel.IsModified()))
		return E_UNEXPECTED;
	if (!newVal)
		return E_POINTER;

	ICWFGM_Fuel *a = dynamic_cast<ICWFGM_Fuel *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	boost::intrusive_ptr<ICWFGM_Fuel> d1;
	m_fuel.GetD1(&d1);
	if (newVal != d1) {
		m_fuel.SetD1((boost::intrusive_ptr<ICWFGM_Fuel> &)newVal);
		m_bRequiresSave = true;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_Accel(const boost::intrusive_ptr<ICWFGM_AccelAttribute> &newVal) {
	ICWFGM_AccelAttribute *a = dynamic_cast<ICWFGM_AccelAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE; 

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_AccelCustom) {
		m_fuel.m_AccelCustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_FMC(const boost::intrusive_ptr<ICWFGM_FMCAttribute> &newVal) {
	ICWFGM_FMCAttribute *a = dynamic_cast<ICWFGM_FMCAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_FMCCustom) {
		m_fuel.m_FMCCustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_SFC(const boost::intrusive_ptr<ICWFGM_SFCAttribute> &newVal) {
	ICWFGM_SFCAttribute *a = dynamic_cast<ICWFGM_SFCAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_SFCCustom) {
		m_fuel.m_SFCCustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_TFC(const boost::intrusive_ptr<ICWFGM_TFCAttribute> &newVal) {
	ICWFGM_TFCAttribute *a = dynamic_cast<ICWFGM_TFCAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_TFCCustom) {
		m_fuel.m_TFCCustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_CFB(const boost::intrusive_ptr<ICWFGM_CFBAttribute> &newVal) {
	ICWFGM_CFBAttribute *a = dynamic_cast<ICWFGM_CFBAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_CFBCustom) {
		m_fuel.m_CFBCustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_RSI(const boost::intrusive_ptr<ICWFGM_RSIAttribute> &newVal) {
	ICWFGM_RSIAttribute *a = dynamic_cast<ICWFGM_RSIAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_RSICustom) {
		m_fuel.m_RSICustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_ISF(const boost::intrusive_ptr<ICWFGM_ISFAttribute> &newVal) {
	ICWFGM_ISFAttribute *a = dynamic_cast<ICWFGM_ISFAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_ISFCustom) {
		m_fuel.m_ISFCustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::put_CustomEquation_LB(const boost::intrusive_ptr<ICWFGM_LBAttribute> &newVal) {
	ICWFGM_LBAttribute *a = dynamic_cast<ICWFGM_LBAttribute *>(newVal.get());
	if (!a)
		return E_NOINTERFACE;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	if (newVal != m_fuel.m_LBCustom) {
		m_fuel.m_LBCustom = newVal;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::CalculateFCValues(double FFMC, double BUI, double FMC, double RSS, double ROS, short flag, const CCWFGM_FuelOverrides* overrides, double* cfb,
    double* cfc, double* rso, double* csi, double* sfc, double* tfc, double* fi) const {
	if (!cfb)
		return E_POINTER;
	if (!cfc)
		return E_POINTER;
	if (!sfc)
		return E_POINTER;
	if (!tfc)
		return E_POINTER;
	if (!rso)
		return E_POINTER;
	if (!csi)
		return E_POINTER;
	if (!fi)
		return E_POINTER;

	try {
		((CCWFGM_Fuel *)this)->m_fuel.CalculateFCValues(FFMC, BUI, FMC, RSS, ROS, flag & FUELCOM_INPUT_MASK, overrides, cfb, cfc, rso, csi, sfc, tfc, fi);
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;

}


HRESULT CCWFGM_Fuel::CalculateStatistics(double ROS, double FROS, double BROS, double CFB, const HSS_Time::WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
    double *area, double *perimeter) const {
	if (!area)
		return E_POINTER;
	if (!perimeter)
		return E_POINTER;

	try {
		WTimeSpan ttt(time);
		((CCWFGM_Fuel *)this)->m_fuel.CalculateStatistics(ROS, FROS, BROS, CFB, ttt, flag & FUELCOM_INPUT_MASK, overrides, area, perimeter);
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::CalculateDistances(double ROS, double FROS, double BROS, double CFB, const HSS_Time::WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides,
    double *dhead, double *dflank, double *dback) const {
	if (!dhead)
		return E_POINTER;
	if (!dflank)
		return E_POINTER;
	if (!dback)
		return E_POINTER;

	try {
		((CCWFGM_Fuel *)this)->m_fuel.CalculateDistances(ROS, FROS, BROS, CFB, time, flag & FUELCOM_INPUT_MASK, overrides, dhead, dflank, dback);
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::CalculateROSTheta(double ROS, double FROS, double BROS, double RAZ, double Theta, double* rosTheta) const {
	if (!rosTheta)
		return E_POINTER;

	try {
		((CCWFGM_Fuel*)this)->m_fuel.CalculateROSTheta(ROS, FROS, BROS, RAZ, Theta, rosTheta);
	}
	catch (...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::SFC(double FFMC, double BUI, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *sfc) const {
	if (!sfc)
		return E_POINTER;

	try {
		*sfc = ((CCWFGM_Fuel *)this)->m_fuel.SFC(FFMC, BUI, (std::int16_t)(flag & FUELCOM_INPUT_MASK), overrides);
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::FMC(double lat, double lon, double elev, std::uint16_t day, const CCWFGM_FuelOverrides* overrides, double *fmc) const {
	if (!fmc)
		return E_POINTER;

	try {
		*fmc = ((CCWFGM_Fuel *)this)->m_fuel.FMC(lat, lon, elev, day, overrides);
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::CalculateROSValues(double GS, double SAZ, double WS, double WAZ, double BUI, double FMC,
    double FFMC, double fF, const HSS_Time::WTimeSpan &t, const HSS_Time::WTimeSpan &ffmc_t, std::int16_t flag,
		const CCWFGM_FuelOverrides* overrides, ICWFGM_PercentileAttribute *RSIadjust,
    double * rss, double *roseq, double *ros, double *frss, double *froseq, double *fros,
    double *brss, double *broseq, double *bros, double *lb, double *wsv, double *raz) const {
	if (!rss)
		return E_POINTER;
	if (!brss)
		return E_POINTER;
	if (!frss)
		return E_POINTER;
	if (!roseq)
		return E_POINTER;
	if (!broseq)
		return E_POINTER;
	if (!froseq)
		return E_POINTER;
	if (!ros)
		return E_POINTER;
	if (!fros)
		return E_POINTER;
	if (!bros)
		return E_POINTER;
	if (!wsv)
		return E_POINTER;
	if (!raz)
		return E_POINTER;

	try {
		((CCWFGM_Fuel *)this)->m_fuel.CalculateValues(GS, SAZ, WS, WAZ, BUI, FMC, FFMC, fF, t, ffmc_t, (std::int16_t)(flag & FUELCOM_INPUT_MASK), overrides, RSIadjust,
		    rss, roseq, ros, frss, froseq, fros, brss, broseq, bros, lb, wsv, raz);
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::RSI(double FFMC, double BUI, double FMC, double ISI, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *rsi) const {
	if (!rsi)
		return E_POINTER;

	try {
		double unused1, unused2;
		*rsi = ((CCWFGM_Fuel *)this)->m_fuel.RSI(FFMC, BUI, FMC, ISI, flag, overrides, &unused1, &unused2);

#ifdef DEBUG
		if ((!m_fuel.IsMixed()) && (!m_fuel.IsMixedDead()))
			if (*rsi != unused1) {
				weak_assert(*rsi == unused1);
				*rsi = ((CCWFGM_Fuel *)this)->m_fuel.RSI(FFMC, BUI, FMC, ISI, (std::int16_t)(flag & FUELCOM_INPUT_MASK), overrides, &unused1, &unused2);
			}
#endif
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsConiferFuelType(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*retbool = (m_fuel.IsConifer()) ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsDeciduousFuelType(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*retbool = (m_fuel.IsDeciduous()) ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsMixedFuelType(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*retbool = (m_fuel.IsMixed()) ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsSlashFuelType(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*retbool = (m_fuel.IsSlash()) ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsMixedDeadFirFuelType(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*retbool = (m_fuel.IsMixedDead()) ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsGrassFuelType(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*retbool = (m_fuel.IsGrass()) ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsC6FuelType(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	*retbool = (m_fuel.IsC6()) ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::IsNonFuel(bool *retbool) const {
	if (!retbool)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	bool res=m_fuel.IsNonFuel();
	*retbool=res ? true : false;
	return S_OK;
}


HRESULT CCWFGM_Fuel::ISF(double RSF, double SF, double ISZ, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *isfValue) const {
	if (!isfValue)
		return E_POINTER;

	try {
		*isfValue = ((CCWFGM_Fuel *)this)->m_fuel.ISF(RSF, RSF, SF, ISZ, (std::int16_t)(flag & FUELCOM_INPUT_MASK), overrides);
	}
	catch(...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::FlameLength(double height, double CFB, double FI, const CCWFGM_FuelOverrides* overrides, double *fl) const {
	if (!fl)
		return E_POINTER;

	try {
		*fl = ((CCWFGM_Fuel *)this)->m_fuel.FlameLength(height, CFB, FI, overrides);
	}
	catch (...) {
		return E_INVALIDARG;
	}
	return S_OK;
}


HRESULT CCWFGM_Fuel::GetDefaultCLSID(_GUID *clsID) const {
	if (!clsID)
		return E_POINTER;

	CRWThreadSemaphoreEngage engage(((CCWFGM_Fuel *)this)->m_mt_lock, SEM_FALSE);

	const _GUID& cls = m_fuel.m_defaultFuelType;
	memcpy(clsID, &cls, sizeof(_GUID));
	return S_OK;
}


HRESULT CCWFGM_Fuel_Readonly::SetDefaultCLSID(_GUID * /*clsID*/) {
	return E_FAIL;
}


HRESULT CCWFGM_Fuel::SetDefaultCLSID(_GUID *clsID) {
	if (!clsID)
		return E_POINTER;

	SEM_BOOL engaged;
	CRWThreadSemaphoreEngage engage(m_mt_lock, SEM_TRUE, &engaged, 1000000LL);
	if (!engaged)
		return ERROR_SCENARIO_SIMULATION_RUNNING;

	memcpy(&m_fuel.m_defaultFuelType, clsID, sizeof(_GUID));
	return S_OK;
}
