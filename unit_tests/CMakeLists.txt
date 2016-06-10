cmake_minimum_required(VERSION 2.6)
project(unit_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(../src ../include)

set(SOURCE_FILES
        src/nmap_test.cpp
        src/computer_information_test.cpp
        src/swap_test.cpp
        src/hdd_test.cpp
        )

add_executable(unit_tests ${SOURCE_FILES})
target_link_libraries(unit_tests gtest gtest_main)