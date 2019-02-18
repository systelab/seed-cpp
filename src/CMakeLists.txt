# configure cpp-sql-webserver-adapter as library
set(CPP_SQL_ADAPTER DbSQLiteAdapter)
file(GLOB_RECURSE CPP_SQL_ADAPTER_SRC "${CPP_SQL_ADAPTER}/*.cpp")
file(GLOB_RECURSE CPP_SQL_ADAPTER_HDR "${CPP_SQL_ADAPTER}/*.h")
add_library(${CPP_SQL_ADAPTER} STATIC ${CPP_SQL_ADAPTER_SRC} ${CPP_SQL_ADAPTER_HDR})

# configure cpp-webserver-interface as library
#set(CPP_WEBSERVER_INTERFACE WebServerInterface)
#file(GLOB_RECURSE CPP_WEBSERVER_INTERFACE_SRC "${CPP_WEBSERVER_INTERFACE}/*.cpp")
#file(GLOB_RECURSE CPP_WEBSERVER_INTERFACE_HDR "${CPP_WEBSERVER_INTERFACE}/*.h")
#add_library(${CPP_WEBSERVER_INTERFACE} STATIC ${CPP_WEBSERVER_INTERFACE_SRC} ${CPP_WEBSERVER_INTERFACE_HDR})

# configure cpp-boostasio-webserver-adapter as library
set(CPP_BOOSTASIO_ADAPTER WebServer)
file(GLOB_RECURSE CPP_BOOSTASIO_ADAPTER_SRC "${CPP_BOOSTASIO_ADAPTER}/*.cpp")
file(GLOB_RECURSE CPP_BOOSTASIO_ADAPTER_HDR "${CPP_BOOSTASIO_ADAPTER}/*.h")
add_library(${CPP_BOOSTASIO_ADAPTER} STATIC ${CPP_BOOSTASIO_ADAPTER_SRC} ${CPP_BOOSTASIO_ADAPTER_HDR})

# configure cpp-json-webserver-adapter as library
set(CPP_RAPIDJSON_ADAPTER RapidJSONAdapter)
file(GLOB_RECURSE CPP_RAPIDJSON_SRC "${CPP_RAPIDJSON_ADAPTER}/*.cpp")
file(GLOB_RECURSE CPP_RAPIDJSON_HDR "${CPP_RAPIDJSON_ADAPTER}/*.h")
add_library(${CPP_RAPIDJSON_ADAPTER} STATIC ${CPP_RAPIDJSON_SRC} ${CPP_RAPIDJSON_SRC})

# Add Interfaces
include_directories(DbAdapterInterface)
include_directories(WebServerInterface)
include_directories(JSONAdapterInterface)

file(GLOB_RECURSE SRC "SeedCpp/*.cpp" "SeedCppCore/*.cpp" )
file(GLOB_RECURSE HDR "SeedCpp/*.h" "SeedCppCore/*.cpp" )

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

link_directories(${Boost_LIBRARY_DIRS})

#target_link_libraries(${DEMO} ${CPP_BOOSTASIO_ADAPTER} ${Boost_LIBRARIES} )
