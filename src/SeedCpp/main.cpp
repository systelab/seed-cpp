#include "stdafx.h"
#include "SeedCppCore/Core.h"

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>


namespace po = boost::program_options;


int main(int ac, char* av[])
{
	try
	{
		int port = 8080;
		bool enableCors = false;
		bool enableHttps = false;

		//po::options_description desc("Allowed options");
		//desc.add_options()
		//	("help", "produce help message")
		//	("cors", "enable cors")
		//	("https", "enable https")
		//	("port", po::value<int>(), "set port");
		//
		//po::variables_map vm;
		//po::store(po::parse_command_line(ac, av, desc), vm);
		//po::notify(vm);
		//
		//if (vm.count("help"))
		//{
		//	std::cout << desc << "\n";
		//	return 0;
		//}

		//if (vm.count("port"))
		//{
		//	port = vm["port"].as<int>();
		//	std::cout << "Port set to " << port << ".\n";
		//}

		//if (vm.count("cors"))
		//{
		//	enableCors = true;
		//	std::cout << "CORS is enabled.\n";
		//}

		//if (vm.count("https"))
		//{
		//	enableHttps = true;
		//	std::cout << "HTTPS is enabled.\n";
		//}

		seed_cpp::Core core;
		core.execute(port, enableCors, enableHttps);
	}
	catch (std::exception &e)
	{
		std::cout << "Unable to start seed core:" << std::endl << e.what();
	}

	return 0;
}
