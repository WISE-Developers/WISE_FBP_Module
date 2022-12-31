/**
 * WISE_FBP_Module: AccAlpha.h
 * Copyright (C) 2023  <Project Name>
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

#ifndef __ACCALPHA_H_
#define __ACCALPHA_H_

#include "FuelAttribute.h" 
#include "valuecache_mt.h"

/**
 * Declaration for the AccAlphaClosed class which inherits the methods and variables from AccAlphaAttribute
 * 
 * Variable list:
 * - m_init of type double
 * - m_multiplier of type double
 * - m_power of type double
 * - m_exp_multiplier of type double
 * - m_cache of type ValueCacheTempl_MT
	
 * Method list:
 * - No argument constructor
 * - Copy constructor
 * - GetAttributeValue with a return type of HRESULT that takes the following parameters:
 *   - An attributeKey value of type uint16_t
 *   - An attribute value of type double
 * - SetAttributeValue with a return type of HRESULT that takes the following parameters:
 *   - An attributeKey value of type uint16_t
 *   - An attribute value of type double
 * - GetExternalDefinition with a return type of uint16_t
 * - Equals with a return type of bool that takes the following parameters:
 *   - An attribute value of type FuelAttribute
 * - Clone with a return type of FuelAttribute
 * - AccAlpha with a return type of double that takes the following parameters:
 *   - A CFB value of type double
 */
class AccAlphaClosed : public AccAlphaAttribute {
private:
	double m_init;
	double m_multiplier;
	double m_power;
	double m_exp_multiplier;

	mutable ValueCacheTempl_MT<double, double> m_cache;

public:
	AccAlphaClosed();
	AccAlphaClosed(const AccAlphaClosed &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const	override	{ return FUELCOM_EQUATION_SELECTION_ACCEL_CLOSED; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new AccAlphaClosed(*this); };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::AccAlphaAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual AccAlphaClosed *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }

	virtual double AccAlpha(double CFB) const override;
};

/**
 * Declaration for the AccAlphaOpen class which inherits the methods and variables from AccAlphaAttribute
 * 
 * Variable list:
 * 	m_init of type double
 * 
 * Method list:
 * 	No argument constructor
 * 	Copy constructor
 * 	GetAttributeValue with a return type of HRESULT that takes the following parameters:
 * 		An attributeKey value of type uint16_t
 * 		An attribute value of type double
 * 	SetAttributeValue with a return type of HRESULT that takes the following parameters:
 * 		An attributeKey value of type uint16_t
 * 		An attribute value of type double
 * 	GetExternalDefinition with a return type of uint16_t
 * 	Equals with a return type of bool that takes the following parameters:
 * 		An attribute value of type FuelAttribute
 * 	Clone with a return type of FuelAttribute
 * 	AccAlpha with a return type of double that takes the following parameters:
 * 		A CFB value of type double
 */
class AccAlphaOpen : public AccAlphaAttribute {
private:
	double m_init;

public:
	AccAlphaOpen();
	AccAlphaOpen(const AccAlphaOpen &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const	override	{ return FUELCOM_EQUATION_SELECTION_ACCEL_OPEN; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new AccAlphaOpen(*this); };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::AccAlphaAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual AccAlphaOpen *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override	{ return std::nullopt; }

	virtual double AccAlpha(double CFB) const override;
};


#endif // define sfc_h
