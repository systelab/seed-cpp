cmake_minimum_required(VERSION 3.2)

# Find external dependencides
find_package(gtest)
find_package(TestUtilitiesInterface)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure SeedCppCoreTestUtilities static library
include_directories(SeedCppCoreTestUtilities)
set(SEED_CPP_CORE_TEST_UTILITIES SeedCppCoreTestUtilities)
file(GLOB_RECURSE SEED_CPP_CORE_TEST_UTILITIES_SRC "*.cpp")
file(GLOB_RECURSE SEED_CPP_CORE_TEST_UTILITIES_HDR "*.h")
add_library(${SEED_CPP_CORE_TEST_UTILITIES} STATIC ${SEED_CPP_CORE_TEST_UTILITIES_SRC} ${SEED_CPP_CORE_TEST_UTILITIES_HDR})
target_link_libraries(${SEED_CPP_CORE_TEST_UTILITIES} SeedCppCore GTest::gtest TestUtilitiesInterface::TestUtilitiesInterface)

#Configure source groups
foreach(FILE ${SEED_CPP_CORE_TEST_UTILITIES_SRC} ${SEED_CPP_CORE_TEST_UTILITIES_HDR}) 
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
