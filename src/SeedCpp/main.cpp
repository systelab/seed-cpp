#include "stdafx.h"
#include "SeedCppCore/Core.h"

#include "DbSQLiteAdapter/Connection.h"
#include "DbSQLiteAdapter/ConnectionConfiguration.h"

#include "RapidJSONAdapter/JSONAdapter.h"

#include "BoostAsioWebServerAdapter/ServerFactory.h"

#include "WebServerAdapterInterface/IServer.h"
#include "WebServerAdapterInterface/Model/CORSConfiguration.h"
#include "WebServerAdapterInterface/Model/Configuration.h"

#include <boost/filesystem.hpp>


bool fileExists(const std::string& filename)
{
	std::ifstream ifs(filename.c_str());
	return ifs.good();
}

void readFileToString(const std::string& filename, std::string& contents)
{
	std::ifstream ifs(filename);
	if (ifs)
	{
		ifs.seekg(0, std::ios::end);
		contents.resize(static_cast<unsigned int>(ifs.tellg()));
		ifs.seekg(0, std::ios::beg);
		ifs.read(&contents[0], contents.size());
		ifs.close();
	}
	else
	{
		throw std::runtime_error("Unable to find SQL file");
	}
}

std::unique_ptr<systelab::db::IDatabase> loadDatabase()
{
	bool existsBD = fileExists("./seed_cpp.db");

	systelab::db::sqlite::ConnectionConfiguration databaseConfiguration("./seed_cpp.db");
	systelab::db::sqlite::Connection databaseConnection;
	std::unique_ptr<systelab::db::IDatabase> database = databaseConnection.loadDatabase(databaseConfiguration);

	if (!existsBD && database)
	{
		std::string databaseSchemaSQL;
		readFileToString("./Database/schema.sql", databaseSchemaSQL);
		database->executeMultipleStatements(databaseSchemaSQL);
	}

	return database;
}

std::unique_ptr<systelab::web_server::IServer> loadWebServer(int port, bool enableCors)
{
	systelab::web_server::Configuration configuration;
	configuration.setHostAddress("127.0.0.1");
	configuration.setPort(port);
	configuration.setThreadPoolSize(5);

	systelab::web_server::CORSConfiguration &corsConfiguration = configuration.getCORSConfiguration();
	if (enableCors) {
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

std::unique_ptr<systelab::json::IJSONAdapter> loadJSONAdapter()
{
	return std::make_unique<systelab::json::rapidjson::JSONAdapter>();
}

int main(int argc, char** argv)
{
	int port = 8080;
	bool enableCors = false;

	int opt; 
	while((opt = getopt(argc, argv, ":p:cx")) != -1)  
	{
		switch(opt)  
        	{
			case 'p':
				if (atoi(optarg)>0)
				{  
					port=atoi(optarg);
					std::cout << "port is set to: " << port << std::endl; 
				}
                		break;  
			case 'c':
				std::cout << "CORS is enabled" << std::endl;  
				enableCors = true;
				break;
			case ':':
				std::cout << "Option -" << optopt << " needs a value" << std::endl;
				break;
			case '?':
				std::cout << "Unknown option: -" << optopt << std::endl;
				break;
		}
	}  

	try
	{
		std::unique_ptr<systelab::db::IDatabase> database = loadDatabase();
		std::unique_ptr<systelab::web_server::IServer> webServer = loadWebServer(port,enableCors);
		std::unique_ptr<systelab::json::IJSONAdapter> jsonAdapter = loadJSONAdapter();

		seed_cpp::Core core(std::move(database), std::move(webServer), std::move(jsonAdapter));
		core.execute();

		std::cout << "Seed core is now running at " << port << " ..." << std::endl;
		while (true)
		{
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Unable to start seed core:" << std::endl << e.what();
	}

	return 0;
}
