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
include CMakeFiles/04-shared-shapes.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/04-shared-shapes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/04-shared-shapes.dir/flags.make

CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.obj: CMakeFiles/04-shared-shapes.dir/flags.make
CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.obj: CMakeFiles/04-shared-shapes.dir/includes_CXX.rsp
CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.obj: ../04-shared-shapes/shared_shapes.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\04-shared-shapes.dir\04-shared-shapes\shared_shapes.cpp.obj -c C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\04-shared-shapes\shared_shapes.cpp

CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\04-shared-shapes\shared_shapes.cpp > CMakeFiles\04-shared-shapes.dir\04-shared-shapes\shared_shapes.cpp.i

CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\04-shared-shapes\shared_shapes.cpp -o CMakeFiles\04-shared-shapes.dir\04-shared-shapes\shared_shapes.cpp.s

# Object files for target 04-shared-shapes
04__shared__shapes_OBJECTS = \
"CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.obj"

# External object files for target 04-shared-shapes
04__shared__shapes_EXTERNAL_OBJECTS =

04-shared-shapes.exe: CMakeFiles/04-shared-shapes.dir/04-shared-shapes/shared_shapes.cpp.obj
04-shared-shapes.exe: CMakeFiles/04-shared-shapes.dir/build.make
04-shared-shapes.exe: CMakeFiles/04-shared-shapes.dir/linklibs.rsp
04-shared-shapes.exe: CMakeFiles/04-shared-shapes.dir/objects1.rsp
04-shared-shapes.exe: CMakeFiles/04-shared-shapes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 04-shared-shapes.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\04-shared-shapes.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/04-shared-shapes.dir/build: 04-shared-shapes.exe

.PHONY : CMakeFiles/04-shared-shapes.dir/build

CMakeFiles/04-shared-shapes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\04-shared-shapes.dir\cmake_clean.cmake
.PHONY : CMakeFiles/04-shared-shapes.dir/clean

CMakeFiles/04-shared-shapes.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m03-transformation\cmake-build-debug\CMakeFiles\04-shared-shapes.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/04-shared-shapes.dir/depend
