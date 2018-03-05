#pragma once

#include <boost/optional.hpp>


namespace systelab { namespace web_server {

	class Request;

	class IRequestParserAgent
	{
	public:
		virtual ~IRequestParserAgent() {};

		virtual boost::optional<bool> parseBuffer(const char* buffer,
												  const std::size_t bufferSize,
												  Request& parsedRequest) = 0;
	};

}}

