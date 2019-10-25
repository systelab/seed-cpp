cmake_minimum_required(VERSION 3.2)

# Enable testing module
enable_testing()

# Find external dependencides
find_package(gtest)
find_package(DbAdapterTestUtilities)
find_package(JSONAdapterTestUtilities)
find_package(JWTUtilsTestUtilities)

# Configure preprocessor definitions
add_compile_options(-DBOOST_ALL_DYN_LINK -DSQLITE_HAS_CODEC)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure test project
set(SEED_CPP_CORE_UNIT_TEST_PROJECT SeedCppCoreUnitTest)
file(GLOB_RECURSE SEED_CPP_CORE_UNIT_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE SEED_CPP_CORE_UNIT_TEST_PROJECT_HDR "*.h")
add_executable(${SEED_CPP_CORE_UNIT_TEST_PROJECT} ${SEED_CPP_CORE_UNIT_TEST_PROJECT_SRC} ${SEED_CPP_CORE_UNIT_TEST_PROJECT_HDR})
target_link_libraries(${SEED_CPP_CORE_UNIT_TEST_PROJECT} SeedCppCore SeedCppCoreTestUtilities
					  gtest::gtest
					  DbAdapterTestUtilities::DbAdapterTestUtilities
					  JSONAdapterTestUtilities::JSONAdapterTestUtilities
					  JWTUtilsTestUtilities::JWTUtilsTestUtilities)
set_target_properties(${SEED_CPP_CORE_UNIT_TEST_PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${SEED_CPP_CORE_UNIT_TEST_PROJECT})

#Configure source groups
foreach(FILE ${SEED_CPP_CORE_UNIT_TEST_PROJECT_SRC} ${SEED_CPP_CORE_UNIT_TEST_PROJECT_HDR}) 
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

# Register tests
add_test(NAME SeedCppCoreUnitTest COMMAND ${SEED_CPP_CORE_UNIT_TEST_PROJECT})

