cmake_minimum_required(VERSION 3.15)
project(Neural_Networks C)

set(CMAKE_C_STANDARD 99)

add_executable(Neural_Networks main.c Neural_Networks_Functions_V2.c Matrix.c)