# configure cpp-sql-webserver-adapter as library
include_directories(DbAdapterInterface)
set(CPP_SQL_ADAPTER DbSQLiteAdapter)
file(GLOB_RECURSE CPP_SQL_ADAPTER_SRC "${CPP_SQL_ADAPTER}/*.cpp")
file(GLOB_RECURSE CPP_SQL_ADAPTER_HDR "${CPP_SQL_ADAPTER}/*.h")
add_library(${CPP_SQL_ADAPTER} STATIC ${CPP_SQL_ADAPTER_SRC} ${CPP_SQL_ADAPTER_HDR})

# configure cpp-webserver_interface as library
set(CPP_WEBSERVER_INTERFACE WebServerInterface)
file(GLOB_RECURSE CPP_WEBSERVER_INTERFACE_SRC "${CPP_WEBSERVER_INTERFACE}/*.cpp")
file(GLOB_RECURSE CPP_WEBSERVER_INTERFACE_HDR "${CPP_WEBSERVER_INTERFACE}/*.h")
add_library(${CPP_WEBSERVER_INTERFACE} STATIC ${CPP_WEBSERVER_INTERFACE_SRC} ${CPP_WEBSERVER_INTERFACE_HDR})

# configure cpp-boostasio-webserver-adapter as library
include_directories(WebServerInterface)
set(CPP_BOOSTASIO_ADAPTER WebServer)
file(GLOB_RECURSE CPP_BOOSTASIO_ADAPTER_SRC "${CPP_BOOSTASIO_ADAPTER}/*.cpp")
file(GLOB_RECURSE CPP_BOOSTASIO_ADAPTER_HDR "${CPP_BOOSTASIO_ADAPTER}/*.h")
add_library(${CPP_BOOSTASIO_ADAPTER} STATIC ${CPP_BOOSTASIO_ADAPTER_SRC} ${CPP_BOOSTASIO_ADAPTER_HDR})
target_link_libraries(${CPP_BOOSTASIO_ADAPTER} ${CPP_WEBSERVER_INTERFACE} ${CONAN_LIBS})

# Copy json schemas to build dir
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SeedCppCore/Resources DESTINATION ${CMAKE_BINARY_DIR})

# configure cpp-json-webserver-adapter as library
include_directories(JSONAdapterInterface)
set(CPP_RAPIDJSON_ADAPTER RapidJSONAdapter)
file(GLOB_RECURSE CPP_RAPIDJSON_SRC "${CPP_RAPIDJSON_ADAPTER}/*.cpp")
file(GLOB_RECURSE CPP_RAPIDJSON_HDR "${CPP_RAPIDJSON_ADAPTER}/*.h")
add_library(${CPP_RAPIDJSON_ADAPTER} STATIC ${CPP_RAPIDJSON_SRC} ${CPP_RAPIDJSON_SRC})

# configure SeedCppCore as library
include_directories(SeedCppCore)
set(CPP_SEEDCORE SeedCppCore)
file(GLOB_RECURSE CPP_SEEDCORE_SRC "${CPP_SEEDCORE}/*.cpp")
file(GLOB_RECURSE CPP_SEEDCORE_HDR "${CPP_SEEDCORE}/*.h")
add_library(${CPP_SEEDCORE} STATIC ${CPP_SEEDCORE_SRC} ${CPP_SEEDCORE_HDR})
target_link_libraries(${CPP_SEEDCORE} ${CONAN_LIBS})


file(GLOB_RECURSE SRC "SeedCpp/*.cpp" )
file(GLOB_RECURSE HDR "SeedCpp/*.h" )

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries(${PROJECT_NAME} ${CPP_SQL_ADAPTER} ${CPP_WEBSERVER_INTERFACE} ${CPP_BOOSTASIO_ADAPTER} ${CPP_RAPIDJSON_ADAPTER} ${CPP_SEEDCORE})
