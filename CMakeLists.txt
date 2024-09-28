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

add_executable(new_SiSH
        src_new/main.c
        src_new/SiSH.c
        src_new/SiSH.h
        src_new/tools/path_finder.c
        src_new/tools/path_finder_test.c

)

add_executable(bin_path_finder_test
        src_new/tools/path_finder.c
        src_new/tools/path_finder_test.c
)