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
CMAKE_BINARY_DIR = /home/hochacha/repos/2024-os-hw1/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/new_SiSH.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/new_SiSH.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/new_SiSH.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/new_SiSH.dir/flags.make

CMakeFiles/new_SiSH.dir/src_new/main.c.o: CMakeFiles/new_SiSH.dir/flags.make
CMakeFiles/new_SiSH.dir/src_new/main.c.o: /home/hochacha/repos/2024-os-hw1/src_new/main.c
CMakeFiles/new_SiSH.dir/src_new/main.c.o: CMakeFiles/new_SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/new_SiSH.dir/src_new/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new_SiSH.dir/src_new/main.c.o -MF CMakeFiles/new_SiSH.dir/src_new/main.c.o.d -o CMakeFiles/new_SiSH.dir/src_new/main.c.o -c /home/hochacha/repos/2024-os-hw1/src_new/main.c

CMakeFiles/new_SiSH.dir/src_new/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new_SiSH.dir/src_new/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src_new/main.c > CMakeFiles/new_SiSH.dir/src_new/main.c.i

CMakeFiles/new_SiSH.dir/src_new/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new_SiSH.dir/src_new/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src_new/main.c -o CMakeFiles/new_SiSH.dir/src_new/main.c.s

CMakeFiles/new_SiSH.dir/src_new/shell.c.o: CMakeFiles/new_SiSH.dir/flags.make
CMakeFiles/new_SiSH.dir/src_new/shell.c.o: /home/hochacha/repos/2024-os-hw1/src_new/shell.c
CMakeFiles/new_SiSH.dir/src_new/shell.c.o: CMakeFiles/new_SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/new_SiSH.dir/src_new/shell.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new_SiSH.dir/src_new/shell.c.o -MF CMakeFiles/new_SiSH.dir/src_new/shell.c.o.d -o CMakeFiles/new_SiSH.dir/src_new/shell.c.o -c /home/hochacha/repos/2024-os-hw1/src_new/shell.c

CMakeFiles/new_SiSH.dir/src_new/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new_SiSH.dir/src_new/shell.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src_new/shell.c > CMakeFiles/new_SiSH.dir/src_new/shell.c.i

CMakeFiles/new_SiSH.dir/src_new/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new_SiSH.dir/src_new/shell.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src_new/shell.c -o CMakeFiles/new_SiSH.dir/src_new/shell.c.s

CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o: CMakeFiles/new_SiSH.dir/flags.make
CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o: /home/hochacha/repos/2024-os-hw1/src_new/tools/path_finder.c
CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o: CMakeFiles/new_SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o -MF CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o.d -o CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o -c /home/hochacha/repos/2024-os-hw1/src_new/tools/path_finder.c

CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src_new/tools/path_finder.c > CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.i

CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src_new/tools/path_finder.c -o CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.s

CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o: CMakeFiles/new_SiSH.dir/flags.make
CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o: /home/hochacha/repos/2024-os-hw1/src_new/argument_parser.c
CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o: CMakeFiles/new_SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o -MF CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o.d -o CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o -c /home/hochacha/repos/2024-os-hw1/src_new/argument_parser.c

CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src_new/argument_parser.c > CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.i

CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src_new/argument_parser.c -o CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.s

CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o: CMakeFiles/new_SiSH.dir/flags.make
CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o: /home/hochacha/repos/2024-os-hw1/src_new/instruction_parser.c
CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o: CMakeFiles/new_SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o -MF CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o.d -o CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o -c /home/hochacha/repos/2024-os-hw1/src_new/instruction_parser.c

CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src_new/instruction_parser.c > CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.i

CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src_new/instruction_parser.c -o CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.s

CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o: CMakeFiles/new_SiSH.dir/flags.make
CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o: /home/hochacha/repos/2024-os-hw1/src_new/tools/stack.c
CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o: CMakeFiles/new_SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o -MF CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o.d -o CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o -c /home/hochacha/repos/2024-os-hw1/src_new/tools/stack.c

CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src_new/tools/stack.c > CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.i

CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src_new/tools/stack.c -o CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.s

CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o: CMakeFiles/new_SiSH.dir/flags.make
CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o: /home/hochacha/repos/2024-os-hw1/src_new/tools/builtin_commands.c
CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o: CMakeFiles/new_SiSH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o -MF CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o.d -o CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o -c /home/hochacha/repos/2024-os-hw1/src_new/tools/builtin_commands.c

CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hochacha/repos/2024-os-hw1/src_new/tools/builtin_commands.c > CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.i

CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hochacha/repos/2024-os-hw1/src_new/tools/builtin_commands.c -o CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.s

# Object files for target new_SiSH
new_SiSH_OBJECTS = \
"CMakeFiles/new_SiSH.dir/src_new/main.c.o" \
"CMakeFiles/new_SiSH.dir/src_new/shell.c.o" \
"CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o" \
"CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o" \
"CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o" \
"CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o" \
"CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o"

# External object files for target new_SiSH
new_SiSH_EXTERNAL_OBJECTS =

new_SiSH: CMakeFiles/new_SiSH.dir/src_new/main.c.o
new_SiSH: CMakeFiles/new_SiSH.dir/src_new/shell.c.o
new_SiSH: CMakeFiles/new_SiSH.dir/src_new/tools/path_finder.c.o
new_SiSH: CMakeFiles/new_SiSH.dir/src_new/argument_parser.c.o
new_SiSH: CMakeFiles/new_SiSH.dir/src_new/instruction_parser.c.o
new_SiSH: CMakeFiles/new_SiSH.dir/src_new/tools/stack.c.o
new_SiSH: CMakeFiles/new_SiSH.dir/src_new/tools/builtin_commands.c.o
new_SiSH: CMakeFiles/new_SiSH.dir/build.make
new_SiSH: CMakeFiles/new_SiSH.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable new_SiSH"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/new_SiSH.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/new_SiSH.dir/build: new_SiSH
.PHONY : CMakeFiles/new_SiSH.dir/build

CMakeFiles/new_SiSH.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/new_SiSH.dir/cmake_clean.cmake
.PHONY : CMakeFiles/new_SiSH.dir/clean

CMakeFiles/new_SiSH.dir/depend:
	cd /home/hochacha/repos/2024-os-hw1/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hochacha/repos/2024-os-hw1 /home/hochacha/repos/2024-os-hw1 /home/hochacha/repos/2024-os-hw1/cmake-build-release /home/hochacha/repos/2024-os-hw1/cmake-build-release /home/hochacha/repos/2024-os-hw1/cmake-build-release/CMakeFiles/new_SiSH.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/new_SiSH.dir/depend

