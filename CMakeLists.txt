cmake_minimum_required(VERSION 3.2)

macro(boost_setup)
    set(BOOST_LIB_DIR "${CMAKE_SOURCE_DIR}/include/boost")
    set(BOOST_COMPONENTS "system" "thread")

    set(BOOST_ROOT "${CMAKE_BINARY_DIR}/boost_build")
    set(BOOST_INCLUDEDIR "${BOOST_ROOT}/include")
    set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")

    set(Boost_USE_STATIC_LIBS ON)       # only find static libs
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    set(Boost_NO_BOOST_CMAKE ON)
    set(Boost_DEBUG OFF)

    find_package(Boost 1.67.0 COMPONENTS ${BOOST_COMPONENTS})
    if(Boost_FOUND)
        # Include 'boost' directory
        include_directories(${Boost_INCLUDE_DIR})
    else()
        # Launch boost compiling script
        set(boost_compile_script "${CMAKE_SOURCE_DIR}/include/compile_boost.sh")
        message(STATUS "Compiling Boost using compile_boost.sh from ${CMAKE_SOURCE_DIR}/include")
        execute_process(COMMAND ${boost_compile_script} WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/include" RESULT_VARIABLE result)
        if(result)
            message(FATAL_ERROR "\nCompiling Boost: ${result}\n")
        endif()

        # re-find package to set the Boost_* variables
        find_package(Boost 1.67.0 COMPONENTS ${BOOST_COMPONENTS})
        if(NOT Boost_FOUND)
            message(FATAL_ERROR "\nSomething went wrong, couldn't find boost after compile it.\n")
        else()
            include_directories(${Boost_INCLUDE_DIR})
        endif()
    endif()
endmacro()

project(seed-cpp)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS -pthread)

find_package (Threads)

# Call boost configuration macro
boost_setup()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
