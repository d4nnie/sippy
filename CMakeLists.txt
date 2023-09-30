cmake_minimum_required(VERSION 3.27)
project(sipphony CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DEFAULT_CXX_FLAGS -pedantic -Wall -Werror)

find_package(GTest REQUIRED)

enable_testing()
add_subdirectory(tests)
