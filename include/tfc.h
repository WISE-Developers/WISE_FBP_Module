/**
 * WISE_FBP_Module: tfc.h
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

#ifndef __TFC_H_
#define __TFC_H_

#include "FuelAttribute.h"

/*
	Declaration for the TFC_C1 class which inherits the methods and variables from TFCAttribute

	Method list:
		No argument constructor
		Copy constructor
		Destructor
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		TFC with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A CFB value of type double
			A SFC value of type double
			A CFC value of type double
*/
class TFC_C1 : public TFCAttribute {
public:
	TFC_C1();
	TFC_C1(const TFC_C1 &toCopy);
	virtual ~TFC_C1();

	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_TFC_C1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new TFC_C1(*this); };

	virtual double TFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double CFB, double SFC, double *CFC) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::TfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual TFC_C1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the TFC_D2 class which inherits the methods and variables from TFCAttribute

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		TFC with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A CFB value of type double
			A SFC value of type double
			A CFC value of type double
*/
class TFC_D2 : public TFCAttribute {
public:
	TFC_D2();
	TFC_D2(const TFC_D2 &toCopy);

	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_TFC_D2; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new TFC_D2(*this); };

	virtual double TFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double CFB, double SFC, double *CFC) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::TfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual TFC_D2 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the TFC_M1 class which inherits the methods and variables from TFCAttribute

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		TFC with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A CFB value of type double
			A SFC value of type double
			A CFC value of type double
*/
class TFC_M1 : public TFCAttribute {
public:
	TFC_M1();
	TFC_M1(const TFC_M1 &toCopy);

	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_TFC_M1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new TFC_M1(*this); };

	virtual double TFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double CFB, double SFC, double *CFC) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::TfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual TFC_M1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the TFC_O1 class which inherits the methods and variables from TFCAttribute

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of uint16_t
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		Clone with a return type of FuelAttribute
		TFC with a return type of double that takes the following parameters:
			A sa object of type SpreadParmsAttribute
			A flag value of type int16_t
			A CFB value of type double
			A SFC value of type double
			A CFC value of type double
*/
class TFC_O1 : public TFCAttribute {
public:
	TFC_O1();
	TFC_O1(const TFC_O1 &toCopy);

	virtual std::uint16_t GetExternalDefinition() const override	{ return FUELCOM_EQUATION_SELECTION_TFC_O1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override					{ return new TFC_O1(*this); };

	virtual double TFC(SpreadParmsAttribute *sa, std::int16_t flag, const CCWFGM_FuelOverrides* overrides, double CFB, double SFC, double *CFC) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::TfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual TFC_O1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif // define TFC_h
