#include "StdAfx.h"
#include "JSONDocument.h"

#include "JSONValue.h"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONDocument::JSONDocument(std::unique_ptr<rapidjson::Document> document)
		:m_document(std::move(document))
		,m_rootValue(std::make_unique<JSONValue>(*m_document, m_document->GetAllocator()))
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

	std::string JSONDocument::serialize() const
	{
		rapidjson::StringBuffer jsonBuffer;
		jsonBuffer.Clear();
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.SetMaxDecimalPlaces(6);
		m_document->Accept(jsonWriter);
		std::string serializedDocument = jsonBuffer.GetString();

		return serializedDocument;
	}

}}}
