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
include CMakeFiles/count_unique.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/count_unique.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/count_unique.dir/flags.make

CMakeFiles/count_unique.dir/count_unique.cpp.o: CMakeFiles/count_unique.dir/flags.make
CMakeFiles/count_unique.dir/count_unique.cpp.o: ../count_unique.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/count_unique.dir/count_unique.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/count_unique.dir/count_unique.cpp.o -c /Users/skull/Programming/Cpp/tools_to_remember/count_unique.cpp

CMakeFiles/count_unique.dir/count_unique.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/count_unique.dir/count_unique.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/skull/Programming/Cpp/tools_to_remember/count_unique.cpp > CMakeFiles/count_unique.dir/count_unique.cpp.i

CMakeFiles/count_unique.dir/count_unique.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/count_unique.dir/count_unique.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/skull/Programming/Cpp/tools_to_remember/count_unique.cpp -o CMakeFiles/count_unique.dir/count_unique.cpp.s

CMakeFiles/count_unique.dir/count_unique.cpp.o.requires:

.PHONY : CMakeFiles/count_unique.dir/count_unique.cpp.o.requires

CMakeFiles/count_unique.dir/count_unique.cpp.o.provides: CMakeFiles/count_unique.dir/count_unique.cpp.o.requires
	$(MAKE) -f CMakeFiles/count_unique.dir/build.make CMakeFiles/count_unique.dir/count_unique.cpp.o.provides.build
.PHONY : CMakeFiles/count_unique.dir/count_unique.cpp.o.provides

CMakeFiles/count_unique.dir/count_unique.cpp.o.provides.build: CMakeFiles/count_unique.dir/count_unique.cpp.o


# Object files for target count_unique
count_unique_OBJECTS = \
"CMakeFiles/count_unique.dir/count_unique.cpp.o"

# External object files for target count_unique
count_unique_EXTERNAL_OBJECTS =

count_unique: CMakeFiles/count_unique.dir/count_unique.cpp.o
count_unique: CMakeFiles/count_unique.dir/build.make
count_unique: CMakeFiles/count_unique.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable count_unique"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/count_unique.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/count_unique.dir/build: count_unique

.PHONY : CMakeFiles/count_unique.dir/build

CMakeFiles/count_unique.dir/requires: CMakeFiles/count_unique.dir/count_unique.cpp.o.requires

.PHONY : CMakeFiles/count_unique.dir/requires

CMakeFiles/count_unique.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/count_unique.dir/cmake_clean.cmake
.PHONY : CMakeFiles/count_unique.dir/clean

CMakeFiles/count_unique.dir/depend:
	cd /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug /Users/skull/Programming/Cpp/tools_to_remember/cmake-build-debug/CMakeFiles/count_unique.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/count_unique.dir/depend

