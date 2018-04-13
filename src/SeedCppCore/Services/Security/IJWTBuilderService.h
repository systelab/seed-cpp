#pragma once

#include <string>


namespace seed_cpp { namespace service {

	class IJWTBuilderService
	{
	public:
		virtual ~IJWTBuilderService() {};

		virtual std::string buildJWT(const std::string& key) const = 0;
	};

}}

