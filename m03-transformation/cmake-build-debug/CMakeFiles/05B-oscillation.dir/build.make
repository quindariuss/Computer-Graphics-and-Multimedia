# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = "C:\Users\quinw\AppData\Local\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Users\quinw\AppData\Local\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/05B-oscillation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/05B-oscillation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/05B-oscillation.dir/flags.make

CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.obj: CMakeFiles/05B-oscillation.dir/flags.make
CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.obj: CMakeFiles/05B-oscillation.dir/includes_CXX.rsp
CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.obj: ../05B-oscillation/oscillation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\05B-oscillation.dir\05B-oscillation\oscillation.cpp.obj -c C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\05B-oscillation\oscillation.cpp

CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\05B-oscillation\oscillation.cpp > CMakeFiles\05B-oscillation.dir\05B-oscillation\oscillation.cpp.i

CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\05B-oscillation\oscillation.cpp -o CMakeFiles\05B-oscillation.dir\05B-oscillation\oscillation.cpp.s

CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.obj: CMakeFiles/05B-oscillation.dir/flags.make
CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.obj: CMakeFiles/05B-oscillation.dir/includes_CXX.rsp
CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.obj: ../05B-oscillation/part_oscillating.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\05B-oscillation.dir\05B-oscillation\part_oscillating.cpp.obj -c C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\05B-oscillation\part_oscillating.cpp

CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\05B-oscillation\part_oscillating.cpp > CMakeFiles\05B-oscillation.dir\05B-oscillation\part_oscillating.cpp.i

CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\05B-oscillation\part_oscillating.cpp -o CMakeFiles\05B-oscillation.dir\05B-oscillation\part_oscillating.cpp.s

# Object files for target 05B-oscillation
05B__oscillation_OBJECTS = \
"CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.obj" \
"CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.obj"

# External object files for target 05B-oscillation
05B__oscillation_EXTERNAL_OBJECTS =

05B-oscillation.exe: CMakeFiles/05B-oscillation.dir/05B-oscillation/oscillation.cpp.obj
05B-oscillation.exe: CMakeFiles/05B-oscillation.dir/05B-oscillation/part_oscillating.cpp.obj
05B-oscillation.exe: CMakeFiles/05B-oscillation.dir/build.make
05B-oscillation.exe: CMakeFiles/05B-oscillation.dir/linklibs.rsp
05B-oscillation.exe: CMakeFiles/05B-oscillation.dir/objects1.rsp
05B-oscillation.exe: CMakeFiles/05B-oscillation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable 05B-oscillation.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\05B-oscillation.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/05B-oscillation.dir/build: 05B-oscillation.exe

.PHONY : CMakeFiles/05B-oscillation.dir/build

CMakeFiles/05B-oscillation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\05B-oscillation.dir\cmake_clean.cmake
.PHONY : CMakeFiles/05B-oscillation.dir/clean

CMakeFiles/05B-oscillation.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug\CMakeFiles\05B-oscillation.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/05B-oscillation.dir/depend

