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
include CMakeFiles/list_reverse.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/list_reverse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/list_reverse.dir/flags.make

CMakeFiles/list_reverse.dir/list_reverse.cpp.o: CMakeFiles/list_reverse.dir/flags.make
CMakeFiles/list_reverse.dir/list_reverse.cpp.o: ../list_reverse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/list_reverse.dir/list_reverse.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/list_reverse.dir/list_reverse.cpp.o -c /Users/skull/Programming/Cpp/tools_to_remember/list_reverse.cpp

CMakeFiles/list_reverse.dir/list_reverse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/list_reverse.dir/list_reverse.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Cpp/tools_to_remember/list_reverse.cpp > CMakeFiles/list_reverse.dir/list_reverse.cpp.i

CMakeFiles/list_reverse.dir/list_reverse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/list_reverse.dir/list_reverse.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Cpp/tools_to_remember/list_reverse.cpp -o CMakeFiles/list_reverse.dir/list_reverse.cpp.s

CMakeFiles/list_reverse.dir/list_reverse.cpp.o.requires:

.PHONY : CMakeFiles/list_reverse.dir/list_reverse.cpp.o.requires

CMakeFiles/list_reverse.dir/list_reverse.cpp.o.provides: CMakeFiles/list_reverse.dir/list_reverse.cpp.o.requires
	$(MAKE) -f CMakeFiles/list_reverse.dir/build.make CMakeFiles/list_reverse.dir/list_reverse.cpp.o.provides.build
.PHONY : CMakeFiles/list_reverse.dir/list_reverse.cpp.o.provides

CMakeFiles/list_reverse.dir/list_reverse.cpp.o.provides.build: CMakeFiles/list_reverse.dir/list_reverse.cpp.o


# Object files for target list_reverse
list_reverse_OBJECTS = \
"CMakeFiles/list_reverse.dir/list_reverse.cpp.o"

# External object files for target list_reverse
list_reverse_EXTERNAL_OBJECTS =

list_reverse: CMakeFiles/list_reverse.dir/list_reverse.cpp.o
list_reverse: CMakeFiles/list_reverse.dir/build.make
list_reverse: CMakeFiles/list_reverse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable list_reverse"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/list_reverse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/list_reverse.dir/build: list_reverse

.PHONY : CMakeFiles/list_reverse.dir/build

CMakeFiles/list_reverse.dir/requires: CMakeFiles/list_reverse.dir/list_reverse.cpp.o.requires

.PHONY : CMakeFiles/list_reverse.dir/requires

CMakeFiles/list_reverse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/list_reverse.dir/cmake_clean.cmake
.PHONY : CMakeFiles/list_reverse.dir/clean

CMakeFiles/list_reverse.dir/depend:
	cd /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles/list_reverse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/list_reverse.dir/depend

