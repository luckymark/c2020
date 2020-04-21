cmake_minimum_required(VERSION 3.15)
project(maze)

set(CMAKE_C_STANDARD 99)
file(GLOB ALLHEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_executable(maze main.c maze.c gameEngine.c ${ALLHEADERS})