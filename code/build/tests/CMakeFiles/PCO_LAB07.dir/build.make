# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/reds/Desktop/git/PCO_lab07/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/reds/Desktop/git/PCO_lab07/code/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/PCO_LAB07.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/PCO_LAB07.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/PCO_LAB07.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/PCO_LAB07.dir/flags.make

tests/CMakeFiles/PCO_LAB07.dir/main.cpp.o: tests/CMakeFiles/PCO_LAB07.dir/flags.make
tests/CMakeFiles/PCO_LAB07.dir/main.cpp.o: ../tests/main.cpp
tests/CMakeFiles/PCO_LAB07.dir/main.cpp.o: tests/CMakeFiles/PCO_LAB07.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reds/Desktop/git/PCO_lab07/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/PCO_LAB07.dir/main.cpp.o"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/PCO_LAB07.dir/main.cpp.o -MF CMakeFiles/PCO_LAB07.dir/main.cpp.o.d -o CMakeFiles/PCO_LAB07.dir/main.cpp.o -c /home/reds/Desktop/git/PCO_lab07/code/tests/main.cpp

tests/CMakeFiles/PCO_LAB07.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PCO_LAB07.dir/main.cpp.i"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/reds/Desktop/git/PCO_lab07/code/tests/main.cpp > CMakeFiles/PCO_LAB07.dir/main.cpp.i

tests/CMakeFiles/PCO_LAB07.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PCO_LAB07.dir/main.cpp.s"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/reds/Desktop/git/PCO_lab07/code/tests/main.cpp -o CMakeFiles/PCO_LAB07.dir/main.cpp.s

tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o: tests/CMakeFiles/PCO_LAB07.dir/flags.make
tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o: ../tests/sasAccess.cpp
tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o: tests/CMakeFiles/PCO_LAB07.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reds/Desktop/git/PCO_lab07/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o -MF CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o.d -o CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o -c /home/reds/Desktop/git/PCO_lab07/code/tests/sasAccess.cpp

tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.i"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/reds/Desktop/git/PCO_lab07/code/tests/sasAccess.cpp > CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.i

tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.s"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/reds/Desktop/git/PCO_lab07/code/tests/sasAccess.cpp -o CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.s

tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o: tests/CMakeFiles/PCO_LAB07.dir/flags.make
tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o: ../tests/ScenarioCreator.cpp
tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o: tests/CMakeFiles/PCO_LAB07.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/reds/Desktop/git/PCO_lab07/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o -MF CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o.d -o CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o -c /home/reds/Desktop/git/PCO_lab07/code/tests/ScenarioCreator.cpp

tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.i"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/reds/Desktop/git/PCO_lab07/code/tests/ScenarioCreator.cpp > CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.i

tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.s"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/reds/Desktop/git/PCO_lab07/code/tests/ScenarioCreator.cpp -o CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.s

# Object files for target PCO_LAB07
PCO_LAB07_OBJECTS = \
"CMakeFiles/PCO_LAB07.dir/main.cpp.o" \
"CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o" \
"CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o"

# External object files for target PCO_LAB07
PCO_LAB07_EXTERNAL_OBJECTS =

tests/PCO_LAB07: tests/CMakeFiles/PCO_LAB07.dir/main.cpp.o
tests/PCO_LAB07: tests/CMakeFiles/PCO_LAB07.dir/sasAccess.cpp.o
tests/PCO_LAB07: tests/CMakeFiles/PCO_LAB07.dir/ScenarioCreator.cpp.o
tests/PCO_LAB07: tests/CMakeFiles/PCO_LAB07.dir/build.make
tests/PCO_LAB07: src/libmodelchecking_lib.a
tests/PCO_LAB07: tests/CMakeFiles/PCO_LAB07.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/reds/Desktop/git/PCO_lab07/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable PCO_LAB07"
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PCO_LAB07.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/PCO_LAB07.dir/build: tests/PCO_LAB07
.PHONY : tests/CMakeFiles/PCO_LAB07.dir/build

tests/CMakeFiles/PCO_LAB07.dir/clean:
	cd /home/reds/Desktop/git/PCO_lab07/code/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/PCO_LAB07.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/PCO_LAB07.dir/clean

tests/CMakeFiles/PCO_LAB07.dir/depend:
	cd /home/reds/Desktop/git/PCO_lab07/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/reds/Desktop/git/PCO_lab07/code /home/reds/Desktop/git/PCO_lab07/code/tests /home/reds/Desktop/git/PCO_lab07/code/build /home/reds/Desktop/git/PCO_lab07/code/build/tests /home/reds/Desktop/git/PCO_lab07/code/build/tests/CMakeFiles/PCO_LAB07.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/PCO_LAB07.dir/depend

