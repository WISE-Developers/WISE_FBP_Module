/**
 * WISE_FBP_Module: FuelAttribute.h
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

#ifndef __FBPFUEL_ATTRIBUTE_H
#define __FBPFUEL_ATTRIBUTE_H

#include "ICWFGM_Fuel.h"
#include "FuelCom_ext.h"
#include "ccwfgmFuel.pb.h"
#include "ISerializeProto.h"

#pragma warning(push)
#pragma warning(disable : 4100)				// turn off warning 'unreferenced formal parameter'
#pragma warning(disable : 4035)				// turn off warning 'no return value'
#pragma warning(disable : 4715)				// turn off warning 'not all control paths return a value'

class FUELCOM_API FuelAttribute: public ISerializeProto {
public:
	FuelAttribute()																						{ };
	FuelAttribute(const FuelAttribute & /*toCopy*/)														{ };
	virtual ~FuelAttribute()																			{ };

	virtual HRESULT GetAttributeValue(std::uint16_t /*attributeKey*/, double* /*attribute*/ ) const		{ return E_UNEXPECTED; };
	virtual HRESULT SetAttributeValue(std::uint16_t /*attributeKey*/, double /*attribute*/)				{ weak_assert(0); return E_UNEXPECTED; };
	virtual std::uint16_t GetExternalDefinition() const													{ weak_assert(0); return (std::uint16_t)1; };
	virtual bool Equals(const FuelAttribute * /*attribute*/)	const									{ weak_assert(0); return false; };
	virtual FuelAttribute *Clone() const																{ weak_assert(0); return nullptr; };

	virtual FuelAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override = 0;
};

/*
	Declaration for the SpreadParmsAttribute class which inherits the methods and variables from FuelAttribute.  This interface class abtracts the table found in STX-3, page 60.
	Initially this table was embedded as hard-coded values but we had unused fiels for some fuel types (mixed, grass, slash).  The introduction of grass phenology introduced the
	appropriate time to refactor this class so that each line in the table could be stored more efficiently, as well as handle grass phenology AND introduce more debugging
	statements, being ensuring that the fuel that is asking for a value from this table is the appropriate type of fuel (e.g. M-1 doesn't look at the 'A' values in the table.)
	
	Method list:
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

class ISerializationData_SP : public ISerializationData {
public:
	boost::intrusive_ptr<ICWFGM_Fuel> c2;
	boost::intrusive_ptr<ICWFGM_Fuel> d1;

	class SpreadParmsAttribute* original;
};


class ISerializationData_FMC : public ISerializationData {
public:
	class FMCAttribute* original;
};


class ISerializationData_SFC : public ISerializationData {
public:
	class SFCAttribute* original;
};


class ISerializationData_TFC : public ISerializationData {
public:
	class TFCAttribute* original;
};


class ISerializationData_CFB : public ISerializationData {
public:
	class CFBAttribute* original;
};


class ISerializationData_RSI : public ISerializationData {
public:
	class RSIAttribute* original;
};


class ISerializationData_ISF : public ISerializationData {
public:
	class ISFAttribute* original;
};


class ISerializationData_ACC : public ISerializationData {
public:
	class AccAlphaAttribute* original;
};


class ISerializationData_LB : public ISerializationData {
public:
	class LBAttribute* original;
};

class ISerializationData_FL : public ISerializationData {
public:
	class FlameLengthAttribute* original;
};


class SpreadParmsAttribute : public FuelAttribute {
public:
	virtual double A(std::int16_t /*flag*/) const { weak_assert(0); return 0.0; };
	virtual double B(std::int16_t /*flag*/) const { weak_assert(0); return 0.0; };
	virtual double C(std::int16_t /*flag*/) const { weak_assert(0); return 0.0; };
	virtual double Q() const { weak_assert(0); return 0.0; };
	virtual double BUI0() const { weak_assert(0); return 0.0; };
	virtual double MaxBE() const { weak_assert(0); return 0.0; };
	virtual double Height(const CCWFGM_FuelOverrides* /*overrides*/) const { weak_assert(0); return 0.0; };
	virtual double CBH(const CCWFGM_FuelOverrides* /*overrides*/) const { weak_assert(0); return 0.0; };
	virtual double CFL(const CCWFGM_FuelOverrides* /*overrides*/) const { weak_assert(0); return 0.0; };
	virtual double CuringDegree(const CCWFGM_FuelOverrides* /*overrides*/) const { weak_assert(0); return 0.0; };
	virtual double PC(const CCWFGM_FuelOverrides* /*overrides*/) const { weak_assert(0); return 0.0; };

	virtual void C2(boost::intrusive_ptr<ICWFGM_Fuel> & /*c2*/) { weak_assert(0); }
	virtual void D1(boost::intrusive_ptr<ICWFGM_Fuel> & /*d1*/) { weak_assert(0); }

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SpreadParmsAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SpreadParmsAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData* defaults) override;
	virtual SpreadParmsAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the FMCAttribute class which inherits the methods and variables from FuelAttribute.  There are two types of fuel types
	in the FBP standard - those which need FMC, and those which do not.  Each fuel type needs one of these two calculator classes.  Derived
	classes can be found declared in fmc.h
	
	Method list:
	FMC (foliar moisture content) with a return type double that takes the following parameters: 
		A latitude value of type double
		A longitude value of type double
		An elevation value of type double
		A day value of type uint16
*/
class FMCAttribute : public FuelAttribute {
public:
	virtual double FMC(double /*lat*/, double /*lon*/, double /*elev*/, std::uint16_t /*day*/, const CCWFGM_FuelOverrides* /*overrides*/) const { weak_assert(0); return 0.0; }

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FmcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FMCAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual FMCAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const  noexcept override { return std::nullopt; }
};

/*
	Declaration for the SFCAttribute class which inherits the methods and variables from FuelAttribute
	
	Method list:
	SFC (total surface fuel consumption) with a return type double that takes the following as parameters: 
		A SpreadParmsAttribute object
		A flag value of type int16
		A FFMC value of type double 
		A BUI value of type double
*/
class SFCAttribute : public FuelAttribute {
public:
	virtual double SFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double /*FFMC*/, double /*BUI*/) const { weak_assert(0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::SfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual SFCAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual SFCAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the TFCAttribute class which inherits the methods and variables from FuelAttribute
	
	Method list:
	TFC (total fuel consumption) with a return type double that takes the following as parameters:
		SpreadParmsAttribute object
		A flag value of type int16
		A CFB value of type double
		A SFC value of type double
		A CFC value of type double
*/
class TFCAttribute : public FuelAttribute {
public:
	virtual double TFC(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double /*CFB*/, double /*SFC*/, double* /*CFC*/) const { weak_assert(0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::TfcAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual TFCAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual TFCAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the CFBAttribute class which inherits the methods and variables from FuelAttribute
	
	Method list:
	CFB (crown fraction burned) with a return type double that takes the following as parameters:
		A CBH value of type double -  value taken from the table found in STX-3, page 60
		A FMC value of type double
		A SFC value of type double
		A ROS value of type double
		A rso value of type double
		A csi value of type double
*/
class CFBAttribute : public FuelAttribute {
public:
	virtual double CFB(double /*CBH*/, double /*FMC*/, double /*SFC*/, double /*ROS*/, double* /*rso*/, double* /*csi*/) const { weak_assert(0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::CfbAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual CFBAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual CFBAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the RSIAttribute class which inherits the methods and variables from FuelAttribute
	
	Method list:
	RSI (initial spread rate without BUI effect) with a return type double that takes the following as parameters:
		A SpreadParmsAttribute object
		A flag value of type int16
		A ISI value of type double
		A FMC value of type double
		A BUI value of type double -  value taken from the table found in STX-3, page 60
		A FFMC value of type double
		A BE value of type double
		A rsi_c2 value of type double
		A rsi_d1 value of type double
	ROS (final spread rate) with a return type double that takes the following as parameters:
		A RSI value of type double
		A CBH value of type double -  value taken from the table found in STX-3, page 60
		A ISI value of type double
		A FMC value of type double
		A SFC value of type double
		A CFBAttribute object
	FOR_FROS (flank fire spread rate) with a return type double that takes the following as parameters:
		A RSS value of type double
		A ROS value of type double
		A CFB value of type double
*/
class RSIAttribute : public FuelAttribute {
public:
	virtual double RSI(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* overrides, double /*ISI*/, double /*FMC*/, double /*BUI*/, double /*FFMC*/, double /*BE*/,
		double * /*rsi_c2*/, double * /*rsi_d1*/) const
											{ weak_assert(0); return 0.0; };
	virtual double ROS(double /*RSI*/, double /*CBH*/, double /*ISI*/, double /*FMC*/, double /*SFC*/, CFBAttribute* /*cfb*/) const
											{ weak_assert(0); return 0.0; };
	virtual double FOR_FROS(double /*RSS*/, double /*ROS*/, double /*CFB*/) const { weak_assert(0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::RsiAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual RSIAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual RSIAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the ISFAttribute class which inherits the methods and variables from FuelAttribute
	
	Method list:
	ISF (ISI with zero wind upslope) with a return type double that takes the following as parameters:
		A SpreadParmsAttribute object
		A flag value of type int16
		A RSF_C2 value of type double
		A RSF_D1 value of type double
		A SF value of type double
		A ISZ value of type double
*/
class ISFAttribute : public FuelAttribute {
public:
 	virtual double ISF(SpreadParmsAttribute * /*sa*/, std::int16_t /*flag*/, const CCWFGM_FuelOverrides* /*overrides*/, double /*RSF_C2*/, double /*RSF_D1*/, double /*SF*/, double /*ISZ*/) const
											{ weak_assert(0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::IsfAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual ISFAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual ISFAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the AccAlphaAttribute class which inherits the methods and variables from FuelAttribute
	
	Method list:
	ACCAlpha with a return type double that takes the following as parameters:
		A CFB value of type double
*/
class AccAlphaAttribute : public FuelAttribute {
public:
	virtual double AccAlpha(double /*CFB*/) const					{ weak_assert (0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::AccAlphaAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual AccAlphaAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual AccAlphaAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the LBAttribute class which inherits the methods and variables from FuelAttribute
	
	Method list:
	LB (length-to-breadth ratio) with a return type double that takes the following as parameters:
		A WSV value of type double
*/
class LBAttribute : public FuelAttribute {
public:
	virtual double LB(double /*WSV*/) const						{ weak_assert (0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::LbAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual LBAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual LBAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

/*
	Declaration for the DBHAttribute class which inherits the methods and variables from FuelAttribute.  Height -> DBH calculations are not part
	of the FBP standard but is included here since it's the ideal location for this functionality.
	
	Method list:
	DBH with a return type double that takes the following as parameters:
		A height value of type double
	SpeciesCode with a return type string
	SpeciesCode with a return type void that takes the following as parameters:
		A code value of type string
*/
class DBHAttribute : public FuelAttribute {
public:
	virtual double DBH(double /*height*/) const					{ weak_assert(0); return 0.0; };
	virtual std::string SpeciesCode() const						{ weak_assert(0); return ""; };
	virtual void SpeciesCode(const std::string & /*code*/)		{ weak_assert(0); };
};

/*
	Declaration for the FlameLengthAttribute class which inherits the methods and variables from FuelAttribute.  Flame length is not part of the
	FBP standard but is included here since it's the ideal location for this functionality.
	
	Method list:
	FlameLength with a return type double that takes the following as parameters:
		A height value of type double
		A CFB value of type double
		A fi value of type double
*/
class FlameLengthAttribute : public FuelAttribute {
public:
	virtual double FlameLength(double /*height*/, double /*CFB*/, double /*fi*/, const CCWFGM_FuelOverrides* /*overrides*/) const { weak_assert(0); return 0.0; };

	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept override { return 1; }
	virtual WISE::FuelProto::FlameLengthAttribute* serialize(const SerializeProtoOptions& options) override;
	virtual FlameLengthAttribute *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData *defaults) override;
	virtual FlameLengthAttribute *deserialize(const google::protobuf::Message& /*proto*/, std::shared_ptr<validation::validation_object> /*valid*/, const std::string& /*name*/) override { weak_assert(0); return nullptr; }
	virtual std::optional<bool> isdirty() const noexcept override { return std::nullopt; }
};

// revert warning messages to defaults
#pragma warning(pop)

#endif
