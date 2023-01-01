/**
 * WISE_FBP_Module: lb.h
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

#ifndef __LB_H_
#define __LB_H_

#include "FuelAttribute.h" 
#include "ccwfgmFuel.pb.h"
#include "valuecache_mt.h"

/*
	Declaration for the LB_C1 class which inherits the methods and variables from LBAttribute
	
	Variable list:
		A m_cache value of type ValueCacheTempl_MT
		A m_init value of type double
		A m_multiplier value of type double
		A m_exp_multiplier value of type double
		A m_power value of type double
	
	Method list:
	No argument constructor
	Copy constructor
	GetAttributeValue with a return type of HRESULT that takes the following parameters:
		An attributeKey value of type double
		An attribute value of type double
	SetAttributeValue with a return type of HRESULT that takes the following parameters:
		An attributeKey value of type double
		An attribute value of type double
	GetExternalDefinition with a return type of uint16_t
	Equals with a return type of bool that takes the following parameters:
		An attribute value of type FuelAttribute
	Clone with a return type of FuelAttribute
	LB (length-to-breadth ratio) with a return type of double that takes the following parameters:
		A WSV value of type double
*/
class LB_C1 : public LBAttribute {
private:
	mutable ValueCacheTempl_MT<double, double> m_cache;

private:
	double m_init;
	double m_multiplier;
	double m_exp_multiplier;
	double m_power;

public:
	LB_C1();
	LB_C1(const LB_C1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_LB_C1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new LB_C1(*this); };

	virtual double LB(double WSV) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::LbAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual LB_C1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the LB_O1 class which inherits the methods and variables from LBAttribute
	
	Variable list:
		A m_cache value of type ValueCacheTempl_MT
		A m_init value of type double
		A m_power value of type double
	
	Method list:
	No argument constructor
	Copy constructor
	GetAttributeValue with a return type of HRESULT that takes the following parameters:
		An attributeKey value of type double
		An attribute value of type double
	SetAttributeValue with a return type of HRESULT that takes the following parameters:
		An attributeKey value of type double
		An attribute value of type double
	GetExternalDefinition with a return type of uint16_t
	Equals with a return type of bool that takes the following parameters:
		An attribute value of type FuelAttribute
	Clone with a return type of FuelAttribute
	LB (length-to-breadth ratio) with a return type of double that takes the following parameters:
		A WSV value of type double
*/
class LB_O1 : public LBAttribute {
private:
	mutable ValueCacheTempl_MT<double, double> m_cache;

private:
	double m_init;
	double m_power;

public:
	LB_O1();
	LB_O1(const LB_O1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_LB_O1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new LB_O1(*this); };

	virtual double LB(double WSV) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::LbAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual LB_O1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif // define sfc_h
