# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /mnt/c/Users/lorenz/source/repos/ode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/lorenz/source/repos/ode/build

# Include any dependencies generated for this target.
include CMakeFiles/demo_bla.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo_bla.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo_bla.dir/flags.make

CMakeFiles/demo_bla.dir/demo_bla.cpp.o: CMakeFiles/demo_bla.dir/flags.make
CMakeFiles/demo_bla.dir/demo_bla.cpp.o: ../demo_bla.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/lorenz/source/repos/ode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo_bla.dir/demo_bla.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo_bla.dir/demo_bla.cpp.o -c /mnt/c/Users/lorenz/source/repos/ode/demo_bla.cpp

CMakeFiles/demo_bla.dir/demo_bla.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo_bla.dir/demo_bla.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/lorenz/source/repos/ode/demo_bla.cpp > CMakeFiles/demo_bla.dir/demo_bla.cpp.i

CMakeFiles/demo_bla.dir/demo_bla.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo_bla.dir/demo_bla.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/lorenz/source/repos/ode/demo_bla.cpp -o CMakeFiles/demo_bla.dir/demo_bla.cpp.s

CMakeFiles/demo_bla.dir/demo_bla.cpp.o.requires:

.PHONY : CMakeFiles/demo_bla.dir/demo_bla.cpp.o.requires

CMakeFiles/demo_bla.dir/demo_bla.cpp.o.provides: CMakeFiles/demo_bla.dir/demo_bla.cpp.o.requires
	$(MAKE) -f CMakeFiles/demo_bla.dir/build.make CMakeFiles/demo_bla.dir/demo_bla.cpp.o.provides.build
.PHONY : CMakeFiles/demo_bla.dir/demo_bla.cpp.o.provides

CMakeFiles/demo_bla.dir/demo_bla.cpp.o.provides.build: CMakeFiles/demo_bla.dir/demo_bla.cpp.o


# Object files for target demo_bla
demo_bla_OBJECTS = \
"CMakeFiles/demo_bla.dir/demo_bla.cpp.o"

# External object files for target demo_bla
demo_bla_EXTERNAL_OBJECTS =

demo_bla: CMakeFiles/demo_bla.dir/demo_bla.cpp.o
demo_bla: CMakeFiles/demo_bla.dir/build.make
demo_bla: CMakeFiles/demo_bla.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/lorenz/source/repos/ode/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable demo_bla"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo_bla.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo_bla.dir/build: demo_bla

.PHONY : CMakeFiles/demo_bla.dir/build

CMakeFiles/demo_bla.dir/requires: CMakeFiles/demo_bla.dir/demo_bla.cpp.o.requires

.PHONY : CMakeFiles/demo_bla.dir/requires

CMakeFiles/demo_bla.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo_bla.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo_bla.dir/clean

CMakeFiles/demo_bla.dir/depend:
	cd /mnt/c/Users/lorenz/source/repos/ode/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/lorenz/source/repos/ode /mnt/c/Users/lorenz/source/repos/ode /mnt/c/Users/lorenz/source/repos/ode/build /mnt/c/Users/lorenz/source/repos/ode/build /mnt/c/Users/lorenz/source/repos/ode/build/CMakeFiles/demo_bla.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo_bla.dir/depend

