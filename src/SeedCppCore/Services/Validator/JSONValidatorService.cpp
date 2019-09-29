#include "stdafx.h"
#include "JSONValidatorService.h"

#include "Services/System/IResourceService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONSchemaValidator.h"


namespace seed_cpp { namespace service {

	JSONValidatorService::RemoteSchemaDocumentProvider::RemoteSchemaDocumentProvider(const service::IResourceService& resourceService,
																					 const systelab::json::IJSONAdapter& jsonAdapter)
		:m_resourceService(resourceService)
		,m_jsonAdapter(jsonAdapter)
	{
	}

	std::unique_ptr<systelab::json::IJSONDocument>
	JSONValidatorService::RemoteSchemaDocumentProvider::getRemoteSchemaDocument(const std::string &uri) const
	{
		std::string schemaContent;
		try
		{
			schemaContent = m_resourceService.loadResourceAsString(uri, "JSON_SCHEMA");
		}
		catch (std::exception&)
		{
			return std::unique_ptr<systelab::json::IJSONDocument>();
		}

		return m_jsonAdapter.buildDocumentFromString(schemaContent);
	}

	JSONValidatorService::JSONValidatorService(const service::IResourceService& resourceService,
											   const systelab::json::IJSONAdapter& jsonAdapter)
		:m_jsonAdapter(jsonAdapter)
		,m_documentProvider(std::make_unique<RemoteSchemaDocumentProvider>(resourceService, jsonAdapter))
	{
	}

	void JSONValidatorService::validate(const systelab::json::IJSONDocument& inputDocument,
										const std::string &schemaName) const
	{
		auto schemaDocument = m_documentProvider->getRemoteSchemaDocument(schemaName);
		if (!schemaDocument)
		{
			throw JSONValidationException("Couldn't retrieve JSON schema '" +
										  schemaName + "'");
		}

		std::string reason = "";
		auto schemaValidator = m_jsonAdapter.buildSchemaValidator(*schemaDocument, *m_documentProvider);
		if (!schemaValidator->validate(inputDocument, reason))
		{
			throw JSONValidationException("Input JSON does not satisfy '" + schemaName +
										  "' schema:\n\n" + reason);
		}
	}

}}
