cmake_minimum_required(VERSION 3.10)
project(carros C)

set(CMAKE_C_STANDARD 11)

add_executable(car_inventory
        src/main.c
        #src/p1.c
        #src/p2.c
        src/mil_tree.c
        #src/list.c
        src/utils.c
        src/year_list.c
        include/year_list.h

)
