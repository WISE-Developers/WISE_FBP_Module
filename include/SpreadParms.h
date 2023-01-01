/**
 * WISE_FBP_Module: SpreadParms.h
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

#ifndef __SPREADPARMS_H_
#define __SPREADPARMS_H_

#ifdef MSVC_COMPILER
#pragma managed(push, off)
#endif

#include "FuelAttribute.h"
#include "ccwfgmFuel.pb.h"

/*
	Declaration for the SpreadParms_S1 class which inherits the methods and variables from SpreadParmsAttribute

	Variable list:
		m_a of type double
		m_b of type double
		m_c of type double
		m_q of type double
		m_bui0 of type double
		m_max_be of type double
	
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
		A (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		B (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		C (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		Q - value taken from the table found in STX-3
		BUI0 (initial buildup index) with a return type double -  value taken from the table found in STX-3, page 60
		MaxBE (maximum buildup effect on spread rate) with a return type double - value taken from the table found in STX-3, page 60
		Height with a return type double
		CBH (height to live crown base (m)) with a return type double - value taken from the table found in STX-3, page 60
		CFL (crown fuel load (kg/m^2)) with a return type double - value taken from the table found in STX-3, page 60
		CuringDegree with a return type double
		PC (percent conifer) with a return type double
		
		C2 is only valid for mixed fuel types, and returns a reference to the C2 fuel type implementation
		D1 is only valid for mixed fuel types, and returns a reference to the D1 fuel type implementation
*/
class SpreadParms_S1 : public SpreadParmsAttribute {
protected:
	double	m_a;
	double	m_b;
	double	m_c;

	double	m_q;		// proportion of max spread rate
	double	m_bui0;		// the average bui for the fuel type
	double	m_max_be;	// maximum effect of bui on the ROS.

public:
	SpreadParms_S1();
	SpreadParms_S1(const SpreadParms_S1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_S1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override		{ return new SpreadParms_S1(*this); }

	virtual double A(std::int16_t flag) const override;
	virtual double B(std::int16_t flag) const override;
	virtual double C(std::int16_t flag) const override;
	virtual double Q() const override;
	virtual double BUI0() const override;
	virtual double MaxBE() const override;
	virtual double Height(const CCWFGM_FuelOverrides* /*overrides*/) const override { return 0.0; };
	virtual double CBH(const CCWFGM_FuelOverrides* /*overrides*/) const override { return 0.0; };
	virtual double CFL(const CCWFGM_FuelOverrides* /*overrides*/) const override { return 0.0; };
	virtual double CuringDegree(const CCWFGM_FuelOverrides* /*overrides*/) const override { return -1.0; }
	virtual double PC(const CCWFGM_FuelOverrides* /*overrides*/) const override { return -1.0; }
	virtual void C2(boost::intrusive_ptr<ICWFGM_Fuel> & /*c2*/) override { }
	virtual void D1(boost::intrusive_ptr<ICWFGM_Fuel> & /*d1*/) override { }

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_S1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_C1 class which inherits the methods and variables from SpreadParmsAttribute

	Variable list:
		m_height of type double
		m_cbh of type double
		m_cfl of type double
	
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
		Height with a return type double
		CBH (height to live crown base (m)) with a return type double - value taken from the table found in STX-3, page 60
		CFL (crown fuel load (kg/m^2)) with a return type double - value taken from the table found in STX-3, page 60
*/
class SpreadParms_C1 : public SpreadParms_S1 {
protected:
	double	m_height;	// stand height (m)
	double	m_cbh;		// height to live crown base
	double	m_cfl;		// crown fuel load

public:
	SpreadParms_C1();
	SpreadParms_C1(const SpreadParms_C1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_C1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new SpreadParms_C1(*this); }

	virtual double Height(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CBH(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CFL(const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_C1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_C6 class which inherits the methods and variables from SpreadParms_C1

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
*/
class SpreadParms_C6 : public SpreadParms_C1 {
public:
	SpreadParms_C6() : SpreadParms_C1() { }
	SpreadParms_C6(const SpreadParms_C6 &toCopy) : SpreadParms_C1(toCopy) { }

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_C6; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new SpreadParms_C6(*this); }

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_C6 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_D1 class which inherits the methods and variables from SpreadParms_C1

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
*/
class SpreadParms_D1 : public SpreadParms_C1 {
public:
	SpreadParms_D1() : SpreadParms_C1() { }
	SpreadParms_D1(const SpreadParms_C1 &toCopy) : SpreadParms_C1(toCopy) { }

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_D1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new SpreadParms_D1(*this); }

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_D1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_NZ class which inherits the methods and variables from SpreadParms_C1

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
*/
class SpreadParms_NZ : public SpreadParms_C1 {
public:
	SpreadParms_NZ() : SpreadParms_C1() { }
	SpreadParms_NZ(const SpreadParms_NZ &toCopy) : SpreadParms_C1(toCopy) { }

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_NZ; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override { return new SpreadParms_NZ(*this); }

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_NZ *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_O1 class which inherits the methods and variables from SpreadParmsAttribute

	Variable list:
		m_curingDegree of type double
	
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
		CuringDegree with a return type double
*/
class SpreadParms_O1 : public SpreadParms_S1 {
protected:
	double	m_curingDegree;	// degree of curing ( 0-1 )

public:
	SpreadParms_O1();
	SpreadParms_O1(const SpreadParms_O1 &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override		{ return new SpreadParms_O1(*this); }

	virtual double CuringDegree(const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_O1 *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_O1ab class which inherits the methods and variables from SpreadParms_O1

	Variable list:
		m_o1ab_standing_a of type double
		m_o1ab_standing_b of type double
		m_o1ab_standing_c of type double
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
		A (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		B (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		C (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
*/
class SpreadParms_O1ab : public SpreadParms_O1 {
private:
	double m_o1ab_standing_a;
	double m_o1ab_standing_b;
	double m_o1ab_standing_c;

public:
	SpreadParms_O1ab();
	SpreadParms_O1ab(const SpreadParms_O1ab &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_O1AB; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override		{ return new SpreadParms_O1ab(*this); }

	virtual double A(std::int16_t flag) const override;
	virtual double B(std::int16_t flag) const override;
	virtual double C(std::int16_t flag) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_O1ab *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_Mixed class which inherits the methods and variables from SpreadParmsAttribute

	Variable list:
		m_q of type double
		m_bui0 of type double
		m_max_be of type double
		m_height of type double
		m_cbh of type double
		m_cfl of type double
		m_pc of type double
		m_C2 of type double
		m_D1 of type double
	
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
		A (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		B (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		C (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		Q - value taken from the table found in STX-3
		BUI0 (initial buildup index) with a return type double -  value taken from the table found in STX-3, page 60
		MaxBE (maximum buildup effect on spread rate) with a return type double - value taken from the table found in STX-3, page 60
		Height with a return type double
		CBH (height to live crown base (m)) with a return type double - value taken from the table found in STX-3, page 60
		CFL (crown fuel load (kg/m^2)) with a return type double - value taken from the table found in STX-3, page 60
		CuringDegree with a return type double
		PC (percent conifer) with a return type double
		
		C2 is only valid for mixed fuel types, and returns a reference to the C2 fuel type implementation
		D1 is only valid for mixed fuel types, and returns a reference to the D1 fuel type implementation
		SetC2 with a return type void that takes the following parameters:
			A c2 object of type ICWFGM_Fuel
			A d1 object of type ICWFGM_Fuel
*/
class SpreadParms_Mixed : public SpreadParmsAttribute {
protected:
	double	m_q;		// proportion of max spread rate
	double	m_bui0;		// the average bui for the fuel type
	double	m_max_be;	// maximum effect of bui on the ROS.

	double	m_height;	// stand height (m)
	double	m_cbh;		// height to live crown base
	double	m_cfl;		// crown fuel load

	double m_pc;
	boost::intrusive_ptr<ICWFGM_Fuel> m_C2;
	boost::intrusive_ptr<ICWFGM_Fuel> m_D1;

public:
	SpreadParms_Mixed();
	SpreadParms_Mixed(const SpreadParms_Mixed &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXED; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override		{ return new SpreadParms_Mixed(*this); }

	virtual double A(std::int16_t /*flag*/) const override { return -1.0; };
	virtual double B(std::int16_t /*flag*/) const override { return -1.0; };
	virtual double C(std::int16_t /*flag*/) const override { return -1.0; };
	virtual double Q() const override;
	virtual double BUI0() const override;
	virtual double MaxBE() const override;
	virtual double Height(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CBH(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CFL(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CuringDegree(const CCWFGM_FuelOverrides* /*overrides*/) const override { return -1.0; };
	virtual double PC(const CCWFGM_FuelOverrides* overrides) const override;
	virtual void C2(boost::intrusive_ptr<ICWFGM_Fuel> &c2) override;
	virtual void D1(boost::intrusive_ptr<ICWFGM_Fuel> &d1) override;

	virtual void SetC2(boost::intrusive_ptr<ICWFGM_Fuel> &c2);
	virtual void SetD1(boost::intrusive_ptr<ICWFGM_Fuel> &d1);

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_Mixed *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_MixedDead class which inherits the methods and variables from SpreadParms_Mixed

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
*/
class SpreadParms_MixedDead : public SpreadParms_Mixed {
public:
	SpreadParms_MixedDead() : SpreadParms_Mixed() { }
	SpreadParms_MixedDead(const SpreadParms_Mixed &toCopy) : SpreadParms_Mixed(toCopy) { }

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual HRESULT SetAttributeValue(std::uint16_t attributeKey, double attribute) override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_MIXEDDEAD; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override		{ return new SpreadParms_MixedDead(*this); }

	virtual double PC(const CCWFGM_FuelOverrides* overrides) const override;

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_MixedDead *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the SpreadParms_Non class which inherits the methods and variables from SpreadParmsAttribute

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
		A (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		B (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		C (rate of spread equation coefficient) with a return type double that takes the following parameters:
			A flag value of type short - this examines the grass phenology bit from the flags parameter passed to this library to determine which "A" value to return.  If the object does not
										 care about grass phenology, then the value returned is simply the 'A' value taken from the table found in STX-3, page 60
		Q - value taken from the table found in STX-3
		BUI0 (initial buildup index) with a return type double -  value taken from the table found in STX-3, page 60
		MaxBE (maximum buildup effect on spread rate) with a return type double - value taken from the table found in STX-3, page 60
		Height with a return type double
		CBH (height to live crown base (m)) with a return type double - value taken from the table found in STX-3, page 60
		CFL (crown fuel load (kg/m^2)) with a return type double - value taken from the table found in STX-3, page 60
		CuringDegree with a return type double
		PC (percent conifer) with a return type double
		
		C2 is only valid for mixed fuel types, and returns a reference to the C2 fuel type implementation
		D1 is only valid for mixed fuel types, and returns a reference to the D1 fuel type implementation
*/
class SpreadParms_Non : public SpreadParmsAttribute {
private:

public:
	SpreadParms_Non();
	SpreadParms_Non(const SpreadParms_Non &toCopy);

	virtual HRESULT GetAttributeValue(std::uint16_t attributeKey, double *attribute) const override;
	virtual std::uint16_t GetExternalDefinition() const override { return FUELCOM_EQUATION_SELECTION_SPREADPARMS_NON; };
	virtual bool Equals(const FuelAttribute *attribute) const override;
	virtual FuelAttribute *Clone() const override		{ return new SpreadParms_Non(*this); }

	virtual double A(std::int16_t flag) const override;
	virtual double B(std::int16_t flag) const override;
	virtual double C(std::int16_t flag) const override;
	virtual double Q() const override;
	virtual double BUI0() const override;
	virtual double MaxBE() const override;
	virtual double Height(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CBH(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CFL(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double CuringDegree(const CCWFGM_FuelOverrides* overrides) const override;
	virtual double PC(const CCWFGM_FuelOverrides* /*overrides*/) const override { return 0.0; }
	virtual void C2(boost::intrusive_ptr<ICWFGM_Fuel> & /*c2*/) override { }
	virtual void D1(boost::intrusive_ptr<ICWFGM_Fuel> & /*d1*/) override { }

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParms_Non *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) override;
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

#ifdef MSVC_COMPILER
#pragma managed(pop)
#endif

#endif // define sfc_h
