#pragma once

namespace systelab {
	namespace db {
		class IDatabase;
	}
	namespace json {
		class IJSONAdapter;
	}
	namespace setting {
		class ISettingsService;
	}
	namespace web_server {
		class IServer;
	}
}

namespace seed_cpp {

	class Context;

	class Core
	{
	public:
		Core(std::unique_ptr<systelab::setting::ISettingsService>);
		virtual ~Core();

		void execute(unsigned int port, bool enableHTTPS, bool enableCORS);

	protected:
		std::unique_ptr<systelab::db::IDatabase> loadDatabase();
		std::unique_ptr<systelab::web_server::IServer> loadWebServer(int port, bool enableHTTPS, bool enableCORS);
		std::unique_ptr<systelab::json::IJSONAdapter> loadJSONAdapter();

		void initializeContext();
		void initializeModel();
		void initializeWebServer();

		bool fileExists(const std::string& filename);
		std::string getFileContents(const std::string& filename);

	private:
		std::unique_ptr<systelab::setting::ISettingsService> m_settingsService;
		std::unique_ptr<Context> m_context;
	};

}
