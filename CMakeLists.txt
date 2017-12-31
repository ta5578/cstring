cmake_minimum_required(VERSION 3.2)
project(cstring)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")
message("Compiling with: ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS}")

# Generate the unit tests
add_custom_target(TestCString COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test/make-tests.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

# Gather source files
include_directories(test)
include_directories(.)

file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "cstring.h" "test/*.h")
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "cstring.c" "test/*.c")

# We need to manually specify the generated test case to link with
add_executable(cstring_tests ${HEADERS} ${SOURCES})
add_dependencies(cstring_tests TestCString)
