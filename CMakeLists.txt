cmake_minimum_required(VERSION 3.17)
project(cpp_4sem)


set(Boost_USE_STATIC_LIBS        ON)

find_package(Boost REQUIRED COMPONENTS locale)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(${Boost_DEFINITIONS})
add_executable(locale_target hw5/2.cpp)
target_include_directories(locale_target PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(locale_target ${Boost_LIBRARIES})


set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_4sem 6/sem.cpp)

