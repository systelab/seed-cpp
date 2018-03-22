#pragma once

#include <memory>


namespace systelab {
	namespace db {
		class IDatabase;
	}
	namespace web_server {
		class IWebServer;
	}
}

namespace seed_cpp {
	namespace dal {
		class IDbTranslatorsFactory;
		class IDbDAOFactory;
	}
	namespace model {
		class Model;
	}
}

namespace seed_cpp {

	class Core
	{
	public:
		Core(std::unique_ptr<systelab::db::IDatabase>,
			 std::unique_ptr<systelab::web_server::IWebServer>);
		virtual ~Core();

		void execute();

		systelab::db::IDatabase& getDatabase() const;
		systelab::web_server::IWebServer& getWebServer() const;

		model::Model& getModel() const;
		dal::IDbTranslatorsFactory& getDbTranslatorsFactory() const;
		dal::IDbDAOFactory& getDbDAOFactory() const;

	private:
		void initializeModel();
		void initializeWebServer();

	private:
		std::unique_ptr<systelab::db::IDatabase> m_database;
		std::unique_ptr<systelab::web_server::IWebServer> m_webServer;

		std::unique_ptr<model::Model> m_model;
		std::unique_ptr<dal::IDbTranslatorsFactory> m_dbTranslatorsFactory;
		std::unique_ptr<dal::IDbDAOFactory> m_dbDAOFactory;
	};

}
