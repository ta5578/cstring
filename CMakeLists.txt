cmake_minimum_required (VERSION 3.2)
project(cstring)

# Set additional compiler flags and link directories
if(CMAKE_C_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /WX")
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
else()
    message(FATAL_ERROR "${CMAKE_C_COMPILER_ID} is not supported!")
endif()

# Set up the output directory for builds
set(CSTRING_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Set the generic runtime output directory for single generators like "make"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CSTRING_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CSTRING_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CSTRING_OUTPUT_DIR})

# Set the generic runtime output directory for multi generators like "msvc"
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CSTRING_OUTPUT_DIR}/${OUTPUTCONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CSTRING_OUTPUT_DIR}/${OUTPUTCONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CSTRING_OUTPUT_DIR}/${OUTPUTCONFIG})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

message("Current output directory: ${CSTRING_OUTPUT_DIR}")

# Set the build type (this only affects single output generators)
if(CMAKE_GENERATOR MATCHES "Unix Makefiles")
    if(NOT CMAKE_BUILD_TYPE)
        message(WARNING "CMAKE_BUILD_TYPE was not specified. The build will default to a 'release' build type.")
        set(CMAKE_BUILD_TYPE "release")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
    else()
        message(STATUS "CMAKE_BUILD_TYPE set to ${CMAKE_BUILD_TYPE}")
        if(CMAKE_BUILD_TYPE MATCHES "debug")
            set(CMAKE_BUILD_TYPE "debug")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
        elseif(CMAKE_BUILD_TYPE MATCHES "release")
            set(CMAKE_BUILD_TYPE "release")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
        else()
            message(FATAL_ERROR "${CMAKE_BUILD_TYPE} is not supported for this generator! The only accepted values are 'debug' or 'release'!")
        endif()
    endif()
endif()

message("Compiling with: ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS}")

# Add additional include directories
include_directories(.)

# Generate the unit tests
if (WIN32)
    message(FATAL_ERROR "Test builds not yet supported on Windows! You can still use the library sources though!")
elseif (APPLE)
    message(FATAL_ERROR "Test builds not yet supported on MacOS! You can still use the library sources though!")
elseif (UNIX AND NOT APPLE)
    add_custom_target(TestCString COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/make-tests.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
else ()
    message(FATAL_ERROR "Unsupported operating system!")
endif()

# Build the tests
add_executable(cstring "cstring.h" "cstring.c" "test/CuTest.h" "test/CuTest.c" "test/tests.c" "test/alltests.c")
add_dependencies(cstring TestCString)
