cmake_minimum_required(VERSION 3.2)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure SeedCppCore static library
include_directories(SeedCppCore)
set(SEED_CPP_CORE SeedCppCore)
file(GLOB_RECURSE SEED_CPP_CORE_SRC "*.cpp")
file(GLOB_RECURSE SEED_CPP_CORE_HDR "*.h")
add_library(${SEED_CPP_CORE} STATIC ${SEED_CPP_CORE_SRC} ${SEED_CPP_CORE_HDR})

#Configure source groups
foreach(FILE ${SEED_CPP_CORE_SRC} ${SEED_CPP_CORE_HDR}) 
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
