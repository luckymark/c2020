cmake_minimum_required(VERSION 3.15)
project(boxes C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(boxes
        boxes.c
        boxes.h
        main.c)
