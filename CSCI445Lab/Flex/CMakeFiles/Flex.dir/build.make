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
CMAKE_SOURCE_DIR = /home/pi/Flex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Flex

# Include any dependencies generated for this target.
include CMakeFiles/Flex.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Flex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Flex.dir/flags.make

CMakeFiles/Flex.dir/flex.cpp.o: CMakeFiles/Flex.dir/flags.make
CMakeFiles/Flex.dir/flex.cpp.o: flex.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/Flex/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Flex.dir/flex.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Flex.dir/flex.cpp.o -c /home/pi/Flex/flex.cpp

CMakeFiles/Flex.dir/flex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Flex.dir/flex.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pi/Flex/flex.cpp > CMakeFiles/Flex.dir/flex.cpp.i

CMakeFiles/Flex.dir/flex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Flex.dir/flex.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pi/Flex/flex.cpp -o CMakeFiles/Flex.dir/flex.cpp.s

CMakeFiles/Flex.dir/flex.cpp.o.requires:
.PHONY : CMakeFiles/Flex.dir/flex.cpp.o.requires

CMakeFiles/Flex.dir/flex.cpp.o.provides: CMakeFiles/Flex.dir/flex.cpp.o.requires
	$(MAKE) -f CMakeFiles/Flex.dir/build.make CMakeFiles/Flex.dir/flex.cpp.o.provides.build
.PHONY : CMakeFiles/Flex.dir/flex.cpp.o.provides

CMakeFiles/Flex.dir/flex.cpp.o.provides.build: CMakeFiles/Flex.dir/flex.cpp.o

# Object files for target Flex
Flex_OBJECTS = \
"CMakeFiles/Flex.dir/flex.cpp.o"

# External object files for target Flex
Flex_EXTERNAL_OBJECTS =

Flex: CMakeFiles/Flex.dir/flex.cpp.o
Flex: CMakeFiles/Flex.dir/build.make
Flex: /opt/vc/lib/libmmal_core.so
Flex: /opt/vc/lib/libmmal_util.so
Flex: /opt/vc/lib/libmmal_vc_client.so
Flex: /opt/vc/lib/libvcos.so
Flex: /opt/vc/lib/libbcm_host.so
Flex: CMakeFiles/Flex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Flex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Flex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Flex.dir/build: Flex
.PHONY : CMakeFiles/Flex.dir/build

CMakeFiles/Flex.dir/requires: CMakeFiles/Flex.dir/flex.cpp.o.requires
.PHONY : CMakeFiles/Flex.dir/requires

CMakeFiles/Flex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Flex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Flex.dir/clean

CMakeFiles/Flex.dir/depend:
	cd /home/pi/Flex && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Flex /home/pi/Flex /home/pi/Flex /home/pi/Flex /home/pi/Flex/CMakeFiles/Flex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Flex.dir/depend
