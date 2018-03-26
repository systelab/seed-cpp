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

	std::unique_ptr<IJSONDocument> JSONAdapter::buildDocument()
	{
		return std::make_unique<JSONDocument>(rapidjson::Document());
	}

	std::unique_ptr<IJSONDocument> JSONAdapter::parseDocument(const std::string& content)
	{
		rapidjson::Document document;
		document.Parse(content);
		if (!document.HasParseError())
		{
			return std::make_unique<JSONDocument>(document);
		}
		else
		{
			return std::unique_ptr<IJSONDocument>();
		}
	}

}}}
