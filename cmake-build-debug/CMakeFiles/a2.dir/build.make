# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/a2.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/a2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a2.dir/flags.make

CMakeFiles/a2.dir/main.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a2.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/main.cpp.o -c "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/main.cpp"

CMakeFiles/a2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/main.cpp" > CMakeFiles/a2.dir/main.cpp.i

CMakeFiles/a2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/main.cpp" -o CMakeFiles/a2.dir/main.cpp.s

CMakeFiles/a2.dir/A2Engine.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/A2Engine.cpp.o: ../A2Engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a2.dir/A2Engine.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/A2Engine.cpp.o -c "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/A2Engine.cpp"

CMakeFiles/a2.dir/A2Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/A2Engine.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/A2Engine.cpp" > CMakeFiles/a2.dir/A2Engine.cpp.i

CMakeFiles/a2.dir/A2Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/A2Engine.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/A2Engine.cpp" -o CMakeFiles/a2.dir/A2Engine.cpp.s

CMakeFiles/a2.dir/WorldMapEngine.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/WorldMapEngine.cpp.o: ../WorldMapEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/a2.dir/WorldMapEngine.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/WorldMapEngine.cpp.o -c "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/WorldMapEngine.cpp"

CMakeFiles/a2.dir/WorldMapEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/WorldMapEngine.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/WorldMapEngine.cpp" > CMakeFiles/a2.dir/WorldMapEngine.cpp.i

CMakeFiles/a2.dir/WorldMapEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/WorldMapEngine.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/WorldMapEngine.cpp" -o CMakeFiles/a2.dir/WorldMapEngine.cpp.s

CMakeFiles/a2.dir/player/Player.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/player/Player.cpp.o: ../player/Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/a2.dir/player/Player.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/player/Player.cpp.o -c "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/player/Player.cpp"

CMakeFiles/a2.dir/player/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/player/Player.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/player/Player.cpp" > CMakeFiles/a2.dir/player/Player.cpp.i

CMakeFiles/a2.dir/player/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/player/Player.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/player/Player.cpp" -o CMakeFiles/a2.dir/player/Player.cpp.s

CMakeFiles/a2.dir/laser/Laser.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/laser/Laser.cpp.o: ../laser/Laser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/a2.dir/laser/Laser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/laser/Laser.cpp.o -c "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/laser/Laser.cpp"

CMakeFiles/a2.dir/laser/Laser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/laser/Laser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/laser/Laser.cpp" > CMakeFiles/a2.dir/laser/Laser.cpp.i

CMakeFiles/a2.dir/laser/Laser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/laser/Laser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/laser/Laser.cpp" -o CMakeFiles/a2.dir/laser/Laser.cpp.s

# Object files for target a2
a2_OBJECTS = \
"CMakeFiles/a2.dir/main.cpp.o" \
"CMakeFiles/a2.dir/A2Engine.cpp.o" \
"CMakeFiles/a2.dir/WorldMapEngine.cpp.o" \
"CMakeFiles/a2.dir/player/Player.cpp.o" \
"CMakeFiles/a2.dir/laser/Laser.cpp.o"

# External object files for target a2
a2_EXTERNAL_OBJECTS =

a2: CMakeFiles/a2.dir/main.cpp.o
a2: CMakeFiles/a2.dir/A2Engine.cpp.o
a2: CMakeFiles/a2.dir/WorldMapEngine.cpp.o
a2: CMakeFiles/a2.dir/player/Player.cpp.o
a2: CMakeFiles/a2.dir/laser/Laser.cpp.o
a2: CMakeFiles/a2.dir/build.make
a2: CMakeFiles/a2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable a2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a2.dir/build: a2
.PHONY : CMakeFiles/a2.dir/build

CMakeFiles/a2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a2.dir/clean

CMakeFiles/a2.dir/depend:
	cd "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2" "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2" "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug" "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug" "/Users/fibonacci/Desktop/Mines/Fall-2021/Computer Graphics/Assignments/A2/cmake-build-debug/CMakeFiles/a2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/a2.dir/depend

