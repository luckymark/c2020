cmake_minimum_required(VERSION 3.15)
project(PI C)

set(CMAKE_C_STANDARD 11)

add_executable(PI main.c BigFloat.c BigFloat.h)