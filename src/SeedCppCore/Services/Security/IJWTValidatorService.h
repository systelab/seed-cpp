#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <string>


namespace seed_cpp { namespace service {

	class IJWTValidatorService
	{
	public:
		virtual ~IJWTValidatorService() {};

		virtual bool validateJWT(const std::string& token, const std::string& key,
								 std::map<std::string, std::string>& claims) const = 0;
	};

}}

