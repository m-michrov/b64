# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "E:\CLion 2018.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "E:\CLion 2018.2.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\CLionProjects\b64

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\CLionProjects\b64\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/b64.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/b64.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/b64.dir/flags.make

CMakeFiles/b64.dir/main.c.obj: CMakeFiles/b64.dir/flags.make
CMakeFiles/b64.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\b64\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/b64.dir/main.c.obj"
	E:\Win-builds\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\b64.dir\main.c.obj   -c E:\CLionProjects\b64\main.c

CMakeFiles/b64.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/b64.dir/main.c.i"
	E:\Win-builds\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\CLionProjects\b64\main.c > CMakeFiles\b64.dir\main.c.i

CMakeFiles/b64.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/b64.dir/main.c.s"
	E:\Win-builds\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\CLionProjects\b64\main.c -o CMakeFiles\b64.dir\main.c.s

CMakeFiles/b64.dir/base64.c.obj: CMakeFiles/b64.dir/flags.make
CMakeFiles/b64.dir/base64.c.obj: ../base64.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CLionProjects\b64\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/b64.dir/base64.c.obj"
	E:\Win-builds\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\b64.dir\base64.c.obj   -c E:\CLionProjects\b64\base64.c

CMakeFiles/b64.dir/base64.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/b64.dir/base64.c.i"
	E:\Win-builds\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\CLionProjects\b64\base64.c > CMakeFiles\b64.dir\base64.c.i

CMakeFiles/b64.dir/base64.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/b64.dir/base64.c.s"
	E:\Win-builds\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\CLionProjects\b64\base64.c -o CMakeFiles\b64.dir\base64.c.s

# Object files for target b64
b64_OBJECTS = \
"CMakeFiles/b64.dir/main.c.obj" \
"CMakeFiles/b64.dir/base64.c.obj"

# External object files for target b64
b64_EXTERNAL_OBJECTS =

b64.exe: CMakeFiles/b64.dir/main.c.obj
b64.exe: CMakeFiles/b64.dir/base64.c.obj
b64.exe: CMakeFiles/b64.dir/build.make
b64.exe: CMakeFiles/b64.dir/linklibs.rsp
b64.exe: CMakeFiles/b64.dir/objects1.rsp
b64.exe: CMakeFiles/b64.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\CLionProjects\b64\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable b64.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\b64.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/b64.dir/build: b64.exe

.PHONY : CMakeFiles/b64.dir/build

CMakeFiles/b64.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\b64.dir\cmake_clean.cmake
.PHONY : CMakeFiles/b64.dir/clean

CMakeFiles/b64.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\CLionProjects\b64 E:\CLionProjects\b64 E:\CLionProjects\b64\cmake-build-debug E:\CLionProjects\b64\cmake-build-debug E:\CLionProjects\b64\cmake-build-debug\CMakeFiles\b64.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/b64.dir/depend

