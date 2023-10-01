cmake_minimum_required(VERSION 3.27)
project(sippy CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(DEFAULT_CXX_FLAGS -pedantic -Wall -Werror)

find_package(Boost REQUIRED COMPONENTS system)
find_package(GTest REQUIRED)

enable_testing()
add_subdirectory(tests)
