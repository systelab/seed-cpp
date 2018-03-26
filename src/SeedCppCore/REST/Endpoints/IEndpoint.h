#pragma once

#include <memory>


namespace systelab { namespace web_server {
	class Reply;
}}

namespace seed_cpp { namespace rest {

	class IEndpoint
	{
	public:
		virtual ~IEndpoint() {};

		virtual std::unique_ptr<systelab::web_server::Reply> execute() = 0;
	};

}}

