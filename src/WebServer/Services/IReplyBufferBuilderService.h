#pragma once

#include <string>
#include <vector>


namespace systelab { namespace web_server {

	class Reply;

	class IReplyBufferBuilderService
	{
	public:
		virtual ~IReplyBufferBuilderService() {};

		virtual std::string buildBuffer(const Reply&) const = 0;
	};

}}

