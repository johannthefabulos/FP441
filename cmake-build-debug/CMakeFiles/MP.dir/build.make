# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\johan\Desktop\John_Reimann_A4\FP441

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MP.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/MP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MP.dir/flags.make

CMakeFiles/MP.dir/main.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/main.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MP.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\main.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\main.cpp

CMakeFiles/MP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\main.cpp > CMakeFiles\MP.dir\main.cpp.i

CMakeFiles/MP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\main.cpp -o CMakeFiles\MP.dir\main.cpp.s

CMakeFiles/MP.dir/MPEngine.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/MPEngine.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/MPEngine.cpp.obj: ../MPEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MP.dir/MPEngine.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\MPEngine.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\MPEngine.cpp

CMakeFiles/MP.dir/MPEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/MPEngine.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\MPEngine.cpp > CMakeFiles\MP.dir\MPEngine.cpp.i

CMakeFiles/MP.dir/MPEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/MPEngine.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\MPEngine.cpp -o CMakeFiles\MP.dir\MPEngine.cpp.s

CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.obj: ../the_warrior/TheWarrior.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\the_warrior\TheWarrior.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\the_warrior\TheWarrior.cpp

CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\the_warrior\TheWarrior.cpp > CMakeFiles\MP.dir\the_warrior\TheWarrior.cpp.i

CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\the_warrior\TheWarrior.cpp -o CMakeFiles\MP.dir\the_warrior\TheWarrior.cpp.s

CMakeFiles/MP.dir/Eeyore/eeyore.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/Eeyore/eeyore.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/Eeyore/eeyore.cpp.obj: ../Eeyore/eeyore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MP.dir/Eeyore/eeyore.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\Eeyore\eeyore.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\Eeyore\eeyore.cpp

CMakeFiles/MP.dir/Eeyore/eeyore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/Eeyore/eeyore.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\Eeyore\eeyore.cpp > CMakeFiles\MP.dir\Eeyore\eeyore.cpp.i

CMakeFiles/MP.dir/Eeyore/eeyore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/Eeyore/eeyore.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\Eeyore\eeyore.cpp -o CMakeFiles\MP.dir\Eeyore\eeyore.cpp.s

CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.obj: ../john_Reimann/JohnReimann.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\john_Reimann\JohnReimann.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\john_Reimann\JohnReimann.cpp

CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\john_Reimann\JohnReimann.cpp > CMakeFiles\MP.dir\john_Reimann\JohnReimann.cpp.i

CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\john_Reimann\JohnReimann.cpp -o CMakeFiles\MP.dir\john_Reimann\JohnReimann.cpp.s

CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.obj: ../hero_cameras/HeroCameras.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\hero_cameras\HeroCameras.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\hero_cameras\HeroCameras.cpp

CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\hero_cameras\HeroCameras.cpp > CMakeFiles\MP.dir\hero_cameras\HeroCameras.cpp.i

CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\hero_cameras\HeroCameras.cpp -o CMakeFiles\MP.dir\hero_cameras\HeroCameras.cpp.s

CMakeFiles/MP.dir/environment/Tree.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/environment/Tree.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/environment/Tree.cpp.obj: ../environment/Tree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MP.dir/environment/Tree.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\environment\Tree.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\environment\Tree.cpp

CMakeFiles/MP.dir/environment/Tree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/environment/Tree.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\environment\Tree.cpp > CMakeFiles\MP.dir\environment\Tree.cpp.i

CMakeFiles/MP.dir/environment/Tree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/environment/Tree.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\environment\Tree.cpp -o CMakeFiles\MP.dir\environment\Tree.cpp.s

CMakeFiles/MP.dir/environment/Castle.cpp.obj: CMakeFiles/MP.dir/flags.make
CMakeFiles/MP.dir/environment/Castle.cpp.obj: CMakeFiles/MP.dir/includes_CXX.rsp
CMakeFiles/MP.dir/environment/Castle.cpp.obj: ../environment/Castle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MP.dir/environment/Castle.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\MP.dir\environment\Castle.cpp.obj -c C:\Users\johan\Desktop\John_Reimann_A4\FP441\environment\Castle.cpp

CMakeFiles/MP.dir/environment/Castle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MP.dir/environment/Castle.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\johan\Desktop\John_Reimann_A4\FP441\environment\Castle.cpp > CMakeFiles\MP.dir\environment\Castle.cpp.i

CMakeFiles/MP.dir/environment/Castle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MP.dir/environment/Castle.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\johan\Desktop\John_Reimann_A4\FP441\environment\Castle.cpp -o CMakeFiles\MP.dir\environment\Castle.cpp.s

# Object files for target MP
MP_OBJECTS = \
"CMakeFiles/MP.dir/main.cpp.obj" \
"CMakeFiles/MP.dir/MPEngine.cpp.obj" \
"CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.obj" \
"CMakeFiles/MP.dir/Eeyore/eeyore.cpp.obj" \
"CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.obj" \
"CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.obj" \
"CMakeFiles/MP.dir/environment/Tree.cpp.obj" \
"CMakeFiles/MP.dir/environment/Castle.cpp.obj"

# External object files for target MP
MP_EXTERNAL_OBJECTS =

MP.exe: CMakeFiles/MP.dir/main.cpp.obj
MP.exe: CMakeFiles/MP.dir/MPEngine.cpp.obj
MP.exe: CMakeFiles/MP.dir/the_warrior/TheWarrior.cpp.obj
MP.exe: CMakeFiles/MP.dir/Eeyore/eeyore.cpp.obj
MP.exe: CMakeFiles/MP.dir/john_Reimann/JohnReimann.cpp.obj
MP.exe: CMakeFiles/MP.dir/hero_cameras/HeroCameras.cpp.obj
MP.exe: CMakeFiles/MP.dir/environment/Tree.cpp.obj
MP.exe: CMakeFiles/MP.dir/environment/Castle.cpp.obj
MP.exe: CMakeFiles/MP.dir/build.make
MP.exe: CMakeFiles/MP.dir/linklibs.rsp
MP.exe: CMakeFiles/MP.dir/objects1.rsp
MP.exe: CMakeFiles/MP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable MP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MP.dir/build: MP.exe
.PHONY : CMakeFiles/MP.dir/build

CMakeFiles/MP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MP.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MP.dir/clean

CMakeFiles/MP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\johan\Desktop\John_Reimann_A4\FP441 C:\Users\johan\Desktop\John_Reimann_A4\FP441 C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug C:\Users\johan\Desktop\John_Reimann_A4\FP441\cmake-build-debug\CMakeFiles\MP.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MP.dir/depend

