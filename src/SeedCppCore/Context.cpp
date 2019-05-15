#include "stdafx.h"
#include "Context.h"

#include "DAL/DAO/Db/IDbDAOFactory.h"
#include "DAL/Translators/Db/IDbTranslatorsFactory.h"
#include "DAL/Translators/JSON/IJSONTranslatorsFactory.h"
#include "Model/Model.h"
#include "REST/Endpoints/IEndpointsFactory.h"
#include "Services/ServicesMgr.h"
#include "Services/Model/IModelServicesFactory.h"
#include "Services/Security/ISecurityServicesFactory.h"
#include "Services/System/ISystemServicesFactory.h"
#include "Services/Validator/IValidatorServicesFactory.h"

#include "DbAdapterInterface/IDatabase.h"
#include "JSONAdapterInterface/IJSONAdapter.h"
#include "WebServerAdapterInterface/IServer.h"


namespace seed_cpp {

	Context::Context(std::unique_ptr<systelab::db::IDatabase> database,
					 std::unique_ptr<systelab::web_server::IServer> webServer,
					 std::unique_ptr<systelab::json::IJSONAdapter> jsonAdapter)
		:m_database(std::move(database))
		, m_webServer(std::move(webServer))
		, m_jsonAdapter(std::move(jsonAdapter))
	{
	}

	Context::~Context() = default;

	// External interfaces
	systelab::db::IDatabase& Context::getDatabase() const
	{
		return *m_database;
	}

	systelab::web_server::IServer& Context::getWebServer() const
	{
		return *m_webServer;
	}

	systelab::json::IJSONAdapter& Context::getJSONAdapter() const
	{
		return *m_jsonAdapter;
	}


	// Model
	model::Model* Context::getModel() const
	{
		return m_model.get();
	}

	void Context::setModel(std::unique_ptr<model::Model> model)
	{
		m_model = std::move(model);
	}


	// Factories
	dal::IDbTranslatorsFactory* Context::getDbTranslatorsFactory() const
	{
		return m_dbTranslatorsFactory.get();
	}

	dal::IDbDAOFactory* Context::getDbDAOFactory() const
	{
		return m_dbDAOFactory.get();
	}

	dal::IJSONTranslatorsFactory* Context::getJSONTranslatorsFactory() const
	{
		return m_jsonTranslatorsFactory.get();
	}

	service::IModelServicesFactory* Context::getModelServicesFactory() const
	{
		return m_modelServicesFactory.get();
	}

	service::ISecurityServicesFactory* Context::getSecurityServicesFactory() const
	{
		return m_securityServicesFactory.get();
	}

	service::ISystemServicesFactory* Context::getSystemServicesFactory() const
	{
		return m_systemServicesFactory.get();
	}

	service::IValidatorServicesFactory* Context::getValidatorServicesFactory() const
	{
		return m_validatorServicesFactory.get();
	}

	rest::IEndpointsFactory* Context::getEndpointsFactory() const
	{
		return m_endpointsFactory.get();
	}

	void Context::setDbTranslatorsFactory(std::unique_ptr<dal::IDbTranslatorsFactory> dbTranslatorsFactory)
	{
		m_dbTranslatorsFactory = std::move(dbTranslatorsFactory);
	}

	void Context::setDbDAOFactory(std::unique_ptr<dal::IDbDAOFactory> dbDAOFactory)
	{
		m_dbDAOFactory = std::move(dbDAOFactory);
	}

	void Context::setJSONTranslatorsFactory(std::unique_ptr<dal::IJSONTranslatorsFactory> jsonTranslatorsFactory)
	{
		m_jsonTranslatorsFactory = std::move(jsonTranslatorsFactory);
	}

	void Context::setModelServicesFactory(std::unique_ptr<service::IModelServicesFactory> modelServicesFactory)
	{
		m_modelServicesFactory = std::move(modelServicesFactory);
	}

	void Context::setSecurityServicesFactory(std::unique_ptr<service::ISecurityServicesFactory> securityServicesFactory)
	{
		m_securityServicesFactory = std::move(securityServicesFactory);
	}

	void Context::setSystemServicesFactory(std::unique_ptr<service::ISystemServicesFactory> systemServicesFactory)
	{
		m_systemServicesFactory = std::move(systemServicesFactory);
	}

	void Context::setValidatorServicesFactory(std::unique_ptr<service::IValidatorServicesFactory> validatorServicesFactory)
	{
		m_validatorServicesFactory = std::move(validatorServicesFactory);
	}

	void Context::setEndpointsFactory(std::unique_ptr<rest::IEndpointsFactory> endpointsFactory)
	{
		m_endpointsFactory = std::move(endpointsFactory);
	}


	// Services
	service::ServicesMgr* Context::getServicesMgr() const
	{
		return m_servicesMgr.get();
	}

	void Context::setServicesMgr(std::unique_ptr<service::ServicesMgr> servicesMgr)
	{
		m_servicesMgr = std::move(servicesMgr);
	}

}
