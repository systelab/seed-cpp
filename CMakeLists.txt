cmake_minimum_required(VERSION 3.2)

project(SeedCpp)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "-no-pie")
endif (UNIX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

# Add application projects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/SeedCppCore)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/SeedCpp)

set_target_properties(SeedCppCore PROPERTIES FOLDER Application)
set_target_properties(SeedCpp PROPERTIES FOLDER Application)


# Add test projects
add_subdirectory(${CMAKE_SOURCE_DIR}/test/SeedCppCoreTestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/SeedCppCoreUnitTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest)

set_target_properties(SeedCppCoreTestUtilities PROPERTIES FOLDER Test)
set_target_properties(SeedCppCoreUnitTest PROPERTIES FOLDER Test)
set_target_properties(DatabaseIntegrationTest PROPERTIES FOLDER Test)


# Add code coverage project
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    setup_target_for_coverage(AutomatedTestCoverage SeedCppCoreUnitTest DatabaseIntegrationTest coverage)
endif()
