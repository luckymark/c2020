cmake_minimum_required(VERSION 3.15)
project(SkipList C)

set(CMAKE_C_STANDARD 11)

add_executable(SkipList main.c SkipList.c SkipList.h)