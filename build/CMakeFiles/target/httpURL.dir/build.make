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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/d/ubuntuWorkspace/workspace/compressStatic/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/d/ubuntuWorkspace/workspace/compressStatic/build

# Include any dependencies generated for this target.
include CMakeFiles/target/httpURL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/target/httpURL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/target/httpURL.dir/flags.make

CMakeFiles/target/httpURL.dir/css/httpURL.c.o: CMakeFiles/target/httpURL.dir/flags.make
CMakeFiles/target/httpURL.dir/css/httpURL.c.o: /media/d/ubuntuWorkspace/workspace/compressStatic/src/css/httpURL.c
	$(CMAKE_COMMAND) -E cmake_progress_report /media/d/ubuntuWorkspace/workspace/compressStatic/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/target/httpURL.dir/css/httpURL.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/target/httpURL.dir/css/httpURL.c.o   -c /media/d/ubuntuWorkspace/workspace/compressStatic/src/css/httpURL.c

CMakeFiles/target/httpURL.dir/css/httpURL.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/target/httpURL.dir/css/httpURL.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /media/d/ubuntuWorkspace/workspace/compressStatic/src/css/httpURL.c > CMakeFiles/target/httpURL.dir/css/httpURL.c.i

CMakeFiles/target/httpURL.dir/css/httpURL.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/target/httpURL.dir/css/httpURL.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /media/d/ubuntuWorkspace/workspace/compressStatic/src/css/httpURL.c -o CMakeFiles/target/httpURL.dir/css/httpURL.c.s

CMakeFiles/target/httpURL.dir/css/httpURL.c.o.requires:
.PHONY : CMakeFiles/target/httpURL.dir/css/httpURL.c.o.requires

CMakeFiles/target/httpURL.dir/css/httpURL.c.o.provides: CMakeFiles/target/httpURL.dir/css/httpURL.c.o.requires
	$(MAKE) -f CMakeFiles/target/httpURL.dir/build.make CMakeFiles/target/httpURL.dir/css/httpURL.c.o.provides.build
.PHONY : CMakeFiles/target/httpURL.dir/css/httpURL.c.o.provides

CMakeFiles/target/httpURL.dir/css/httpURL.c.o.provides.build: CMakeFiles/target/httpURL.dir/css/httpURL.c.o

# Object files for target target/httpURL
target/httpURL_OBJECTS = \
"CMakeFiles/target/httpURL.dir/css/httpURL.c.o"

# External object files for target target/httpURL
target/httpURL_EXTERNAL_OBJECTS =

lib/libtarget/httpURL.a: CMakeFiles/target/httpURL.dir/css/httpURL.c.o
lib/libtarget/httpURL.a: CMakeFiles/target/httpURL.dir/build.make
lib/libtarget/httpURL.a: CMakeFiles/target/httpURL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library lib/libtarget/httpURL.a"
	$(CMAKE_COMMAND) -P CMakeFiles/target/httpURL.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/target/httpURL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/target/httpURL.dir/build: lib/libtarget/httpURL.a
.PHONY : CMakeFiles/target/httpURL.dir/build

CMakeFiles/target/httpURL.dir/requires: CMakeFiles/target/httpURL.dir/css/httpURL.c.o.requires
.PHONY : CMakeFiles/target/httpURL.dir/requires

CMakeFiles/target/httpURL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/target/httpURL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/target/httpURL.dir/clean

CMakeFiles/target/httpURL.dir/depend:
	cd /media/d/ubuntuWorkspace/workspace/compressStatic/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/d/ubuntuWorkspace/workspace/compressStatic/src /media/d/ubuntuWorkspace/workspace/compressStatic/src /media/d/ubuntuWorkspace/workspace/compressStatic/build /media/d/ubuntuWorkspace/workspace/compressStatic/build /media/d/ubuntuWorkspace/workspace/compressStatic/build/CMakeFiles/target/httpURL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/target/httpURL.dir/depend

