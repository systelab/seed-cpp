#include "stdafx.h"
#include "ReplyBuilderHelper.h"


namespace seed_cpp { namespace rest {

	std::unique_ptr<systelab::web_server::Reply>
	ReplyBuilderHelper::build(systelab::web_server::Reply::StatusType status, const std::string& content)
	{
		auto reply = std::make_unique<systelab::web_server::Reply>();
		reply->setStatus(status);
		reply->setContent(content);

		reply->addHeader("Content-Type", "application/json");
		reply->addHeader("Content-Length", std::to_string(content.size()));

		return std::move(reply);
	}

}}
