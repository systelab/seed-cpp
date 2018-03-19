#pragma once

#include "IReplyBuffersBuilderService.h"
#include "WebServerInterface/Model/Reply.h"


namespace systelab { namespace web_server {

	class ReplyBuffersBuilderService : public IReplyBuffersBuilderService
	{
	public:
		ReplyBuffersBuilderService();
		virtual ~ReplyBuffersBuilderService();

		std::vector<std::string> buildBuffers(const Reply&) const;

	private:
		std::string translateStatusToString(Reply::StatusType) const;
	};

}}
