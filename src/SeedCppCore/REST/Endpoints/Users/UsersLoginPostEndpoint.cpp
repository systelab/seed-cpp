#include "stdafx.h"
#include "UsersLoginPostEndpoint.h"

#include "Model/Settings.h"
#include "Model/User.h"
#include "Model/UserMgr.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "REST/Helpers/RequestURLEncodedParserHelper.h"
#include "Services/Model/IUserModelService.h"
#include "Services/System/ITimeService.h"

#include "JWTUtils/Services/ITokenBuilderService.h"

#include "RESTAPICore/Endpoint/EndpointRequestData.h"

#include "WebServerAdapterInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	UsersLoginPostEndpoint::UsersLoginPostEndpoint(const service::IUserModelService& userModelService,
												   const service::ITimeService& timeService,
												   const systelab::jwt::ITokenBuilderService& jwtBuilderService)
		:m_userModelService(userModelService)
		,m_timeService(timeService)
		,m_jwtBuilderService(jwtBuilderService)
	{
	}
	
	UsersLoginPostEndpoint::~UsersLoginPostEndpoint() = default;

	std::unique_ptr<systelab::web_server::Reply> UsersLoginPostEndpoint::execute(const systelab::rest_api_core::EndpointRequestData& requestData)
	{
		std::string requestContent = requestData.getContent();
		std::unique_ptr<LoginData> loginData = getLoginDataFromRequestContent(requestContent);
		if (!loginData)
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
		}

		if (!authenticate(*loginData))
		{
			return ReplyBuilderHelper::build(systelab::web_server::Reply::UNAUTHORIZED);
		}

		std::string jwt = buildJWT(loginData->m_login);
		auto reply = ReplyBuilderHelper::build(systelab::web_server::Reply::OK);
		reply->addHeader("Authorization", "Bearer " + jwt);

		return reply;
	}

	std::unique_ptr<UsersLoginPostEndpoint::LoginData>
	UsersLoginPostEndpoint::getLoginDataFromRequestContent(const std::string& requestContent) const
	{
		std::map<std::string, std::string> requestParams = RequestURLEncodedParserHelper::parse(requestContent);

		auto loginIt = requestParams.find("login");
		if (loginIt == requestParams.end())
		{
			return std::unique_ptr<LoginData>();
		}

		auto passwordIt = requestParams.find("password");
		if (passwordIt == requestParams.end())
		{
			return std::unique_ptr<LoginData>();
		}

		auto loginData = std::make_unique<LoginData>();
		loginData->m_login = loginIt->second;
		loginData->m_password = passwordIt->second;

		return loginData;
	}

	const model::User* UsersLoginPostEndpoint::authenticate(const LoginData& loginData) const
	{
		model::UserMgr::SharedLock readLock(m_userModelService.getEntityMgr());
		const model::User* user = m_userModelService.getUserByLogin(loginData.m_login, readLock);
		if (!user)
		{
			return NULL;
		}

		if (user->getPassword() != loginData.m_password)
		{
			return NULL;
		}

		return user;
	}

	std::string UsersLoginPostEndpoint::buildJWT(const std::string& login) const
	{
		std::string iat = std::to_string((long long)boost::posix_time::to_time_t(m_timeService.getCurrentLocalTime()));

		std::vector< std::pair<std::string, std::string> > claims;
		claims.push_back({"iat", iat});
		claims.push_back({"sub", login});

		std::string jwtSecretKey = model::setting::JWT_SECRET_KEY;
		return m_jwtBuilderService.buildJWT(jwtSecretKey, claims);
	}

}}
