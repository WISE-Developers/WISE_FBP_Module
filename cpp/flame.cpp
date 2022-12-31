/**
 * WISE_FBP_Module: flame.cpp
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

#if __has_include(<mathimf.h>)
#include <mathimf.h>
#else
#include <cmath>
#endif

#include "flame.h"
#include "doubleBuilder.h"
#include "str_printf.h"
#include "results.h"

#ifdef DEBUG
#include <assert.h>
#endif

/*
	This is a no-argument constructor to initialize a FlameLength_Alexander82 object
*/
FlameLength_Alexander82::FlameLength_Alexander82() {
	m_p1 = 0.0775;
	m_p2 = 0.46;
}

/*
	This is a 1-argument constructor to initialize a FlameLength_Alexander82 object by copying another FlameLength_Alexander82 object
*/
FlameLength_Alexander82::FlameLength_Alexander82(const FlameLength_Alexander82 &toCopy) {
	m_p1 = toCopy.m_p1;
	m_p2 = toCopy.m_p2;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a FlameLength_Alexander82 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Alexander82::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_DEFAULTS:		if ((m_p1 == 0.0775) && (m_p2 == 0.46))
																	return S_OK;
																return S_FALSE;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_P1:				*attribute = m_p1;	
																return S_OK;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_P2:				*attribute = m_p2;
																return S_OK;

	}
	return FlameLengthAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a FlameLength_Alexander82 and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Alexander82::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_DEFAULTS:		m_p1 = 0.0775; m_p2 = 0.46;	return S_OK;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_P1:				m_p1 = attribute;			return S_OK;
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_P2:				m_p2 = attribute;			return S_OK;
	}
	return FlameLengthAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the FlameLength_Alexander82 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool FlameLength_Alexander82::Equals(const FuelAttribute *attribute) const {
	const FlameLength_Alexander82 *a = dynamic_cast<const FlameLength_Alexander82 *>(attribute);
	if (!a)
		return false;
	if ((m_p1 != a->m_p1) || (m_p2 != a->m_p2))
		return false;
	return true;
}

/*
	This is a method to get the flame length of a FlameLength_Alexander82 object and takes the following parameters:
		A fi value of type double
*/
double FlameLength_Alexander82::FlameLength(double /*height*/, double /*CFB*/, double fi, const CCWFGM_FuelOverrides* /*overrides*/) const {
	double fl = m_p1 * pow(fi, m_p2);
	return fl;
}


WISE::FuelProto::FlameLengthAttribute* FlameLength_Alexander82::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FlameLengthAttribute *attr = new WISE::FuelProto::FlameLengthAttribute();
	attr->set_version(FlameLengthAttribute::serialVersionUid(options));

	WISE::FuelProto::FlameLengthAlexander82 *msgRet = new WISE::FuelProto::FlameLengthAlexander82();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::FlameLengthAlexander82_Parms *msg = new WISE::FuelProto::FlameLengthAlexander82_Parms();
	msg->set_version(1);
	msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
	msg->set_allocated_p2(DoubleBuilder().withValue(m_p2).forProtobuf(options.useVerboseFloats()));
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_alexander82(msgRet);
	return attr;
}


FlameLength_Alexander82 *FlameLength_Alexander82::deserialize(const google::protobuf::Message& proto,
		std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::FlameLengthAlexander82 *msgRead = dynamic_cast_assert<const WISE::FuelProto::FlameLengthAlexander82 *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Alexander82: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Alexander82: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	if (!msgRead->has_parms()) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Alexander82: Incomplete initialization");
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FlameLengthAlexander82", name);
	auto v = vt.lock();

	const WISE::FuelProto::FlameLengthAlexander82_Parms &msg = msgRead->parms();
	if (msg.version() != 1) {
		if (v)
			v->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Alexander82: Version is invalid");
	}

	auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.FlameLengthAlexander82.Parms", "parms");
	auto v2 = vt2.lock();

	if (msg.has_p1())
		m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();
	if (msg.has_p2())
		m_p2 = DoubleBuilder().withProtobuf(msg.p2(), v2, "p2").getValue();
	return this;
}

/*
	This is a no-argument constructor to initialize a FlameLength_Alexander82_Tree object
*/
FlameLength_Alexander82_Tree::FlameLength_Alexander82_Tree() {
	m_cfb = 0.9;
	m_th = 2.5;
}

/*
	This is a 1-argument constructor to initialize a FlameLength_Alexander82_Tree object by copying another FlameLength_Alexander82_Tree object
*/
FlameLength_Alexander82_Tree::FlameLength_Alexander82_Tree(const FlameLength_Alexander82_Tree &toCopy) : FlameLength_Alexander82(toCopy) {
	m_cfb = toCopy.m_cfb;
	m_th = toCopy.m_th;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a FlameLength_Alexander82_Tree and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Alexander82_Tree::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_DEFAULTS:		if ((m_cfb == 0.9) && (m_th == 2.5))
																	break;
																return S_FALSE;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_CFB_THRESHOLD:	*attribute = m_cfb;
																return S_OK;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_TH_FACTOR:		*attribute = m_th;
																return S_OK;
	}
	return FlameLength_Alexander82::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a FlameLength_Alexander82_Tree and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Alexander82_Tree::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_DEFAULTS:		m_cfb = 0.9; m_th = 2.5;	break;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_CFB_THRESHOLD:	m_cfb = attribute;			return S_OK;
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_TH_FACTOR:		m_th = attribute;			return S_OK;
	}
	return FlameLength_Alexander82::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the FlameLength_Alexander82_Tree object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool FlameLength_Alexander82_Tree::Equals(const FuelAttribute *attribute) const {
	const FlameLength_Alexander82_Tree *a = dynamic_cast<const FlameLength_Alexander82_Tree *>(attribute);
	if (!a)
		return false;
	if ((m_cfb != a->m_cfb) || (m_th != a->m_th))
		return false;
	return FlameLength_Alexander82::Equals(attribute);
}

/*
	This is a method to get the flame length of a FlameLength_Alexander82_Tree object and takes the following parameters:
		A height value of type double
		A CFB value of type double
		A fi value of type double
*/
double FlameLength_Alexander82_Tree::FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides) const {
	if (CFB > m_cfb) {
		if (height == 0.0)
			return 0.0;
		return height * m_th;
	}
	return FlameLength_Alexander82::FlameLength(height, CFB, fi, overrides);
}


WISE::FuelProto::FlameLengthAttribute* FlameLength_Alexander82_Tree::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FlameLengthAttribute *attr = new WISE::FuelProto::FlameLengthAttribute();
	attr->set_version(FlameLengthAttribute::serialVersionUid(options));

	WISE::FuelProto::FlameLengthAlexander82Tree *msgRet = new WISE::FuelProto::FlameLengthAlexander82Tree();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::FlameLengthAlexander82Tree_Parms *msg = new WISE::FuelProto::FlameLengthAlexander82Tree_Parms();
	msg->set_version(1);
	msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
	msg->set_allocated_p2(DoubleBuilder().withValue(m_p2).forProtobuf(options.useVerboseFloats()));
	msg->set_allocated_cfb(DoubleBuilder().withValue(m_cfb).forProtobuf(options.useVerboseFloats()));
	msg->set_allocated_th(DoubleBuilder().withValue(m_th).forProtobuf(options.useVerboseFloats()));
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_alexander82tree(msgRet);
	return attr;
}


FlameLength_Alexander82_Tree *FlameLength_Alexander82_Tree::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::FlameLengthAlexander82Tree *msgRead = dynamic_cast_assert<const WISE::FuelProto::FlameLengthAlexander82Tree *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82Tree", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Alexander82_Tree: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82Tree", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Alexander82_Tree: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	if (!msgRead->has_parms()) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82Tree", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Alexander82_Tree: Incomplete initialization");
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FlameLengthAlexander82Tree", name);
	auto v = vt.lock();

	const WISE::FuelProto::FlameLengthAlexander82Tree_Parms &msg = msgRead->parms();
	if (msg.version() != 1) {
		if (v)
			v->add_child_validation("CWFGM.FuelProto.FlameLengthAlexander82Tree.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Alexander82_Tree: Version is invalid");
	}

	auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.FlameLengthAlexander82.Parms", "parms");
	auto v2 = vt2.lock();

	if (msg.has_p1())
		m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();
	if (msg.has_p2())
		m_p2 = DoubleBuilder().withProtobuf(msg.p2(), v2, "p2").getValue();
	if (msg.has_cfb())
		m_cfb = DoubleBuilder().withProtobuf(msg.cfb(), v2, "cfb").getValue();
	if (msg.has_th())
		m_th = DoubleBuilder().withProtobuf(msg.th(), v2, "th").getValue();

	return this;
}

/*
	This is a no-argument constructor to initialize a FlameLength_Tree object
*/
FlameLength_Tree::FlameLength_Tree() {
	m_p1 = 300.0;
	m_th = 2.5;
	m_cfb = 0.9;
}

/*
	This is a 1-argument constructor to initialize a FlameLength_Tree object by copying another FlameLength_Tree object
*/
FlameLength_Tree::FlameLength_Tree(const FlameLength_Tree &toCopy) {
	m_p1 = toCopy.m_p1;
	m_th = toCopy.m_th;
	m_cfb = toCopy.m_cfb;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a FlameLength_Tree and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Tree::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_DEFAULTS:		if ((m_p1 == 300.0) && (m_th == 2.5) && (m_cfb == 0.9))
																	return S_OK;
																return S_FALSE;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_P1:				*attribute = m_p1;
																return S_OK;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_TH_FACTOR:		*attribute = m_th;
																return S_OK;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_CFB_THRESHOLD:	*attribute = m_cfb;
																return S_OK;
	}
	return FlameLengthAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a FlameLength_Tree and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Tree::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_DEFAULTS:		m_p1 = 300.0; m_th = 2.5; m_cfb = 0.9;	return S_OK;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_P1:				m_p1 = attribute;						return S_OK;
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_TH_FACTOR:		m_th = attribute;						return S_OK;
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_TREE_CFB_THRESHOLD:	m_cfb = attribute;						return S_OK;
	}
	return FlameLengthAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the FlameLength_Tree object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool FlameLength_Tree::Equals(const FuelAttribute *attribute) const {
	const FlameLength_Tree *a = dynamic_cast<const FlameLength_Tree *>(attribute);
	if (!a)
		return false;
	if ((m_p1 != a->m_p1) || (m_th != a->m_th) || (m_cfb != a->m_cfb))
		return false;
	return true;
}

/*
	This is a method to get the flame length of a FlameLength_Tree object and takes the following parameters:
		A fi value of type double
*/
double FlameLength_Tree::FlameLength(double height, double CFB, double fi, const CCWFGM_FuelOverrides* overrides) const {
	if (CFB > m_cfb) {
		if (height == 0.0)
			return 0.0;
		return height * m_th;
	}
	if (fi == 0.0)
		return 0.0;
	return sqrt(fi / m_p1);
}


WISE::FuelProto::FlameLengthAttribute* FlameLength_Tree::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FlameLengthAttribute *attr = new WISE::FuelProto::FlameLengthAttribute();
	attr->set_version(FlameLengthAttribute::serialVersionUid(options));

	WISE::FuelProto::FlameLengthTree *msgRet = new WISE::FuelProto::FlameLengthTree();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::FlameLengthTree_Parms *msg = new WISE::FuelProto::FlameLengthTree_Parms();
	msg->set_version(1);
	msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
	msg->set_allocated_cfb(DoubleBuilder().withValue(m_cfb).forProtobuf(options.useVerboseFloats()));
	msg->set_allocated_th(DoubleBuilder().withValue(m_th).forProtobuf(options.useVerboseFloats()));
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_tree(msgRet);
	return attr;
}


FlameLength_Tree *FlameLength_Tree::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::FlameLengthTree *msgRead = dynamic_cast_assert<const WISE::FuelProto::FlameLengthTree *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthTree", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Tree: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthTree", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Tree: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	if (!msgRead->has_parms()) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthTree", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Tree: Incomplete initialization");
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FlameLengthTree", name);
	auto v = vt.lock();

	const WISE::FuelProto::FlameLengthTree_Parms &msg = msgRead->parms();
	if (msg.version() != 1) {
		if (v)
			v->add_child_validation("CWFGM.FuelProto.FlameLengthTree.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Tree: Version is invalid");
	}

	auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.FlameLengthTree.Parms", "parms");
	auto v2 = vt2.lock();

	if (msg.has_p1())
		m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();
	if (msg.has_cfb())
		m_cfb = DoubleBuilder().withProtobuf(msg.cfb(), v2, "cfb").getValue();
	if (msg.has_th())
		m_th = DoubleBuilder().withProtobuf(msg.th(), v2, "th").getValue();

	return this;
}

/*
	This is a no-argument constructor to initialize a FlameLength_Other object
*/
FlameLength_Other::FlameLength_Other() {
	m_p1 = 300.0;
}

/*
	This is a 1-argument constructor to initialize a FlameLength_Other object by copying another FlameLength_Other object
*/
FlameLength_Other::FlameLength_Other(const FlameLength_Other &toCopy) {
	m_p1 = toCopy.m_p1;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a FlameLength_Other and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Other::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_OTHER_DEFAULTS:		if (m_p1 == 300.0)
																	return S_OK;
																return S_FALSE;

		case FUELCOM_ATTRIBUTE_FLAMELENGTH_OTHER_P1:			*attribute = m_p1;
																return S_OK;
	}
	return FlameLengthAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a FlameLength_Other and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT FlameLength_Other::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_OTHER_DEFAULTS:		m_p1 = 300.0;			return S_OK;
		case FUELCOM_ATTRIBUTE_FLAMELENGTH_OTHER_P1:			m_p1 = attribute;		return S_OK;
	}
	return FlameLengthAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the FlameLength_Other object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool FlameLength_Other::Equals(const FuelAttribute *attribute) const {
	const FlameLength_Other *a = dynamic_cast<const FlameLength_Other *>(attribute);
	if (!a)
		return false;
	if (m_p1 != a->m_p1)
		return false;
	return true;
}

/*
	This is a method to get the flame length of a FlameLength_Alexander82 object and takes the following parameters
		A fi value of type double
*/
double FlameLength_Other::FlameLength(double /*height*/, double /*cfb*/, double fi, const CCWFGM_FuelOverrides* overrides) const {
	if (fi == 0.0)
		return 0.0;
	return sqrt(fi / m_p1);
}


WISE::FuelProto::FlameLengthAttribute* FlameLength_Other::serialize(const SerializeProtoOptions& options) {
	WISE::FuelProto::FlameLengthAttribute *attr = new WISE::FuelProto::FlameLengthAttribute();
	attr->set_version(FlameLengthAttribute::serialVersionUid(options));

	WISE::FuelProto::FlameLengthOther *msgRet = new WISE::FuelProto::FlameLengthOther();
	msgRet->set_version(serialVersionUid(options));

	WISE::FuelProto::FlameLengthOther_Parms *msg = new WISE::FuelProto::FlameLengthOther_Parms();
	msg->set_version(1);
	msg->set_allocated_p1(DoubleBuilder().withValue(m_p1).forProtobuf(options.useVerboseFloats()));
	msgRet->set_allocated_parms(msg);

	attr->set_allocated_other(msgRet);
	return attr;
}


FlameLength_Other *FlameLength_Other::deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) {
	const WISE::FuelProto::FlameLengthOther *msgRead = dynamic_cast_assert<const WISE::FuelProto::FlameLengthOther *>(&proto);

	if (!msgRead) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthOther", name, validation::error_level::SEVERE, validation::id::object_invalid, proto.GetDescriptor()->name());
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Other: Protobuf object invalid", ERROR_PROTOBUF_OBJECT_INVALID);
	}

	if (msgRead->version() != 1) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthOther", name, validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msgRead->version()));
		weak_assert(0);
		throw ISerializeProto::DeserializeError("FlameLength_Other: Version is invalid", ERROR_PROTOBUF_OBJECT_VERSION_INVALID);
	}

	if (!msgRead->has_parms()) {
		if (valid)
			valid->add_child_validation("CWFGM.FuelProto.FlameLengthOther", name, validation::error_level::SEVERE, validation::id::object_incomplete, "parms");
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Other: Incomplete initialization");
	}

	auto vt = validation::conditional_make_object(valid, "CWFGM.FuelProto.FlameLengthOther", name);
	auto v = vt.lock();

	const WISE::FuelProto::FlameLengthOther_Parms &msg = msgRead->parms();
	if (msg.version() != 1) {
		if (v)
			v->add_child_validation("CWFGM.FuelProto.FlameLengthOther.Parms", "parms", validation::error_level::SEVERE, validation::id::version_mismatch, std::to_string(msg.version()));
		weak_assert(0);
		throw std::invalid_argument("FlameLength_Other: Version is invalid");
	}

	auto vt2 = validation::conditional_make_object(v, "CWFGM.FuelProto.FlameLengthOther.Parms", "parms");
	auto v2 = vt2.lock();

	if (msg.has_p1())
		m_p1 = DoubleBuilder().withProtobuf(msg.p1(), v2, "p1").getValue();

	return this;
}
