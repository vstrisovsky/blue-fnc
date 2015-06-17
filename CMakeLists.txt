cmake_minimum_required(VERSION 2.8)

project("Functions")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(Functions Functions.cpp)
