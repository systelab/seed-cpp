#include "UsersGetEndpoint.h"

#include "DAL/Translators/JSON/IJSONSaveTranslator.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/User.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "IJSONAdapter.h"
#include "IJSONDocument.h"

#include "Model/Reply.h"


namespace seed_cpp { namespace rest {

	UsersGetEndpoint::UsersGetEndpoint(const systelab::web_server::RequestHeaders& headers,
											 const std::string& id,
											 model::EntityMgr<model::User>& userMgr,
											 dal::IJSONTranslatorsFactory& jsonTranslatorsFactory,
											 systelab::json_adapter::IJSONAdapter& jsonAdapter,
											 service::IAuthorizationValidatorService& authorizationValidatorService)
		:m_headers(headers)
		,m_id(id)
		,m_userMgr(userMgr)
		,m_jsonTranslatorsFactory(jsonTranslatorsFactory)
		,m_jsonAdapter(jsonAdapter)
		,m_authorizationValidatorService(authorizationValidatorService)
	{
	}
	
	UsersGetEndpoint::~UsersGetEndpoint()
	{
	}

	bool UsersGetEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> UsersGetEndpoint::execute()
	{
		model::EntityMgr<model::User>::SharedLock readLock(m_userMgr);
		const model::User* user = m_userMgr.getEntityById(m_id, readLock);
		if (!user)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
		}

		auto jsonResponse = m_jsonAdapter.buildEmptyDocument();
		auto userTranslator = m_jsonTranslatorsFactory.buildUserSaveTranslator(*user);
		userTranslator->saveEntityToJSON(jsonResponse->getRootValue());

		return ReplyBuilderHelper::build(systelab::web_server::Reply::OK, jsonResponse->serialize());
	}

}}

