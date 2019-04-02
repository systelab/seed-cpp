[![Build Status](https://travis-ci.org/systelab/seed-cpp.svg?branch=master)](https://travis-ci.org/systelab/seed-cpp)
[![Build status](https://ci.appveyor.com/api/projects/status/kiy6ugv134i7nbon?svg=true)](https://ci.appveyor.com/project/systelab/seed-cpp)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/1da2b731322b4856a2f2f6b49bdfa729)](https://www.codacy.com/app/systelab/seed-cpp?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=systelab/seed-cpp&amp;utm_campaign=Badge_Grade)

# seed-cpp — Seed for C++ Systelab projects

This project is an application skeleton for a typical C++ application. You can use it to quickly bootstrap your projects and dev environment.

The seed contains a Patient Management sample REST API.

The app doesn't do much, just shows how to use different C++ patterns and other suggested tools together:
* [SQLite](https://www.sqlite.org)
* [JSON](https://www.json.org/)
* [HTTPS](https://en.wikipedia.org/wiki/HTTPS) `Not available yet`
* [JWT](https://jwt.io/)
* [CORS](https://en.wikipedia.org/wiki/Cross-origin_resource_sharing)
* [Swagger](https://swagger.io/) `Not available yet`

## Download from bintray

Not available yet. Meanwhile, you can build it from sources.

## Build from sources

To build the application, the following *prerequisites* are mandatory:

  - [Git](https://git-scm.com/)
  - [Conan](https://conan.io/)
  - [CMake](https://cmake.org/)
  - [Visual Studio](https://visualstudio.microsoft.com/) (only on Windows)
  - [GCC](https://gcc.gnu.org/) (only on Linux)

On Linux, Homebrew (http://brew.sh/) is good alternative to install the prerequisites. If you have Homebrew installed, run the following commands:

```bash
brew install git
brew install conan
brew install cmake
brew install gcc
```

To build the application, we will follow the next steps:
  1. Clone this repository in a local drive
  2. Make a build directory (i.e. `build/`)
  3. Install `conan` dependencies in the build directory
  4. Run `cmake` in the build directory to configure build targets
  5. Use `Visual Studio` (on Windows) or `make` (on Linux) to build the library

### Windows

In order to build the application on Windows, run the following commands:

``` bash
git clone https://github.com/systelab/seed-cpp
cd seed-cpp
md build && cd build
conan install .. -s arch=x86
cmake ..
devenv.exe SeedCpp.sln
```

### Linux

In order to build the application on Linux, run the following commands:

``` bash
git clone https://github.com/systelab/seed-cpp
cd seed-cpp
mkdir build && cd build
conan install ..
cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
make
```

## Usage

To run the application, just launch the `SeedCpp` executable.

Use the following commmand line options:

--help to produce help message
--cors to enable cors (by default is disabled)
--port arg to set an specific port (by default is 8080)

For example:

```
SeedCpp --port 80 --cors
```

> In Linux and macOS, if you have the error 'dyld: Library not loaded', as a workaround, please copy the generated *.dyld libraries to /usr/local/lib

> In Linux and macOS, if you have the error 'dyld: Library not loaded', as a workaround, please copy the generated *.dyld libraries to /usr/local/lib

### Login

Before any request, users must authenticate to the REST API by using the login endpoint (with username `Systelab` and password `Systelab`):

```
curl -v -d "login=Systelab&password=Systelab" -H "Content-Type: application/x-www-form-urlencoded" http://127.0.0.1:8080/seed/v1/users/login
```

The response for this request should contain an authentication token (based on [JWT](https://jwt.io/)) in the `Authorization` header:

```
* Trying 127.0.0.1...
* TCP_NODELAY set
* Connected to 127.0.0.1 (127.0.0.1) port 8080 (#0)
> POST /seed/v1/users/login HTTP/1.1
> Host: 127.0.0.1:8080
> User-Agent: curl/7.54.0
> Accept: */*
> Content-Type: application/x-www-form-urlencoded
> Content-Length: 32
> 
* upload completely sent off: 32 out of 32 bytes
* HTTP 1.0, assume close after body
< HTTP/1.0 200 OK
< Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpYXQiOiIxNTUzOTMxNTU3Iiwic3ViIjoiU3lzdGVsYWIifQ.AcpzW6QZMLZ39ST0tXBzz7ZAWDWyzATd3nJxZsMRxdQ
< Content-Length: 0
< Content-Type: application/json
< 
* Closing connection 0
```

This token should be added as an `Authorization` header in further requests to the REST API.

### Patients CRUD

The following endpoints allow managing the patients of the system:

```
GET /seed/v1/patients
GET /seed/v1/patients/:id
POST /seed/v1/patients/patient
PUT /seed/v1/patients/patient
DELETE /seed/v1/patients/patient
```

### Allergies CRUD

The following endpoints allow managing the catalog of allergies of the system:

`TBD`

Additionally, the register of the allergies that each patient has had can be managed with:

`TBD`

