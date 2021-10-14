# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Projects/CSCI446MP"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Projects/CSCI446MP"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Projects/CSCI446MP/CMakeFiles" "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Projects/CSCI446MP//CMakeFiles/progress.marks"
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Projects/CSCI446MP/CMakeFiles" 0
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
# Target rules for targets named MP

# Build rule for target.
MP: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 MP
.PHONY : MP

# fast build rule for target.
MP/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/build
.PHONY : MP/fast

Eeyore/eeyore.o: Eeyore/eeyore.cpp.o
.PHONY : Eeyore/eeyore.o

# target to build an object file
Eeyore/eeyore.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/Eeyore/eeyore.cpp.o
.PHONY : Eeyore/eeyore.cpp.o

Eeyore/eeyore.i: Eeyore/eeyore.cpp.i
.PHONY : Eeyore/eeyore.i

# target to preprocess a source file
Eeyore/eeyore.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/Eeyore/eeyore.cpp.i
.PHONY : Eeyore/eeyore.cpp.i

Eeyore/eeyore.s: Eeyore/eeyore.cpp.s
.PHONY : Eeyore/eeyore.s

# target to generate assembly for a file
Eeyore/eeyore.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/Eeyore/eeyore.cpp.s
.PHONY : Eeyore/eeyore.cpp.s

MPEngine.o: MPEngine.cpp.o
.PHONY : MPEngine.o

# target to build an object file
MPEngine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/MPEngine.cpp.o
.PHONY : MPEngine.cpp.o

MPEngine.i: MPEngine.cpp.i
.PHONY : MPEngine.i

# target to preprocess a source file
MPEngine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/MPEngine.cpp.i
.PHONY : MPEngine.cpp.i

MPEngine.s: MPEngine.cpp.s
.PHONY : MPEngine.s

# target to generate assembly for a file
MPEngine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/MPEngine.cpp.s
.PHONY : MPEngine.cpp.s

car/Car.o: car/Car.cpp.o
.PHONY : car/Car.o

# target to build an object file
car/Car.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/car/Car.cpp.o
.PHONY : car/Car.cpp.o

car/Car.i: car/Car.cpp.i
.PHONY : car/Car.i

# target to preprocess a source file
car/Car.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/car/Car.cpp.i
.PHONY : car/Car.cpp.i

car/Car.s: car/Car.cpp.s
.PHONY : car/Car.s

# target to generate assembly for a file
car/Car.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/car/Car.cpp.s
.PHONY : car/Car.cpp.s

hero_cameras/HeroCameras.o: hero_cameras/HeroCameras.cpp.o
.PHONY : hero_cameras/HeroCameras.o

# target to build an object file
hero_cameras/HeroCameras.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.o
.PHONY : hero_cameras/HeroCameras.cpp.o

hero_cameras/HeroCameras.i: hero_cameras/HeroCameras.cpp.i
.PHONY : hero_cameras/HeroCameras.i

# target to preprocess a source file
hero_cameras/HeroCameras.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.i
.PHONY : hero_cameras/HeroCameras.cpp.i

hero_cameras/HeroCameras.s: hero_cameras/HeroCameras.cpp.s
.PHONY : hero_cameras/HeroCameras.s

# target to generate assembly for a file
hero_cameras/HeroCameras.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.s
.PHONY : hero_cameras/HeroCameras.cpp.s

john_Reimann/JohnReimann.o: john_Reimann/JohnReimann.cpp.o
.PHONY : john_Reimann/JohnReimann.o

# target to build an object file
john_Reimann/JohnReimann.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.o
.PHONY : john_Reimann/JohnReimann.cpp.o

john_Reimann/JohnReimann.i: john_Reimann/JohnReimann.cpp.i
.PHONY : john_Reimann/JohnReimann.i

# target to preprocess a source file
john_Reimann/JohnReimann.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.i
.PHONY : john_Reimann/JohnReimann.cpp.i

john_Reimann/JohnReimann.s: john_Reimann/JohnReimann.cpp.s
.PHONY : john_Reimann/JohnReimann.s

# target to generate assembly for a file
john_Reimann/JohnReimann.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.s
.PHONY : john_Reimann/JohnReimann.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/main.cpp.s
.PHONY : main.cpp.s

the_warrior/TheWarrior.o: the_warrior/TheWarrior.cpp.o
.PHONY : the_warrior/TheWarrior.o

# target to build an object file
the_warrior/TheWarrior.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.o
.PHONY : the_warrior/TheWarrior.cpp.o

the_warrior/TheWarrior.i: the_warrior/TheWarrior.cpp.i
.PHONY : the_warrior/TheWarrior.i

# target to preprocess a source file
the_warrior/TheWarrior.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.i
.PHONY : the_warrior/TheWarrior.cpp.i

the_warrior/TheWarrior.s: the_warrior/TheWarrior.cpp.s
.PHONY : the_warrior/TheWarrior.s

# target to generate assembly for a file
the_warrior/TheWarrior.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/MP.dir/build.make CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.s
.PHONY : the_warrior/TheWarrior.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... MP"
	@echo "... Eeyore/eeyore.o"
	@echo "... Eeyore/eeyore.i"
	@echo "... Eeyore/eeyore.s"
	@echo "... MPEngine.o"
	@echo "... MPEngine.i"
	@echo "... MPEngine.s"
	@echo "... car/Car.o"
	@echo "... car/Car.i"
	@echo "... car/Car.s"
	@echo "... hero_cameras/HeroCameras.o"
	@echo "... hero_cameras/HeroCameras.i"
	@echo "... hero_cameras/HeroCameras.s"
	@echo "... john_Reimann/JohnReimann.o"
	@echo "... john_Reimann/JohnReimann.i"
	@echo "... john_Reimann/JohnReimann.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... the_warrior/TheWarrior.o"
	@echo "... the_warrior/TheWarrior.i"
	@echo "... the_warrior/TheWarrior.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

