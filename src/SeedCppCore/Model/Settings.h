#pragma once

#include "JSONSettings/SettingDefinitionMacros.h"

#include <string>


namespace seed_cpp { namespace model { namespace setting {

	bool static CACHE_DISABLED = false;

	JSON_SETTINGS_FILE(ApplicationSettingsFile, "AppSettings.json",

		// Database settings
		JSON_SETTING_STR (DBFilepath,							"db.filepath",							"./SeedCpp.db",						CACHE_DISABLED)

		// Web server settings
		JSON_SETTING_STR (WebServerHostAddress,					"webServer.address",					"127.0.0.1",						CACHE_DISABLED)
		JSON_SETTING_INT (WebServerPort,						"webServer.port",						8080,								CACHE_DISABLED)
		JSON_SETTING_INT (WebServerThreadPoolSize,				"webServer.threadPoolSize",				5,									CACHE_DISABLED)
		JSON_SETTING_BOOL(WebServerHTTPSEnabled,				"webServer.https.enabled",				false,								CACHE_DISABLED)
		JSON_SETTING_STR (WebServerHTTPSCertificateFilepath,	"webServer.https.certificateFilepath",	"Certificates/server-cert.crt",		CACHE_DISABLED)
		JSON_SETTING_STR (WebServerHTTPSPrivateKeyFilepath,		"webServer.https.privateKeyFilepath",	"Certificates/server-key.pem",		CACHE_DISABLED)
		JSON_SETTING_STR (WebServerHTTPSDHParamFilepath,		"webServer.https.dhParamFilepath",		"Certificates/server-dhparam.pem",	CACHE_DISABLED)
		JSON_SETTING_BOOL(WebServerCORSEnabled,					"webServer.cors.enabled",				true,								CACHE_DISABLED)

		// JWT settings
		JSON_SETTING_STR(JWTSecretKey,							"jwt.secretKey",						"SeedCppRocks!",					CACHE_DISABLED)
		JSON_SETTING_INT(JWTExpirationSeconds,					"jwt.expirationSeconds",				/*30 minutes*/ 1800,				CACHE_DISABLED)
	);

}}}
