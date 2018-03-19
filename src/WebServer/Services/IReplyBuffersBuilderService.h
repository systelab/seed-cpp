#pragma once

#include <string>
#include <vector>


namespace systelab { namespace web_server {

	class Reply;

	class IReplyBuffersBuilderService
	{
	public:
		virtual ~IReplyBuffersBuilderService() {};

		virtual std::vector<std::string> buildBuffers(const Reply&) const = 0;
	};

}}

