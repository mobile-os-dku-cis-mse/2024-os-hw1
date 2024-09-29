cmake_minimum_required(VERSION 3.22)
project(2024-os-hw1 C)

set(CMAKE_C_STANDARD 11)

add_executable(new_SiSH
        src/main.c
        src/shell.c
        src/tools/path_finder.c
        src/argument_parser.c
        src/instruction_parser.c
        src/tools/stack.c
        src/shell.h
        src/tools/builtin_commands.c
        src/tools/builtin_commands.h
)
