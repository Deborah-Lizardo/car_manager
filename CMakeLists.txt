cmake_minimum_required(VERSION 3.30)
project(carros C)

set(CMAKE_C_STANDARD 11)

add_executable(carros
        main.c
        p1.c
        p2.c
        arvore.c
        lista.c
        utils.c
        lista_ano.c
        lista_ano.h
)