#pragma once

#include "JSONSettings/SettingDefinitionMacros.h"

#include <string>


namespace seed_cpp { namespace model { namespace setting {

	bool static CACHE_DISABLED = false;

	JSON_SETTINGS_FILE(ApplicationSettingsFile, "AppSettings.json",

		// Database settings
		JSON_SETTING_BOOL(DbFilepath,				"Database.Filepath",		"./SeedCpp.db",		CACHE_DISABLED)

		// Web server settings
		JSON_SETTING_INT (WebServerPort,			"WebServer.Port",			8080,				CACHE_DISABLED)
		JSON_SETTING_BOOL(WebServerHTTPSEnabled,	"WebServer.HTTPS.Enabled",	true,				CACHE_DISABLED)
		JSON_SETTING_BOOL(WebServerCORSEnabled,		"WebServer.CORS.Enabled",	true,				CACHE_DISABLED)

		// JWT settings
		JSON_SETTING_STR(JWTSecretKey,				"JWT.SecretKey",			"SeedCppRocks!",	CACHE_DISABLED)
		JSON_SETTING_INT(JWTExpirationSeconds,		"JWT.ExpirationSeconds",	1800,				CACHE_DISABLED)  // 30 minutes
	);


	// Web server settings
	static unsigned int WEB_SERVER_PORT = 8080;
	static bool WEB_SERVER_CORS_ENABLED = true;

	// JWT settings
	static std::string JWT_SECRET_KEY = "SeedCppRocks!";
	static long JWT_EXPIRATION_SECONDS = 1800; // 30 minutes

}}}
