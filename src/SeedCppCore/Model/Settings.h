#pragma once

#include <string>

namespace seed_cpp { namespace model { namespace setting {

	// Web server settings
	static unsigned int WEB_SERVER_PORT = 8080;
	static bool WEB_SERVER_CORS_ENABLED = true;

	// JWT settings
	static std::string JWT_SECRET_KEY = "SeedCppRocks!";
	static long JWT_EXPIRATION_SECONDS = 1800; // 30 minutes

}}}
