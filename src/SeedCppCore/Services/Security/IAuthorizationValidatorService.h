#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <string>


namespace seed_cpp { namespace service {

	class IAuthorizationValidatorService
	{
	public:
		virtual ~IAuthorizationValidatorService() {};

		virtual bool validate(const std::string& token) const = 0;
	};

}}

