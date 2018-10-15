#pragma once

#include <memory>
#include <string>


namespace systelab { namespace web_server {
	class Reply;
}}

namespace seed_cpp { namespace rest {

	class IEndpoint
	{
	public:
		virtual ~IEndpoint() {};

		virtual bool hasAccess(const std::string& token) = 0;
		virtual std::unique_ptr<systelab::web_server::Reply> execute() = 0;
	};

}}

