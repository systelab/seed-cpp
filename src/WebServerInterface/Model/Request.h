#pragma once

#include "RequestHeaders.h"
#include "RequestQueryStrings.h"

#include <string>
#include <vector>
#include <map>
#include <boost/optional.hpp>


namespace systelab { namespace web_server {

	class Request
	{
	public:
		Request();
		Request(const std::string& method,
				const std::string& uri,
				const std::map<std::string, std::string>& queryStrings,
				unsigned int httpVersionMajor,
				unsigned int httpVersionMinor,
				const std::map<std::string, std::string>& headers,
				const std::string& content);

		std::string getMethod() const;
		std::string getURI() const;
		unsigned int getHttpVersionMajor() const;
		unsigned int getHttpVersionMinor() const;
		std::string getContent() const;

		void setMethod(const std::string&);
		void setURI(const std::string&);
		void setHttpVersionMajor(unsigned int);
		void setHttpVersionMinor(unsigned int);
		void setContent(const std::string&);

		RequestHeaders& getHeaders();
		const RequestHeaders& getHeaders() const;

		RequestQueryStrings& getQueryStrings();
		const RequestQueryStrings& getQueryStrings() const;

	private:
		std::string m_method;
		std::string m_uri;
		unsigned int m_httpVersionMajor;
		unsigned int m_httpVersionMinor;
		RequestHeaders m_headers;
		RequestQueryStrings m_queryStrings;
		std::string m_content;
	};

}}
