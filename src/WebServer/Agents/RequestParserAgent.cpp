#include "StdAfx.h"
#include "RequestParserAgent.h"

#include "WebServerInterface/Model/Request.h"

#include <boost/lexical_cast.hpp>


namespace systelab { namespace web_server {

	RequestParserAgent::RequestParserAgent()
		:m_state(method_start)
		,m_header()
		,m_contentLength(0)
		,m_contentCharSize(0)
	{
	}

	RequestParserAgent::~RequestParserAgent()
	{
	}

	boost::optional<bool> RequestParserAgent::parseBuffer(const char* buffer,
														  const std::size_t bufferSize,
														  Request& parsedRequest)
	{
		for (unsigned int i = 0; i < bufferSize; i++)
		{
			boost::optional<bool> result = consume(parsedRequest, buffer[i]);
			if (result.is_initialized())
			{
				return result;
			}
		}

		return boost::optional<bool>();
	}

	boost::optional<bool> RequestParserAgent::consume(Request& req, char input)
	{
		switch (m_state)
		{
			case method_start:
				if (!isChar(input) || isCtl(input) || isTspecial(input))
				{
					return false;
				}
				else
				{
					m_state = method;
					req.setMethod(req.getMethod() + input);
					return boost::optional<bool>();
				}

			case method:
				if (input == ' ')
				{
					m_state = uri;
					return boost::optional<bool>();
				}
				else if (!isChar(input) || isCtl(input) || isTspecial(input))
				{
					return false;
				}
				else
				{
					req.setMethod(req.getMethod() + input);
					return boost::optional<bool>();
				}

			case uri:
				if (input == ' ')
				{
					m_state = http_version_h;
					return boost::optional<bool>();
				}
				else if (isCtl(input))
				{
					return false;
				}
				else
				{
					req.setURI(req.getURI() + input);
					return boost::optional<bool>();
				}

			case http_version_h:
				if (input == 'H')
				{
					m_state = http_version_t_1;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_t_1:
				if (input == 'T')
				{
					m_state = http_version_t_2;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_t_2:
				if (input == 'T')
				{
					m_state = http_version_p;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_p:
				if (input == 'P')
				{
					m_state = http_version_slash;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_slash:
				if (input == '/')
				{
					req.setHttpVersionMajor(0);
					req.setHttpVersionMinor(0);
					m_state = http_version_major_start;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_major_start:
				if (isDigit(input))
				{
					req.setHttpVersionMajor(req.getHttpVersionMajor() * 10 + input - '0');
					m_state = http_version_major;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_major:
				if (input == '.')
				{
					m_state = http_version_minor_start;
					return boost::optional<bool>();
				}
				else if (isDigit(input))
				{
					req.setHttpVersionMajor(req.getHttpVersionMajor() * 10 + input - '0');
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_minor_start:
				if (isDigit(input))
				{
					req.setHttpVersionMinor(req.getHttpVersionMinor() * 10 + input - '0');
					m_state = http_version_minor;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case http_version_minor:
				if (input == '\r')
				{
					m_state = expecting_newline_1;
					return boost::optional<bool>();
				}
				else if (isDigit(input))
				{
					req.setHttpVersionMinor(req.getHttpVersionMinor() * 10 + input - '0');
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case expecting_newline_1:
				if (input == '\n')
				{
					m_state = header_line_start;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case header_line_start:
				if (input == '\r')
				{
					m_state = expecting_newline_3;
					return boost::optional<bool>();
				}
				else if (!isChar(input) || isCtl(input) || isTspecial(input))
				{
					return false;
				}
				else
				{
					m_header.first.clear();
					m_header.second.clear();
					m_header.first.push_back(input);
					m_state = header_name;
					return boost::optional<bool>();
				}

			case header_name:
				if (input == ':')
				{
					m_state = space_before_header_value;
					return boost::optional<bool>();
				}
				else if (!isChar(input) || isCtl(input) || isTspecial(input))
				{
					return false;
				}
				else
				{
					m_header.first.push_back(input);
					return boost::optional<bool>();
				}

			case space_before_header_value:
				if (input == ' ')
				{
					m_state = header_value;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case header_value:
				if (input == '\r')
				{
					if(m_header.first == "Content-Length")
					{
						try
						{
							m_contentLength = boost::lexical_cast<int>(m_header.second);
						}
						catch(const boost::bad_lexical_cast &)
						{
							m_contentLength = 0;
						}
					}

					req.getHeaders().addHeader(m_header.first, m_header.second);

					m_header.first.clear();
					m_header.second.clear();

					m_state = expecting_newline_2;
					return boost::optional<bool>();
				}
				else if (isCtl(input))
				{
					return false;
				}
				else
				{
					m_header.second.push_back(input);
					return boost::optional<bool>();
				}

			case expecting_newline_2:
				if (input == '\n')
				{
					m_state = header_line_start;
					return boost::optional<bool>();
				}
				else
				{
					return false;
				}

			case expecting_newline_3:
				if (input == '\n')
				{
					if(m_contentLength > 0)
					{
						m_state = expecting_content_char1;
						return boost::optional<bool>();
					}
					else
					{
						return true;
					}
				}
				else
				{
					return false;
				}

			case expecting_content_char1:
				m_contentCharSize = getUTF8Length(input);
				if (m_contentCharSize > 0)
				{
					req.setContent(req.getContent() + input);
					if (m_contentCharSize == 1)
					{
						if (req.getContent().size() >= m_contentLength)
						{
							return true;
						}
						else
						{
							return boost::optional<bool>();
						}
					}
					else
					{
						m_state = expecting_content_char2;
						return boost::optional<bool>();
					}
				}
				else
				{
					return false;
				}

			case expecting_content_char2:
				if (isValidUTF8ContinuationByte(input))
				{
					req.setContent(req.getContent() + input);
					if (m_contentCharSize == 2)
					{
						if (req.getContent().size() >= m_contentLength)
						{
							return true;
						}
						else
						{
							m_state = expecting_content_char1;
							return boost::optional<bool>();
						}
					}
					else
					{
						m_state = expecting_content_char3;
						return boost::optional<bool>();
					}
				}
				else
				{
					return false;
				}

			case expecting_content_char3:
				if (isValidUTF8ContinuationByte(input))
				{
					req.setContent(req.getContent() + input);
					if (m_contentCharSize == 3)
					{
						if (req.getContent().size() >= m_contentLength)
						{
							return true;
						}
						else
						{
							m_state = expecting_content_char1;
							return boost::optional<bool>();
						}
					}
					else
					{
						m_state = expecting_content_char4;
						return boost::optional<bool>();
					}
				}
				else
				{
					return false;
				}

			case expecting_content_char4:
				if (isValidUTF8ContinuationByte(input))
				{
					req.setContent(req.getContent() + input);
					if (req.getContent().size() >= m_contentLength)
					{
						m_state = method_start;
						return true;
					}
					else
					{
						m_state = expecting_content_char1;
						return boost::optional<bool>();
					}
				}
				else
				{
					return false;
				}

			default:
				return false;
		}
	}

	bool RequestParserAgent::isChar(int c) const
	{
		return c >= 0 && c <= 127;
	}

	bool RequestParserAgent::isCtl(int c) const
	{
		return (c >= 0 && c <= 31) || (c == 127);
	}

	bool RequestParserAgent::isTspecial(int c)const
	{
		switch (c)
		{
			case '(': case ')': case '<': case '>': case '@':
			case ',': case ';': case ':': case '\\': case '"':
			case '/': case '[': case ']': case '?': case '=':
			case '{': case '}': case ' ': case '\t':
				return true;

			default:
				return false;
		}
	}

	bool RequestParserAgent::isDigit(int c) const
	{
		return c >= '0' && c <= '9';
	}

	unsigned int RequestParserAgent::getUTF8Length(unsigned char c) const
	{
		if ((c & 0x80) == 0)
		{
			return 1;
		}
		else if ((c & 0xE0) == 0xC0)
		{
			return 2;
		}
		else if ((c & 0xF0) == 0xE0)
		{
			return 3;
		}
		else if ((c & 0xF8) == 0xF0)
		{
			return 4;
		}
		else
		{
			return 0;
		}
	}

	bool RequestParserAgent::isValidUTF8ContinuationByte(unsigned char c) const
	{
		if ((c & 0xC0) != 0x80)
		{
			return false;
		}

		return true;
	}

}}
