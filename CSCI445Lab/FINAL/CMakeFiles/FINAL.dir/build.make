# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/pi/FINAL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/FINAL

# Include any dependencies generated for this target.
include CMakeFiles/FINAL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FINAL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FINAL.dir/flags.make

CMakeFiles/FINAL.dir/main.cpp.o: CMakeFiles/FINAL.dir/flags.make
CMakeFiles/FINAL.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/FINAL/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/FINAL.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/FINAL.dir/main.cpp.o -c /home/pi/FINAL/main.cpp

CMakeFiles/FINAL.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FINAL.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/FINAL/main.cpp > CMakeFiles/FINAL.dir/main.cpp.i

CMakeFiles/FINAL.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FINAL.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/FINAL/main.cpp -o CMakeFiles/FINAL.dir/main.cpp.s

CMakeFiles/FINAL.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/FINAL.dir/main.cpp.o.requires

CMakeFiles/FINAL.dir/main.cpp.o.provides: CMakeFiles/FINAL.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/FINAL.dir/build.make CMakeFiles/FINAL.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/FINAL.dir/main.cpp.o.provides

CMakeFiles/FINAL.dir/main.cpp.o.provides.build: CMakeFiles/FINAL.dir/main.cpp.o

# Object files for target FINAL
FINAL_OBJECTS = \
"CMakeFiles/FINAL.dir/main.cpp.o"

# External object files for target FINAL
FINAL_EXTERNAL_OBJECTS =

FINAL: CMakeFiles/FINAL.dir/main.cpp.o
FINAL: CMakeFiles/FINAL.dir/build.make
FINAL: CMakeFiles/FINAL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable FINAL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FINAL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FINAL.dir/build: FINAL
.PHONY : CMakeFiles/FINAL.dir/build

CMakeFiles/FINAL.dir/requires: CMakeFiles/FINAL.dir/main.cpp.o.requires
.PHONY : CMakeFiles/FINAL.dir/requires

CMakeFiles/FINAL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FINAL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FINAL.dir/clean

CMakeFiles/FINAL.dir/depend:
	cd /home/pi/FINAL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/FINAL /home/pi/FINAL /home/pi/FINAL /home/pi/FINAL /home/pi/FINAL/CMakeFiles/FINAL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FINAL.dir/depend

