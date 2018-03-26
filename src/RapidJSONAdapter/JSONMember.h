#pragma once

#include "JSONAdapterInterface/IJSONMember.h"

#include <rapidjson/document.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	class JSONMember : public IJSONMember
	{
	public:
		JSONMember(const std::string&, rapidjson::Value&, rapidjson::Document::AllocatorType&);
		virtual ~JSONMember();

		std::string getName() const;
		IJSONValue& getValue() const;

	private:
		std::string m_name;
		std::unique_ptr<IJSONValue> m_value;
	};

}}}
