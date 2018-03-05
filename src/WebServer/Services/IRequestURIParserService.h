#pragma once


namespace systelab { namespace web_server {

	class Request;

	class IRequestURIParserService
	{
	public:
		virtual ~IRequestURIParserService() {};

		virtual bool parse(Request&) const = 0;
	};

}}

