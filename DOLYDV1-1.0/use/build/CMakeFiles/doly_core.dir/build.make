# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/pi/DOLYDV/DOLYDV1-1.0/use/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/DOLYDV/DOLYDV1-1.0/use/build

# Include any dependencies generated for this target.
include CMakeFiles/doly_core.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/doly_core.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/doly_core.dir/flags.make

CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.o: CMakeFiles/doly_core.dir/flags.make
CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.o: /home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/DOLYDV/DOLYDV1-1.0/use/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.o -c /home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp

CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp > CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.i

CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp -o CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.s

CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.o: CMakeFiles/doly_core.dir/flags.make
CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.o: /home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/DOLYDV/DOLYDV1-1.0/use/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.o -c /home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp

CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp > CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.i

CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp -o CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.s

# Object files for target doly_core
doly_core_OBJECTS = \
"CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.o" \
"CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.o"

# External object files for target doly_core
doly_core_EXTERNAL_OBJECTS =

bin/doly_core: CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/main.cpp.o
bin/doly_core: CMakeFiles/doly_core.dir/home/pi/DOLYDV/DOLYDV1-1.0/use/init/init.cpp.o
bin/doly_core: CMakeFiles/doly_core.dir/build.make
bin/doly_core: ../lib/libGpio.a
bin/doly_core: ../lib/libLcdControl.a
bin/doly_core: ../lib/libMotor.a
bin/doly_core: ../lib/libServoMotor.a
bin/doly_core: ../lib/libTimer.a
bin/doly_core: ../lib/libTof.a
bin/doly_core: ../lib/libapp.a
bin/doly_core: ../lib/libbase.a
bin/doly_core: ../lib/libcommu.a
bin/doly_core: ../lib/libgui.a
bin/doly_core: ../lib/libxGpio.a
bin/doly_core: CMakeFiles/doly_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/DOLYDV/DOLYDV1-1.0/use/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/doly_core"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/doly_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/doly_core.dir/build: bin/doly_core

.PHONY : CMakeFiles/doly_core.dir/build

CMakeFiles/doly_core.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/doly_core.dir/cmake_clean.cmake
.PHONY : CMakeFiles/doly_core.dir/clean

CMakeFiles/doly_core.dir/depend:
	cd /home/pi/DOLYDV/DOLYDV1-1.0/use/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/DOLYDV/DOLYDV1-1.0/use/build /home/pi/DOLYDV/DOLYDV1-1.0/use/build /home/pi/DOLYDV/DOLYDV1-1.0/use/build /home/pi/DOLYDV/DOLYDV1-1.0/use/build /home/pi/DOLYDV/DOLYDV1-1.0/use/build/CMakeFiles/doly_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/doly_core.dir/depend

