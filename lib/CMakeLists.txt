cmake_minimum_required(VERSION 2.6)
project(lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(swap SHARED ../src/swap.cpp)

add_library(hdd SHARED ../src/hdd.cpp)

add_library(nmap SHARED ../src/nmap.cpp ../include/nmap.h)

add_library(info SHARED ../src/computer_information.cpp
        ../include/computer_information.h)