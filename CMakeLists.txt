cmake_minimum_required(VERSION 3.29)
project(snake C)

set(CMAKE_C_STANDARD 23)

add_executable(play main.c
        snake.h
        snake.c)
add_executable(generate_path generate_path.c)
add_executable(tests tests.c
        snake.h
        snake.c)
