# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hochacha/repos/2024-os-hw1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hochacha/repos/2024-os-hw1/build

# Include any dependencies generated for this target.
include CMakeFiles/SiSH.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SiSH.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SiSH.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SiSH.dir/flags.make

CMakeFiles/SiSH.dir/src/main.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/main.c.o: ../src/main.c
CMakeFiles/SiSH.dir/src/main.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SiSH.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/main.c.o -MF CMakeFiles/SiSH.dir/src/main.c.o.d -o CMakeFiles/SiSH.dir/src/main.c.o -c /home/hochacha/repos/2024-os-hw1/src/main.c

CMakeFiles/SiSH.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/main.c > CMakeFiles/SiSH.dir/src/main.c.i

CMakeFiles/SiSH.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/main.c -o CMakeFiles/SiSH.dir/src/main.c.s

CMakeFiles/SiSH.dir/src/shell.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/shell.c.o: ../src/shell.c
CMakeFiles/SiSH.dir/src/shell.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/SiSH.dir/src/shell.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/shell.c.o -MF CMakeFiles/SiSH.dir/src/shell.c.o.d -o CMakeFiles/SiSH.dir/src/shell.c.o -c /home/hochacha/repos/2024-os-hw1/src/shell.c

CMakeFiles/SiSH.dir/src/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/shell.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/shell.c > CMakeFiles/SiSH.dir/src/shell.c.i

CMakeFiles/SiSH.dir/src/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/shell.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/shell.c -o CMakeFiles/SiSH.dir/src/shell.c.s

CMakeFiles/SiSH.dir/src/tools/path_finder.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/tools/path_finder.c.o: ../src/tools/path_finder.c
CMakeFiles/SiSH.dir/src/tools/path_finder.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/SiSH.dir/src/tools/path_finder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/tools/path_finder.c.o -MF CMakeFiles/SiSH.dir/src/tools/path_finder.c.o.d -o CMakeFiles/SiSH.dir/src/tools/path_finder.c.o -c /home/hochacha/repos/2024-os-hw1/src/tools/path_finder.c

CMakeFiles/SiSH.dir/src/tools/path_finder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/tools/path_finder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/tools/path_finder.c > CMakeFiles/SiSH.dir/src/tools/path_finder.c.i

CMakeFiles/SiSH.dir/src/tools/path_finder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/tools/path_finder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/tools/path_finder.c -o CMakeFiles/SiSH.dir/src/tools/path_finder.c.s

CMakeFiles/SiSH.dir/src/argument_parser.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/argument_parser.c.o: ../src/argument_parser.c
CMakeFiles/SiSH.dir/src/argument_parser.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/SiSH.dir/src/argument_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/argument_parser.c.o -MF CMakeFiles/SiSH.dir/src/argument_parser.c.o.d -o CMakeFiles/SiSH.dir/src/argument_parser.c.o -c /home/hochacha/repos/2024-os-hw1/src/argument_parser.c

CMakeFiles/SiSH.dir/src/argument_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/argument_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/argument_parser.c > CMakeFiles/SiSH.dir/src/argument_parser.c.i

CMakeFiles/SiSH.dir/src/argument_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/argument_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/argument_parser.c -o CMakeFiles/SiSH.dir/src/argument_parser.c.s

CMakeFiles/SiSH.dir/src/instruction_parser.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/instruction_parser.c.o: ../src/instruction_parser.c
CMakeFiles/SiSH.dir/src/instruction_parser.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/SiSH.dir/src/instruction_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/instruction_parser.c.o -MF CMakeFiles/SiSH.dir/src/instruction_parser.c.o.d -o CMakeFiles/SiSH.dir/src/instruction_parser.c.o -c /home/hochacha/repos/2024-os-hw1/src/instruction_parser.c

CMakeFiles/SiSH.dir/src/instruction_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/instruction_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/instruction_parser.c > CMakeFiles/SiSH.dir/src/instruction_parser.c.i

CMakeFiles/SiSH.dir/src/instruction_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/instruction_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/instruction_parser.c -o CMakeFiles/SiSH.dir/src/instruction_parser.c.s

CMakeFiles/SiSH.dir/src/tools/stack.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/tools/stack.c.o: ../src/tools/stack.c
CMakeFiles/SiSH.dir/src/tools/stack.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/SiSH.dir/src/tools/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/tools/stack.c.o -MF CMakeFiles/SiSH.dir/src/tools/stack.c.o.d -o CMakeFiles/SiSH.dir/src/tools/stack.c.o -c /home/hochacha/repos/2024-os-hw1/src/tools/stack.c

CMakeFiles/SiSH.dir/src/tools/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/tools/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/tools/stack.c > CMakeFiles/SiSH.dir/src/tools/stack.c.i

CMakeFiles/SiSH.dir/src/tools/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/tools/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/tools/stack.c -o CMakeFiles/SiSH.dir/src/tools/stack.c.s

CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o: ../src/tools/builtin_commands.c
CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o -MF CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o.d -o CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o -c /home/hochacha/repos/2024-os-hw1/src/tools/builtin_commands.c

CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/tools/builtin_commands.c > CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.i

CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/tools/builtin_commands.c -o CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.s

CMakeFiles/SiSH.dir/src/tools/string_tools.c.o: CMakeFiles/SiSH.dir/flags.make
CMakeFiles/SiSH.dir/src/tools/string_tools.c.o: ../src/tools/string_tools.c
CMakeFiles/SiSH.dir/src/tools/string_tools.c.o: CMakeFiles/SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/SiSH.dir/src/tools/string_tools.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SiSH.dir/src/tools/string_tools.c.o -MF CMakeFiles/SiSH.dir/src/tools/string_tools.c.o.d -o CMakeFiles/SiSH.dir/src/tools/string_tools.c.o -c /home/hochacha/repos/2024-os-hw1/src/tools/string_tools.c

CMakeFiles/SiSH.dir/src/tools/string_tools.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SiSH.dir/src/tools/string_tools.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src/tools/string_tools.c > CMakeFiles/SiSH.dir/src/tools/string_tools.c.i

CMakeFiles/SiSH.dir/src/tools/string_tools.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SiSH.dir/src/tools/string_tools.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src/tools/string_tools.c -o CMakeFiles/SiSH.dir/src/tools/string_tools.c.s

# Object files for target SiSH
SiSH_OBJECTS = \
"CMakeFiles/SiSH.dir/src/main.c.o" \
"CMakeFiles/SiSH.dir/src/shell.c.o" \
"CMakeFiles/SiSH.dir/src/tools/path_finder.c.o" \
"CMakeFiles/SiSH.dir/src/argument_parser.c.o" \
"CMakeFiles/SiSH.dir/src/instruction_parser.c.o" \
"CMakeFiles/SiSH.dir/src/tools/stack.c.o" \
"CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o" \
"CMakeFiles/SiSH.dir/src/tools/string_tools.c.o"

# External object files for target SiSH
SiSH_EXTERNAL_OBJECTS =

SiSH: CMakeFiles/SiSH.dir/src/main.c.o
SiSH: CMakeFiles/SiSH.dir/src/shell.c.o
SiSH: CMakeFiles/SiSH.dir/src/tools/path_finder.c.o
SiSH: CMakeFiles/SiSH.dir/src/argument_parser.c.o
SiSH: CMakeFiles/SiSH.dir/src/instruction_parser.c.o
SiSH: CMakeFiles/SiSH.dir/src/tools/stack.c.o
SiSH: CMakeFiles/SiSH.dir/src/tools/builtin_commands.c.o
SiSH: CMakeFiles/SiSH.dir/src/tools/string_tools.c.o
SiSH: CMakeFiles/SiSH.dir/build.make
SiSH: CMakeFiles/SiSH.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hochacha/repos/2024-os-hw1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable SiSH"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SiSH.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SiSH.dir/build: SiSH
.PHONY : CMakeFiles/SiSH.dir/build

CMakeFiles/SiSH.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SiSH.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SiSH.dir/clean

CMakeFiles/SiSH.dir/depend:
	cd /home/hochacha/repos/2024-os-hw1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hochacha/repos/2024-os-hw1 /home/hochacha/repos/2024-os-hw1 /home/hochacha/repos/2024-os-hw1/build /home/hochacha/repos/2024-os-hw1/build /home/hochacha/repos/2024-os-hw1/build/CMakeFiles/SiSH.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SiSH.dir/depend

