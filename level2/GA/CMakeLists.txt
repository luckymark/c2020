cmake_minimum_required(VERSION 3.15)
project(GA C)

set(CMAKE_C_STANDARD 11)

add_executable(GA main.c maze.c GA.c)
target_link_libraries(GA m)