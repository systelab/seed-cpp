#pragma once

#include "IReplyBuffersBuilderService.h"
#include "WebServerInterface/Model/Reply.h"


namespace systelab { namespace web_server {

	class ReplyBuffersBuilderService : public IReplyBuffersBuilderService
	{
	public:
		ReplyBuffersBuilderService();
		virtual ~ReplyBuffersBuilderService();

		std::vector<boost::asio::const_buffer> buildBuffers(const Reply& reply) const;

	private:
		std::string translateStatusToString(Reply::StatusType) const;
	};
}}
