/**
 * WISE_FBP_Module: flame.h
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

#ifndef __FLAMELENGTH_H_
#define __FLAMELENGTH_H_

#include "FuelAttribute.h" 
#include "ccwfgmFuel.pb.h"

/*
	Declaration for the FlameLength_Alexander82 class which inherits the methods and variables from FlameLengthAttribute
	
	Variable list:
		m_p1 of type double
		m_p2 of type double
	
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
		FlameLength with a return type double that takes the following parameters:
			A height of type double
			A CFB of type double
			A fi of type double
*/
class FlameLength_Alexander82 : public FlameLengthAttribute {
protected:
	double m_p1, m_p2;

public:
	FlameLength_Alexander82();
	FlameLength_Alexander82(const FlameLength_Alexander82 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_FLAMELENGTH_ALEXANDER82; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute* Clone() const override		{ return new FlameLength_Alexander82(*this); }

	virtual double FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FlameLengthAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FlameLength_Alexander82 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the FlameLength_Alexander82_Tree class which inherits the methods and variables from FlameLengthAttribute
	
	Variable list:
		m_cfb of type double
		m_th of type double
	
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
		FlameLength with a return type double that takes the following parameters:
			A height of type double
			A CFB of type double
			A fi of type double
*/
class FlameLength_Alexander82_Tree : public FlameLength_Alexander82 {
protected:
	double m_cfb, m_th;

public:
	FlameLength_Alexander82_Tree();
	FlameLength_Alexander82_Tree(const FlameLength_Alexander82_Tree &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_FLAMELENGTH_ALEXANDER82_TREE; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute* Clone() const override		{ return new FlameLength_Alexander82_Tree(*this); }

	virtual double FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FlameLengthAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FlameLength_Alexander82_Tree *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the FlameLength_Tree class which inherits the methods and variables from FlameLengthAttribute
	
	Variable list:
		m_p1 of type double
		m_th of type double
		m_cfb of type double
	
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
		FlameLength with a return type double that takes the following parameters:
			A height of type double
			A CFB of type double
			A fi of type double
*/
class FlameLength_Tree : public FlameLengthAttribute {
protected:
	double m_p1, m_th, m_cfb;

public:
	FlameLength_Tree();
	FlameLength_Tree(const FlameLength_Tree &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_FLAMELENGTH_TREE; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute* Clone() const override		{ return new FlameLength_Tree(*this); }

	virtual double FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FlameLengthAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FlameLength_Tree *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the FlameLength_Other class which inherits the methods and variables from FlameLengthAttribute
	
	Variable list:
		m_p1 of type double
	
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
		FlameLength with a return type double that takes the following parameters:
			A height of type double
			A CFB of type double
			A fi of type double
*/
class FlameLength_Other : public FlameLengthAttribute {
protected:
	double m_p1;

public:
	FlameLength_Other();
	FlameLength_Other(const FlameLength_Other &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_FLAMELENGTH_OTHER; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute* Clone() const override		{ return new FlameLength_Other(*this); }

	virtual double FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FlameLengthAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FlameLength_Other *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif // define sfc_h
