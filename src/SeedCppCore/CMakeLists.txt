cmake_minimum_required(VERSION 3.2)

# Find external dependencies
find_package(Boost)
find_package(DbAdapterInterface)
find_package(DbSQLiteAdapter)
find_package(RapidJSONAdapter)
find_package(rapidjson)
find_package(BoostAsioWebServerAdapter)
find_package(JWTUtils)
find_package(RESTAPICore)
find_package(JSONSettings)
find_package(JSONAdapterInterface)
find_package(TimeAdapter)
find_package(WebServerAdapterInterface)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure SeedCppCore static library
set(SEED_CPP_CORE SeedCppCore)
file(GLOB_RECURSE SEED_CPP_CORE_SRC "*.cpp")
file(GLOB_RECURSE SEED_CPP_CORE_HDR "*.h")
add_library(${SEED_CPP_CORE} STATIC ${SEED_CPP_CORE_SRC} ${SEED_CPP_CORE_HDR})
target_link_libraries(${SEED_CPP_CORE}
                      Boost::boost
                      DbAdapterInterface::DbAdapterInterface
                      DbSQLiteAdapter::DbSQLiteAdapter
                      RapidJSONAdapter::RapidJSONAdapter
                      rapidjson::rapidjson					  
                      BoostAsioWebServerAdapter::BoostAsioWebServerAdapter
                      JWTUtils::JWTUtils
                      RESTAPICore::RESTAPICore
                      JSONSettings::JSONSettings
                      JSONAdapterInterface::JSONAdapterInterface
                      TimeAdapter::TimeAdapter					  
                      WebServerAdapterInterface::WebServerAdapterInterface)

#Configure source groups
foreach(FILE ${SEED_CPP_CORE_SRC} ${SEED_CPP_CORE_HDR}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()
