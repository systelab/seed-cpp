#pragma once

#include <string>
#include <memory>
#include <vector>


namespace systelab { namespace json_adapter {

	enum Type
	{
		NULL_TYPE = 0,
		BOOLEAN_TYPE = 1,
		OBJECT_TYPE = 2,
		ARRAY_TYPE = 3,
		STRING_TYPE = 4,
		NUMBER_TYPE = 5
	};

	class IJSONMember;

	class IJSONValue
	{
	public:
		virtual ~IJSONValue() {};

		virtual Type getType() = 0;
		virtual void setType(Type) = 0;

		// Only for boolean values
		virtual bool getBoolean() const = 0;
		virtual void setBoolean(bool) = 0;

		// Only for string values
		virtual std::string getString() const = 0;
		virtual void setString(const std::string&) = 0;

		// Only for number values
		virtual bool isInteger() const = 0;
		virtual int getInteger() const = 0;
		virtual double getDouble(double) const = 0;

		virtual void setInteger(int) = 0;
		virtual void setLong(long) = 0;
		virtual void setLongLong(long long) = 0;
		virtual void setDouble(double) = 0;

		// Only for object values
		virtual unsigned int getObjectMemberCount() const = 0;
		virtual bool hasObjectMember(const std::string&) const = 0;
		virtual std::vector<std::string> getObjectMemberNames() const = 0;
		virtual IJSONValue& getObjectMemberValue(const std::string&) const = 0;

		virtual void addMember(const std::string& name, bool value) = 0;
		virtual void addMember(const std::string& name, int value) = 0;
		virtual void addMember(const std::string& name, long value) = 0;
		virtual void addMember(const std::string& name, long long value) = 0;
		virtual void addMember(const std::string& name, double value) = 0;
		virtual void addMember(const std::string& name, const std::string& value) = 0;
		virtual void addMember(const std::string& name, std::unique_ptr<IJSONValue>) = 0;
		virtual void removeMember(const std::string& name) = 0;

		// Only for array values
		virtual unsigned int getArrayValueCount() const = 0;
		virtual IJSONValue& getArrayValue(unsigned int) const = 0;

		virtual void addArrayValue(std::unique_ptr<IJSONValue>) = 0;
		virtual void clearArray() = 0;

		// Factory of values
		virtual std::unique_ptr<IJSONValue> buildValue(Type) const = 0;
	};

}}
