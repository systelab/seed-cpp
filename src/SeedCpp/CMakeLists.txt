cmake_minimum_required(VERSION 3.2)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure SeedCpp executable
set(SEED_CPP_PROJECT SeedCpp)
file(GLOB_RECURSE SEED_CPP_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE SEED_CPP_PROJECT_HDR "*.h")
add_executable(${SEED_CPP_PROJECT} ${SEED_CPP_PROJECT_SRC} ${SEED_CPP_PROJECT_HDR})
target_link_libraries(${SEED_CPP_PROJECT} SeedCppCore)
set_target_properties(${SEED_CPP_PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${SEED_CPP_PROJECT})

#Configure source groups
foreach(FILE ${SEED_CPP_PROJECT_SRC} ${SEED_CPP_PROJECT_HDR}) 
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

# Copy resources to build dir
add_custom_command(TARGET ${SEED_CPP_PROJECT} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/src/SeedCppCore/Resources $<TARGET_FILE_DIR:${SEED_CPP_PROJECT}>)

