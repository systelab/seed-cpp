#pragma once

#include "IRequestParserAgent.h"

#include <string>

namespace systelab { namespace web_server {

	class RequestParserAgent : public IRequestParserAgent
	{
	public:
		RequestParserAgent();
		virtual ~RequestParserAgent();

		boost::optional<bool> parseBuffer(const char* buffer,
										  const std::size_t bufferSize,
										  Request& parsedRequest);

	private:
		boost::optional<bool> consume(Request& req, char input);

		bool isChar(int c) const;
		bool isCtl(int c) const;
		bool isTspecial(int c) const;
		bool isDigit(int c) const;

		unsigned int getUTF8Length(unsigned char c) const;
		bool isValidUTF8ContinuationByte(unsigned char c) const;

	private:
		/// The current state of the parser.
		enum ParsingState
		{
			method_start,
			method,
			uri,
			http_version_h,
			http_version_t_1,
			http_version_t_2,
			http_version_p,
			http_version_slash,
			http_version_major_start,
			http_version_major,
			http_version_minor_start,
			http_version_minor,
			expecting_newline_1,
			header_line_start,
			header_name,
			space_before_header_value,
			header_value,
			expecting_newline_2,
			expecting_newline_3,
			expecting_content_char1,
			expecting_content_char2,
			expecting_content_char3,
			expecting_content_char4
		};

		ParsingState m_state;
		std::pair<std::string, std::string> m_header;
		unsigned int m_contentLength;
		unsigned int m_contentCharSize;
	};

}}
