enable_testing()

# Configure preprocessor definitions
add_compile_options(-DBOOST_ALL_DYN_LINK -DSQLITE_HAS_CODEC)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure test project
set(DATABASE_INTEGRATION_TEST_PROJECT DatabaseIntegrationTest)
file(GLOB_RECURSE DATABASE_INTEGRATION_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE DATABASE_INTEGRATION_TEST_PROJECT_HDR "*.h")
file(GLOB_RECURSE DATABASE_INTEGRATION_TEST_PROJECT_SQL "*.sql")
add_executable(${DATABASE_INTEGRATION_TEST_PROJECT} ${DATABASE_INTEGRATION_TEST_PROJECT_SRC} ${DATABASE_INTEGRATION_TEST_PROJECT_HDR} ${DATABASE_INTEGRATION_TEST_PROJECT_SQL})
target_link_libraries(${DATABASE_INTEGRATION_TEST_PROJECT} gmock_main SeedCppCore SeedCppCoreTestUtilities)
set_target_properties(${DATABASE_INTEGRATION_TEST_PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${DATABASE_INTEGRATION_TEST_PROJECT})

#Configure source groups
foreach(FILE ${DATABASE_INTEGRATION_TEST_PROJECT_SRC} ${DATABASE_INTEGRATION_TEST_PROJECT_HDR} ${DATABASE_INTEGRATION_TEST_PROJECT_SQL}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.sql")
       set(GROUP "Resource Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

# Register tests
add_test(NAME DatabaseIntegrationTest COMMAND ${DATABASE_INTEGRATION_TEST_PROJECT})

# Copy extern dynamic libraries to build dir
add_custom_command(TARGET ${DATABASE_INTEGRATION_TEST_PROJECT} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_BINARY_DIR}/lib/extern $<TARGET_FILE_DIR:${DATABASE_INTEGRATION_TEST_PROJECT}>)

# Copy needed database resources to target dir
add_custom_command(TARGET ${DATABASE_INTEGRATION_TEST_PROJECT} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src/SeedCppCore/Resources/Database $<TARGET_FILE_DIR:${DATABASE_INTEGRATION_TEST_PROJECT}>/Database)

add_custom_command(TARGET ${DATABASE_INTEGRATION_TEST_PROJECT} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest/Databases $<TARGET_FILE_DIR:${DATABASE_INTEGRATION_TEST_PROJECT}>/Database)


# Copy needed database resources to target dir for code coverage
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    add_custom_command(TARGET DatabaseIntegrationTest POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/SeedCppCore/Resources/Database ${CMAKE_BINARY_DIR}/Database)

    add_custom_command(TARGET DatabaseIntegrationTest POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest/Databases ${CMAKE_BINARY_DIR}/Database)
endif()
