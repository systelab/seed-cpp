#pragma once

#include "IReplyBufferBuilderService.h"
#include "WebServerInterface/Model/Reply.h"


namespace systelab { namespace web_server {

	class ReplyBufferBuilderService : public IReplyBufferBuilderService
	{
	public:
		ReplyBufferBuilderService();
		virtual ~ReplyBufferBuilderService();

		std::string buildBuffer(const Reply&) const;

	private:
		std::string translateStatusToString(Reply::StatusType) const;
	};

}}
