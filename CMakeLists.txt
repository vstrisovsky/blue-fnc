cmake_minimum_required(VERSION 3.1)

project("Functions")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include/catch)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -g -Wall")

include(ExternalProject)

add_executable(examples examples/examples.cpp)

set_property(TARGET examples PROPERTY CXX_STANDARD 11)

# ExternalProject_Add(CATCH
#  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external
#   GIT_REPOSITORY https://github.com/dreal-deps/Catch.git
#   CONFIGURE_COMMAND echo "nothing to configure"
#   BUILD_COMMAND echo "nothing to build"
#   BUILD_IN_SOURCE 1
#   INSTALL_COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/include/catch && cp -v single_include/catch.hpp ${CMAKE_CURRENT_BINARY_DIR}/include/catch/)

# add_custom_target(update_catch
#   COMMAND git fetch --all && git reset --hard origin/master && mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/include/catch && cp -v single_include/catch.hpp ${CMAKE_CURRENT_BINARY_DIR}/include/catch/
#   WORKING_DIRECTORY ${DREAL_BINARY_DIR}/external/src/CATCH)

enable_testing()

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)

foreach(testSrc ${TEST_SRCS})
        get_filename_component(unitTest ${testSrc} NAME_WE)
        set(testName ${unitTest})
        add_executable(${testName} ${testSrc})
        set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY tests)
        add_test(NAME ${testName} COMMAND ${CMAKE_CURRENT_BINARY_DIR}/tests/${testName})
        set_property(TARGET ${testName} PROPERTY CXX_STANDARD 11)
endforeach(testSrc)
