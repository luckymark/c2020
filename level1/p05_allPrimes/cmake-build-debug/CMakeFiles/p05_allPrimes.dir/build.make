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
CMAKE_SOURCE_DIR = C:\Users\Dai\c2020\level1\p05_allPrimes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Dai\c2020\level1\p05_allPrimes\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p05_allPrimes.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p05_allPrimes.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p05_allPrimes.dir/flags.make

CMakeFiles/p05_allPrimes.dir/main.c.obj: CMakeFiles/p05_allPrimes.dir/flags.make
CMakeFiles/p05_allPrimes.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dai\c2020\level1\p05_allPrimes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/p05_allPrimes.dir/main.c.obj"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\p05_allPrimes.dir\main.c.obj   -c C:\Users\Dai\c2020\level1\p05_allPrimes\main.c

CMakeFiles/p05_allPrimes.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p05_allPrimes.dir/main.c.i"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dai\c2020\level1\p05_allPrimes\main.c > CMakeFiles\p05_allPrimes.dir\main.c.i

CMakeFiles/p05_allPrimes.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p05_allPrimes.dir/main.c.s"
	D:\CodeBlocks\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dai\c2020\level1\p05_allPrimes\main.c -o CMakeFiles\p05_allPrimes.dir\main.c.s

# Object files for target p05_allPrimes
p05_allPrimes_OBJECTS = \
"CMakeFiles/p05_allPrimes.dir/main.c.obj"

# External object files for target p05_allPrimes
p05_allPrimes_EXTERNAL_OBJECTS =

p05_allPrimes.exe: CMakeFiles/p05_allPrimes.dir/main.c.obj
p05_allPrimes.exe: CMakeFiles/p05_allPrimes.dir/build.make
p05_allPrimes.exe: CMakeFiles/p05_allPrimes.dir/linklibs.rsp
p05_allPrimes.exe: CMakeFiles/p05_allPrimes.dir/objects1.rsp
p05_allPrimes.exe: CMakeFiles/p05_allPrimes.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Dai\c2020\level1\p05_allPrimes\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable p05_allPrimes.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\p05_allPrimes.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p05_allPrimes.dir/build: p05_allPrimes.exe

.PHONY : CMakeFiles/p05_allPrimes.dir/build

CMakeFiles/p05_allPrimes.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\p05_allPrimes.dir\cmake_clean.cmake
.PHONY : CMakeFiles/p05_allPrimes.dir/clean

CMakeFiles/p05_allPrimes.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Dai\c2020\level1\p05_allPrimes C:\Users\Dai\c2020\level1\p05_allPrimes C:\Users\Dai\c2020\level1\p05_allPrimes\cmake-build-debug C:\Users\Dai\c2020\level1\p05_allPrimes\cmake-build-debug C:\Users\Dai\c2020\level1\p05_allPrimes\cmake-build-debug\CMakeFiles\p05_allPrimes.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p05_allPrimes.dir/depend

