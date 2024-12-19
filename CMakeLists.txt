cmake_minimum_required(VERSION 3.29)
project(snake C)

set(CMAKE_C_STANDARD 23)

add_executable(snake main.c)
add_executable(generate_path path.c)
