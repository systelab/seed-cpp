#pragma once

#include <map>
#include <string>


namespace seed_cpp { namespace rest {

	class RequestURLEncodedParserHelper
	{
	public:
		static std::map<std::string, std::string> parse(const std::string&);
	};

}}
