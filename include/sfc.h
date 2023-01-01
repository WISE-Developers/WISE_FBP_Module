/**
 * WISE_FBP_Module: sfc.h
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

#ifndef __SFC_H_
#define __SFC_H_

#include "FuelAttribute.h" 
#include "ccwfgmFuel.pb.h"
#include "valuecache_mt.h"

/*
	Declaration for the SFC_C1 class which inherits the methods and variables from SFCAttribute

	Variable list:
		m_cache of type ValueCacheTempl_MT
		m_notes of type string
		m_p1 of type double
		m_p2 of type double
		m_p3 of type double
		m_p4 of type double
		m_multiplier of type double
	
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
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A FFMC value of type double
			A BUI value of type double
*/
class SFC_C1 : public SFCAttribute {
private:
	mutable ValueCacheTempl_MT<double, double>	m_cache;

private:
	double m_p1;
	double m_p2;
	double m_p3;
	double m_p4;
	double m_multiplier;

public:
	SFC_C1() ;
	SFC_C1(const SFC_C1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_SFC_C1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new SFC_C1(*this); };

	virtual double SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFC_C1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SFC_C2 class which inherits the methods and variables from SFCAttribute

	Variable list:
		m_cache of type ValueCacheTempl_MT
		m_notes of type string
		m_p1 of type double
		m_p2 of type double
		m_power of type double
		m_multiplier of type double
	
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
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A FFMC value of type double
			A BUI value of type double
*/
class SFC_C2 : public SFCAttribute {
protected:
	mutable ValueCacheTempl_MT<double, double>	m_cache;

protected:
	double m_p1;
	double m_p2;
	double m_power;
	double m_multiplier;

public:
	SFC_C2() ;
	SFC_C2(const SFC_C2 &toCopy);

	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_SFC_C2; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new SFC_C2(*this); };

	virtual double SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const override;

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFC_C2 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SFC_C7 class which inherits the methods and variables from SFCAttribute

	Variable list:
		A key value that stores the following variables:
			m_ffmc of type double
			m_bui of type double
		m_cache of type ValueCacheTempl_MT
		m_p1_f of type double
		m_p2_f of type double
		m_p3_f of type double
		m_p1_w of type double
		m_p2_w of type double
		m_ffc_multiplier of type double
		m_wfc_multiplier of type double
		m_sfc_multiplier of type double
	
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
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A FFMC value of type double
			A BUI value of type double
*/
class SFC_C7 : public SFCAttribute {
private:
	struct key {
		double m_ffmc, m_bui;
	};
	mutable ValueCacheTempl_MT<key, double> m_cache;

private:
	double m_p1_f;
	double m_p2_f;
	double m_p3_f;
	double m_p1_w;
	double m_p2_w;
	double m_ffc_multiplier, m_wfc_multiplier, m_sfc_multiplier;

public:
	SFC_C7();
	SFC_C7(const SFC_C7 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_SFC_C7; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new SFC_C7(*this); };

	virtual double SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFC_C7 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override	{ return std::nullopt; }
};

/*
	Declaration for the SFC_D2 class which inherits the methods and variables from SFC_C2

	Variable list:
		m_threshold of type double
		m_scale1 of type double
		m_scale2 of type double
	
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
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A FFMC value of type double
			A BUI value of type double
*/
class SFC_D2 : public SFC_C2 {
private:
	double	m_threshold,
			m_scale1,
			m_scale2;
public:
	SFC_D2();
	SFC_D2(const SFC_D2 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_SFC_D2; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new SFC_D2(*this); };

	virtual double SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFC_D2 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override	{ return std::nullopt; }
};

/*
	Declaration for the SFC_M1 class which inherits the methods and variables from SFCAttribute

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
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A FFMC value of type double
			A BUI value of type double
*/
class SFC_M1 : public SFCAttribute {
public:
	SFC_M1();
	SFC_M1(const SFC_M1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override									{ return FUELCOM_EQUATION_SELECTION_SFC_M1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override													{ return new SFC_M1(*this); };

	virtual double SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides *overrides, double FFMC, double BUI) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFC_M1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SFC_O1 class which inherits the methods and variables from SFCAttribute

	Variable list:
		m_fuel_load of type double
		m_notes of type string
	
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
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A FFMC value of type double
			A BUI value of type double
*/
class SFC_O1 : public SFCAttribute {
private:
	double m_fuel_load;				// in kg/m^2 (same as SFC)

public:
	SFC_O1();
	SFC_O1(const SFC_O1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override									{ return FUELCOM_EQUATION_SELECTION_SFC_O1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override													{ return new SFC_O1(*this); };

	virtual double SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFC_O1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SFC_S1 class which inherits the methods and variables from SFCAttribute

	Variable list:
		m_cache of type ValueCacheTempl_MT
		m_p1_f of type double
		m_p2_f of type double
		m_p1_w of type double
		m_p2_w of type double
		m_ffc_multiplier of type double
		m_wfc_multiplier of type double
		m_sfc_multiplier of type double
		m_ffc_bui_multiplier of type double
		m_wfc_bui_multiplier of type double
	
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
		SFC (total surface fuel consumption) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A FFMC value of type double
			A BUI value of type double
*/
class SFC_S1 : public SFCAttribute {
private:
	mutable ValueCacheTempl_MT<double, double>	m_cache;

private:
	double m_p1_f;
	double m_p2_f;
	double m_p1_w;
	double m_p2_w;
	double m_ffc_multiplier, m_wfc_multiplier, m_sfc_multiplier;
	double m_ffc_bui_multiplier, m_wfc_bui_multiplier;

public:
	SFC_S1();
	SFC_S1(const SFC_S1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_SFC_S1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new SFC_S1(*this); };

	virtual double SFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double FFMC, double BUI) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFC_S1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif // define sfc_h
