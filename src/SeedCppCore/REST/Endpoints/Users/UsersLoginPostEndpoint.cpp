#include "StdAfx.h"
#include "UsersLoginPostEndpoint.h"

#include "Model/User.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "REST/Helpers/RequestURLEncodedParserHelper.h"
#include "Services/Model/IUserModelService.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	UsersLoginPostEndpoint::UsersLoginPostEndpoint(const std::string& requestContent,
												   const service::IUserModelService& userModelService)
		:m_requestContent(requestContent)
		,m_userModelService(userModelService)
	{
	}
	
	UsersLoginPostEndpoint::~UsersLoginPostEndpoint()
	{
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

		return ReplyBuilderHelper::build(systelab::web_server::Reply::OK);
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

}}

