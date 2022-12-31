/**
 * WISE_FBP_Module: dbh.h
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

#ifndef __DBH_H_
#define __DBH_H_

#include "FuelAttribute.h" 

/**
	Declaration for the DBH_None class which inherits the methods and variables from DBHAttribute
	
	Variable list:
		m_SpeciesCode of type string
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
		SpeciesCode with a return type of string
		SpeciesCode with a return type of void that takes the following parameters:
			A code value of type string
		DBH with a return type of double that takes the following parameters:
			A height value of type double
*/
class DBH_None : public DBHAttribute {
protected:
	std::string m_SpeciesCode;

public:
	DBH_None();
	DBH_None(const DBH_None &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual bool Equals(const FuelAttribute *attribute) const override;

	virtual std::string SpeciesCode() const override;
	virtual void SpeciesCode(const std::string &code) override;

	virtual double DBH(double height) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the DBH_HuangCommon class which inherits the methods and variables from DBHAttribute
	
	Variable list:
		m_b1 of type double
		m_b2 of type double
		m_b3 of type double
		m_SpeciesCode of type string
	Method list:
		No argument constructor
		Copy constructor
		GetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		SetAttributeValue with a return type of HRESULT that takes the following parameters:
			An attributeKey value of type uint16_t
			An attribute value of type double
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		SpeciesCode with a return type of string
		SpeciesCode with a return type of void that takes the following parameters:
			A code value of type string
*/
class DBH_HuangCommon : public DBHAttribute {
protected:
	double m_b1, m_b2, m_b3;
	std::string m_SpeciesCode;

public:
	DBH_HuangCommon();
	DBH_HuangCommon(const DBH_HuangCommon &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual bool Equals(const FuelAttribute *attribute) const override;

	virtual std::string SpeciesCode() const override;
	virtual void SpeciesCode(const std::string &code) override;


	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the DBH_1 class which inherits the methods and variables from DBH_HuangCommon

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of short
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		DBH with a return type of double that takes the following parameters:
			A height value of type double
*/
class DBH_1 : public DBH_HuangCommon {
public:
	DBH_1();
	DBH_1(const DBH_1 &toCopy);

	virtual bool Equals(const FuelAttribute *attribute) const override;

	virtual double DBH(double height) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the DBH_2 class which inherits the methods and variables from DBH_HuangCommon

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of short
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		DBH with a return type of double that takes the following parameters:
			A height value of type double
*/
class DBH_2 : public DBH_HuangCommon {
public:
	DBH_2();
	DBH_2(const DBH_2 &toCopy);

	virtual bool Equals(const FuelAttribute *attribute) const override;

	virtual double DBH(double height) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the DBH_3 class which inherits the methods and variables from DBH_HuangCommon

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of short
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		DBH with a return type of double that takes the following parameters:
			A height value of type double
*/
class DBH_3 : public DBH_HuangCommon {
public:
	DBH_3();
	DBH_3(const DBH_3 &toCopy);

	virtual bool Equals(const FuelAttribute *attribute) const override;

	virtual double DBH(double height) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the DBH_4 class which inherits the methods and variables from DBH_HuangCommon

	Method list:
		No argument constructor
		Copy constructor
		GetExternalDefinition with a return type of short
		Equals with a return type of bool that takes the following parameters:
			An attribute value of type FuelAttribute
		DBH with a return type of double that takes the following parameters:
			A height value of type double
*/
class DBH_4 : public DBH_HuangCommon {
public:
	DBH_4();
	DBH_4(const DBH_4 &toCopy);

	virtual bool Equals(const FuelAttribute *attribute) const override;

	virtual double DBH(double height) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#endif // define dbh_h
