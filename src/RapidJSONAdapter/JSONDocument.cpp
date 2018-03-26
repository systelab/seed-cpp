#include "StdAfx.h"
#include "JSONDocument.h"

#include "JSONValue.h"


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

}}}
