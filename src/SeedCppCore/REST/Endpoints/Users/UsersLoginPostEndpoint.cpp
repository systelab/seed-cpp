#include "StdAfx.h"
#include "UsersLoginPostEndpoint.h"

#include "Model/User.h"
#include "REST/Helpers/ReplyBuilderHelper.h"
#include "REST/Helpers/RequestURLEncodedParserHelper.h"

#include "WebServerInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	UsersLoginPostEndpoint::UsersLoginPostEndpoint(const std::string& requestContent,
												   model::EntityMgr<model::User>& userMgr)
		:m_requestContent(requestContent)
		,m_userMgr(userMgr)
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




		return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
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

}}

