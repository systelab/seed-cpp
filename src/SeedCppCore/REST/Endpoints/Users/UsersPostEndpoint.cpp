#include "StdAfx.h"
#include "UsersPostEndpoint.h"

#include "Model/EntityMgr.h"
#include "Model/User.h"
#include "DAL/Translators/JSON/IJSONLoadTranslator.h"
#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"
#include "Services/Validator/IJSONValidatorService.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	UsersPostEndpoint::UsersPostEndpoint(const systelab::web_server::RequestHeaders& headers,
										 const std::string& requestContent,
										 dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
										 systelab::json_adapter::IJSONAdapter& jsonAdapter,
										 service::IAuthorizationValidatorService& authorizationValidatorService,
										 service::IJSONValidatorService& jsonValidatorService,
										 service::IUserModelService& userModelService)
		:m_headers(headers)
		,m_requestContent(requestContent)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
		,m_authorizationValidatorService(authorizationValidatorService)
		,m_jsonValidatorService(jsonValidatorService)
		,m_userModelService(userModelService)
	{
	}

	UsersPostEndpoint::~UsersPostEndpoint()
	{
	}

	bool UsersPostEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> UsersPostEndpoint::execute()
	{
		std::unique_ptr<systelab::json_adapter::IJSONDocument> jsonRequest = m_jsonAdapter.buildDocumentFromString(m_requestContent);
		if (!jsonRequest)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
		}

		try
		{
			m_jsonValidatorService.validate(*jsonRequest, "JSON_SCHEMA_ENDPOINT_USERS_POST");
		}
		catch(service::IJSONValidatorService::JSONValidationException& exc)
		{
			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto& jsonRootValue = jsonResponse->getRootValue();
			jsonRootValue.setType(systelab::json_adapter::OBJECT_TYPE);
			jsonRootValue.addMember("reason", exc.toString());
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST, jsonResponse->serialize());
		}

		try
		{
			auto userToAdd = std::make_unique<model::User>();
			auto userJSONLoadTranslator = m_jsonTranslatorsFactory.buildUserLoadTranslator(*userToAdd);
			userJSONLoadTranslator->loadEntityFromJSON(jsonRequest->getRootValue());

			model::EntityMgr<model::User>::UniqueLock writeLock(m_userModelService.getEntityMgr());
			const model::User& addedUser = m_userModelService.addEntity(std::move(userToAdd), writeLock);

			auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
			auto userJSONSaveTranslator = m_jsonTranslatorsFactory.buildUserSaveTranslator(addedUser);
			userJSONSaveTranslator->saveEntityToJSON(jsonResponse->getRootValue());

			return ReplyBuilderHelper::build(systelab::web_server::Reply::CREATED, jsonResponse->serialize());
		}
		catch (std::exception& exc)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
		}
	}

}}

