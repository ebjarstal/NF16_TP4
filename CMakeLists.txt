cmake_minimum_required(VERSION 3.24)
project(NF16_TP4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(NF16_TP4
        main.c
        tp4.c
        tp4.h)
