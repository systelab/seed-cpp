#include "StdAfx.h"
#include "UsersLoginPostEndpoint.h"

#include "Model/User.h"
#include "REST/Helpers/ReplyBuilderHelper.h"

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
		return ReplyBuilderHelper::build(systelab::web_server::Reply::BAD_REQUEST);
	}

}}

