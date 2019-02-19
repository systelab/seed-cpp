# configure cpp-sql-webserver-adapter as library
set(CPP_SQL_ADAPTER DbSQLiteAdapter)
file(GLOB_RECURSE CPP_SQL_ADAPTER_SRC "${CPP_SQL_ADAPTER}/*.cpp")
file(GLOB_RECURSE CPP_SQL_ADAPTER_HDR "${CPP_SQL_ADAPTER}/*.h")
add_library(${CPP_SQL_ADAPTER} STATIC ${CPP_SQL_ADAPTER_SRC} ${CPP_SQL_ADAPTER_HDR})
target_link_libraries(${CPP_SQL_ADAPTER} -lpthread)

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

# configure cpp-webserver-interface as library
#set(CPP_WEBSERVER_INTERFACE WebServerInterface)
#file(GLOB_RECURSE CPP_WEBSERVER_INTERFACE_SRC "${CPP_WEBSERVER_INTERFACE}/*.cpp")
#file(GLOB_RECURSE CPP_WEBSERVER_INTERFACE_HDR "${CPP_WEBSERVER_INTERFACE}/*.h")
#add_library(${CPP_WEBSERVER_INTERFACE} STATIC ${CPP_WEBSERVER_INTERFACE_SRC} ${CPP_WEBSERVER_INTERFACE_HDR})

# configure SeedCppCore as library
set(CPP_SEEDCORE_INTERFACE SeedCppCore)
file(GLOB_RECURSE CPP_SEEDCORE_INTERFACE_SRC "${CPP_SEEDCORE_INTERFACE}/*.cpp")
file(GLOB_RECURSE CPP_SEEDCORE_INTERFACE_HDR "${CPP_SEEDCORE_INTERFACE}/*.h")
add_library(${CPP_SEEDCORE_INTERFACE} STATIC ${CPP_SEEDCORE_INTERFACE_SRC} ${CPP_SEEDCORE_INTERFACE_HDR})

# Add Interfaces
include_directories(DbAdapterInterface)
include_directories(WebServerInterface)
include_directories(JSONAdapterInterface)
include_directories(SeedCppCore)

file(GLOB_RECURSE SRC "SeedCpp/*.cpp" )
file(GLOB_RECURSE HDR "SeedCpp/*.h" )

add_executable(${PROJECT_NAME} ${SRC} ${HDR})

link_directories(${Boost_LIBRARY_DIRS})

target_link_libraries(${PROJECT_NAME} ${CPP_SQL_ADAPTER} ${CPP_BOOSTASIO_ADAPTER} ${CPP_RAPIDJSON_ADAPTER} ${CPP_SEEDCORE_INTERFACE})

#target_link_libraries(${DEMO} ${CPP_BOOSTASIO_ADAPTER} ${Boost_LIBRARIES} )
