#include "stdafx.h"
#include "Core.h"

#include "SeedCppCore/Context.h"
#include "SeedCppCore/DAL/DAO/Db/DbDAOFactory.h"
#include "SeedCppCore/DAL/Translators/Db/DbTranslatorsFactory.h"
#include "SeedCppCore/Model/Model.h"
#include "SeedCppCore/Services/ServicesMgr.h"
#include "SeedCppCore/Services/Model/ModelLoaderService.h"
#include "SeedCppCore/Services/Model/ModelServicesFactory.h"
#include "SeedCppCore/Services/System/SystemServicesFactory.h"

#include "DbSQLiteAdapter/Connection.h"
#include "DbSQLiteAdapter/ConnectionConfiguration.h"

#include "DbAdapterInterface/IDatabase.h"
#include "JSONAdapterInterface/IJSONAdapter.h"
#include "WebServerAdapterInterface/IServer.h"


namespace seed_cpp { namespace db_test {

	Core::Core(const std::string& databaseFilepath)
		:m_databaseFilepath(databaseFilepath)
		,m_context()
	{
	}

	Core::~Core() = default;

	void Core::initialize()
	{
		systelab::db::sqlite::Connection databaseConnection;
		systelab::db::sqlite::ConnectionConfiguration databaseConfiguration(m_databaseFilepath);
		auto database = databaseConnection.loadDatabase(databaseConfiguration);

		m_context = std::make_unique<Context>(std::move(database),
											  std::unique_ptr<systelab::web_server::IServer>(),
											  std::unique_ptr<systelab::json::IJSONAdapter>());

		buildModel();
		buildFactories();
		buildServices();

		initializeModel();
	}

	model::Model& Core::getModel()
	{
		return *m_context->getModel();
	}

	service::ServicesMgr& Core::getServicesMgr()
	{
		return *m_context->getServicesMgr();
	}

	void Core::buildModel()
	{
		auto model = std::make_unique<model::Model>();
		m_context->setModel(std::move(model));
	}

	void Core::buildFactories()
	{
		auto dbTranslatorsFactory = std::make_unique<dal::DbTranslatorsFactory>();
		auto dbDAOFactory = std::make_unique<dal::DbDAOFactory>(*m_context);
		auto modelServicesFactory = std::make_unique<service::ModelServicesFactory>(*m_context);
		auto systemServicesFactory = std::make_unique<service::SystemServicesFactory>(*m_context);

		m_context->setDbTranslatorsFactory(std::move(dbTranslatorsFactory));
		m_context->setDbDAOFactory(std::move(dbDAOFactory));
		m_context->setModelServicesFactory(std::move(modelServicesFactory));
		m_context->setSystemServicesFactory(std::move(systemServicesFactory));
	}

	void Core::buildServices()
	{
		auto servicesMgr = std::make_unique<service::ServicesMgr>(*m_context);
		m_context->setServicesMgr(std::move(servicesMgr));
	}

	void Core::initializeModel()
	{
		service::ModelLoaderService loader(*m_context);
		loader.loadModel();
	}

}}
