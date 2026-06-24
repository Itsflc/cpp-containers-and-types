cmake_minimum_required(VERSION 3.20)
project(jaggeda)

set(CMAKE_CXX_STANDARD 23)

add_library(jaggeda jaggeda.cpp jaggeda.hpp)

target_include_directories(arrayd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
