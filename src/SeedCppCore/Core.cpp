#include "StdAfx.h"
#include "Core.h"

#include "DAL/DAO/ILoadDAO.h"
#include "DAL/DAO/ISaveDAO.h"
#include "DAL/DAO/Db/DbDAOFactory.h"
#include "DAL/Translators/Db/DbTranslatorsFactory.h"
#include "DAL/Translators/JSON/JSONTranslatorsFactory.h"
#include "Model/Model.h"
#include "Model/User.h"
#include "REST/RESTAPIWebService.h"
#include "REST/Endpoints/EndpointsFactory.h"
#include "Services/ServicesFactory.h"
#include "Services/ServicesMgr.h"
#include "Services/System/IUUIDGeneratorService.h"

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
		m_model = std::make_unique<model::Model>();
		m_dbTranslatorsFactory = std::make_unique<dal::DbTranslatorsFactory>();
		m_dbDAOFactory = std::make_unique<dal::DbDAOFactory>(*this);
		m_jsonTranslatorsFactory = std::make_unique<dal::JSONTranslatorsFactory>();
		m_servicesFactory = std::make_unique<service::ServicesFactory>(*this);
		m_servicesMgr = std::make_unique<service::ServicesMgr>(*m_servicesFactory);
		m_endpointsFactory = std::make_unique<rest::EndpointsFactory>(*this);
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

	dal::IJSONTranslatorsFactory& Core::getJSONTranslatorsFactory() const
	{
		return *m_jsonTranslatorsFactory;
	}

	service::IServicesFactory& Core::getServicesFactory() const
	{
		return *m_servicesFactory;
	}

	service::ServicesMgr& Core::getServicesMgr() const
	{
		return *m_servicesMgr;
	}

	rest::IEndpointsFactory& Core::getEndpointsFactory() const
	{
		return *m_endpointsFactory;
	}

	void Core::initializeModel()
	{
		std::unique_ptr<dal::ILoadDAO> userLoadDAO = m_dbDAOFactory->buildUserLoadDAO();
		userLoadDAO->loadAll();

		model::EntityMgr<model::User>& userMgr = getModel().getUserMgr();
		if (userMgr.count() == 0)
		{
			std::string uuid = m_servicesMgr->getUUIDGeneratorService().generateUUID();

			auto defaultUser = std::make_unique<model::User>();
			defaultUser->setId(uuid);
			defaultUser->setSurname("Systelab");
			defaultUser->setName("Systelab");
			defaultUser->setLogin("Systelab");
			defaultUser->setPassword("Systelab");
			defaultUser->setRole(model::User::ADMIN_ROLE);

			auto userSaveDAO = getDbDAOFactory().buildUserSaveDAO(*defaultUser);
			userSaveDAO->addEntity();
			userMgr.addEntity(std::move(defaultUser));
		}

		std::unique_ptr<dal::ILoadDAO> patientLoadDAO = m_dbDAOFactory->buildPatientLoadDAO();
		patientLoadDAO->loadAll();
	}

	void Core::initializeWebServer()
	{
		std::unique_ptr<systelab::web_server::IWebService> restWebService;
		restWebService = std::make_unique<rest::RESTAPIWebService>(getEndpointsFactory());
		m_webServer->registerWebService(std::move(restWebService));

		m_webServer->start();
	}

}
