#include "stdafx.h"
#include "SeedCppCore/Core.h"
#include "SeedCppCore/Model/Settings.h"

#include "JSONSettings/SettingsService.h"
#include "JSONSettings/SettingsMacros.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>


namespace po = boost::program_options;

int main(int ac, char* av[])
{
	try
	{
		SET_JSON_SETTINGS_FOLDER("./Settings");

		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("cors", "enable cors")
			("https", "enable https")
			("port", po::value<int>(), "set port");

		po::variables_map vm;
		po::store(po::parse_command_line(ac, av, desc), vm);
		po::notify(vm);

		if (vm.count("help"))
		{
			std::cout << desc << "\n";
			return 0;
		}

		auto settingsService = std::make_unique<systelab::setting::SettingsService>();
		int port = GET_JSON_SETTING_INT((*settingsService), seed_cpp::model::setting::ApplicationSettingsFile, WebServerPort);
		if (vm.count("port"))
		{
			port = vm["port"].as<int>();
		}

		bool enableHTTPS = GET_JSON_SETTING_BOOL((*settingsService), seed_cpp::model::setting::ApplicationSettingsFile, WebServerHTTPSEnabled);
		if (vm.count("https"))
		{
			enableHTTPS = true;
		}

		bool enableCORS = GET_JSON_SETTING_BOOL((*settingsService), seed_cpp::model::setting::ApplicationSettingsFile, WebServerCORSEnabled);
		if (vm.count("cors"))
		{
			enableCORS = true;
		}

		std::cout << "Port set to " << port << "." << std::endl;
		std::cout << "HTTPS is " << (enableHTTPS ? "enabled" : "disabled") << "." << std::endl;
		std::cout << "CORS is " << (enableCORS ? "enabled" : "disabled") << "." << std::endl;

		seed_cpp::Core core(std::move(settingsService));
		core.execute(port, enableHTTPS, enableCORS);
	}
	catch (std::exception &e)
	{
		std::cout << "Unable to start seed core:" << std::endl << e.what();
	}

	return 0;
}
