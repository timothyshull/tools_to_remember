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
include CMakeFiles/case_find.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/case_find.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/case_find.dir/flags.make

CMakeFiles/case_find.dir/case_find.cpp.o: CMakeFiles/case_find.dir/flags.make
CMakeFiles/case_find.dir/case_find.cpp.o: ../case_find.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/case_find.dir/case_find.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/case_find.dir/case_find.cpp.o -c /Users/skull/Programming/Cpp/tools_to_remember/case_find.cpp

CMakeFiles/case_find.dir/case_find.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/case_find.dir/case_find.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Cpp/tools_to_remember/case_find.cpp > CMakeFiles/case_find.dir/case_find.cpp.i

CMakeFiles/case_find.dir/case_find.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/case_find.dir/case_find.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Cpp/tools_to_remember/case_find.cpp -o CMakeFiles/case_find.dir/case_find.cpp.s

CMakeFiles/case_find.dir/case_find.cpp.o.requires:

.PHONY : CMakeFiles/case_find.dir/case_find.cpp.o.requires

CMakeFiles/case_find.dir/case_find.cpp.o.provides: CMakeFiles/case_find.dir/case_find.cpp.o.requires
	$(MAKE) -f CMakeFiles/case_find.dir/build.make CMakeFiles/case_find.dir/case_find.cpp.o.provides.build
.PHONY : CMakeFiles/case_find.dir/case_find.cpp.o.provides

CMakeFiles/case_find.dir/case_find.cpp.o.provides.build: CMakeFiles/case_find.dir/case_find.cpp.o


# Object files for target case_find
case_find_OBJECTS = \
"CMakeFiles/case_find.dir/case_find.cpp.o"

# External object files for target case_find
case_find_EXTERNAL_OBJECTS =

case_find: CMakeFiles/case_find.dir/case_find.cpp.o
case_find: CMakeFiles/case_find.dir/build.make
case_find: CMakeFiles/case_find.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable case_find"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/case_find.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/case_find.dir/build: case_find

.PHONY : CMakeFiles/case_find.dir/build

CMakeFiles/case_find.dir/requires: CMakeFiles/case_find.dir/case_find.cpp.o.requires

.PHONY : CMakeFiles/case_find.dir/requires

CMakeFiles/case_find.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/case_find.dir/cmake_clean.cmake
.PHONY : CMakeFiles/case_find.dir/clean

CMakeFiles/case_find.dir/depend:
	cd /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles/case_find.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/case_find.dir/depend

