#include "StdAfx.h"
#include "Core.h"

#include "Model/Model.h"

#include "DbSQLiteAdapter/Connection.h"
#include "DbSQLiteAdapter/ConnectionConfiguration.h"

#include "WebServer/WebServer.h"
#include "WebServerInterface/Model/Configuration.h"


namespace seed_cpp {

	Core::Core()
		:m_model(new model::Model())
		,m_database()
		,m_webServer()
	{
	}

	Core::~Core()
	{
	}

	void Core::initialize()
	{
		m_database = buildDatabase();
		m_webServer = buildWebServer();
	}

	void Core::execute()
	{
		m_webServer->start();
	}

	std::unique_ptr<systelab::db::IDatabase> Core::buildDatabase()
	{
		systelab::db::sqlite::ConnectionConfiguration databaseConfiguration("./database.db");
		systelab::db::sqlite::Connection connection;
		return connection.loadDatabase(databaseConfiguration);
	}

	std::unique_ptr<systelab::web_server::IWebServer> Core::buildWebServer()
	{
		std::string hostAddress = "127.0.0.1";
		unsigned int port = 8080;
		unsigned int threadPoolSize = 5;
		systelab::web_server::Configuration configuration(hostAddress, port, threadPoolSize);

		return std::unique_ptr<systelab::web_server::IWebServer>(new systelab::web_server::WebServer(configuration));
	}

}
