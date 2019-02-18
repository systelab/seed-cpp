#include "JSONAdapter.h"

#include "JSONDocument.h"
#include "JSONSchemaValidator.h"


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONAdapter::JSONAdapter()
	{
	}

	JSONAdapter::~JSONAdapter()
	{
	}

	std::unique_ptr<IJSONDocument> JSONAdapter::buildEmptyDocument() const
	{
		std::unique_ptr<rapidjson::Document> rapidjsonDocument = std::make_unique<rapidjson::Document>();
		return std::make_unique<JSONDocument>(std::move(rapidjsonDocument));
	}

	std::unique_ptr<IJSONDocument> JSONAdapter::buildDocumentFromString(const std::string& content) const
	{
		std::unique_ptr<rapidjson::Document> rapidjsonDocument = std::make_unique<rapidjson::Document>();
        rapidjsonDocument->Parse(content.c_str());
		if (!rapidjsonDocument->HasParseError())
		{
			return std::make_unique<JSONDocument>(std::move(rapidjsonDocument));
		}
		else
		{
			return std::unique_ptr<IJSONDocument>();
		}
	}

	std::unique_ptr<IJSONSchemaValidator> JSONAdapter::buildSchemaValidator(const IJSONDocument& jsonDocument) const
	{
		return std::make_unique<JSONSchemaValidator>(jsonDocument);
	}

	std::unique_ptr<IJSONSchemaValidator> JSONAdapter::buildSchemaValidator(const IJSONDocument& jsonDocument,
																			const IJSONRemoteSchemaProvider& remoteSchemaProvider) const
	{
		return std::make_unique<JSONSchemaValidator>(jsonDocument, remoteSchemaProvider);
	}

}}}
