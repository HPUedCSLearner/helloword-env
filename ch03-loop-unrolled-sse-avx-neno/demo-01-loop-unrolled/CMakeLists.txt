cmake_minimum_required(VERSION 3.5.0)
project(loop-unrolled VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(loop-unrolled main.cpp)
# target_compile_options(loop-unrolled PRIVATE "-O0")

message(STATUS "==CMAKE_CXX_FALGS: ${CMAKE_CXX_FLAGS}")