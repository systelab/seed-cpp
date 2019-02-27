cmake_minimum_required(VERSION 3.2)

project(seed-cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Conan
include(cmake/conan.cmake)
conan_cmake_run(REQUIRES boost/1.67.0@conan/stable
                         OpenSSL/1.0.2n@conan/stable
                         sqlite3/3.27.2@bincrafters/stable
                         rapidjson/1.1.0@bincrafters/stable
                BASIC_SETUP
                BUILD missing)

# Add src
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
