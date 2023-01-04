/**
 * WISE_FBP_Module: FBPFuel.h
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

#if !defined(AFX_FBPFUEL_H__CC0D45A6_1F7F_11D4_BD42_00A0833B165D__INCLUDED_)
#define AFX_FBPFUEL_H__CC0D45A6_1F7F_11D4_BD42_00A0833B165D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(_MSC_VER) && !defined(_NO_MFC)
#include <afx.h>
#else
#include "guid.h"
#include "types.h"
#endif

#include "ICWFGM_FBPFuel.h"


#include "FwiCom.h"
#include "FireEngine_ext.h"
#include "WTime.h"
#include "ccwfgmFuel.pb.h"
#include "ISerializeProto.h"
#include "hssconfig/config.h"

using namespace HSS_Time;

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(push, 8)
#endif

/*
	Declaration for the FBPFuel class

	Method list:
		ISF (ISI with zero wind upslope) with a return type of double that takes the following parameters:
			A RSF_C2 value of type double
			A RSF_D1 value of type double
			A SF value of type double
			A ISZ of type double
			A flag value of int16_t
		CFC with a return type of double that takes the following parameters:
			A cfb value of type double
		IsConifer with a return type of bool
		IsDeciduous with a return type of bool
		IsNonFuel with a return type of bool
		IsGrass with a return type of bool
		IsFBPGrass with a return type of bool
		IsSlash with a return type of bool
		IsMixed with a return type of bool
		IsMixedDead with a return type of bool
		IsC6 with a return type of bool
		IsModified with a return type of bool
		SetC2 with a return type of void that takes the following parameters:
			A newVal object of type ICWFGM_Fuel
		SetD1 with a return type of void that takes the following parameters:
			A newVal object of type ICWFGM_Fuel
		GetC2 with a return type of void that takes the following parameters:
			A newVal object of type ICWFGM_Fuel
		GetD1 with a return type of void that takes the following parameters:
			A newVal object of type ICWFGM_Fuel
		CalculateValues with a return type of bool that takes the following parameters:
			A GS value of type double
			A SAZ value of type double
			A WS value of type double
			A WAZ value of type double
			A BUI value of type double
			A FMC value of type double
			A FFMC value of type double
			A fF value of type double
			A t value of type WTimeSpan
			A ffmc_t value of type WTimeSpan
			A flag value of type int16_t
			A RSIadjust value of type ICWFGM_PercentileAttribute
			A rss value of type double
			A roseq value of type double
			A ros value of type double
			A frss value of type double
			A froseq value of type double
			A fros value of type double
			A brss value of type double
			A broseq value of type double
			A bros value of type double
			A lb value of type double
			A wsv value of type double
			A raz value of type double
		CalculateFCValues with a return type of void that takes the following parameters:
			A FFMC value of type double
			A BUI value of type double
			A FMC value of type double
			A RSS value of type double
			A ROS value of type double
			A flag value of type short
			A cfb value of type double
			A cfc value of type double
			A rso value of type double
			A csi value of type double
			A sfc value of type double
			A tfc value of type double
			A fi value of type double
		CalculateStatistics with a return type of void that takes the following parameters:
			A ROS value of type double
			A FROS value of type double
			A BROS value of type double
			A CFB value of type double
			A time value of type WTimeSpan
			A flag value of type short
			A area value of type double
			A perimeter value of type double
		CalculateDistances with a return type of void that takes the following parameters:
			A ROS value of type double
			A FROS value of type double
			A BROS value of type double
			A CFB value of type double
			A time value of type WTimeSpan
			A flag value of type short
			A dhead value of type double
			A dfalnk value of type double
			A dback value of type double
		CalculateROSTheta calculates the equation 94 from the FBP update, but where-as the defined equation is provided as angle off RAZ=0 cartesian, this implementation
		inputs RAZ and to appropriate rotate Theta, thus simplifying client code
			A ROS value of type double
			A FROS value of type double
			A BROS value of type double
			A RAZ value of type double
			A theta value of type double
			A rosTheta value of type double
		FI with a return type of double that takes the following parameters:
			A TFC value of type double
			A ROS value of type double
			A flag value of type int16_t
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A FFMC value of type double
			A BUI value of type double
			A flag value of int16_t
		TFC  (total fuel consumption) with a return type of double that takes the following parameters:
			A CFB value of type double
			A SFC value of type double
			A flag value of type int16_t
			A CFC value of type double
		CFB (crown fraction burned) with a return type of double that takes the following parameters:
			A FMC value of type double
			A SFC value of type double
			A RSS value of type double
			A ROS value of type double
			A flag value of type int16_t
			A rso value of type double
			A csi value of type double
		FMC (foliar moisture content) with a return value of type double that takes the following parameters:
			A lat value of type double
			A lon value of type double
			A elev value of type double
			A day value of type uint16_t
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A FFMC value of type double
			A BUI value of type double
			A FMC value of type double
			A ISI value of type double
			A flag value of type int16_t
			A RSI_C2 value of type double
			A RSI_D1 value of type double
		WSV with a return type of double that takes the following parameters:
			A GS value of type double
			A SAZ value of type double
			A WAZ value of type double
			A BUI value of type double
			A FMC value of type double
			A FFMC value of type double
			A fF value of type double
			A flag value of type int16_t
			A ffmc_t value of type WTimeSpan
			A raz value of type double
		FlameLength with a return type of double that takes the following parameters:
			A height value of type double
			A CFB value of type double
			A fi value of type double
		BE with a return type of double that takes the following parameters:
			A BUI value of type double
		LB (length-to-breadth ratio) with a return type of double that takes the following parameters:
			A WSV value of type double
			A RSS value of type double
			A ROS_EQ value of type double
			A BUI value of type double
			A FMC value of type double
			A FFMC value of type double
			A t value of type WTimeSpan
			A flag value of type int16_t
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A BUI value of type double
			A FMC value of type double
			A FFMC value of type double
			A fF value of type double
			A t value of type WTimeSpan
			A ffmc_t value of type WTimeSpan
			A flag value of type int16_t
			A RSIadjust value of type ICWFGM_PercentileAttribute
			A ros_eq value of type double
			A rss value of type double
		BROS with a return type of double that takes the following parameters:
			A WSV value of type double
			A RSS value of type double
			A ROS_EQ value of type double
			A BUI value of type double
			A FMC value of type double
			A FFMC value of type double
			A fF value of type double
		FROS with a return type of double that takes the following parameters:
			A ROS value of type double
			A BROS value of type double
			A LB value of type double
		ACC with a return type of double that takes the following parameters:
			A cfb value of type double
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetEquation with a return type of HRESULT that takes the following parameters:
			An equationKey value of type uint16_t
			An equation value of type double
		SetEquation with a return type of HRESULT that takes the following parameters:
			An equationKey value of type uint16_t
			An equation value of type double
		Clone with a return type of FBPFuel	
		Equals with a return type of bool that takes the following parameters:
			A fuel object of type FBPFuel
*/
class FUELCOM_API FBPFuel : public ISerializeProto {
	friend class CWFGM_FuelHelper;

public:
	FBPFuel();
	FBPFuel(const FBPFuel &toCopy);

	virtual ~FBPFuel();

	FBPFuel &operator=(const FBPFuel &toCopy);

	_GUID	m_defaultFuelType;

	ICWFGM_FWI*		m_fwi;

	std::string			m_loadWarning;

protected:
	bool	m_fuelTypeModified;

public:
	class SpreadParmsAttribute *m_spread;
	class FMCAttribute *m_FMCCalculation;
	class SFCAttribute *m_SFCCalculation, *m_SFCCalculation_Greenup; // my sfc calculation Engine
	class TFCAttribute *m_TFCCalculation, *m_TFCCalculation_Greenup; // my tfc calculation Engine
	class RSIAttribute *m_RSICalculation, *m_RSICalculation_Greenup; // my rate of spread calculation Engine
	class ISFAttribute *m_ISFCalculation, *m_ISFCalculation_Greenup;
	class AccAlphaAttribute *m_AccAlphaCalculation;
	class LBAttribute  *m_LBCalculation;
	class CFBAttribute  *m_CFBCalculation, *m_CFBCalculation_Greenup;
	class FlameLengthAttribute *m_FLCalculation;

	boost::intrusive_ptr<ICWFGM_AccelAttribute> m_AccelCustom;
	boost::intrusive_ptr<ICWFGM_FMCAttribute> m_FMCCustom;
	boost::intrusive_ptr<ICWFGM_SFCAttribute> m_SFCCustom;
	boost::intrusive_ptr<ICWFGM_TFCAttribute> m_TFCCustom;
	boost::intrusive_ptr<ICWFGM_CFBAttribute> m_CFBCustom;
	boost::intrusive_ptr<ICWFGM_RSIAttribute> m_RSICustom;
	boost::intrusive_ptr<ICWFGM_ISFAttribute> m_ISFCustom;
	boost::intrusive_ptr<ICWFGM_LBAttribute> m_LBCustom;

#define USE_ACCELERATION	((std::uint16_t)(1 << CWFGM_SCENARIO_OPTION_ACCEL))
#define USE_BUI				((std::uint16_t)(1 << CWFGM_SCENARIO_OPTION_BUI))
#define USE_SLOPE			((std::uint16_t)(1 << CWFGM_SCENARIO_OPTION_TOPOGRAPHY))
#define USE_WIND			((std::uint16_t)(1 << CWFGM_SCENARIO_OPTION_WIND))
#define USE_GREENUP			((std::uint16_t)(1 << CWFGM_SCENARIO_OPTION_GREENUP))
#define USE_GRASSPHENOLOGY	((std::uint16_t)(1 << CWFGM_SCENARIO_OPTION_GRASSPHENOLOGY))
#define FUELCOM_INPUT_MASK	(USE_ACCELERATION | USE_BUI | USE_SLOPE | USE_WIND | USE_GREENUP | USE_GRASSPHENOLOGY)	// for sane inputs
#define CALC_FOR_RSF		((std::uint16_t)0x4000)

public:
	double ISF(double RSF_C2, double RSF_D1, double SF, double ISZ, std::int16_t flag, const CCWFGM_FuelOverrides* overrides);			// ISI with zero wind, but some slope.
	bool IsConifer() const;
	bool IsDeciduous() const;
	bool IsNonFuel() const;
	bool IsGrass() const;
	bool IsSlash() const;
	bool IsMixed() const;
	bool IsMixedDead() const;
	bool IsC6() const;
	bool IsModified() const			{ return m_fuelTypeModified ? true : false; }

	void SetC2(boost::intrusive_ptr<ICWFGM_Fuel> &newVal);
	void SetD1(boost::intrusive_ptr<ICWFGM_Fuel> &newVal);
	void GetC2(boost::intrusive_ptr<ICWFGM_Fuel> *newVal) const;
	void GetD1(boost::intrusive_ptr<ICWFGM_Fuel> *newVal) const;

	bool CalculateValues( double GS, double SAZ, double WS, double WAZ, double BUI, double FMC, double FFMC, double fF,
	    const WTimeSpan &t, const WTimeSpan &ffmc_t, std::int16_t flag, const CCWFGM_FuelOverrides* /*overrides*/, ICWFGM_PercentileAttribute *RSIadjust, double *rss,
	    double *roseq, double *ros, double *frss, double *froseq, double *fros, double *brss, double *broseq, double *bros, double *lb,
	    double *wsv, double *raz);
	void CalculateFCValues(double FFMC, double BUI, double FMC, double RSS, double ROS, short flag, const CCWFGM_FuelOverrides* overrides, double* cfb, double* cfc, double *rso, double *csi, double* sfc, double* tfc, double *fi);
	void CalculateStatistics(double ROS, double FROS, double BROS, double CFB, const WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides, double *area, double *perimeter);
	void CalculateDistances(double ROS, double FROS, double BROS, double CFB, const WTimeSpan &time, short flag, const CCWFGM_FuelOverrides* overrides, double *dhead, double *dflank, double *dback);
	void CalculateROSTheta(double ROS, double FROS, double BROS, double RAZ, double Theta, double* rosTheta);

	double FI(double TFC, double ROS, std::int16_t flag);

	double SFC(double FFMC, double BUI, std::int16_t flag, const CCWFGM_FuelOverrides* overrides);	// get surface fuel consumption.
	double TFC(double CFB, double SFC, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *CFC);

	double CFB(double FMC, double SFC, double RSS, double ROS, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *rso, double *csi);

	double FMC(double lat, double lon, double elev, std::uint16_t day, const CCWFGM_FuelOverrides* overrides);

	double RSI(double FFMC, double BUI, double FMC, double ISI, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double *RSI_C2, double *RSI_D1);
						// return a rate of spread, based only on a
						// value for ISI.  To get actual ROS, use the
						// function ROS(), which will call this.
	double WSV(double GS, double SAZ, double WS, double WAZ, double BUI, double FMC, double FFMC, double fF, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, const WTimeSpan &ffmc_t, double *raz);

	double FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides);

    protected:
	double BE(double BUI);
	double LB(double WSV, double RSS, double ROS_EQ, double BUI, double FMC, double FFMC, /*double fF,*/ const WTimeSpan &t, std::int16_t flag, const CCWFGM_FuelOverrides* overrides);

	// calculate rate of spread, accounting for things like slope or wind.
	// use the flag parameter to determine which variables are to be used.
	double ROS(	double WSV,		// wind speed vector
			double BUI,		// buildup effect.
			double FMC, 
			double FFMC, 
			const WTimeSpan &t,	// elapsed time (count in seconds). only used if USE_ACCELERATION is on.
			const WTimeSpan &ffmc_t,//time step used to calculate FFMC - for sub-hourly or hourly differentiation
			std::int16_t flag,		// bit flag.
			const CCWFGM_FuelOverrides* overrides,
			ICWFGM_PercentileAttribute *RSIadjust,
			double *ros_eq, double *rss
		) ;
	double BROS(double WSV, double RSS, double ROS_EQ, double BUI, double FMC, double FFMC, double fF,
	    const WTimeSpan &t, std::int16_t flag, const CCWFGM_FuelOverrides* /*overrides*/, ICWFGM_PercentileAttribute *RSIadjust, double *bros_eq, double *brss);
	double FROS(double ROS, double BROS, double LB);
	double ACC(double cfb);

public:
	HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const;
	HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute);
	HRESULT GetEquation(std::uint16_t equationKey, std::uint16_t *equation) const;
	HRESULT SetEquation(std::uint16_t equationKey, std::uint16_t equation);
	virtual FBPFuel *Clone() const { return new FBPFuel(*this); };
	virtual bool Equals(const FBPFuel &fuel) const;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override;
	virtual WISE::FuelProto::FbpFuel* serialize(const SerializeProtoOptions& options) override;
	virtual WISE::FuelProto::FbpFuel* serialize(const SerializeProtoOptions& options, ISerializationData* userData) override;
	virtual FBPFuel *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

class SerializeFuelData : public ISerializationData {
public:
	FBPFuel* defaultFuel;
	int defaultFuelType;
};

#ifdef HSS_SHOULD_PRAGMA_PACK
#pragma pack(pop)
#endif

#endif // !defined(AFX_FBPFUEL_H__CC0D45A6_1F7F_11D4_BD42_00A0833B165D__INCLUDED_)
