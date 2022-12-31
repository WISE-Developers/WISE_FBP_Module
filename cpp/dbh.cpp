/**
 * WISE_FBP_Module: dbh.cpp
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

#include "dbh.h"
#include "doubleBuilder.h"

#ifdef DEBUG
#include <assert.h>
#endif

// from FuelCom_ext.h
#define FUELCOM_EQUATION_SELECTION_DBH_1			18430
#define FUELCOM_EQUATION_SELECTION_DBH_2			18431
#define FUELCOM_EQUATION_SELECTION_DBH_3			18432
#define FUELCOM_EQUATION_SELECTION_DBH_4			18433
#define FUELCOM_EQUATION_SELECTION_DBH_NONE			18434

#define FUELCOM_ATTRIBUTE_HUANG_DBH_START			16900
#define FUELCOM_ATTRIBUTE_HUANG_DBH_B1				16901
#define FUELCOM_ATTRIBUTE_HUANG_DBH_B2				16902
#define FUELCOM_ATTRIBUTE_HUANG_DBH_B3				16903

#define FUELCOM_ATTRIBUTE_HUANG_DBH_C1_DEFAULTS		17000
#define FUELCOM_ATTRIBUTE_HUANG_DBH_C2_DEFAULTS		17001
#define FUELCOM_ATTRIBUTE_HUANG_DBH_C3_DEFAULTS		17002
#define FUELCOM_ATTRIBUTE_HUANG_DBH_C4_DEFAULTS		17003
#define FUELCOM_ATTRIBUTE_HUANG_DBH_C5_DEFAULTS		17004
#define FUELCOM_ATTRIBUTE_HUANG_DBH_C6_DEFAULTS		17005
#define FUELCOM_ATTRIBUTE_HUANG_DBH_C7_DEFAULTS		17006
#define FUELCOM_ATTRIBUTE_HUANG_DBH_D1_DEFAULTS		17007
#define FUELCOM_ATTRIBUTE_HUANG_DBH_D2_DEFAULTS		17008
#define FUELCOM_ATTRIBUTE_HUANG_DBH_M1_DEFAULTS		17009
#define FUELCOM_ATTRIBUTE_HUANG_DBH_M2_DEFAULTS		17010
#define FUELCOM_ATTRIBUTE_HUANG_DBH_M3_DEFAULTS		17011
#define FUELCOM_ATTRIBUTE_HUANG_DBH_M4_DEFAULTS		17012
#define FUELCOM_ATTRIBUTE_HUANG_DBH_END				17099


namespace dbh {
	uint16_t GetDefaultValue(WISE::FuelProto::FuelName def) {
		uint16_t val;

		switch (def) {
		case(WISE::FuelProto::FuelName::C1):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_C1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C2):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_C2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C3):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_C3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C4):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_C4_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C5):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_C5_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C6):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_C6_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::C7):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_C7_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D1):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_D1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::D2):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_D2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M1):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_M1_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M2):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_M2_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M3):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_M3_DEFAULTS;
			break;

		case(WISE::FuelProto::FuelName::M4):
			val = FUELCOM_ATTRIBUTE_HUANG_DBH_M4_DEFAULTS;
			break;

		default:
			val = (uint16_t)-1;
		}

		return val;
	}
}

/*
	This is a no-argument constructor to initialize a DBH_None object
*/
DBH_None::DBH_None() {
}

/*
	This is a 1-argument constructor to initialize a DBH_None object by copying another DBH_None object
*/
DBH_None::DBH_None(const DBH_None &toCopy) {
	m_SpeciesCode = toCopy.m_SpeciesCode;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a DBH_None and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT DBH_None::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	return DBHAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a DBH_None and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT DBH_None::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	return DBHAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the DBH_None object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool DBH_None::Equals(const FuelAttribute *attribute) const {
	const DBH_None*a = dynamic_cast<const DBH_None*>(attribute);
	if (!a)
		return false;
	return true;
}

/*
	See dbh.h for this definition
*/
std::string DBH_None::SpeciesCode() const {
	return m_SpeciesCode;
}

/*
	See dbh.h for this definition
*/
void DBH_None::SpeciesCode(const std::string &code) {
	m_SpeciesCode = code;
}

/*
	See dbh.h for this definition
*/
double DBH_None::DBH(double /*height*/) const {
	return 0.0;
}

/*
	This is a no-argument constructor to initialize a DBH_HuangCommon object
*/
DBH_HuangCommon::DBH_HuangCommon() {
	m_b1 = -1.0;
	m_b2 = -1.0;
	m_b3 = -1.0;
	m_SpeciesCode.clear();
} 

/*
	This is a 1-argument constructor to initialize a DBH_HuangCommon object by copying another DBH_HuangCommon object
*/
DBH_HuangCommon::DBH_HuangCommon(const DBH_HuangCommon &toCopy) {
	m_b1 = toCopy.m_b1;
	m_b2 = toCopy.m_b2;
	m_b3 = toCopy.m_b3;
	m_SpeciesCode = toCopy.m_SpeciesCode;
}

/*
	This is a method to return the attribute value, associated with the passed key, used in a DBH_HuangCommon and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT DBH_HuangCommon::GetAttributeValue(std::uint16_t attributeKey, double *attribute) const {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C2_DEFAULTS:	if ((m_b1 == 2.1948) &&
															(m_b2 == 0.6184) &&
															(m_b3 == -0.0273))
															return S_OK;
														return S_FALSE;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C4_DEFAULTS:	if ((m_b1 == 2.0408) &&
															(m_b2 == 0.5377) &&
															(m_b3 == -0.0455))
															return S_OK;
														return S_FALSE;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C6_DEFAULTS:	if ((m_b1 == 2.1881) &&
															(m_b2 == 0.6161) &&
															(m_b3 == -0.0264))
															return S_OK;
														return S_FALSE;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C7_DEFAULTS:	if ((m_b1 == 2.9394) &&
															(m_b2 == 0.4047) &&
															(m_b3 == -0.0626))
															return S_OK;
														return S_FALSE;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_D2_DEFAULTS:	if ((m_b1 == 1.1091) &&
															(m_b2 == 0.8055) &&
															(m_b3 == -0.0332))
															return S_OK;
														return S_FALSE;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M2_DEFAULTS:	if ((m_b1 == 2.2494) &&
															(m_b2 == 0.6556) &&
															(m_b3 == -0.0233))
															return S_OK;
														return S_FALSE;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M4_DEFAULTS:	if ((m_b1 == 2.1260) &&
															(m_b2 == 0.7151) &&
															(m_b3 == -0.0182))
															return S_OK;
														return S_FALSE;

		case FUELCOM_ATTRIBUTE_HUANG_DBH_B1:	*attribute = m_b1;		return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_B2:	*attribute = m_b2;		return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_B3:	*attribute = m_b3;		return S_OK;
	}
	return DBHAttribute::GetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to set the attribute value, defined by the passed key, used in a DBH_HuangCommon and takes the following parameters:
		An attribute key value of type uint16
		An attribute value of type double
*/
HRESULT DBH_HuangCommon::SetAttributeValue(std::uint16_t attributeKey, double attribute) {
	switch (attributeKey) {
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C2_DEFAULTS:	m_b1 = 2.1948;	m_b2 = 0.6184;	m_b3 = -0.0273;	m_SpeciesCode = "Sb";	return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C4_DEFAULTS:	m_b1 = 2.0408;	m_b2 = 0.5377;	m_b3 = -0.0455;	m_SpeciesCode = "Pj";	return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C5_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C6_DEFAULTS:	m_b1 = 2.1881;	m_b2 = 0.6161;	m_b3 = -0.0264;	m_SpeciesCode = "Pl";	return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_C7_DEFAULTS:	m_b1 = 2.9394;	m_b2 = 0.4047;	m_b3 = -0.0626; m_SpeciesCode = "Fd";	return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_D1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_D2_DEFAULTS:	m_b1 = 1.1091;	m_b2 = 0.8055;	m_b3 = -0.0332;	m_SpeciesCode = "Aw";	return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M1_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M2_DEFAULTS:	m_b1 = 2.2494;	m_b2 = 0.6556;	m_b3 = -0.0233;	m_SpeciesCode = "Sw";	return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M3_DEFAULTS:
		case FUELCOM_ATTRIBUTE_HUANG_DBH_M4_DEFAULTS:	m_b1 = 2.1260;	m_b2 = 0.7151;	m_b3 = -0.0182;	m_SpeciesCode = "Fb";	return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_B1:			m_b1 = attribute;		return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_B2:			m_b2 = attribute;		return S_OK;
		case FUELCOM_ATTRIBUTE_HUANG_DBH_B3:			m_b3 = attribute;		return S_OK;
	}
	return DBHAttribute::SetAttributeValue(attributeKey, attribute);
}

/*
	This is a method to check if the DBH_HuangCommon object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool DBH_HuangCommon::Equals(const FuelAttribute *attribute) const {
	const DBH_HuangCommon *a = dynamic_cast<const DBH_HuangCommon *>(attribute);
	if (!a)
		return false;
	if (m_b1 != a->m_b1)			return false;
	if (m_b2 != a->m_b2)			return false;
	if (m_b3 != a->m_b3)			return false;
	return true;
}



/*
	See dbh.h for this definition
*/
std::string DBH_HuangCommon::SpeciesCode() const {
	return m_SpeciesCode;
}

/*
	See dbh.h for this definition
*/
void DBH_HuangCommon::SpeciesCode(const std::string &code) {
	m_SpeciesCode = code;
}

/*
	This is a no-argument constructor to initialize a DBH_1 object
*/
DBH_1::DBH_1() : DBH_HuangCommon() {
}

/*
	This is a 1-argument constructor to initialize a DBH_1 object by copying another DBH_1 object
*/
DBH_1::DBH_1(const DBH_1 & toCopy) : DBH_HuangCommon(toCopy) {
}

/*
	This is a method to check if the DBH_1 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool DBH_1::Equals(const FuelAttribute *attribute) const {
	const DBH_1 *a = dynamic_cast<const DBH_1 *>(attribute);
	if (!a)
		return false;
	return DBH_HuangCommon::Equals(attribute);
}

/*
	See dbh.h for this definition
*/
double DBH_1::DBH(double height) const {
	double h = height - 1.3;
	if (h <= 0.0)
		return 0.0;
	double dbh = m_b1 * pow(h, m_b2) * exp((0.0 - m_b3) * h);
	return dbh;
}

/*
	This is a no-argument constructor to initialize a DBH_2 object
*/
DBH_2::DBH_2() : DBH_HuangCommon() {
}

/*
	This is a 1-argument constructor to initialize a DBH_2 object by copying another DBH_2 object
*/
DBH_2::DBH_2(const DBH_2 & toCopy) : DBH_HuangCommon(toCopy) {
}

/*
	This is a method to check if the DBH_2 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool DBH_2::Equals(const FuelAttribute *attribute) const {
	const DBH_2 *a = dynamic_cast<const DBH_2 *>(attribute);
	if (!a)
		return false;
	return DBH_HuangCommon::Equals(attribute);
}

/*
	See dbh.h for this definition
*/
double DBH_2::DBH(double height) const {
	if (height <= 1.3)
		return 0.0;
	double t = (m_b1 / m_b2) * (1.0 - exp((0.0 - m_b2) * m_b3 * (height - 1.3)));
	double dbh = pow(t, (1.0 / m_b3));
	return dbh;
}

/*
	This is a no-argument constructor to initialize a DBH_3 object
	which extends the DBH_HuangCommon constructor
*/
DBH_3::DBH_3() : DBH_HuangCommon() {
}

/*
	This is a 1-argument constructor to initialize a DBH_3 object by copying another DBH_3 object
	which extends the DBH_HuangCommon constructor
*/
DBH_3::DBH_3(const DBH_3 & toCopy) : DBH_HuangCommon(toCopy) {
}

/*
	This is a method to check if the DBH_3 object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool DBH_3::Equals(const FuelAttribute *attribute) const {
	const DBH_3 *a = dynamic_cast<const DBH_3 *>(attribute);
	if (!a)
		return false;
	return DBH_HuangCommon::Equals(attribute);
}

/*
	See dbh.h for this definition
*/
double DBH_3::DBH(double height) const {
	double h = height - 1.3;
	if (h <= 0.0)
		return 0.0;
	double dbh = h / (m_b1 + m_b2 * h + m_b3 * h * h);
	return dbh;
}

/*
	This is a no-argument constructor to initialize a DBH_4 object
	which extends the DBH_HuangCommon constructor
*/
DBH_4::DBH_4() : DBH_HuangCommon() {
}

/*
	This is a 1-argument constructor to initialize a DBH_4 object by copying another DBH_4 object
	which extends the DBH_HuangCommon constructor
*/
DBH_4::DBH_4(const DBH_4 & toCopy) : DBH_HuangCommon(toCopy) {
}

/*
	This is a method to check if the FlameLength_Alexander82_Tree object is equal to a FuelAttribute object and takes the following parameters:
		An attribute object of type FuelAttribute
*/
bool DBH_4::Equals(const FuelAttribute *attribute) const {
	const DBH_4 *a = dynamic_cast<const DBH_4 *>(attribute);
	if (!a)
		return false;
	return DBH_HuangCommon::Equals(attribute);
}

/*
	See dbh.h for this definition
*/
double DBH_4::DBH(double height) const {
	double h = height - 1.3;
	if (h <= 0.0)
		return 0.0;
	double dbh = m_b1 + m_b2 * pow(h, m_b3);
	return dbh;
}
