#include "stdafx.h"
#include "Core.h"

#include "Context.h"
#include "Model/Settings.h"
#include "REST/RESTAPIWebService.h"
#include "Services/Model/ModelInitializationService.h"
#include "Services/System/ContextBuilderService.h"

#include "DbSQLiteAdapter/Connection.h"
#include "DbSQLiteAdapter/ConnectionConfiguration.h"

#include "BoostAsioWebServerAdapter/ServerFactory.h"

#include "WebServerAdapterInterface/IServer.h"
#include "WebServerAdapterInterface/Model/CORSConfiguration.h"
#include "WebServerAdapterInterface/Model/Configuration.h"

#include "RapidJSONAdapter/JSONAdapter.h"

#include "JSONSettings/ISettingsService.h"
#include "JSONSettings/SettingsMacros.h"

#include <thread>


namespace seed_cpp {

	Core::Core(std::unique_ptr<systelab::setting::ISettingsService> settingsService)
		:m_settingsService(std::move(settingsService))
		,m_context()
	{
	}

	Core::~Core() = default;

	void Core::execute(unsigned int port, bool enableHttps, bool enableCors)
	{
		std::unique_ptr<systelab::db::IDatabase> database = loadDatabase();
		std::unique_ptr<systelab::web_server::IServer> webServer = loadWebServer(port, enableHttps, enableCors);
		std::unique_ptr<systelab::json::IJSONAdapter> jsonAdapter = loadJSONAdapter();

		m_context = std::make_unique<Context>(std::move(database), std::move(webServer), std::move(jsonAdapter));

		initializeContext();
		initializeModel();
		initializeWebServer();

		std::cout << "Seed core is now running at " << port << " ..." << std::endl;
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	std::unique_ptr<systelab::db::IDatabase> Core::loadDatabase()
	{
		std::string dbFilepath = GET_JSON_SETTING_STR((*m_settingsService), model::setting::ApplicationSettingsFile, DBFilepath);
		bool existsDB = fileExists(dbFilepath);

		systelab::db::sqlite::ConnectionConfiguration databaseConfiguration(dbFilepath);
		systelab::db::sqlite::Connection databaseConnection;
		std::unique_ptr<systelab::db::IDatabase> database = databaseConnection.loadDatabase(databaseConfiguration);

		if (!existsDB && database)
		{
			std::string databaseSchemaSQL = getFileContents("./Database/schema.sql");
			database->executeMultipleStatements(databaseSchemaSQL);
		}

		return database;
	}

	std::unique_ptr<systelab::web_server::IServer> Core::loadWebServer(int port, bool enableHttps, bool enableCors)
	{
		std::string hostAddress = GET_JSON_SETTING_STR((*m_settingsService), model::setting::ApplicationSettingsFile, WebServerHostAddress);
		size_t threadPoolSize = GET_JSON_SETTING_INT((*m_settingsService), model::setting::ApplicationSettingsFile, WebServerThreadPoolSize);

		systelab::web_server::Configuration configuration;
		configuration.setHostAddress(hostAddress);
		configuration.setPort(port);
		configuration.setThreadPoolSize(threadPoolSize);

		systelab::web_server::SecurityConfiguration& securityConfiguration = configuration.getSecurityConfiguration();
		securityConfiguration.setHTTPSEnabled(enableHttps);
		if (enableHttps)
		{
			std::string serverCertificateFilepath = GET_JSON_SETTING_STR((*m_settingsService), model::setting::ApplicationSettingsFile, WebServerHTTPSCertificateFilepath);
			std::string serverPrivateKeyFilepath = GET_JSON_SETTING_STR((*m_settingsService), model::setting::ApplicationSettingsFile, WebServerHTTPSPrivateKeyFilepath);
			std::string serverDHParamFilepath = GET_JSON_SETTING_STR((*m_settingsService), model::setting::ApplicationSettingsFile, WebServerHTTPSDHParamFilepath);

			securityConfiguration.setServerCertificate(getFileContents(serverCertificateFilepath));
			securityConfiguration.setServerPrivateKey(getFileContents(serverPrivateKeyFilepath));
			securityConfiguration.setServerDHParam(getFileContents(serverDHParamFilepath));
		}

		systelab::web_server::CORSConfiguration& corsConfiguration = configuration.getCORSConfiguration();
		if (enableCors)
		{
			corsConfiguration.setEnabled(true);
			corsConfiguration.addAllowedOrigin("*");
			corsConfiguration.addAllowedHeader("origin");
			corsConfiguration.addAllowedHeader("content-type");
			corsConfiguration.addAllowedHeader("accept");
			corsConfiguration.addAllowedHeader("authorization");
			corsConfiguration.addAllowedHeader("Etag");
			corsConfiguration.addAllowedHeader("if-none-match");
			corsConfiguration.setAllowedCredentials(true);
			corsConfiguration.addAllowedMethod("GET");
			corsConfiguration.addAllowedMethod("POST");
			corsConfiguration.addAllowedMethod("PUT");
			corsConfiguration.addAllowedMethod("DELETE");
			corsConfiguration.addAllowedMethod("OPTIONS");
			corsConfiguration.addAllowedMethod("HEAD");
			corsConfiguration.setMaxAge(1209600);
			corsConfiguration.addExposedHeader("origin");
			corsConfiguration.addExposedHeader("content-type");
			corsConfiguration.addExposedHeader("accept");
			corsConfiguration.addExposedHeader("authorization");
			corsConfiguration.addExposedHeader("ETag");
			corsConfiguration.addExposedHeader("if-none-match");
		}
		else
		{
			corsConfiguration.setEnabled(false);
		}

		systelab::web_server::boostasio::ServerFactory serverFactory;
		return serverFactory.buildServer(configuration);
	}

	std::unique_ptr<systelab::json::IJSONAdapter> Core::loadJSONAdapter()
	{
		return std::make_unique<systelab::json::rapidjson::JSONAdapter>();
	}

	void Core::initializeContext()
	{
		service::ContextBuilderService contextBuilderService(*m_context);
		contextBuilderService.buildFactories();
		contextBuilderService.buildModel();
		contextBuilderService.buildServices();
	}

	void Core::initializeModel()
	{
		service::ModelInitializationService modelInitializationService(*m_context);
		modelInitializationService.initialize();
	}

	void Core::initializeWebServer()
	{
		auto& webServer = m_context->getWebServer();
		auto& endpointsFactory = *m_context->getEndpointsFactory();
		auto& routeAccessValidatorsFactory = *m_context->getRouteAccessValidatorsFactory();
		auto restWebService = std::make_unique<rest::RESTAPIWebService>(endpointsFactory, routeAccessValidatorsFactory, *m_settingsService);
		
		webServer.registerWebService(std::move(restWebService));
		webServer.start();
	}

	bool Core::fileExists(const std::string& filename)
	{
		std::ifstream ifs(filename.c_str());
		return ifs.good();
	}

	std::string Core::getFileContents(const std::string& filename)
	{
		std::ifstream ifs(filename);
		if (ifs)
		{
			std::stringstream ss;
			ss << ifs.rdbuf();
			std::string fileContents = ss.str();
			ifs.close();

			return fileContents;
		}
		else
		{
			throw std::runtime_error("Unable to find file " + filename);
		}
	}

}
