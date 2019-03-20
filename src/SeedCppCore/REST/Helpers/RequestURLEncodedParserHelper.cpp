#include "stdafx.h"
#include "RequestURLEncodedParserHelper.h"

#include <sstream>


namespace seed_cpp { namespace rest {

	std::map<std::string, std::string>
	RequestURLEncodedParserHelper::parse(const std::string& content)
	{
		std::map<std::string, std::string> parameters;

		std::istringstream contentStream(content);
		std::string param;
		while (std::getline(contentStream, param, '&'))
		{
			std::size_t found = param.find_first_of("=");
			if (found == std::string::npos)
			{
				break;
			}

			std::string name = param.substr(0, found);
			std::string value = param.substr(found + 1);
			found = value.find_first_of("=");
			if (found != std::string::npos)
			{
				break;
			}

			if (!name.empty() && !value.empty())
			{
				parameters.insert(std::make_pair(name, value));
			}
		}

		return parameters;
	}

}}
