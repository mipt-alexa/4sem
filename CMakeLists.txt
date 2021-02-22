cmake_minimum_required(VERSION 3.17)
project(cpp_4sem)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost)
include_directories (${Boost_INCLUDE_DIRS})


set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_4sem hw3/task2.cpp)