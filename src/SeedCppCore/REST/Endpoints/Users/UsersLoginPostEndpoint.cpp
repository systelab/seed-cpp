#include "StdAfx.h"
#include "UsersLoginPostEndpoint.h"

#include "Model/User.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "REST/Helpers/RequestURLEncodedParserHelper.h"
#include "Services/Model/IUserModelService.h"
#include "Services/Security/IJWTBuilderService.h"
#include "Services/System/ITimeService.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	UsersLoginPostEndpoint::UsersLoginPostEndpoint(const std::string& requestContent,
												   const service::IUserModelService& userModelService,
												   const service::IJWTBuilderService& jwtBuilderService,
												   const service::ITimeService& timeService)
		:m_requestContent(requestContent)
		,m_userModelService(userModelService)
		,m_jwtBuilderService(jwtBuilderService)
		,m_timeService(timeService)
	{
	}
	
	UsersLoginPostEndpoint::~UsersLoginPostEndpoint()
	{
	}

	bool UsersLoginPostEndpoint::hasAccess() const
	{
		return true;
	}

	std::unique_ptr<systelab::web_server::Reply> UsersLoginPostEndpoint::execute()
	{
		std::unique_ptr<LoginData> loginData = getLoginDataFromRequestContent();
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

	std::unique_ptr<UsersLoginPostEndpoint::LoginData> UsersLoginPostEndpoint::getLoginDataFromRequestContent() const
	{
		std::map<std::string, std::string> requestParams = RequestURLEncodedParserHelper::parse(m_requestContent);

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
		const model::User* user = m_userModelService.getUserByLogin(loginData.m_login);
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
		std::map<std::string, std::string> claims;
		claims.insert({"iat", std::to_string((long long) boost::posix_time::to_time_t(m_timeService.getCurrentLocalTime()))});
		claims.insert({"sub", login});

		std::string jwtSecurityKey = "SeedCppRocks!";
		return m_jwtBuilderService.buildJWT(jwtSecurityKey, claims);
	}

}}

