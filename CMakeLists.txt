cmake_minimum_required(VERSION 3.2)

project(SeedCpp)

# Configure environment
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Setup up Google test
include(ConfigureGoogleTest)
configure_google_test()

# Setup 3rd party libraries through conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()	

# Setup extern repositories
include(GitCloneRepository)
git_clone_repository(URL https://github.com/systelab/cpp-test-utilities.git                DIR extern/TestUtilities               BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-db-adapter.git                    DIR extern/DbAdapter                   BRANCH v1.1.0)
git_clone_repository(URL https://github.com/systelab/cpp-sqlite-db-adapter.git             DIR extern/DbSQLiteAdapter             BRANCH v1.1.0)
git_clone_repository(URL https://github.com/systelab/cpp-json-adapter.git                  DIR extern/JSONAdapter                 BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-rapidjson-json-adapter.git        DIR extern/RapidJSONAdapter            BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-webserver-adapter.git             DIR extern/WebServerAdapter            BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-boostasio-webserver-adapter.git   DIR extern/BoostAsioWebServerAdapter   BRANCH v1.0.0)
git_clone_repository(URL https://github.com/systelab/cpp-jwt-utils.git                     DIR extern/JWTUtils                    BRANCH v1.0.0)


# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/extern/DbSQLiteAdapter/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/DbSQLiteAdapter/src/sqleet-v0.27.2)
include_directories(${CMAKE_SOURCE_DIR}/extern/RapidJSONAdapter/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/BoostAsioWebServerAdapter/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/JWTUtils/src)


# Add extern projects
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/DbAdapter/DbAdapterTestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/DbSQLiteAdapter/src/sqleet-v0.27.2)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/DbSQLiteAdapter/src/DbSQLiteAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/JSONAdapter/JSONAdapterTestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/RapidJSONAdapter/src/RapidJSONAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/BoostAsioWebServerAdapter/src/BoostAsioWebServerAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/JWTUtils/src/JWTUtils)

set_target_properties (gmock_main PROPERTIES FOLDER Extern)
set_target_properties (DbAdapterTestUtilities PROPERTIES FOLDER Extern)
set_target_properties (sqlite3 PROPERTIES FOLDER Extern)
set_target_properties (sqleet PROPERTIES FOLDER Extern)
set_target_properties (DbSQLiteAdapter PROPERTIES FOLDER Extern)
set_target_properties (JSONAdapterTestUtilities PROPERTIES FOLDER Extern)
set_target_properties (RapidJSONAdapter PROPERTIES FOLDER Extern)
set_target_properties (BoostAsioWebServerAdapter PROPERTIES FOLDER Extern)
set_target_properties (JWTUtils PROPERTIES FOLDER Extern)


# Add application projects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/SeedCppCore)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/SeedCpp)

set_target_properties (SeedCppCore PROPERTIES FOLDER Application)
set_target_properties (SeedCpp PROPERTIES FOLDER Application)


# Add test projects
add_subdirectory(${CMAKE_SOURCE_DIR}/test/SeedCppCoreTestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/SeedCppCoreUnitTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest)

set_target_properties (SeedCppCoreTestUtilities PROPERTIES FOLDER Test)
set_target_properties (SeedCppCoreUnitTest PROPERTIES FOLDER Test)
set_target_properties (DatabaseIntegrationTest PROPERTIES FOLDER Test)


# Add code coverage project
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    add_custom_command(TARGET DatabaseIntegrationTest POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/SeedCppCore/Resources/Database ${CMAKE_BINARY_DIR}/Database)

    add_custom_command(TARGET DatabaseIntegrationTest POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest/Databases ${CMAKE_BINARY_DIR}/Database)

    include(CodeCoverage)
    setup_target_for_coverage(AutomatedTestCoverage SeedCppCoreUnitTest DatabaseIntegrationTest coverage)
endif()
