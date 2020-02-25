cmake_minimum_required(VERSION 3.15)
project(p12_warehouse C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(p12_warehouse goods.c goods.h main.c)
