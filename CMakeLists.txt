cmake_minimum_required(VERSION 3.30)
project(carros C)

set(CMAKE_C_STANDARD 11)

add_executable(carros
        src/main.c
        src/p1.c
        src/p2.c
        src/tree.c
        src/list.c
        src/utils.c
        src/year_list.c
        include/year_list.h
)