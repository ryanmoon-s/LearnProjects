# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/shishun/AllProject/cmake/version

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/shishun/AllProject/cmake/version/build

# Include any dependencies generated for this target.
include CMakeFiles/version.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/version.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/version.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/version.out.dir/flags.make

CMakeFiles/version.out.dir/version.cpp.o: CMakeFiles/version.out.dir/flags.make
CMakeFiles/version.out.dir/version.cpp.o: /Users/shishun/AllProject/cmake/version/version.cpp
CMakeFiles/version.out.dir/version.cpp.o: CMakeFiles/version.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/shishun/AllProject/cmake/version/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/version.out.dir/version.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/version.out.dir/version.cpp.o -MF CMakeFiles/version.out.dir/version.cpp.o.d -o CMakeFiles/version.out.dir/version.cpp.o -c /Users/shishun/AllProject/cmake/version/version.cpp

CMakeFiles/version.out.dir/version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/version.out.dir/version.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/shishun/AllProject/cmake/version/version.cpp > CMakeFiles/version.out.dir/version.cpp.i

CMakeFiles/version.out.dir/version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/version.out.dir/version.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/shishun/AllProject/cmake/version/version.cpp -o CMakeFiles/version.out.dir/version.cpp.s

# Object files for target version.out
version_out_OBJECTS = \
"CMakeFiles/version.out.dir/version.cpp.o"

# External object files for target version.out
version_out_EXTERNAL_OBJECTS =

version.out: CMakeFiles/version.out.dir/version.cpp.o
version.out: CMakeFiles/version.out.dir/build.make
version.out: CMakeFiles/version.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/shishun/AllProject/cmake/version/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable version.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/version.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/version.out.dir/build: version.out
.PHONY : CMakeFiles/version.out.dir/build

CMakeFiles/version.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/version.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/version.out.dir/clean

CMakeFiles/version.out.dir/depend:
	cd /Users/shishun/AllProject/cmake/version/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/shishun/AllProject/cmake/version /Users/shishun/AllProject/cmake/version /Users/shishun/AllProject/cmake/version/build /Users/shishun/AllProject/cmake/version/build /Users/shishun/AllProject/cmake/version/build/CMakeFiles/version.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/version.out.dir/depend

