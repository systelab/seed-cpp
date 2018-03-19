#include "StdAfx.h"
#include "Core.h"

#include "Model/Model.h"

#include "DbAdapterInterface/IDatabase.h"

#include "WebServerInterface/IWebServer.h"


namespace seed_cpp {

	Core::Core(std::unique_ptr<systelab::db::IDatabase> database,
			   std::unique_ptr<systelab::web_server::IWebServer> webServer)
		:m_model(new model::Model())
		,m_database(std::move(database))
		,m_webServer(std::move(webServer))
	{
	}

	Core::~Core()
	{
	}

	void Core::execute()
	{
		m_webServer->start();
	}

}
