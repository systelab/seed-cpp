#include "StdAfx.h"
#include "JSONAdapter.h"

#include "JSONDocument.h"


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONAdapter::JSONAdapter()
	{
	}

	JSONAdapter::~JSONAdapter()
	{
	}

	std::unique_ptr<IJSONDocument> JSONAdapter::buildEmptyDocument()
	{
		std::unique_ptr<rapidjson::Document> rapidjsonDocument = std::make_unique<rapidjson::Document>();
		return std::make_unique<JSONDocument>(std::move(rapidjsonDocument));
	}

	std::unique_ptr<IJSONDocument> JSONAdapter::buildDocumentFromString(const std::string& content)
	{
		std::unique_ptr<rapidjson::Document> rapidjsonDocument = std::make_unique<rapidjson::Document>();
		rapidjsonDocument->Parse(content);
		if (!rapidjsonDocument->HasParseError())
		{
			return std::make_unique<JSONDocument>(std::move(rapidjsonDocument));
		}
		else
		{
			return std::unique_ptr<IJSONDocument>();
		}
	}

}}}
