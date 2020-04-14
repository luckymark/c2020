cmake_minimum_required(VERSION 3.15)
project(warehouse C)

set(CMAKE_C_STANDARD 99)

add_executable(warehouse main.c getch.h)