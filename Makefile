# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A3"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.18.4/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.18.4/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A3/CMakeFiles" "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A3//CMakeFiles/progress.marks"
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A3/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named A3

# Build rule for target.
A3: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 A3
.PHONY : A3

# fast build rule for target.
A3/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/build
.PHONY : A3/fast

A3Engine.o: A3Engine.cpp.o

.PHONY : A3Engine.o

# target to build an object file
A3Engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/A3Engine.cpp.o
.PHONY : A3Engine.cpp.o

A3Engine.i: A3Engine.cpp.i

.PHONY : A3Engine.i

# target to preprocess a source file
A3Engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/A3Engine.cpp.i
.PHONY : A3Engine.cpp.i

A3Engine.s: A3Engine.cpp.s

.PHONY : A3Engine.s

# target to generate assembly for a file
A3Engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/A3Engine.cpp.s
.PHONY : A3Engine.cpp.s

Car.o: Car.cpp.o

.PHONY : Car.o

# target to build an object file
Car.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/Car.cpp.o
.PHONY : Car.cpp.o

Car.i: Car.cpp.i

.PHONY : Car.i

# target to preprocess a source file
Car.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/Car.cpp.i
.PHONY : Car.cpp.i

Car.s: Car.cpp.s

.PHONY : Car.s

# target to generate assembly for a file
Car.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/Car.cpp.s
.PHONY : Car.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/A3.dir/build.make CMakeFiles/A3.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... A3"
	@echo "... A3Engine.o"
	@echo "... A3Engine.i"
	@echo "... A3Engine.s"
	@echo "... Car.o"
	@echo "... Car.i"
	@echo "... Car.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

