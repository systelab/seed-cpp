#pragma once

#include "IJSONMember.h"

#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONDocument;

	class JSONMember : public IJSONMember
	{
	public:
		JSONMember(JSONDocument&, const std::string&, rapidjson::Value&, rapidjson::Document::AllocatorType&);
		virtual ~JSONMember();

		std::string getName() const;
		IJSONValue& getValue() const;

	private:
		std::string m_name;
		std::unique_ptr<IJSONValue> m_value;
	};

}}}
