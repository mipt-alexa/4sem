
#
#find_package(Boost REQUIRED COMPONENTS locale)
#
#include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})
#add_definitions(${Boost_DEFINITIONS})
#add_executable(locale_target hw5/2.cpp)
#target_include_directories(locale_target PUBLIC ${Boost_INCLUDE_DIRS})
#target_link_libraries(locale_target ${Boost_LIBRARIES})
#



cmake_minimum_required(VERSION 3.17)
project(cpp_4sem)


set(SFML_DIR C:/SFML-2.5.1)
set(SFML_ROOT ${SFML_DIR})
set(CMAKE_MODULE_PATH "${SFML_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML-2.5.1/include)

add_executable(game hw11/game.cpp)
target_link_libraries (game sfml-graphics sfml-window sfml-system)

add_executable(SFMLTest main.cpp)
