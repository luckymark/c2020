# cmake_minimum_required(VERSION <specify CMake version here>)
project(p10_pushBoxes C)

set(CMAKE_C_STANDARD 11)

IF(WIN32)
    add_executable(p10_pushBoxes main_for_windows.c boxes.c)
ELSE()
    add_executable(p10_pushBoxes main_for_unix-like.c boxes.c)
ENDIF()
