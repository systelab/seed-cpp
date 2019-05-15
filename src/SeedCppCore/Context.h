#pragma once

namespace systelab {
	namespace db {
		class IDatabase;
	}
	namespace json {
		class IJSONAdapter;
	}
	namespace web_server {
		class IServer;
	}
}

namespace seed_cpp {
	namespace dal {
		class IDbTranslatorsFactory;
		class IDbDAOFactory;
		class IJSONTranslatorsFactory;
	}
	namespace model {
		class Model;
	}
	namespace rest {
		class IEndpointsFactory;
	}
	namespace service {
		class IModelServicesFactory;
		class ISecurityServicesFactory;
		class ISystemServicesFactory;
		class IValidatorServicesFactory;
		class ServicesMgr;
	}
}

namespace seed_cpp {

	class Context
	{
	public:
		Context(std::unique_ptr<systelab::db::IDatabase>,
				std::unique_ptr<systelab::web_server::IServer>,
				std::unique_ptr<systelab::json::IJSONAdapter>);
		virtual ~Context();

		// External interfaces
		systelab::db::IDatabase& getDatabase() const;
		systelab::web_server::IServer& getWebServer() const;
		systelab::json::IJSONAdapter& getJSONAdapter() const;

		// Model
		model::Model* getModel() const;
		void setModel(std::unique_ptr<model::Model>);

		// Factories
		dal::IDbTranslatorsFactory* getDbTranslatorsFactory() const;
		dal::IDbDAOFactory* getDbDAOFactory() const;
		dal::IJSONTranslatorsFactory* getJSONTranslatorsFactory() const;
		service::IModelServicesFactory* getModelServicesFactory() const;
		service::ISecurityServicesFactory* getSecurityServicesFactory() const;
		service::ISystemServicesFactory* getSystemServicesFactory() const;
		service::IValidatorServicesFactory* getValidatorServicesFactory() const;
		rest::IEndpointsFactory* getEndpointsFactory() const;

		void setDbTranslatorsFactory(std::unique_ptr<dal::IDbTranslatorsFactory>);
		void setDbDAOFactory(std::unique_ptr<dal::IDbDAOFactory>);
		void setJSONTranslatorsFactory(std::unique_ptr<dal::IJSONTranslatorsFactory>);
		void setModelServicesFactory(std::unique_ptr<service::IModelServicesFactory>);
		void setSecurityServicesFactory(std::unique_ptr<service::ISecurityServicesFactory>);
		void setSystemServicesFactory(std::unique_ptr<service::ISystemServicesFactory>);
		void setValidatorServicesFactory(std::unique_ptr<service::IValidatorServicesFactory>);
		void setEndpointsFactory(std::unique_ptr<rest::IEndpointsFactory>);

		// Services
		service::ServicesMgr* getServicesMgr() const;
		void setServicesMgr(std::unique_ptr<service::ServicesMgr>);

	protected:
		std::unique_ptr<systelab::db::IDatabase> m_database;
		std::unique_ptr<systelab::web_server::IServer> m_webServer;
		std::unique_ptr<systelab::json::IJSONAdapter> m_jsonAdapter;

		std::unique_ptr<model::Model> m_model;

		std::unique_ptr<dal::IDbTranslatorsFactory> m_dbTranslatorsFactory;
		std::unique_ptr<dal::IDbDAOFactory> m_dbDAOFactory;
		std::unique_ptr<dal::IJSONTranslatorsFactory> m_jsonTranslatorsFactory;
		std::unique_ptr<service::IModelServicesFactory> m_modelServicesFactory;
		std::unique_ptr<service::ISecurityServicesFactory> m_securityServicesFactory;
		std::unique_ptr<service::ISystemServicesFactory> m_systemServicesFactory;
		std::unique_ptr<service::IValidatorServicesFactory> m_validatorServicesFactory;
		std::unique_ptr<rest::IEndpointsFactory> m_endpointsFactory;

		std::unique_ptr<service::ServicesMgr> m_servicesMgr;
	};

}
