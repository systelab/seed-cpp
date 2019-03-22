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

Prerequisites:
  - [Git](https://git-scm.com/)
  - [Conan](https://conan.io/)
  - [CMake](https://cmake.org/)
  - [Visual Studio](https://visualstudio.microsoft.com/) (only on Windows)
  - [GCC](https://gcc.gnu.org/) (only on Linux)

Build the application with the following steps:
  1. Clone this repository in a local drive
  2. Make a build directory (i.e. `build/`)
  3. Install `conan` dependencies in the build directory
  4. Run `cmake` in the build directory to configure build targets
  5. Use `Visual Studio` (on Windows) or `make` (on Linux) to build the library

### Windows
``` bash
> git clone https://github.com/systelab/seed-cpp
> md build && cd build
> conan install .. -s arch=x86
> cmake ..
> devenv.exe SeedCpp.sln
```

### Linux
``` bash
> git clone https://github.com/systelab/seed-cpp
> mkdir build && cd build
> conan install ..
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
```

## Usage

To run the application, just launch the `SeedCpp` executable. It will set up an HTTP server on port `8080` which implements the patient management REST API.

### Login

Before any request, users must authenticate to the REST API by using the login endpoint (with username `Systelab` and password `Systelab`):

```
POST /seed/v1/users/login HTTP/1.1
Host: 127.0.0.1:8080
Content-Type: application/x-www-form-urlencoded
login=Systelab
password=Systelab
```

The response for this request should contain an authentication token (based on [JWT](https://jwt.io/)) in the `Authorization` header:

```
TBD
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

