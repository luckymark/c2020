cmake_minimum_required(VERSION 3.15)
project(GA_Maze)

set(CMAKE_CXX_STANDARD 14)

add_executable(GA_Maze main.cpp cmake-build-debug/GA.h GA.h GA.cpp)