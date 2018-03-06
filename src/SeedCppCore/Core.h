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

namespace seed_cpp { namespace model {
	class Model;
}}

namespace seed_cpp {

	class Core
	{
	public:
		Core();
		virtual ~Core();

		void initialize();
		void execute();

	protected:
		std::unique_ptr<systelab::db::IDatabase> buildDatabase();
		std::unique_ptr<systelab::web_server::IWebServer> buildWebServer();

	private:
		std::unique_ptr<model::Model> m_model;
		std::unique_ptr<systelab::db::IDatabase> m_database;
		std::unique_ptr<systelab::web_server::IWebServer> m_webServer;
	};

}
