cmake_minimum_required(VERSION 2.6)
project(course)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_EXE src/main.cpp)

add_subdirectory(lib)

add_executable(course ${SOURCE_EXE})

target_link_libraries(course ${CMAKE_DL_LIBS})