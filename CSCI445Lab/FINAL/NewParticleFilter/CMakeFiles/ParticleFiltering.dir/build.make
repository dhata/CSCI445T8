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
CMAKE_SOURCE_DIR = /home/pi/FINAL/NewParticleFilter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/FINAL/NewParticleFilter

# Include any dependencies generated for this target.
include CMakeFiles/ParticleFiltering.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ParticleFiltering.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ParticleFiltering.dir/flags.make

CMakeFiles/ParticleFiltering.dir/main.cpp.o: CMakeFiles/ParticleFiltering.dir/flags.make
CMakeFiles/ParticleFiltering.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/FINAL/NewParticleFilter/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ParticleFiltering.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ParticleFiltering.dir/main.cpp.o -c /home/pi/FINAL/NewParticleFilter/main.cpp

CMakeFiles/ParticleFiltering.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ParticleFiltering.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/FINAL/NewParticleFilter/main.cpp > CMakeFiles/ParticleFiltering.dir/main.cpp.i

CMakeFiles/ParticleFiltering.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ParticleFiltering.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/FINAL/NewParticleFilter/main.cpp -o CMakeFiles/ParticleFiltering.dir/main.cpp.s

CMakeFiles/ParticleFiltering.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/ParticleFiltering.dir/main.cpp.o.requires

CMakeFiles/ParticleFiltering.dir/main.cpp.o.provides: CMakeFiles/ParticleFiltering.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ParticleFiltering.dir/build.make CMakeFiles/ParticleFiltering.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/ParticleFiltering.dir/main.cpp.o.provides

CMakeFiles/ParticleFiltering.dir/main.cpp.o.provides.build: CMakeFiles/ParticleFiltering.dir/main.cpp.o

# Object files for target ParticleFiltering
ParticleFiltering_OBJECTS = \
"CMakeFiles/ParticleFiltering.dir/main.cpp.o"

# External object files for target ParticleFiltering
ParticleFiltering_EXTERNAL_OBJECTS =

ParticleFiltering: CMakeFiles/ParticleFiltering.dir/main.cpp.o
ParticleFiltering: CMakeFiles/ParticleFiltering.dir/build.make
ParticleFiltering: CMakeFiles/ParticleFiltering.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ParticleFiltering"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ParticleFiltering.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ParticleFiltering.dir/build: ParticleFiltering
.PHONY : CMakeFiles/ParticleFiltering.dir/build

CMakeFiles/ParticleFiltering.dir/requires: CMakeFiles/ParticleFiltering.dir/main.cpp.o.requires
.PHONY : CMakeFiles/ParticleFiltering.dir/requires

CMakeFiles/ParticleFiltering.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ParticleFiltering.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ParticleFiltering.dir/clean

CMakeFiles/ParticleFiltering.dir/depend:
	cd /home/pi/FINAL/NewParticleFilter && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/FINAL/NewParticleFilter /home/pi/FINAL/NewParticleFilter /home/pi/FINAL/NewParticleFilter /home/pi/FINAL/NewParticleFilter /home/pi/FINAL/NewParticleFilter/CMakeFiles/ParticleFiltering.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ParticleFiltering.dir/depend

