# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xuechen/graph

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xuechen/graph/build

# Include any dependencies generated for this target.
include CMakeFiles/Graph.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Graph.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Graph.dir/flags.make

CMakeFiles/Graph.dir/graph.c.o: CMakeFiles/Graph.dir/flags.make
CMakeFiles/Graph.dir/graph.c.o: ../graph.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xuechen/graph/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Graph.dir/graph.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Graph.dir/graph.c.o -c /home/xuechen/graph/graph.c

CMakeFiles/Graph.dir/graph.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Graph.dir/graph.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/xuechen/graph/graph.c > CMakeFiles/Graph.dir/graph.c.i

CMakeFiles/Graph.dir/graph.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Graph.dir/graph.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/xuechen/graph/graph.c -o CMakeFiles/Graph.dir/graph.c.s

# Object files for target Graph
Graph_OBJECTS = \
"CMakeFiles/Graph.dir/graph.c.o"

# External object files for target Graph
Graph_EXTERNAL_OBJECTS =

Graph: CMakeFiles/Graph.dir/graph.c.o
Graph: CMakeFiles/Graph.dir/build.make
Graph: CMakeFiles/Graph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xuechen/graph/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Graph"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Graph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Graph.dir/build: Graph

.PHONY : CMakeFiles/Graph.dir/build

CMakeFiles/Graph.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Graph.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Graph.dir/clean

CMakeFiles/Graph.dir/depend:
	cd /home/xuechen/graph/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xuechen/graph /home/xuechen/graph /home/xuechen/graph/build /home/xuechen/graph/build /home/xuechen/graph/build/CMakeFiles/Graph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Graph.dir/depend

