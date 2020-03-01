# cmake_minimum_required(VERSION <specify CMake version here>)
project(p09_maze)

set(CMAKE_CXX_STANDARD 14)

IF(WIN32)
    add_executable(p09_maze main_for_windows.c maze.c)
ELSE()
    add_executable(p09_maze main_for_unix-like.c maze.c)
ENDIF()
