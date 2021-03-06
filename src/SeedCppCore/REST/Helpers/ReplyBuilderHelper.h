#pragma once

#include "WebServerAdapterInterface/Model/Reply.h"


namespace seed_cpp { namespace rest {

	class ReplyBuilderHelper
	{
	public:
		static std::unique_ptr<systelab::web_server::Reply> buildEmpty(systelab::web_server::Reply::StatusType);
		static std::unique_ptr<systelab::web_server::Reply> build(systelab::web_server::Reply::StatusType, const std::string& content);
	};

}}
