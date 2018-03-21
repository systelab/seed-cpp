#include "StdAfx.h"
#include "Core.h"

#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
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

	systelab::db::IDatabase& Core::getDatabase() const
	{
		return *m_database;
	}

	systelab::web_server::IWebServer& Core::getWebServer() const
	{
		return *m_webServer;
	}

	model::Model& Core::getModel() const
	{
		return *m_model;
	}

	dal::IDbTranslatorsFactory& Core::getDbTranslatorsFactory() const
	{
		return *m_dbTranslatorsFactory;
	}

}
