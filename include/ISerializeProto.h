/**
 * WISE_FBP_Module: ISerializeProto.h
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

#pragma once

#include <optional>
#include <type_traits>
#include <stdexcept>

#include "FuelConfig.h"
#include "validation_object.h"

#ifndef _MANAGED
#include <google/protobuf/message.h>
#else
namespace google {
	namespace protobuf {
		class Message;
	};
};
#endif

class FUELCOM_API SerializeProtoOptions {
public:
	SerializeProtoOptions() : m_verboseOutput(false), m_clearDirty(false), m_zip(false), m_verboseFloat(false), m_fileVersion(-1) { }

public:
	inline bool useVerboseOutput() const	{ return m_verboseOutput; }
	void setVerboseOutput(bool value)		{ m_verboseOutput = value; }

	inline bool clearDirty() const			{ return m_clearDirty; }
	void setClearDirty(bool value)			{ m_clearDirty = value; }

	inline bool zipOutput() const			{ return m_zip; }
	void setZipOutput(bool value)			{ m_zip = value; }

	inline bool useVerboseFloats() const	{ return m_verboseFloat; }
	void setVerboseFloat(bool value)		{ m_verboseFloat = value; }

	inline std::int32_t fileVersion() const { return m_fileVersion; }
	void setFileVersion(std::int32_t value) { m_fileVersion = value; }

private:
	bool m_verboseOutput;
	bool m_clearDirty;
	bool m_zip;
	bool m_verboseFloat;
	std::int32_t m_fileVersion;
};

class ISerializationData {
public:
	virtual ~ISerializationData() { }
};

/**
 * The interface that all classes that will be serialized using
 * Google Protocol Buffers must inherit from.
 */
class ISerializeProto {
public:

	class DeserializeError : public std::logic_error {
	protected:
		std::string msg_;

	public:
		explicit DeserializeError(const std::string& message) :
			logic_error(message)
		{}
		explicit DeserializeError(const std::string& message, std::uint32_t hr_) :
			logic_error(message)
		{
			hr = hr_;
		}

		std::uint32_t hr = 0;
	};


	virtual std::int32_t serialVersionUid(const SerializeProtoOptions& options) const noexcept = 0;

	/**
	 * Create, then serialize the class to its equivalent protobuf class. Return the protobuf class
	 */
	virtual google::protobuf::Message* serialize(const SerializeProtoOptions& options) = 0;

	/**
	 * Create, then serialize the class to its equivalent protobuf class.
	 * @param options Serialization options.
	 * @param userData Internal user data needed for serialization.
	 * @returns The protobuf class.
	 */
	virtual google::protobuf::Message* serialize(const SerializeProtoOptions& options, ISerializationData* /*userData*/) { return serialize(options); }

    /**
     * Deserialize the class from its equivalent protobuf class.
	   * Returns the object that was just serialized, which may be itself or an object of a derived class.
     */
	virtual ISerializeProto *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name) = 0;

	/**
	 * Deserialize the class from its equivalent protobuf class.
	 * @param userData Internal user data needed for serialization.
	 * @returns The object that was just serialized, which may be itself or an object of a derived class.
	 */
	virtual ISerializeProto *deserialize(const google::protobuf::Message& proto, std::shared_ptr<validation::validation_object> valid, const std::string& name, ISerializationData* /*userData*/) { return deserialize(proto, valid, name); }

	/**
	 * Returns whether the object needs to be saved, or if it even cares or knows.
	 */
	virtual std::optional<bool> isdirty(void) const noexcept = 0;
};
