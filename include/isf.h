/**
 * WISE_FBP_Module: isf.h
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

#ifndef __ISF_H_
#define __ISF_H_

#include "FuelAttribute.h" 
#include "ccwfgmFuel.pb.h"

/*
	Declaration for the ISF_C1 class which inherits the methods and variables from ISFAttribute
	
	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of uint16
		Equals with a return type of bool that takes the following parameters:
			An attribute object of type FuelAttribute
		Clone with a return type of FuelAttribute
		ISF (ISI with zero wind upslope) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int64_t
			A RSF_C2 value of type double
			A RSF_D1 value of type double
			A SF value of type double
			A ISZ value of type double
*/
class ISF_C1 : public ISFAttribute {
public:
	ISF_C1();
	ISF_C1(const ISF_C1 &toCopy);

	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_ISF_C1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new ISF_C1(*this); };

	virtual double ISF(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double RSF_C2, double RSF_D1, double SF, double ISZ) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::IsfAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual ISF_C1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the ISF_M1 class which inherits the methods and variables from ISFAttribute
	
	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of uint16
		Equals with a return type of bool that takes the following parameters:
			An attribute object of type FuelAttribute
		Clone with a return type of FuelAttribute
		ISF (ISI with zero wind upslope) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int64_t
			A RSF_C2 value of type double
			A RSF_D1 value of type double
			A SF value of type double
			A ISZ value of type double
*/
class ISF_M1 : public ISFAttribute {
public:
	ISF_M1();
	ISF_M1(const ISF_M1 &toCopy);

	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_ISF_M1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new ISF_M1(*this); };

	virtual double ISF(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double RSF_C2, double RSF_D1, double SF, double ISZ) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::IsfAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual ISF_M1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the ISF_M3M4 class which inherits the methods and variables from ISFAttribute
	
	Variable list:
		A m_m_a value of type double
		A m_m_b value of type double
		A m_m_c value of type double
	
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey of type uint16
			An attribute of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey of type uint16
			An attribute of type double
		GetExternalDefinition with a return type of uint16
		Equals with a return type of bool that takes the following parameters:
			An attribute object of type FuelAttribute
		Clone with a return type of FuelAttribute
		ISF (ISI with zero wind upslope) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int64_t
			A RSF_C2 value of type double
			A RSF_D1 value of type double
			A SF value of type double
			A ISZ value of type double
*/
class ISF_M3M4 : public ISFAttribute {
private:
	double m_m_a, m_m_b, m_m_c;

public:
	ISF_M3M4();
	ISF_M3M4(const ISF_M3M4 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_ISF_M3M4; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new ISF_M3M4(*this); };

	virtual double ISF(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double RSF_C2, double RSF_D1, double SF, double ISZ) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::IsfAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual ISF_M3M4 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the ISF_O1 class which inherits the methods and variables from ISFAttribute
	
	Variable list:
		A m_threshold value of type double
		A m_f1 value of type double
		A m_f2 value of type double
		A m_f3 value of type double
		A m_f4 value of type double
		
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey of type uint16
			An attribute of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey of type uint16
			An attribute of type double
		GetExternalDefinition with a return type of uint16
		Equals with a return type of bool that takes the following parameters:
			An attribute object of type FuelAttribute
		Clone with a return type of FuelAttribute
		ISF (ISI with zero wind upslope) with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int64_t
			A RSF_C2 value of type double
			A RSF_D1 value of type double
			A SF value of type double
			A ISZ value of type double
*/
class ISF_O1 : public ISFAttribute {
private:
	double m_threshold;
	double m_f1, m_f2, m_f3, m_f4;

public:
	ISF_O1();
	ISF_O1(const ISF_O1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_ISF_O1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new ISF_O1(*this); };

	virtual double ISF(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double RSF_C2, double RSF_D1, double SF, double ISZ) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::IsfAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual ISF_O1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif // define sfc_h
