cmake_minimum_required(VERSION 2.6)
project(course)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_EXE src/main.cpp)
        #src/swap.cpp
        #src/nmap.cpp
        #src/hdd.cpp
        #src/computer_information.cpp
        #include/nmap.h)
        #include/computer_information.h)

add_subdirectory(lib)

add_executable(course ${SOURCE_EXE})

target_link_libraries(course ${CMAKE_DL_LIBS})