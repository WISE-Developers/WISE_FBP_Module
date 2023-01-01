/**
 * WISE_FBP_Module: fmc.h
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

#ifndef __FMC_H_
#define __FMC_H_

#include "FuelAttribute.h" 
#include "ccwfgmFuel.pb.h"
#include "valuecache_mt.h"

/*
	Declaration for the FMC_Calc class which inherits the methods and variables from FMCAttribute
	
	Variable list:
		key value that stores the following variables:
			m_lat of type double
			m_lon of type double
			m_elev of type double
			m_day of type double
		m_cache of type ValueCacheTempl_MT
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type HRESULT that takes the following parameters:
			An attribute key of type std::uint16_t
			An attribute of type double
		SetAttributeValue with return type HRESULT that takes the following parameters:
			An attribute key of type std::uint16_t
			An attribute of type double
		GetExternalDefinition with return type std::uint16_t
		Equals with a return type bool that takes the following parameters:
			An attribute of type FuelAttribute
		FMC (foliar moisture content) with return type double that takes the following parameters:
			A lat value of type double
			A lon value of type double
			A elev value of type double
			A day value of type uint16_t
		Clone with a return type FuelAttribute
*/
class FMC_Calc : public FMCAttribute {
	struct key {
		double m_lat, m_lon, m_elev, m_day;
	};
	mutable ValueCacheTempl_MT<key, double> m_cache;

public:
	FMC_Calc();
	FMC_Calc(const FMC_Calc &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_FMC_CALC; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new FMC_Calc(*this); };

	virtual double FMC(double lat, double lon, double elev, std::uint16_t day, const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FmcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FMC_Calc *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }

private:
	std::int16_t	m_day0;
};

/*
	Declaration for the FMC_NoCalc class which inherits the methods and variables from FMCAttribute

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with return type std::uint16_t
		Equals with a return type bool that takes the following parameters:
			An attribute of type FuelAttribute
		Clone with a return type FuelAttribute
		FMC (foliar moisture content) with return type double that takes the following parameters:
			A lat value of type double
			A lon value of type double
			A elev value of type double
			A day value of type uint16_t
*/
class FMC_NoCalc : public FMCAttribute {
public:
	FMC_NoCalc();
	FMC_NoCalc(const FMC_NoCalc &toCopy);

	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_FMC_NOCALC; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new FMC_NoCalc(*this); };

	virtual double FMC(double lat, double lon, double elev, std::uint16_t day, const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FmcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FMC_NoCalc *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif // define fmc_h
