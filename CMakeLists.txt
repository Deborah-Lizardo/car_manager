cmake_minimum_required(VERSION 3.10)
project(car_manager)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(p1
        src/p1.c
        src/list.c
        src/utils.c
)

add_executable(p2
        src/p2.c
        src/utils.c
        src/year_list.c
        src/tree/bst_mileage.c
        src/tree/bst_price.c
)