#include "Connection.h"

#include "Agents/IRequestParserAgent.h"
#include "Services/IReplyBufferBuilderService.h"
#include "Services/IRequestURIParserService.h"
#include "Services/IRequestHandlingService.h"

#include "Model/Configuration.h"
#include "Model/Reply.h"
#include "Model/Request.h"

#include <vector>
#include <boost/bind.hpp>


namespace systelab { namespace web_server {

	Connection::Connection(boost::asio::io_service& io_service,
						   std::unique_ptr<IRequestParserAgent> requestParserAgent,
						   std::unique_ptr<IRequestURIParserService> requestURIParserService,
						   std::unique_ptr<IRequestHandlingService> requestHandlingService,
						   std::unique_ptr<IReplyBufferBuilderService> replyBuffersBuilderService)
		:m_strand(io_service)
		,m_socket(io_service)
		,m_requestBuffer()
		,m_replyBuffer()
		,m_requestParserAgent(std::move(requestParserAgent))
		,m_requestURIParserService(std::move(requestURIParserService))
		,m_requestHandlingService(std::move(requestHandlingService))
		,m_replyBufferBuilderService(std::move(replyBuffersBuilderService))
		,m_request()
		,m_reply()
	{
	}

	Connection::~Connection()
	{
	}

	void Connection::start()
	{
		m_request.reset(new Request());
		m_reply.reset();

		m_socket.async_read_some(boost::asio::buffer(m_requestBuffer),
								 m_strand.wrap(boost::bind(&Connection::handleRead, shared_from_this(),
											   boost::asio::placeholders::error,
											   boost::asio::placeholders::bytes_transferred)));
	}

	boost::asio::basic_socket<boost::asio::ip::tcp>& Connection::socket()
	{
		return m_socket;
	}

	void Connection::handleRead(const boost::system::error_code& e, std::size_t bytes_transferred)
	{
		if (!e)
		{
			boost::optional<bool> result = m_requestParserAgent->parseBuffer(m_requestBuffer.data(), bytes_transferred, *m_request);

			if (!result.is_initialized())
			{
				m_socket.async_read_some(boost::asio::buffer(m_requestBuffer),
					m_strand.wrap(
					boost::bind(&Connection::handleRead, shared_from_this(),
								boost::asio::placeholders::error,
								boost::asio::placeholders::bytes_transferred)));
			}
			else
			{
				if(result)
				{
					result = m_requestURIParserService->parse(*m_request);
				}

				if (result)
				{
					m_reply = m_requestHandlingService->processRequest(*m_request);
				}
				else
				{
					m_reply.reset(new Reply());
					m_reply->setStatus(Reply::BAD_REQUEST);
				}

				m_replyBuffer = m_replyBufferBuilderService->buildBuffer(*m_reply);

				boost::asio::async_write(m_socket, boost::asio::buffer(m_replyBuffer),
										 m_strand.wrap(boost::bind(&Connection::handleWrite, shared_from_this(),
													   boost::asio::placeholders::error)));
			}
		}
		else
		{
			std::string message = e.message();
			message = message;
		}
	}

	void Connection::handleWrite(const boost::system::error_code& e)
	{
		if (!e)
		{
			boost::system::error_code ignored_ec;
			m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
		}
	}

}}
