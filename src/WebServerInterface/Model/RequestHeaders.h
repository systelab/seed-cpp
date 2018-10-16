#pragma once

#include <string>
#include <map>


namespace systelab { namespace web_server {

	class RequestHeaders
	{
	public:
		RequestHeaders();
		RequestHeaders(const std::map<std::string, std::string>&);
		virtual ~RequestHeaders();

		bool hasHeader(const std::string& name) const;
		std::string getHeader(const std::string& name) const;

		void addHeader(const std::string& name, const std::string& value);

	private:
		std::map<std::string, std::string> m_headers;
	};

}}
