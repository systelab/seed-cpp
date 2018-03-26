#include "StdAfx.h"
#include "JSONDocument.h"

#include "JSONValue.h"


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONDocument::JSONDocument(rapidjson::Document& document)
		:m_document(document)
		,m_rootValue(std::make_unique<JSONValue>(document, document.GetAllocator()))
	{
	}

	JSONDocument::~JSONDocument()
	{
	}

	IJSONValue& JSONDocument::getRootValue()
	{
		return *m_rootValue;
	}

	const IJSONValue& JSONDocument::getRootValue() const
	{
		return *m_rootValue;
	}

	std::unique_ptr<IJSONValue> JSONDocument::buildValue()
	{
		rapidjson::Value newValue(rapidjson::kNullType);
		return std::make_unique<JSONValue>(newValue, m_document.GetAllocator());
	}

}}}
