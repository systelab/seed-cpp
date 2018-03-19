#include "stdafx.h"
#include "ReplyBuffersBuilderService.h"

#include <string>


namespace systelab { namespace web_server {

	ReplyBuffersBuilderService::ReplyBuffersBuilderService()
	{
	}

	ReplyBuffersBuilderService::~ReplyBuffersBuilderService()
	{
	}

	std::vector<std::string> ReplyBuffersBuilderService::buildBuffers(const Reply& reply) const
	{
		std::vector<std::string> buffers;

		const char name_value_separator[] = { ':', ' ' };
		const char crlf[] = { '\r', '\n' };

		std::string status = translateStatusToString(reply.getStatus());
		buffers.push_back(status);
		buffers.push_back(crlf);

		std::map<std::string, std::string> headers = reply.getHeaders();
		for (auto it = headers.begin(); it != headers.end(); it++)
		{
			buffers.push_back(it->first);
			buffers.push_back(name_value_separator);
			buffers.push_back(it->second);
			buffers.push_back(crlf);
		}

		std::string content = reply.getContent();
		buffers.push_back(crlf);
		buffers.push_back(content);

		return buffers;
	}

	std::string ReplyBuffersBuilderService::translateStatusToString(Reply::StatusType status) const
	{
		switch (status)
		{
			case Reply::StatusType::OK:
				return "HTTP/1.0 200 OK";
			case Reply::StatusType::CREATED:
				return "HTTP/1.0 201 Created";
			case Reply::StatusType::ACCEPTED:
				return "HTTP/1.0 202 Accepted";
			case Reply::StatusType::NO_CONTENT:
				return "HTTP/1.0 204 No Content";
			case Reply::StatusType::MULTIPLE_CHOICES:
				return "HTTP/1.0 300 Multiple Choices";
			case Reply::StatusType::MOVED_PERMANENTLY:
				return "HTTP/1.0 301 Moved Permanently";
			case Reply::StatusType::MOVED_TEMPORARILY:
				return "HTTP/1.0 302 Moved Temporarily";
			case Reply::StatusType::NOT_MODIFIED:
				return "HTTP/1.0 304 Not Modified";
			case Reply::StatusType::BAD_REQUEST:
				return "HTTP/1.0 400 Bad Request";
			case Reply::StatusType::UNAUTHORIZED:
				return "HTTP/1.0 401 Unauthorized";
			case Reply::StatusType::FORBIDDEN:
				return "HTTP/1.0 403 Forbidden";
			case Reply::StatusType::NOT_FOUND:
				return "HTTP/1.0 404 Not Found";
			case Reply::StatusType::INTERNAL_SERVER_ERROR:
				return "HTTP/1.0 500 Internal Server Error";
			case Reply::StatusType::NOT_IMPLEMENTED:
				return "HTTP/1.0 501 Not Implemented";
			case Reply::StatusType::BAD_GATEWAY:
				return "HTTP/1.0 502 Bad Gateway";
			case Reply::StatusType::SERVICE_UNAVAILABLE:
				return "HTTP/1.0 503 Service Unavailable";
			default:
				throw std::exception("");
		}
	}

}}
