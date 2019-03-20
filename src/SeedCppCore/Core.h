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
		class IServicesFactory;
		class ServicesMgr;
	}
}

namespace seed_cpp {

	class Core
	{
	public:
		Core(std::unique_ptr<systelab::db::IDatabase>,
			 std::unique_ptr<systelab::web_server::IServer>,
			 std::unique_ptr<systelab::json::IJSONAdapter>);
		virtual ~Core();

		void execute();

		systelab::db::IDatabase& getDatabase() const;
		systelab::web_server::IServer& getWebServer() const;
		systelab::json::IJSONAdapter& getJSONAdapter() const;

		model::Model& getModel() const;
		dal::IDbTranslatorsFactory& getDbTranslatorsFactory() const;
		dal::IDbDAOFactory& getDbDAOFactory() const;
		dal::IJSONTranslatorsFactory& getJSONTranslatorsFactory() const;
		service::IServicesFactory& getServicesFactory() const;
		service::ServicesMgr& getServicesMgr() const;
		rest::IEndpointsFactory& getEndpointsFactory() const;

	private:
		void initializeModel();
		void initializeWebServer();

	private:
		std::unique_ptr<systelab::db::IDatabase> m_database;
		std::unique_ptr<systelab::web_server::IServer> m_webServer;
		std::unique_ptr<systelab::json::IJSONAdapter> m_jsonAdapter;

		std::unique_ptr<model::Model> m_model;
		std::unique_ptr<dal::IDbTranslatorsFactory> m_dbTranslatorsFactory;
		std::unique_ptr<dal::IDbDAOFactory> m_dbDAOFactory;
		std::unique_ptr<dal::IJSONTranslatorsFactory> m_jsonTranslatorsFactory;
		std::unique_ptr<service::IServicesFactory> m_servicesFactory;
		std::unique_ptr<service::ServicesMgr> m_servicesMgr;
		std::unique_ptr<rest::IEndpointsFactory> m_endpointsFactory;
	};

}
