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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/07-shading-textures.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/07-shading-textures.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/07-shading-textures.dir/flags.make

CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.obj: CMakeFiles/07-shading-textures.dir/flags.make
CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.obj: CMakeFiles/07-shading-textures.dir/includes_CXX.rsp
CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.obj: ../07-shading-textures/shading_textures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\07-shading-textures.dir\07-shading-textures\shading_textures.cpp.obj -c C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\07-shading-textures\shading_textures.cpp

CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\07-shading-textures\shading_textures.cpp > CMakeFiles\07-shading-textures.dir\07-shading-textures\shading_textures.cpp.i

CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\07-shading-textures\shading_textures.cpp -o CMakeFiles\07-shading-textures.dir\07-shading-textures\shading_textures.cpp.s

# Object files for target 07-shading-textures
07__shading__textures_OBJECTS = \
"CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.obj"

# External object files for target 07-shading-textures
07__shading__textures_EXTERNAL_OBJECTS =

07-shading-textures.exe: CMakeFiles/07-shading-textures.dir/07-shading-textures/shading_textures.cpp.obj
07-shading-textures.exe: CMakeFiles/07-shading-textures.dir/build.make
07-shading-textures.exe: CMakeFiles/07-shading-textures.dir/linklibs.rsp
07-shading-textures.exe: CMakeFiles/07-shading-textures.dir/objects1.rsp
07-shading-textures.exe: CMakeFiles/07-shading-textures.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 07-shading-textures.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\07-shading-textures.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/07-shading-textures.dir/build: 07-shading-textures.exe

.PHONY : CMakeFiles/07-shading-textures.dir/build

CMakeFiles/07-shading-textures.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\07-shading-textures.dir\cmake_clean.cmake
.PHONY : CMakeFiles/07-shading-textures.dir/clean

CMakeFiles/07-shading-textures.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m07-lighting-and-shading\cmake-build-debug\CMakeFiles\07-shading-textures.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/07-shading-textures.dir/depend

