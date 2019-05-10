#include "stdafx.h"
#include "Context.h"

#include "DbSQLiteAdapter/Connection.h"
#include "DbSQLiteAdapter/ConnectionConfiguration.h"
#include "DbSQLiteAdapter/Database.h"

#include "DbAdapterInterface/IDatabase.h"
#include "JSONAdapterInterface/IJSONAdapter.h"
#include "WebServerAdapterInterface/IServer.h"


namespace seed_cpp { namespace db_test {

	Context::Context(const std::string& databaseFilepath)
		:Core(std::unique_ptr<systelab::db::IDatabase>(),
			  std::unique_ptr<systelab::web_server::IServer>(),
			  std::unique_ptr<systelab::json::IJSONAdapter>())
		,m_databaseFilepath(databaseFilepath)
	{
	}

	Context::~Context() = default;

	void Context::initialize()
	{
		initializeDatabase();
		initializeModel();
	}

	void Context::initializeDatabase()
	{
		systelab::db::sqlite::Connection databaseConnection;
		systelab::db::sqlite::ConnectionConfiguration databaseConfiguration(m_databaseFilepath);
		m_database = databaseConnection.loadDatabase(databaseConfiguration);
	}

}}
