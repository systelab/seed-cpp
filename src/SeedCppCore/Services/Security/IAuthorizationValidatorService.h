#pragma once

namespace systelab { namespace web_server {
	class RequestHeaders;
}}

namespace seed_cpp { namespace service {

	class IAuthorizationValidatorService
	{
	public:
		virtual ~IAuthorizationValidatorService() {};

		virtual bool validate(const systelab::web_server::RequestHeaders&) const = 0;
	};

}}

