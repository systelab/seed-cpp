#include "RequestHeaders.h"


namespace systelab { namespace web_server {

	RequestHeaders::RequestHeaders()
		:m_headers()
	{
	}

	RequestHeaders::RequestHeaders(const std::map<std::string, std::string>& headers)
		: m_headers(headers)
	{
	}

	RequestHeaders::~RequestHeaders()
	{
	}

	bool RequestHeaders::hasHeader(const std::string& name) const
	{
		return (m_headers.find(name) != m_headers.end());
	}

	std::string RequestHeaders::getHeader(const std::string& name) const
	{
		auto it = m_headers.find(name);
		if (m_headers.find(name) != m_headers.end())
		{
			return it->second;
		}
		else
		{
			std::string exc = std::string("Header '") + name + std::string("' not found.");
            throw std::string(exc);
		}
	}

	void RequestHeaders::addHeader(const std::string& name, const std::string& value)
	{
		m_headers.insert(std::make_pair(name, value));
	}

}}
