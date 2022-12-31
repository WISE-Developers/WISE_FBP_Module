/**
 * WISE_FBP_Module: cbh.h
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

#ifndef __CFB_H_
#define __CFB_H_

#include "FuelAttribute.h"

#include "valuecache_mt.h"
#include "ISerializeProto.h"

#include <stdexcept>

/**
 * Declaration for the CFB_C1 class which inherits the methods and variables from CFBAttribute
 * 	
 * Variable list:
 * 	A key value that stores the following variables:
 * 		A CBH value of type double
 * 		A FMC value of type double
 * 		A SFC value of type double
 * 		A ROS value of type double
 * 	A result value that stores the following variables:
 * 		A RSO value of type double
 * 		A CSI value of type double
 * 		A CFB value of type double
 * 	m_cache of type ValueCacheTempl_MT
 * 	m_csi_multiplier of type double
 * 	m_csi_cbh_exponent of type double
 * 	m_csi_exp_adder of type double
 * 	m_csi_exp_multiplier of type double
 * 	m_csi_power of type double
 * 	m_rso_div of type double
 * 	m_cfb_exp of type double
 * 	m_cfb_possible of type bool
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
 * 	CFB with a return type of double that takes the following parameters:
 * 		A CBH value of type double
 * 		A FMC value of type double
 * 		A SFC value of type double
 * 		A ROS value of type double
 * 		A rso value of type double
 * 		A csi value of type double
 */
class CFB_C1 : public CFBAttribute {
private:

	struct key {
		double cbh, fmc, sfc, ros;
	};
	struct result {
		double rso, csi, cfb;
	};
	mutable ValueCacheTempl_MT<key, result> m_cache;

private:
	double m_csi_multiplier;
	double m_csi_cbh_exponent;
	double m_csi_exp_adder;
	double m_csi_exp_multiplier;
	double m_csi_power;
	double m_rso_div;
	double m_cfb_exp;
	bool   m_cfb_possible;

public:
	CFB_C1();
	CFB_C1(const CFB_C1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const	override	{ return FUELCOM_EQUATION_SELECTION_CFB_C1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new CFB_C1(*this); };

	virtual double CFB(double CBH, double FMC, double SFC, double ROS, double *rso, double *csi) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::CfbAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual CFB_C1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override	{ return std::nullopt; }
};

/**
 * Declaration for the CFB_D2 class which inherits the methods and variables from CFBAttribute
 * 
 * Method list:
 * 	No argument constructor
 * 	Copy constructor
 * 	GetExternalDefinition with a return type of uint16_t
 * 	Equals with a return type of bool that takes the following parameters:
 * 		An attribute value of type FuelAttribute
 * 	Clone with a return type of FuelAttribute
 * 	CFB with a return type of double that takes the following parameters:
 * 		A CBH value of type double
 * 		A FMC value of type double
 * 		A SFC value of type double
 * 		A ROS value of type double
 * 		A rso value of type double
 * 		A csi value of type double
 */
class CFB_D2 : public CFBAttribute {
public:
	CFB_D2();
	CFB_D2(const CFB_D2 &toCopy);

	virtual std::uint16_t GetExternalDefinition() const	override			{ return FUELCOM_EQUATION_SELECTION_CFB_D2; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override							{ return new CFB_D2(*this); };

	virtual double CFB(double CBH, double FMC, double SFC, double ROS, double *rso, double *csi) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::CfbAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual CFB_D2 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override	{ return std::nullopt; }
};

#endif // define sfc_h
