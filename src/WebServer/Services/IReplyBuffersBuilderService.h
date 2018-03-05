#pragma once

#include <boost/asio.hpp>
#include <vector>


namespace systelab { namespace web_server {

	class Reply;

	class IReplyBuffersBuilderService
	{
	public:
		virtual ~IReplyBuffersBuilderService() {};

		virtual std::vector<boost::asio::const_buffer> buildBuffers(const Reply& reply) const = 0;
	};

}}

