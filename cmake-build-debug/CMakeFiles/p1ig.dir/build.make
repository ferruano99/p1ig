# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p1ig.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/p1ig.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p1ig.dir/flags.make

CMakeFiles/p1ig.dir/src/Model.cpp.obj: CMakeFiles/p1ig.dir/flags.make
CMakeFiles/p1ig.dir/src/Model.cpp.obj: CMakeFiles/p1ig.dir/includes_CXX.rsp
CMakeFiles/p1ig.dir/src/Model.cpp.obj: ../src/Model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p1ig.dir/src/Model.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\p1ig.dir\src\Model.cpp.obj -c C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\Model.cpp

CMakeFiles/p1ig.dir/src/Model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p1ig.dir/src/Model.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\Model.cpp > CMakeFiles\p1ig.dir\src\Model.cpp.i

CMakeFiles/p1ig.dir/src/Model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p1ig.dir/src/Model.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\Model.cpp -o CMakeFiles\p1ig.dir\src\Model.cpp.s

CMakeFiles/p1ig.dir/src/Shaders.cpp.obj: CMakeFiles/p1ig.dir/flags.make
CMakeFiles/p1ig.dir/src/Shaders.cpp.obj: CMakeFiles/p1ig.dir/includes_CXX.rsp
CMakeFiles/p1ig.dir/src/Shaders.cpp.obj: ../src/Shaders.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/p1ig.dir/src/Shaders.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\p1ig.dir\src\Shaders.cpp.obj -c C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\Shaders.cpp

CMakeFiles/p1ig.dir/src/Shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p1ig.dir/src/Shaders.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\Shaders.cpp > CMakeFiles\p1ig.dir\src\Shaders.cpp.i

CMakeFiles/p1ig.dir/src/Shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p1ig.dir/src/Shaders.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\Shaders.cpp -o CMakeFiles\p1ig.dir\src\Shaders.cpp.s

CMakeFiles/p1ig.dir/src/main.cpp.obj: CMakeFiles/p1ig.dir/flags.make
CMakeFiles/p1ig.dir/src/main.cpp.obj: CMakeFiles/p1ig.dir/includes_CXX.rsp
CMakeFiles/p1ig.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/p1ig.dir/src/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\p1ig.dir\src\main.cpp.obj -c C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\main.cpp

CMakeFiles/p1ig.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p1ig.dir/src/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\main.cpp > CMakeFiles\p1ig.dir\src\main.cpp.i

CMakeFiles/p1ig.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p1ig.dir/src/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\src\main.cpp -o CMakeFiles\p1ig.dir\src\main.cpp.s

# Object files for target p1ig
p1ig_OBJECTS = \
"CMakeFiles/p1ig.dir/src/Model.cpp.obj" \
"CMakeFiles/p1ig.dir/src/Shaders.cpp.obj" \
"CMakeFiles/p1ig.dir/src/main.cpp.obj"

# External object files for target p1ig
p1ig_EXTERNAL_OBJECTS =

binary/p1ig.exe: CMakeFiles/p1ig.dir/src/Model.cpp.obj
binary/p1ig.exe: CMakeFiles/p1ig.dir/src/Shaders.cpp.obj
binary/p1ig.exe: CMakeFiles/p1ig.dir/src/main.cpp.obj
binary/p1ig.exe: CMakeFiles/p1ig.dir/build.make
binary/p1ig.exe: CMakeFiles/p1ig.dir/linklibs.rsp
binary/p1ig.exe: CMakeFiles/p1ig.dir/objects1.rsp
binary/p1ig.exe: CMakeFiles/p1ig.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable binary\p1ig.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\p1ig.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p1ig.dir/build: binary/p1ig.exe
.PHONY : CMakeFiles/p1ig.dir/build

CMakeFiles/p1ig.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\p1ig.dir\cmake_clean.cmake
.PHONY : CMakeFiles/p1ig.dir/clean

CMakeFiles/p1ig.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug C:\Users\ferna\Desktop\Universidad\4\IG\practicas\prac1\p1ig\cmake-build-debug\CMakeFiles\p1ig.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p1ig.dir/depend
