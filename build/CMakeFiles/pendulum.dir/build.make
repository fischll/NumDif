# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lorenz/Documents/NumDif

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lorenz/Documents/NumDif/build

# Include any dependencies generated for this target.
include CMakeFiles/pendulum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pendulum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pendulum.dir/flags.make

CMakeFiles/pendulum.dir/pendulum.cpp.o: CMakeFiles/pendulum.dir/flags.make
CMakeFiles/pendulum.dir/pendulum.cpp.o: ../pendulum.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lorenz/Documents/NumDif/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pendulum.dir/pendulum.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pendulum.dir/pendulum.cpp.o -c /home/lorenz/Documents/NumDif/pendulum.cpp

CMakeFiles/pendulum.dir/pendulum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pendulum.dir/pendulum.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenz/Documents/NumDif/pendulum.cpp > CMakeFiles/pendulum.dir/pendulum.cpp.i

CMakeFiles/pendulum.dir/pendulum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pendulum.dir/pendulum.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenz/Documents/NumDif/pendulum.cpp -o CMakeFiles/pendulum.dir/pendulum.cpp.s

CMakeFiles/pendulum.dir/pendulum.cpp.o.requires:

.PHONY : CMakeFiles/pendulum.dir/pendulum.cpp.o.requires

CMakeFiles/pendulum.dir/pendulum.cpp.o.provides: CMakeFiles/pendulum.dir/pendulum.cpp.o.requires
	$(MAKE) -f CMakeFiles/pendulum.dir/build.make CMakeFiles/pendulum.dir/pendulum.cpp.o.provides.build
.PHONY : CMakeFiles/pendulum.dir/pendulum.cpp.o.provides

CMakeFiles/pendulum.dir/pendulum.cpp.o.provides.build: CMakeFiles/pendulum.dir/pendulum.cpp.o


# Object files for target pendulum
pendulum_OBJECTS = \
"CMakeFiles/pendulum.dir/pendulum.cpp.o"

# External object files for target pendulum
pendulum_EXTERNAL_OBJECTS =

pendulum: CMakeFiles/pendulum.dir/pendulum.cpp.o
pendulum: CMakeFiles/pendulum.dir/build.make
pendulum: bla/libmybla.so
pendulum: CMakeFiles/pendulum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lorenz/Documents/NumDif/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pendulum"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pendulum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pendulum.dir/build: pendulum

.PHONY : CMakeFiles/pendulum.dir/build

CMakeFiles/pendulum.dir/requires: CMakeFiles/pendulum.dir/pendulum.cpp.o.requires

.PHONY : CMakeFiles/pendulum.dir/requires

CMakeFiles/pendulum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pendulum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pendulum.dir/clean

CMakeFiles/pendulum.dir/depend:
	cd /home/lorenz/Documents/NumDif/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lorenz/Documents/NumDif /home/lorenz/Documents/NumDif /home/lorenz/Documents/NumDif/build /home/lorenz/Documents/NumDif/build /home/lorenz/Documents/NumDif/build/CMakeFiles/pendulum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pendulum.dir/depend

