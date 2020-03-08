cmake_minimum_required(VERSION 3.15)
project(p12_warehouse C)

set(CMAKE_C_STANDARD 99)

add_executable(p12_warehouse warehouse.h warehouse1.c warehouse2.c)