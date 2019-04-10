cmake_minimum_required(VERSION 3.2)

project(SeedCpp)

# Configure environment
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup up Google test
include(ConfigureGoogleTest)
configure_google_test()

# Setup 3rd party libraries through conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()	

# Setup extern repositories
include(GitCloneRepository)
git_clone_repository(URL https://github.com/systelab/cpp-test-utilities.git                DIR extern/TestUtilities               BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-db-adapter.git                    DIR extern/DbAdapter                   BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-sqlite-db-adapter.git             DIR extern/DbSQLiteAdapter             BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-json-adapter.git                  DIR extern/JSONAdapter                 BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-rapidjson-json-adapter.git        DIR extern/RapidJSONAdapter            BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-webserver-adapter.git             DIR extern/WebServerAdapter            BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-boostasio-webserver-adapter.git   DIR extern/BoostAsioWebServerAdapter   BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-jwt-utils.git                     DIR extern/JWTUtils                    BRANCH v1.0.0)

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/extern/DbSQLiteAdapter/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/RapidJSONAdapter/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/BoostAsioWebServerAdapter/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/JWTUtils/src)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/DbSQLiteAdapter/src/DbSQLiteAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/RapidJSONAdapter/src/RapidJSONAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/BoostAsioWebServerAdapter/src/BoostAsioWebServerAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/JWTUtils/src/JWTUtils)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/SeedCppCore)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/SeedCpp)
