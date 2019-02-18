#include "JSONMember.h"

#include "JSONValue.h"


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONMember::JSONMember(JSONDocument& document,
						   const std::string& name,
						   rapidjson::Value& value,
						   rapidjson::Document::AllocatorType& allocator)
		:m_name(name)
		,m_value(std::make_unique<JSONValue>(document, value, allocator))
	{
	}

	JSONMember::~JSONMember()
	{
	}

	std::string JSONMember::getName() const
	{
		return m_name;
	}

	IJSONValue& JSONMember::getValue() const
	{
		return *m_value;
	}

}}}
