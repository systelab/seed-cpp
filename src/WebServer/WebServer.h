#pragma once

#include "WebServerInterface/IWebServer.h"

#include <boost/asio.hpp>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>


namespace systelab { namespace web_server {

	class Connection;
	class Configuration;
	class WebServicesMgr;

	class WebServer : public IWebServer
	{
	public:
		WebServer(const Configuration&);
		virtual ~WebServer();

		void setConfiguration(std::unique_ptr<Configuration>);
		void registerWebService(std::unique_ptr<IWebService>);

		bool isRunning() const;
		void start();
		void stop();

	private:
		void runThread();

		void openAcceptor();
		void startAcceptor();
		void handleAccept(const boost::system::error_code&);

	protected:
		std::unique_ptr<Configuration> m_configuration;
		std::unique_ptr<WebServicesMgr> m_webServicesMgr;

		boost::asio::io_service m_io_service;
		boost::asio::ip::tcp::acceptor m_acceptor;
		std::vector< boost::shared_ptr<std::thread> > m_threads;
		bool m_running;

		boost::shared_ptr<Connection> m_newConnection;
	};

}}
