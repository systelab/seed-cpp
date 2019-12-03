# Configuration Settings

The application behavior can be adjusted without recompiling it by means of some predefined settings.
The value assigned to each setting can be set at different levels to facilitate the usage:
* Command line options
* JSON configuration file
* Hard-coded default values


## Command line options

The value of some settings can be defined through the command line arguments passed when executing the application. This method will be the one with top most priority, so it will override the value defined with other mechanisms.

The following commmand line options are available:

```
--help     to produce help message
--cors     to enable cors (by default is disabled)
--port     arg to set an specific port (by default is 8080)
--https    to enable HTTPS support
```

For example:

```
SeedCpp --port 80 --https
```

The parsing of these arguments can be easily implemented by using Boost program options library.
See associated [documentation](https://www.boost.org/doc/libs/1_68_0/doc/html/program_options.html) or [main.cpp](https://github.com/systelab/seed-cpp/blob/master/src/SeedCpp/main.cpp) for a practical example of how to use it.


## JSON Configuration file

When not specified on command line arguments, the settings values will be retrieved from a configuration file in JSON format. The path of this file is `Settings/AppSettings.json` relative to the folder where the `SeedCpp.exe` is stored. The different settings will be structured in sections according to the affected area as shown in the following example:

```json
{
	"db":
	{
		"filepath": "./SeedCpp.db"
	},
	"webServer":
	{
		"address": "127.0.0.1", 
		"port": 7070,
		"threadPoolSize": 3,
		"https":
		{
			"enabled": true,
			"certificateFilepath": "Certificates/server-cert.crt",
			"privateKeyFilepath": "Certificates/server-key.pem",
			"dhParamFilepath": "Certificates/server-dhparam.pem"
		},
		"cors":
		{
			"enabled": true
		}
	},
	"jwt":
	{
		"secretKey": "SeedCppRocksEvenMore!",
		"expirationSeconds": 3600
	}
}
```

The use of a JSON configuration file can be implemented using the [JSONSettings](https://github.com/systelab/cpp-json-settings) library. See the associated documentation for how to formally define the available settings and how to access to them.


## Hard-coded default values

When not specified on a command line option nor on a JSON settings file, a hard-coded value is used. The following table shows the default value for each existing setting:

|*Setting*                          |*Description*                            |*Default Value*                  |
|db.filepath                        |Path where the database file is stored   |'./SeedCpp.db'                   |
|webServer.address                  |IP address of the web server             |127.0.0.1                        |
|webServer.port                     |Port of the web server                   |8080                             |
|webServer.threadPoolSize           |Number of threads of the web server      |5                                |
|webServer.https.enabled            |Shows if web server works with HTTPS     |true                             |
|webServer.https.certificateFilepath|Path of server certificate file          |'Certificates/server-cert.crt'   |
|webServer.https.privateKeyFilepath |Path of server private key file          |'Certificates/server-key.pem'    |
|webServer.https.dhParamFilepath    |Path of server DH param file             |'Certificates/server-dhparam.pem'|
|webServer.cors.enabled             |Shows if web server uses CORS            |true                             |
|jwt.secretKey                      |Secret key used to generate JWT tokens   |'SeedCppRocks!'                  |
|jwt.expirationSeconds              |Time (in seconds) to expire a JWT token  |1800                             |


The implementation of the hard-coded default values can also be implemented using the [JSONSettings](https://github.com/systelab/cpp-json-settings) library.
