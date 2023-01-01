/**
 * WISE_FBP_Module: rsi.h
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

#ifndef __RSI_H_
#define __RSI_H_

#include "FuelAttribute.h" 
#include "ccwfgmFuel.pb.h"
#include "valuecache_mt.h"

/*
	Declaration for the RSI_StdCalc class
	
	Variable list:
		A key value that stores the following values
			a of type double
			b of type double
			c of type double
			ISI of type double
		A m_cache value of type ValueCacheTempl_MT
	
	Method list:
		No argument constructor
		_rsi with a return type of double that takes the following parameters:
			A 'a' value of type double
			A 'b' value of type double
			A 'c' value of type double
			A ISI value of type double
*/
class RSI_StdCalc {
protected:
	struct key {
		    double a, b, c, ISI;
	};
	mutable ValueCacheTempl_MT<key, double> m_cache;

public:
	RSI_StdCalc() : m_cache(16) { };
	double _rsi(double a, double b, double c, double ISI) const;
};

/*
	Declaration for the RSI_C1 class which inherits the methods and variables from RSIAttribute and RSI_StdCalc

	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A ROS value of type double
*/
class RSI_C1 : public RSIAttribute, public RSI_StdCalc {
public:
	RSI_C1();
	RSI_C1(const RSI_C1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_RSI_C1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new RSI_C1(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const override { return RSI; };
	virtual double FOR_FROS(double /*RSS*/, double ROS, double /*CFB*/) const override { return ROS; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_C1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSI_C6 class which inherits the methods and variables from RSI_C1

	Variable list:
		m_fme_multiplier of type double
		m_fme_pow_adder of type double
		m_fme_pow_multiplier of type double
		m_fme_div_adder of type double
		m_fme_div_multiplier of type double
		m_fme_power of type double
		m_rsc_multiplier of type double
		m_rsc_exp_multiplier of type double
		m_fme_avg of type double
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
			A CBH value of type double
			A ISI value of type double
			A FMC value of type double
			A SFC value of type double
			A cfb value of type CFBAttribute
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A RSS value of type double
			A ROS value of type double
			A CFB value of type double
*/
class RSI_C6 : public RSI_C1 {
private:
	double m_fme_multiplier;
	double m_fme_pow_adder;
	double m_fme_pow_multiplier;
	double m_fme_div_adder;
	double m_fme_div_multiplier;
	double m_fme_power;
	double m_rsc_multiplier;
	double m_rsc_exp_multiplier;
	double m_fme_avg;

public:
	RSI_C6();
	RSI_C6(const RSI_C6 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_RSI_C6; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new RSI_C6(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double CBH, double ISI, double FMC, double SFC, CFBAttribute* cfb) const override;
	virtual double FOR_FROS(double RSS, double ROS, double CFB) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_C6 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSI_D2 class which inherits the methods and variables from RSI_C1

	Variable list:
		m_threshold
		m_scale1
		m_scale2
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A ROS value of type double
*/
class RSI_D2 : public RSI_C1 {
private:
	double	m_threshold,
			m_scale1,
			m_scale2;

public:
	RSI_D2();
	RSI_D2(const RSI_D2 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_RSI_D2; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new RSI_D2(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const override { return RSI; };
	virtual double FOR_FROS(double /*RSS*/, double ROS, double /*CFB*/) const override { return ROS; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_D2 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSI_M1 class which inherits the methods and variables from RSIAttribute

	Variable list:
		m_p1 of type double
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A ROS value of type double
*/
class RSI_M1 : public RSIAttribute {
private:
	double m_p1;

public:
	RSI_M1() ;
	RSI_M1(const RSI_M1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_RSI_M1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new RSI_M1(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const override { return RSI; };
	virtual double FOR_FROS(double /*RSS*/, double ROS, double /*CFB*/) const override { return ROS; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_M1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSI_M3 class which inherits the methods and variables from RSIAttribute and RSI_StdCalc

	Variable list:
		m_m_a of type double
		m_m_b of type double
		m_m_c of type double
		m_p of type double
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A ROS value of type double
*/
class RSI_M3 : public RSIAttribute, public RSI_StdCalc {
private:
	double m_m_a, m_m_b, m_m_c;
	double m_p;

public:
	RSI_M3();
	RSI_M3(const RSI_M3 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_RSI_M3; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new RSI_M3(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const override { return RSI; };
	virtual double FOR_FROS(double /*RSS*/, double ROS, double /*CFB*/) const override { return ROS; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_M3 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSI_M4 class which inherits the methods and variables from RSIAttribute and RSI_StdCalc

	Variable list:
		m_m_a of type double
		m_m_b of type double
		m_m_c of type double
		m_d1_a of type double
		m_d1_b of type double
		m_d1_c of type double
		m_p of type double
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A ROS value of type double
*/
class RSI_M4 : public RSIAttribute, public RSI_StdCalc {
private:
	double m_m_a, m_m_b, m_m_c;
	double m_d1_a, m_d1_b, m_d1_c;
	double m_p;

public:
	RSI_M4();
	RSI_M4(const RSI_M4 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_RSI_M4; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new RSI_M4(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const override { return RSI; };
	virtual double FOR_FROS(double /*RSS*/, double ROS, double /*CFB*/) const override { return ROS; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_M4 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSI_O1 class which inherits the methods and variables from RSIAttribute and RSI_StdCalc

	Variable list:
		m_threshold of type double
		m_f1 of type double
		m_f2 of type double
		m_f3 of type double
		m_f4 of type double
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A ROS value of type double
*/
class RSI_O1 : public RSIAttribute, public RSI_StdCalc {
private:
	double m_threshold;
	double m_f1, m_f2, m_f3, m_f4;

public:
	RSI_O1();
	RSI_O1(const RSI_O1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_RSI_O1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new RSI_O1(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const override { return RSI; };
	virtual double FOR_FROS(double /*RSS*/, double ROS, double /*CFB*/) const override { return ROS; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_O1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSI_Constant class which inherits the methods and variables from RSIAttribute

	Variable list:
		m_rsi of type double
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		RSI (initial spread rate without BUI effect) with a return type of double that takes the following parameters:
			A sa value of type SpreadParmsAttribute
			A flag value of type int16_t
			An ISI value of type double
			A FMC value of type double
			A BUI value of type double
			A FFMC value of type double
			A BE value of type double
			A rsi_c2 value of type double
			A rsi_d1 value of type double
		ROS (final spread rate) with a return type of double that takes the following parameters:
			A RSI value of type double
		FOR_FROS (flank fire spread rate) with a return type of double that takes the following parameters:
			A ROS value of type double
*/
class RSI_Constant : public RSIAttribute {
private:
	double m_rsi;

public:
	RSI_Constant();
	RSI_Constant(const RSI_Constant &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_RSI_CONSTANT; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new RSI_Constant(*this); };

	virtual double RSI(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double ISI, double FMC, double BUI, double FFMC, double BE, double *rsi_c2, double *rsi_d1) const override;
	virtual double ROS(double RSI, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const override { return RSI; };
	virtual double FOR_FROS(double /*RSS*/, double ROS, double /*CFB*/) const override { return ROS; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSI_Constant *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif
