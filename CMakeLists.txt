cmake_minimum_required(VERSION 3.29)
project(2024-os-hw1 C)

set(CMAKE_C_STANDARD 11)

add_executable(main
        src/main.c
        src/instruction_parser.c
        src/tools/stack.c
        src/tools/string_tools.c
        src/argument_parser.c
)

