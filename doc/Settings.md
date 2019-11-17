# Configuration Settings

The application behavior can be adjusted without recompiling it by means of some predefined settings.
The value assigned to each setting can be set at different levels to facilitate the usage:
* Command line options
* JSON configuration file
* Hard-coded default value


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

```
TBD
```


## Default values

```
TBD
```
