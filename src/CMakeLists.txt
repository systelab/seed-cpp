file(GLOB_RECURSE SRC "*.cpp" )
file(GLOB_RECURSE HDR "*.h" )

add_executable(${PROJECT_NAME} ${SRC} ${HDR})
