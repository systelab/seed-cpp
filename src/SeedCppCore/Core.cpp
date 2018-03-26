#include "StdAfx.h"
#include "Core.h"

#include "DAL/DAO/ILoadDAO.h"
#include "DAL/DAO/Db/DbDAOFactory.h"
#include "DAL/Translators/Db/DbTranslatorsFactory.h"
#include "Model/Model.h"
#include "REST/RESTAPIWebService.h"
#include "REST/Endpoints/EndpointsFactory.h"

#include "DbAdapterInterface/IDatabase.h"
#include "JSONAdapterInterface/IJSONAdapter.h"
#include "WebServerInterface/IWebServer.h"


namespace seed_cpp {

	Core::Core(std::unique_ptr<systelab::db::IDatabase> database,
			   std::unique_ptr<systelab::web_server::IWebServer> webServer,
			   std::unique_ptr<systelab::json_adapter::IJSONAdapter> jsonAdapter)
		:m_database(std::move(database))
		,m_webServer(std::move(webServer))
		,m_jsonAdapter(std::move(jsonAdapter))
	{
		m_model.reset(new model::Model());
		m_dbTranslatorsFactory.reset(new dal::DbTranslatorsFactory());
		m_dbDAOFactory.reset(new dal::DbDAOFactory(*this));
		m_endpointsFactory.reset(new rest::EndpointsFactory(*this));
	}

	Core::~Core()
	{
	}

	void Core::execute()
	{
		initializeModel();
		initializeWebServer();
	}

	systelab::db::IDatabase& Core::getDatabase() const
	{
		return *m_database;
	}

	systelab::web_server::IWebServer& Core::getWebServer() const
	{
		return *m_webServer;
	}

	systelab::json_adapter::IJSONAdapter& Core::getJSONAdapter() const
	{
		return *m_jsonAdapter;
	}

	model::Model& Core::getModel() const
	{
		return *m_model;
	}

	dal::IDbTranslatorsFactory& Core::getDbTranslatorsFactory() const
	{
		return *m_dbTranslatorsFactory;
	}

	dal::IDbDAOFactory& Core::getDbDAOFactory() const
	{
		return *m_dbDAOFactory;
	}

	rest::IEndpointsFactory& Core::getEndpointsFactory() const
	{
		return *m_endpointsFactory;
	}

	void Core::initializeModel()
	{
		std::unique_ptr<dal::ILoadDAO> patientLoadDAO = m_dbDAOFactory->buildPatientLoadDAO();
		patientLoadDAO->loadAll();
	}

	void Core::initializeWebServer()
	{
		std::unique_ptr<systelab::web_server::IWebService> restWebService(new rest::RESTAPIWebService(getEndpointsFactory()));
		m_webServer->registerWebService(std::move(restWebService));

		m_webServer->start();
	}

}
