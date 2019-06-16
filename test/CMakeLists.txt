enable_testing()

# Configure preprocessor definitions
add_compile_options(-DBOOST_ALL_DYN_LINK -DSQLITE_HAS_CODEC)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Additional target for code coverage analysis
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    add_custom_command(TARGET DatabaseIntegrationTest POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/src/SeedCppCore/Resources/Database ${CMAKE_BINARY_DIR}/Database)

    add_custom_command(TARGET DatabaseIntegrationTest POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/test/DatabaseIntegrationTest/Databases ${CMAKE_BINARY_DIR}/Database)

    include(CodeCoverage)
    setup_target_for_coverage(AutomatedTestCoverage SeedCppCoreUnitTest DatabaseIntegrationTest coverage)
endif()
