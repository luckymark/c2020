# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2019.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Dai\c2020\level1\p10_pushBoxes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Dai\c2020\level1\p10_pushBoxes\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p10_pushBoxes.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p10_pushBoxes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p10_pushBoxes.dir/flags.make

CMakeFiles/p10_pushBoxes.dir/main.c.obj: CMakeFiles/p10_pushBoxes.dir/flags.make
CMakeFiles/p10_pushBoxes.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dai\c2020\level1\p10_pushBoxes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/p10_pushBoxes.dir/main.c.obj"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\p10_pushBoxes.dir\main.c.obj   -c C:\Users\Dai\c2020\level1\p10_pushBoxes\main.c

CMakeFiles/p10_pushBoxes.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p10_pushBoxes.dir/main.c.i"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dai\c2020\level1\p10_pushBoxes\main.c > CMakeFiles\p10_pushBoxes.dir\main.c.i

CMakeFiles/p10_pushBoxes.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p10_pushBoxes.dir/main.c.s"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dai\c2020\level1\p10_pushBoxes\main.c -o CMakeFiles\p10_pushBoxes.dir\main.c.s

CMakeFiles/p10_pushBoxes.dir/Game.c.obj: CMakeFiles/p10_pushBoxes.dir/flags.make
CMakeFiles/p10_pushBoxes.dir/Game.c.obj: ../Game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dai\c2020\level1\p10_pushBoxes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/p10_pushBoxes.dir/Game.c.obj"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\p10_pushBoxes.dir\Game.c.obj   -c C:\Users\Dai\c2020\level1\p10_pushBoxes\Game.c

CMakeFiles/p10_pushBoxes.dir/Game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p10_pushBoxes.dir/Game.c.i"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dai\c2020\level1\p10_pushBoxes\Game.c > CMakeFiles\p10_pushBoxes.dir\Game.c.i

CMakeFiles/p10_pushBoxes.dir/Game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p10_pushBoxes.dir/Game.c.s"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dai\c2020\level1\p10_pushBoxes\Game.c -o CMakeFiles\p10_pushBoxes.dir\Game.c.s

# Object files for target p10_pushBoxes
p10_pushBoxes_OBJECTS = \
"CMakeFiles/p10_pushBoxes.dir/main.c.obj" \
"CMakeFiles/p10_pushBoxes.dir/Game.c.obj"

# External object files for target p10_pushBoxes
p10_pushBoxes_EXTERNAL_OBJECTS =

p10_pushBoxes.exe: CMakeFiles/p10_pushBoxes.dir/main.c.obj
p10_pushBoxes.exe: CMakeFiles/p10_pushBoxes.dir/Game.c.obj
p10_pushBoxes.exe: CMakeFiles/p10_pushBoxes.dir/build.make
p10_pushBoxes.exe: CMakeFiles/p10_pushBoxes.dir/linklibs.rsp
p10_pushBoxes.exe: CMakeFiles/p10_pushBoxes.dir/objects1.rsp
p10_pushBoxes.exe: CMakeFiles/p10_pushBoxes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Dai\c2020\level1\p10_pushBoxes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable p10_pushBoxes.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\p10_pushBoxes.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p10_pushBoxes.dir/build: p10_pushBoxes.exe

.PHONY : CMakeFiles/p10_pushBoxes.dir/build

CMakeFiles/p10_pushBoxes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\p10_pushBoxes.dir\cmake_clean.cmake
.PHONY : CMakeFiles/p10_pushBoxes.dir/clean

CMakeFiles/p10_pushBoxes.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Dai\c2020\level1\p10_pushBoxes C:\Users\Dai\c2020\level1\p10_pushBoxes C:\Users\Dai\c2020\level1\p10_pushBoxes\cmake-build-debug C:\Users\Dai\c2020\level1\p10_pushBoxes\cmake-build-debug C:\Users\Dai\c2020\level1\p10_pushBoxes\cmake-build-debug\CMakeFiles\p10_pushBoxes.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p10_pushBoxes.dir/depend

