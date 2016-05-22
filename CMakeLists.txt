cmake_minimum_required(VERSION 3.5)
project(course)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp hdd.cpp nmap.cpp swap.cpp)

add_executable(course swap.cpp filesystem.cpp)