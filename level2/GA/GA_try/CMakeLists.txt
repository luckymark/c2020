cmake_minimum_required(VERSION 3.15)
project(GA_try C)

set(CMAKE_C_STANDARD 99)

add_executable(GA_try main.c GA_.c GA_.h)