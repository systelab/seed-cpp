#pragma once

#include <memory>


namespace systelab { namespace web_server {

	class Request;
	class Reply;

	class IRequestHandlingService
	{
	public:
		virtual ~IRequestHandlingService() {};

		virtual std::unique_ptr<Reply> processRequest(const Request&) const = 0;
	};

}}

