# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/hochacha/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/hochacha/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hochacha/repos/2024-os-hw1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hochacha/repos/2024-os-hw1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.c.o: /home/hochacha/repos/2024-os-hw1/src/main.c
CMakeFiles/main.dir/src/main.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/main.c.o -MF CMakeFiles/main.dir/src/main.c.o.d -o CMakeFiles/main.dir/src/main.c.o -c /home/hochacha/repos/2024-os-hw1/src/main.c

CMakeFiles/main.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/main.c > CMakeFiles/main.dir/src/main.c.i

CMakeFiles/main.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/main.c -o CMakeFiles/main.dir/src/main.c.s

CMakeFiles/main.dir/src/instruction_parser.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/instruction_parser.c.o: /home/hochacha/repos/2024-os-hw1/src/instruction_parser.c
CMakeFiles/main.dir/src/instruction_parser.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/src/instruction_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/instruction_parser.c.o -MF CMakeFiles/main.dir/src/instruction_parser.c.o.d -o CMakeFiles/main.dir/src/instruction_parser.c.o -c /home/hochacha/repos/2024-os-hw1/src/instruction_parser.c

CMakeFiles/main.dir/src/instruction_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/instruction_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/instruction_parser.c > CMakeFiles/main.dir/src/instruction_parser.c.i

CMakeFiles/main.dir/src/instruction_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/instruction_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/instruction_parser.c -o CMakeFiles/main.dir/src/instruction_parser.c.s

CMakeFiles/main.dir/src/tools/stack.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/tools/stack.c.o: /home/hochacha/repos/2024-os-hw1/src/tools/stack.c
CMakeFiles/main.dir/src/tools/stack.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/src/tools/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/tools/stack.c.o -MF CMakeFiles/main.dir/src/tools/stack.c.o.d -o CMakeFiles/main.dir/src/tools/stack.c.o -c /home/hochacha/repos/2024-os-hw1/src/tools/stack.c

CMakeFiles/main.dir/src/tools/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/tools/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/tools/stack.c > CMakeFiles/main.dir/src/tools/stack.c.i

CMakeFiles/main.dir/src/tools/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/tools/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/tools/stack.c -o CMakeFiles/main.dir/src/tools/stack.c.s

CMakeFiles/main.dir/src/tools/string_tools.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/tools/string_tools.c.o: /home/hochacha/repos/2024-os-hw1/src/tools/string_tools.c
CMakeFiles/main.dir/src/tools/string_tools.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/src/tools/string_tools.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/tools/string_tools.c.o -MF CMakeFiles/main.dir/src/tools/string_tools.c.o.d -o CMakeFiles/main.dir/src/tools/string_tools.c.o -c /home/hochacha/repos/2024-os-hw1/src/tools/string_tools.c

CMakeFiles/main.dir/src/tools/string_tools.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/tools/string_tools.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/tools/string_tools.c > CMakeFiles/main.dir/src/tools/string_tools.c.i

CMakeFiles/main.dir/src/tools/string_tools.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/tools/string_tools.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/tools/string_tools.c -o CMakeFiles/main.dir/src/tools/string_tools.c.s

CMakeFiles/main.dir/src/argument_parser.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/argument_parser.c.o: /home/hochacha/repos/2024-os-hw1/src/argument_parser.c
CMakeFiles/main.dir/src/argument_parser.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/main.dir/src/argument_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/argument_parser.c.o -MF CMakeFiles/main.dir/src/argument_parser.c.o.d -o CMakeFiles/main.dir/src/argument_parser.c.o -c /home/hochacha/repos/2024-os-hw1/src/argument_parser.c

CMakeFiles/main.dir/src/argument_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/argument_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/argument_parser.c > CMakeFiles/main.dir/src/argument_parser.c.i

CMakeFiles/main.dir/src/argument_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/argument_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/argument_parser.c -o CMakeFiles/main.dir/src/argument_parser.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/main.c.o" \
"CMakeFiles/main.dir/src/instruction_parser.c.o" \
"CMakeFiles/main.dir/src/tools/stack.c.o" \
"CMakeFiles/main.dir/src/tools/string_tools.c.o" \
"CMakeFiles/main.dir/src/argument_parser.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/main.c.o
main: CMakeFiles/main.dir/src/instruction_parser.c.o
main: CMakeFiles/main.dir/src/tools/stack.c.o
main: CMakeFiles/main.dir/src/tools/string_tools.c.o
main: CMakeFiles/main.dir/src/argument_parser.c.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/hochacha/repos/2024-os-hw1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hochacha/repos/2024-os-hw1 /home/hochacha/repos/2024-os-hw1 /home/hochacha/repos/2024-os-hw1/cmake-build-debug /home/hochacha/repos/2024-os-hw1/cmake-build-debug /home/hochacha/repos/2024-os-hw1/cmake-build-debug/CMakeFiles/main.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

