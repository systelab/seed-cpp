enable_testing()

# Configure preprocessor definitions
add_compile_options(-DBOOST_ALL_DYN_LINK -DSQLITE_HAS_CODEC)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure test project
set(DATABASE_INTEGRATION_TEST_PROJECT DatabaseIntegrationTest)
file(GLOB_RECURSE DATABASE_INTEGRATION_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE DATABASE_INTEGRATION_TEST_PROJECT_HDR "*.h")
add_executable(${DATABASE_INTEGRATION_TEST_PROJECT} ${DATABASE_INTEGRATION_TEST_PROJECT_SRC} ${DATABASE_INTEGRATION_TEST_PROJECT_HDR})
target_link_libraries(${DATABASE_INTEGRATION_TEST_PROJECT} gmock_main SeedCppCore SeedCppCoreTestUtilities DbSQLiteAdapter sqleet sqlite3 ${CONAN_LIBS})

#Configure source groups
foreach(FILE ${DATABASE_INTEGRATION_TEST_PROJECT_SRC} ${DATABASE_INTEGRATION_TEST_PROJECT_HDR}) 
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
add_test(NAME DatabaseIntegrationTest COMMAND ${DATABASE_INTEGRATION_TEST_PROJECT})

# Copy needed database resources to target dir
add_custom_command(TARGET ${DATABASE_INTEGRATION_TEST_PROJECT} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src/SeedCppCore/Resources/Database $<TARGET_FILE_DIR:${DATABASE_INTEGRATION_TEST_PROJECT}>/Database)

add_custom_command(TARGET ${DATABASE_INTEGRATION_TEST_PROJECT} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest/Databases $<TARGET_FILE_DIR:${DATABASE_INTEGRATION_TEST_PROJECT}>/Database)

# Additional target for code coverage analysis
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
	include(CodeCoverage)
	setup_target_for_coverage(DatabaseIntegrationTestCoverage DatabaseIntegrationTest coverage)

	add_custom_command(TARGET DatabaseIntegrationTestCoverage POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_directory
					   ${CMAKE_SOURCE_DIR}/src/SeedCppCore/Resources/Database $<TARGET_FILE_DIR:DatabaseIntegrationTestCoverage>/Database)

	add_custom_command(TARGET DatabaseIntegrationTestCoverage POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_directory
					   ${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest/Databases $<TARGET_FILE_DIR:DatabaseIntegrationTestCoverage>/Database)
endif()
