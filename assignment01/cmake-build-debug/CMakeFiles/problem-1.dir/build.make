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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Computer-Graphics-and-Multimedia\assignment01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Computer-Graphics-and-Multimedia\assignment01\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/problem-1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/problem-1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/problem-1.dir/flags.make

CMakeFiles/problem-1.dir/problem-1/one_point.cpp.obj: CMakeFiles/problem-1.dir/flags.make
CMakeFiles/problem-1.dir/problem-1/one_point.cpp.obj: CMakeFiles/problem-1.dir/includes_CXX.rsp
CMakeFiles/problem-1.dir/problem-1/one_point.cpp.obj: ../problem-1/one_point.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Computer-Graphics-and-Multimedia\assignment01\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/problem-1.dir/problem-1/one_point.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\problem-1.dir\problem-1\one_point.cpp.obj -c C:\Computer-Graphics-and-Multimedia\assignment01\problem-1\one_point.cpp

CMakeFiles/problem-1.dir/problem-1/one_point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/problem-1.dir/problem-1/one_point.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Computer-Graphics-and-Multimedia\assignment01\problem-1\one_point.cpp > CMakeFiles\problem-1.dir\problem-1\one_point.cpp.i

CMakeFiles/problem-1.dir/problem-1/one_point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/problem-1.dir/problem-1/one_point.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Computer-Graphics-and-Multimedia\assignment01\problem-1\one_point.cpp -o CMakeFiles\problem-1.dir\problem-1\one_point.cpp.s

# Object files for target problem-1
problem__1_OBJECTS = \
"CMakeFiles/problem-1.dir/problem-1/one_point.cpp.obj"

# External object files for target problem-1
problem__1_EXTERNAL_OBJECTS =

problem-1.exe: CMakeFiles/problem-1.dir/problem-1/one_point.cpp.obj
problem-1.exe: CMakeFiles/problem-1.dir/build.make
problem-1.exe: CMakeFiles/problem-1.dir/linklibs.rsp
problem-1.exe: CMakeFiles/problem-1.dir/objects1.rsp
problem-1.exe: CMakeFiles/problem-1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Computer-Graphics-and-Multimedia\assignment01\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable problem-1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\problem-1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/problem-1.dir/build: problem-1.exe

.PHONY : CMakeFiles/problem-1.dir/build

CMakeFiles/problem-1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\problem-1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/problem-1.dir/clean

CMakeFiles/problem-1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Computer-Graphics-and-Multimedia\assignment01 C:\Computer-Graphics-and-Multimedia\assignment01 C:\Computer-Graphics-and-Multimedia\assignment01\cmake-build-debug C:\Computer-Graphics-and-Multimedia\assignment01\cmake-build-debug C:\Computer-Graphics-and-Multimedia\assignment01\cmake-build-debug\CMakeFiles\problem-1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/problem-1.dir/depend

