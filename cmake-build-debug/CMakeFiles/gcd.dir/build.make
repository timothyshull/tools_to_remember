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
include CMakeFiles/gcd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gcd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gcd.dir/flags.make

CMakeFiles/gcd.dir/gcd.cpp.o: CMakeFiles/gcd.dir/flags.make
CMakeFiles/gcd.dir/gcd.cpp.o: ../gcd.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gcd.dir/gcd.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gcd.dir/gcd.cpp.o -c /Users/skull/Programming/Cpp/tools_to_remember/gcd.cpp

CMakeFiles/gcd.dir/gcd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gcd.dir/gcd.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Cpp/tools_to_remember/gcd.cpp > CMakeFiles/gcd.dir/gcd.cpp.i

CMakeFiles/gcd.dir/gcd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gcd.dir/gcd.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Cpp/tools_to_remember/gcd.cpp -o CMakeFiles/gcd.dir/gcd.cpp.s

CMakeFiles/gcd.dir/gcd.cpp.o.requires:

.PHONY : CMakeFiles/gcd.dir/gcd.cpp.o.requires

CMakeFiles/gcd.dir/gcd.cpp.o.provides: CMakeFiles/gcd.dir/gcd.cpp.o.requires
	$(MAKE) -f CMakeFiles/gcd.dir/build.make CMakeFiles/gcd.dir/gcd.cpp.o.provides.build
.PHONY : CMakeFiles/gcd.dir/gcd.cpp.o.provides

CMakeFiles/gcd.dir/gcd.cpp.o.provides.build: CMakeFiles/gcd.dir/gcd.cpp.o


# Object files for target gcd
gcd_OBJECTS = \
"CMakeFiles/gcd.dir/gcd.cpp.o"

# External object files for target gcd
gcd_EXTERNAL_OBJECTS =

gcd: CMakeFiles/gcd.dir/gcd.cpp.o
gcd: CMakeFiles/gcd.dir/build.make
gcd: CMakeFiles/gcd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gcd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gcd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gcd.dir/build: gcd

.PHONY : CMakeFiles/gcd.dir/build

CMakeFiles/gcd.dir/requires: CMakeFiles/gcd.dir/gcd.cpp.o.requires

.PHONY : CMakeFiles/gcd.dir/requires

CMakeFiles/gcd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gcd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gcd.dir/clean

CMakeFiles/gcd.dir/depend:
	cd /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles/gcd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gcd.dir/depend

