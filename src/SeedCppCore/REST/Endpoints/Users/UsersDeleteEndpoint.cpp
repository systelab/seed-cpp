#include "UsersDeleteEndpoint.h"

#include "Model/User.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Security/IAuthorizationValidatorService.h"

#include "Model/Reply.h"
#include "Model/RequestHeaders.h"


namespace seed_cpp { namespace rest {

	UsersDeleteEndpoint::UsersDeleteEndpoint(const systelab::web_server::RequestHeaders& headers,
											 const std::string& id,
											 service::IUserModelService& userModelService,
											 service::IAuthorizationValidatorService& authorizationValidatorService)
		:m_headers(headers)
		,m_id(id)
		,m_userModelService(userModelService)
		,m_authorizationValidatorService(authorizationValidatorService)
	{
	}
	
	UsersDeleteEndpoint::~UsersDeleteEndpoint()
	{
	}

	bool UsersDeleteEndpoint::hasAccess() const
	{
		return m_authorizationValidatorService.validate(m_headers);
	}

	std::unique_ptr<systelab::web_server::Reply> UsersDeleteEndpoint::execute()
	{
		model::EntityMgr<model::User>::UniqueLock writeLock(m_userModelService.getEntityMgr());
		const model::User* existingUser = m_userModelService.getEntityById(m_id, writeLock);
		if (!existingUser)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::NOT_FOUND);
		}

		try
		{
			m_userModelService.deleteEntity(m_id, writeLock);
			return ReplyBuilderHelper::build(systelab::web_server::Reply::NO_CONTENT);
		}
		catch (std::exception& exc)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::INTERNAL_SERVER_ERROR, exc.what());
		}
	}

}}

