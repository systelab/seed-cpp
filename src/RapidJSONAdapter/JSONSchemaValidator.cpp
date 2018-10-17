#include "StdAfx.h"
#include "JSONSchemaValidator.h"

#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONRemoteSchemaProvider.h"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>


namespace systelab { namespace json_adapter { namespace rapidjson_adapter {

	JSONSchemaValidator::RapidjsonSchemaRemoteDocumentProvider::RapidjsonSchemaRemoteDocumentProvider(const IJSONRemoteSchemaProvider& remoteSchemaProvider)
		:m_remoteSchemaProvider(remoteSchemaProvider)
	{
	}

	const rapidjson::SchemaDocument*
	JSONSchemaValidator::RapidjsonSchemaRemoteDocumentProvider::GetRemoteDocument(const char* uri, rapidjson::SizeType length)
	{
		std::string uriStr(uri, length + 1);
		std::unique_ptr<rapidjson::SchemaDocument> schemaDocument = buildSchemaDocument(uriStr);
		return schemaDocument.release();
	}

	std::unique_ptr<rapidjson::SchemaDocument>
	JSONSchemaValidator::RapidjsonSchemaRemoteDocumentProvider::buildSchemaDocument(const std::string& uri)
	{
		std::unique_ptr<IJSONDocument> remoteSchemaDocument = m_remoteSchemaProvider.getRemoteSchemaDocument(uri);
		if (!remoteSchemaDocument)
		{
			return std::unique_ptr<rapidjson::SchemaDocument>();
		}

		rapidjson::Document jsonDocument;
		jsonDocument.Parse(remoteSchemaDocument->serialize());
		if (jsonDocument.HasParseError())
		{
			return std::unique_ptr<rapidjson::SchemaDocument>();
		}

		return std::make_unique<rapidjson::SchemaDocument>(jsonDocument, this);
	}


	JSONSchemaValidator::JSONSchemaValidator(const IJSONDocument& document)
		:m_rapidjsonRemoteSchemaProvider()
		,m_schemaDocument()
	{
		rapidjson::Document jsonDocument;
		jsonDocument.Parse(document.serialize());
		m_schemaDocument = std::make_unique<rapidjson::SchemaDocument>(jsonDocument);
	}

	JSONSchemaValidator::JSONSchemaValidator(const IJSONDocument& document,
											 const IJSONRemoteSchemaProvider& remoteSchemaProvider)
		:m_rapidjsonRemoteSchemaProvider(std::make_unique<RapidjsonSchemaRemoteDocumentProvider>(remoteSchemaProvider))
		,m_schemaDocument()
	{
		rapidjson::Document jsonDocument;
		jsonDocument.Parse(document.serialize());

		m_schemaDocument = std::make_unique<rapidjson::SchemaDocument>(jsonDocument, m_rapidjsonRemoteSchemaProvider.get());
	}

	JSONSchemaValidator::~JSONSchemaValidator()
	{
	}

	bool JSONSchemaValidator::validate(const IJSONDocument& inputDocument, std::string& reason) const
	{
		rapidjson::Document inputJSONDocument;
		inputJSONDocument.Parse(inputDocument.serialize());

		rapidjson::SchemaValidator schemaValidator(*m_schemaDocument);
		if (!inputJSONDocument.Accept(schemaValidator))
		{
			rapidjson::StringBuffer buffer;
			schemaValidator.GetInvalidSchemaPointer().StringifyUriFragment(buffer);
			std::string invalidSchema = buffer.GetString();
			std::string invalidKeyword = schemaValidator.GetInvalidSchemaKeyword();
			buffer.Clear();
			schemaValidator.GetInvalidDocumentPointer().StringifyUriFragment(buffer);
			std::string invalidDocument = buffer.GetString();

			reason = std::string("Invalid schema: ") + invalidSchema + std::string("\n") +
					 std::string("Invalid keyword: ") + invalidKeyword + std::string("\n") +
					 std::string("Invalid document: ") + invalidDocument;
			return false;
		}

		return true;
	}

}}}
