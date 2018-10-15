#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <string>


namespace seed_cpp { namespace service {

	class IJWTBuilderService
	{
	public:
		virtual ~IJWTBuilderService() {};

		virtual std::string buildJWT(const std::string& key,
									 const std::map<std::string, std::string>& claims) const = 0;
	};

}}

