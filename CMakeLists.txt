cmake_minimum_required(VERSION 3.20)
project(lang C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(lang
    src/main.c
    src/obj.c
    src/env.c
    src/eval.c
    src/builtin.c
)

target_include_directories(lang PRIVATE include)
target_compile_options(lang PRIVATE -Wall -Wextra)
