#include "stdafx.h"
#include "RequestURIParserService.h"

#include "WebServerInterface/Model/Request.h"

#include <sstream>
#include <regex>


namespace systelab { namespace web_server {

	RequestURIParserService::RequestURIParserService()
	{
	}

	RequestURIParserService::~RequestURIParserService()
	{
	}

	bool RequestURIParserService::parse(Request& request) const
	{
		std::string in = request.getURI();

		std::string out;
		out.reserve(in.size());

		for (std::size_t i = 0; i < in.size(); ++i)
		{
			if (in[i] == '%')
			{
				if (i + 3 <= in.size())
				{
					int value = 0;
					std::istringstream is(in.substr(i + 1, 2));

					if (is >> std::hex >> value)
					{
						out += static_cast<char>(value);
						i += 2;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else if (in[i] == '+')
			{
				out += ' ';
			}
			else
			{
				out += in[i];
			}
		}

		size_t posDotDot = out.find("..");

		if (posDotDot != std::string::npos)
		{
			size_t posQuery = out.find("?");

			if (posQuery == std::string::npos || posQuery > posDotDot)
			{
				return false;
			}
		}

		bool bad = out.size() <= 0 || out[0] != '/';
		if (bad)
		{
			return false;
		}

		request.setURI(out);
		parseQueryString(request);

		return true;
	}

	void RequestURIParserService::parseQueryString(Request& request) const
	{
		if (request.getURI().find("?") != std::string::npos)
		{
			std::regex pattern("([\\w+%]+)=([^&]*)");
			auto words_begin = std::sregex_iterator(request.getURI().begin(), request.getURI().end(), pattern);
			auto words_end = std::sregex_iterator();

			for (std::sregex_iterator i = words_begin; i != words_end; i++)
			{
				std::string name = (*i)[1].str();
				std::string value = (*i)[2].str();
				request.getQueryStrings().addItem(name, value);
			}
		}
	}

}}
