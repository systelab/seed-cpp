#include "StdAfx.h"
#include "JSONValue.h"

#include "JSONMember.h"


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONValue::JSONValue(rapidjson::Value& value,
						 rapidjson::Document::AllocatorType& allocator)
		:m_value(value)
		,m_allocator(allocator)
	{
	}

	JSONValue::~JSONValue()
	{
	}

	Type JSONValue::getType()
	{
		rapidjson::Type type = m_value.GetType();
		switch (type)
		{
			case rapidjson::kFalseType:
			case rapidjson::kTrueType:
				return BOOLEAN_TYPE;
			case rapidjson::kObjectType:
				return OBJECT_TYPE;
			case rapidjson::kArrayType:
				return ARRAY_TYPE;
			case rapidjson::kStringType:
				return STRING_TYPE;
			case rapidjson::kNumberType:
				return NUMBER_TYPE;
			case rapidjson::kNullType:
			default:
				return NULL_TYPE;
		}
	}

	void JSONValue::setType(Type type)
	{
		switch (type)
		{
			case BOOLEAN_TYPE:
				m_value.SetBool(false);
				clearObjectMembers();
				clearArrayValues();
				break;

			case OBJECT_TYPE:
				m_value.SetObject();
				clearArrayValues();
				break;

			case ARRAY_TYPE:
				m_value.SetArray();
				clearObjectMembers();
				break;

			case STRING_TYPE:
				m_value.SetString("");
				clearObjectMembers();
				clearArrayValues();
				break;

			case NUMBER_TYPE:
				m_value.SetInt(0);
				clearObjectMembers();
				clearArrayValues();
				break;

			case NULL_TYPE:
			default:
				m_value.SetNull();
				clearObjectMembers();
				clearArrayValues();
				break;
		}
	}

	bool JSONValue::getBoolean() const
	{
		return m_value.GetBool();
	}

	void JSONValue::setBoolean(bool value)
	{
		m_value.SetBool(value);
	}

	std::string JSONValue::getString() const
	{
		return m_value.GetString();
	}

	void JSONValue::setString(const std::string& value)
	{
		m_value.SetString(value, m_allocator);
	}

	bool JSONValue::isInteger() const
	{
		return m_value.IsInt();
	}

	int JSONValue::getInteger() const
	{
		return m_value.GetInt();
	}

	double JSONValue::getDouble(double) const
	{
		return m_value.GetDouble();
	}

	void JSONValue::setInteger(int value)
	{
		m_value.SetInt(value);
	}
	
	void JSONValue::setDouble(double value)
	{
		m_value.SetDouble(value);
	}

	unsigned int JSONValue::getObjectMemberCount() const
	{
		return m_value.GetObject().MemberCount();
	}

	bool JSONValue::hasObjectMember(const std::string& name) const
	{
		return m_value.HasMember(name);
	}

	IJSONValue& JSONValue::getObjectMemberValue(const std::string& name) const
	{
		loadObjectMembers();

		auto itr = m_objectMembers.find(name);
		if (itr != m_objectMembers.end())
		{
			return itr->second->getValue();
		}
		else
		{
			throw std::exception(std::string("Member '" + name + "' not found").c_str());
		}
	}

	void JSONValue::addMember(const std::string& name, std::unique_ptr<IJSONValue> value)
	{
		loadObjectMembers();

		JSONValue* adapterValue = dynamic_cast<JSONValue*>(value.get());
		if (!adapterValue)
		{
			throw std::exception("JSONValue::addMember() Provided value is not valid");
		}

		rapidjson::Value memberName(name, m_allocator);
		rapidjson::Value& memberValue = adapterValue->m_value;
		m_value.AddMember(memberName.Move(), memberValue.Move(), m_allocator);

		std::unique_ptr<IJSONMember> member = std::make_unique<JSONMember>(name, memberValue, m_allocator);
		m_objectMembers.insert(std::make_pair(name, std::move(member)));
	}

	void JSONValue::removeMember(const std::string& name)
	{
		loadObjectMembers();

		m_value.RemoveMember(name);
		m_objectMembers.erase(name);
	}

	unsigned int JSONValue::getArrayValueCount() const
	{
		return m_value.GetArray().Size();
	}

	IJSONValue& JSONValue::getArrayValue(unsigned int index) const
	{
		loadArrayValues();

		return *m_arrayValues[index];
	}

	void JSONValue::addArrayValue(std::unique_ptr<IJSONValue> value)
	{
		loadArrayValues();

		JSONValue* adapterValue = dynamic_cast<JSONValue*>(value.get());
		if (!adapterValue)
		{
			throw std::exception("JSONValue::addArrayValue() Provided value is not valid");
		}

		m_value.PushBack(adapterValue->m_value, m_allocator);
		m_arrayValues.push_back(std::move(value));
	}
	
	void JSONValue::clearArray()
	{
		m_value.GetArray().Clear();
		m_arrayValuesLoaded = true;
		m_arrayValues.clear();
	}

	void JSONValue::loadObjectMembers() const
	{
		if (m_objectMembersLoaded)
		{
			return;
		}

		for (auto itr = m_value.MemberBegin(); itr != m_value.MemberEnd(); ++itr)
		{
			std::string memberName = itr->name.GetString();
			std::unique_ptr<IJSONMember> member = std::make_unique<JSONMember>(memberName, itr->value, m_allocator);
			m_objectMembers.insert(std::make_pair(memberName, std::move(member)));
		}

		m_objectMembersLoaded = true;
	}

	void JSONValue::clearObjectMembers()
	{
		m_objectMembersLoaded = false;
		m_objectMembers.clear();
	}

	void JSONValue::loadArrayValues() const
	{
		if (m_arrayValuesLoaded)
		{
			return;
		}

		for (auto itr = m_value.Begin(); itr != m_value.End(); ++itr)
		{
			std::unique_ptr<IJSONValue> value = std::make_unique<JSONValue>(*itr, m_allocator);
			m_arrayValues.push_back(std::move(value));
		}

		m_arrayValuesLoaded = true;
	}

	void JSONValue::clearArrayValues()
	{
		m_arrayValuesLoaded = false;
		m_arrayValues.clear();
	}

}}}
