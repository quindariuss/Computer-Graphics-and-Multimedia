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
CMAKE_SOURCE_DIR = C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/02-sky-box.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/02-sky-box.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/02-sky-box.dir/flags.make

CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.obj: CMakeFiles/02-sky-box.dir/flags.make
CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.obj: CMakeFiles/02-sky-box.dir/includes_CXX.rsp
CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.obj: ../02-sky-box/skybox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\02-sky-box.dir\02-sky-box\skybox.cpp.obj -c C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\skybox.cpp

CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\skybox.cpp > CMakeFiles\02-sky-box.dir\02-sky-box\skybox.cpp.i

CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\skybox.cpp -o CMakeFiles\02-sky-box.dir\02-sky-box\skybox.cpp.s

CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.obj: CMakeFiles/02-sky-box.dir/flags.make
CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.obj: CMakeFiles/02-sky-box.dir/includes_CXX.rsp
CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.obj: ../02-sky-box/setup_skybox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\02-sky-box.dir\02-sky-box\setup_skybox.cpp.obj -c C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\setup_skybox.cpp

CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\setup_skybox.cpp > CMakeFiles\02-sky-box.dir\02-sky-box\setup_skybox.cpp.i

CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\setup_skybox.cpp -o CMakeFiles\02-sky-box.dir\02-sky-box\setup_skybox.cpp.s

CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.obj: CMakeFiles/02-sky-box.dir/flags.make
CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.obj: CMakeFiles/02-sky-box.dir/includes_CXX.rsp
CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.obj: ../02-sky-box/setup_parts.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\02-sky-box.dir\02-sky-box\setup_parts.cpp.obj -c C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\setup_parts.cpp

CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\setup_parts.cpp > CMakeFiles\02-sky-box.dir\02-sky-box\setup_parts.cpp.i

CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\02-sky-box\setup_parts.cpp -o CMakeFiles\02-sky-box.dir\02-sky-box\setup_parts.cpp.s

# Object files for target 02-sky-box
02__sky__box_OBJECTS = \
"CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.obj" \
"CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.obj" \
"CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.obj"

# External object files for target 02-sky-box
02__sky__box_EXTERNAL_OBJECTS =

02-sky-box.exe: CMakeFiles/02-sky-box.dir/02-sky-box/skybox.cpp.obj
02-sky-box.exe: CMakeFiles/02-sky-box.dir/02-sky-box/setup_skybox.cpp.obj
02-sky-box.exe: CMakeFiles/02-sky-box.dir/02-sky-box/setup_parts.cpp.obj
02-sky-box.exe: CMakeFiles/02-sky-box.dir/build.make
02-sky-box.exe: CMakeFiles/02-sky-box.dir/linklibs.rsp
02-sky-box.exe: CMakeFiles/02-sky-box.dir/objects1.rsp
02-sky-box.exe: CMakeFiles/02-sky-box.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable 02-sky-box.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\02-sky-box.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/02-sky-box.dir/build: 02-sky-box.exe

.PHONY : CMakeFiles/02-sky-box.dir/build

CMakeFiles/02-sky-box.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\02-sky-box.dir\cmake_clean.cmake
.PHONY : CMakeFiles/02-sky-box.dir/clean

CMakeFiles/02-sky-box.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug C:\Users\quinw\Documents\Computer-Graphics-and-Multimedia\m06-advanced-textures\cmake-build-debug\CMakeFiles\02-sky-box.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/02-sky-box.dir/depend
