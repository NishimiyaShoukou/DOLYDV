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
CMAKE_SOURCE_DIR = /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build

# Include any dependencies generated for this target.
include CMakeFiles/tof_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tof_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tof_static.dir/flags.make

CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.o: CMakeFiles/tof_static.dir/flags.make
CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.o: /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.o -c /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp

CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp > CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.i

CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp -o CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.s

CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.o: CMakeFiles/tof_static.dir/flags.make
CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.o: /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.o -c /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp

CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp > CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.i

CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp -o CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.s

# Object files for target tof_static
tof_static_OBJECTS = \
"CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.o" \
"CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.o"

# External object files for target tof_static
tof_static_EXTERNAL_OBJECTS =

/home/pi/DOLYDV/DOLYDV1-1.0/use/lib/libTof.a: CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/Tof.cpp.o
/home/pi/DOLYDV/DOLYDV1-1.0/use/lib/libTof.a: CMakeFiles/tof_static.dir/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/src/vl6180_pi.cpp.o
/home/pi/DOLYDV/DOLYDV1-1.0/use/lib/libTof.a: CMakeFiles/tof_static.dir/build.make
/home/pi/DOLYDV/DOLYDV1-1.0/use/lib/libTof.a: CMakeFiles/tof_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library /home/pi/DOLYDV/DOLYDV1-1.0/use/lib/libTof.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tof_static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tof_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tof_static.dir/build: /home/pi/DOLYDV/DOLYDV1-1.0/use/lib/libTof.a

.PHONY : CMakeFiles/tof_static.dir/build

CMakeFiles/tof_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tof_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tof_static.dir/clean

CMakeFiles/tof_static.dir/depend:
	cd /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build /home/pi/DOLYDV/DOLYDV1-1.0/drivehd/Tof/build/CMakeFiles/tof_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tof_static.dir/depend
