#pragma once

#include "JSONAdapterInterface/IJSONValue.h"

#include <string>
#include <map>
#include <memory>
#include <vector>

#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONValue : public IJSONValue
	{
	public:
		JSONValue(rapidjson::Value&, rapidjson::Document::AllocatorType&);
		virtual ~JSONValue();

		Type getType();
		void setType(Type);

		// Only for boolean values
		bool getBoolean() const;
		void setBoolean(bool);

		// Only for string values
		std::string getString() const;
		void setString(const std::string&);

		// Only for number values
		bool isInteger() const;
		int getInteger() const;
		double getDouble(double) const;

		void setInteger(int);
		void setDouble(double);

		// Only for object values
		unsigned int getObjectMemberCount() const;
		bool hasObjectMember(const std::string&) const;
		IJSONValue& getObjectMemberValue(const std::string&) const;

		void addMember(const std::string& name, std::unique_ptr<IJSONValue>);
		void removeMember(const std::string& name);

		// Only for array values
		unsigned int getArrayValueCount() const;
		IJSONValue& getArrayValue(unsigned int) const;

		void addArrayValue(std::unique_ptr<IJSONValue>);
		void clearArray();

	private:
		void loadObjectMembers() const;
		void clearObjectMembers();

		void loadArrayValues() const;
		void clearArrayValues();

	private:
		rapidjson::Value& m_value;
		rapidjson::Value::AllocatorType& m_allocator;

		mutable bool m_objectMembersLoaded;
		mutable std::map< std::string, std::unique_ptr<IJSONMember> > m_objectMembers;

		mutable bool m_arrayValuesLoaded;
		mutable std::vector< std::unique_ptr<IJSONValue> > m_arrayValues;
	};

}}}
