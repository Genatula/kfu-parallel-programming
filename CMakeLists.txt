cmake_minimum_required(VERSION 3.23)
project(kfu_parallel_programming)

set(CMAKE_CXX_STANDARD 14)

include(FindOpenMP)

if (OpenMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

add_executable(kfu_parallel_programming openmp/01.cpp)
