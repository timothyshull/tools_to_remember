# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.13906.4/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/skull/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/163.13906.4/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/skull/Programming/Cpp/tools_to_remember

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tabs_to_spaces.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tabs_to_spaces.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tabs_to_spaces.dir/flags.make

CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o: CMakeFiles/tabs_to_spaces.dir/flags.make
CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o: ../tabs_to_spaces.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o -c /Users/skull/Programming/Cpp/tools_to_remember/tabs_to_spaces.cpp

CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Cpp/tools_to_remember/tabs_to_spaces.cpp > CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.i

CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Cpp/tools_to_remember/tabs_to_spaces.cpp -o CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.s

CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.requires:

.PHONY : CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.requires

CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.provides: CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.requires
	$(MAKE) -f CMakeFiles/tabs_to_spaces.dir/build.make CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.provides.build
.PHONY : CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.provides

CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.provides.build: CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o


# Object files for target tabs_to_spaces
tabs_to_spaces_OBJECTS = \
"CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o"

# External object files for target tabs_to_spaces
tabs_to_spaces_EXTERNAL_OBJECTS =

tabs_to_spaces: CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o
tabs_to_spaces: CMakeFiles/tabs_to_spaces.dir/build.make
tabs_to_spaces: CMakeFiles/tabs_to_spaces.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tabs_to_spaces"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tabs_to_spaces.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tabs_to_spaces.dir/build: tabs_to_spaces

.PHONY : CMakeFiles/tabs_to_spaces.dir/build

CMakeFiles/tabs_to_spaces.dir/requires: CMakeFiles/tabs_to_spaces.dir/tabs_to_spaces.cpp.o.requires

.PHONY : CMakeFiles/tabs_to_spaces.dir/requires

CMakeFiles/tabs_to_spaces.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tabs_to_spaces.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tabs_to_spaces.dir/clean

CMakeFiles/tabs_to_spaces.dir/depend:
	cd /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles/tabs_to_spaces.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tabs_to_spaces.dir/depend

