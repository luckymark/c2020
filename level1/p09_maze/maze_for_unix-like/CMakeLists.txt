# cmake_minimum_required(VERSION <specify CMake version here>)
project(p09_maze)

set(CMAKE_CXX_STANDARD 14)

add_executable(p09_maze main.c maze.c maze.h)
