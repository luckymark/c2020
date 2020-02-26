cmake_minimum_required(VERSION 3.15)
project(p07_encrypt_decrypt)

set(CMAKE_CXX_STANDARD 14)

add_executable(p07_encrypt_decrypt main.c encrypt_decrypt.c encrypt_decrypt.h)