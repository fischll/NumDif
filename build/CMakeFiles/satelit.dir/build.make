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
include CMakeFiles/satelit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/satelit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/satelit.dir/flags.make

CMakeFiles/satelit.dir/satelit.cpp.o: CMakeFiles/satelit.dir/flags.make
CMakeFiles/satelit.dir/satelit.cpp.o: ../satelit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lorenz/Documents/NumDif/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/satelit.dir/satelit.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/satelit.dir/satelit.cpp.o -c /home/lorenz/Documents/NumDif/satelit.cpp

CMakeFiles/satelit.dir/satelit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/satelit.dir/satelit.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lorenz/Documents/NumDif/satelit.cpp > CMakeFiles/satelit.dir/satelit.cpp.i

CMakeFiles/satelit.dir/satelit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/satelit.dir/satelit.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lorenz/Documents/NumDif/satelit.cpp -o CMakeFiles/satelit.dir/satelit.cpp.s

CMakeFiles/satelit.dir/satelit.cpp.o.requires:

.PHONY : CMakeFiles/satelit.dir/satelit.cpp.o.requires

CMakeFiles/satelit.dir/satelit.cpp.o.provides: CMakeFiles/satelit.dir/satelit.cpp.o.requires
	$(MAKE) -f CMakeFiles/satelit.dir/build.make CMakeFiles/satelit.dir/satelit.cpp.o.provides.build
.PHONY : CMakeFiles/satelit.dir/satelit.cpp.o.provides

CMakeFiles/satelit.dir/satelit.cpp.o.provides.build: CMakeFiles/satelit.dir/satelit.cpp.o


# Object files for target satelit
satelit_OBJECTS = \
"CMakeFiles/satelit.dir/satelit.cpp.o"

# External object files for target satelit
satelit_EXTERNAL_OBJECTS =

satelit: CMakeFiles/satelit.dir/satelit.cpp.o
satelit: CMakeFiles/satelit.dir/build.make
satelit: bla/libmybla.so
satelit: CMakeFiles/satelit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lorenz/Documents/NumDif/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable satelit"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/satelit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/satelit.dir/build: satelit

.PHONY : CMakeFiles/satelit.dir/build

CMakeFiles/satelit.dir/requires: CMakeFiles/satelit.dir/satelit.cpp.o.requires

.PHONY : CMakeFiles/satelit.dir/requires

CMakeFiles/satelit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/satelit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/satelit.dir/clean

CMakeFiles/satelit.dir/depend:
	cd /home/lorenz/Documents/NumDif/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lorenz/Documents/NumDif /home/lorenz/Documents/NumDif /home/lorenz/Documents/NumDif/build /home/lorenz/Documents/NumDif/build /home/lorenz/Documents/NumDif/build/CMakeFiles/satelit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/satelit.dir/depend
