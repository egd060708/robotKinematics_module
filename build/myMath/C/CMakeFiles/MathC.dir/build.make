# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = D:\usefulTools\Cmake\bin\cmake.exe

# The command to remove a file.
RM = D:\usefulTools\Cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Git_Project\github\robot_module

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Git_Project\github\robot_module\build

# Include any dependencies generated for this target.
include myMath/C/CMakeFiles/MathC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include myMath/C/CMakeFiles/MathC.dir/compiler_depend.make

# Include the progress variables for this target.
include myMath/C/CMakeFiles/MathC.dir/progress.make

# Include the compile flags for this target's objects.
include myMath/C/CMakeFiles/MathC.dir/flags.make

myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.obj: myMath/C/CMakeFiles/MathC.dir/flags.make
myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.obj: myMath/C/CMakeFiles/MathC.dir/includes_C.rsp
myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.obj: D:/Git_Project/github/robot_module/myMath/C/source/mathPrint.c
myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.obj: myMath/C/CMakeFiles/MathC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Git_Project\github\robot_module\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.obj"
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && D:\usefulTools\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.obj -MF CMakeFiles\MathC.dir\source\mathPrint.c.obj.d -o CMakeFiles\MathC.dir\source\mathPrint.c.obj -c D:\Git_Project\github\robot_module\myMath\C\source\mathPrint.c

myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MathC.dir/source/mathPrint.c.i"
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && D:\usefulTools\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Git_Project\github\robot_module\myMath\C\source\mathPrint.c > CMakeFiles\MathC.dir\source\mathPrint.c.i

myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MathC.dir/source/mathPrint.c.s"
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && D:\usefulTools\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Git_Project\github\robot_module\myMath\C\source\mathPrint.c -o CMakeFiles\MathC.dir\source\mathPrint.c.s

myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.obj: myMath/C/CMakeFiles/MathC.dir/flags.make
myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.obj: myMath/C/CMakeFiles/MathC.dir/includes_C.rsp
myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.obj: D:/Git_Project/github/robot_module/myMath/C/source/mathTool.c
myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.obj: myMath/C/CMakeFiles/MathC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Git_Project\github\robot_module\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.obj"
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && D:\usefulTools\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.obj -MF CMakeFiles\MathC.dir\source\mathTool.c.obj.d -o CMakeFiles\MathC.dir\source\mathTool.c.obj -c D:\Git_Project\github\robot_module\myMath\C\source\mathTool.c

myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MathC.dir/source/mathTool.c.i"
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && D:\usefulTools\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Git_Project\github\robot_module\myMath\C\source\mathTool.c > CMakeFiles\MathC.dir\source\mathTool.c.i

myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MathC.dir/source/mathTool.c.s"
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && D:\usefulTools\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Git_Project\github\robot_module\myMath\C\source\mathTool.c -o CMakeFiles\MathC.dir\source\mathTool.c.s

# Object files for target MathC
MathC_OBJECTS = \
"CMakeFiles/MathC.dir/source/mathPrint.c.obj" \
"CMakeFiles/MathC.dir/source/mathTool.c.obj"

# External object files for target MathC
MathC_EXTERNAL_OBJECTS =

myMath/C/libMathC.a: myMath/C/CMakeFiles/MathC.dir/source/mathPrint.c.obj
myMath/C/libMathC.a: myMath/C/CMakeFiles/MathC.dir/source/mathTool.c.obj
myMath/C/libMathC.a: myMath/C/CMakeFiles/MathC.dir/build.make
myMath/C/libMathC.a: myMath/C/CMakeFiles/MathC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Git_Project\github\robot_module\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libMathC.a"
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && $(CMAKE_COMMAND) -P CMakeFiles\MathC.dir\cmake_clean_target.cmake
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\MathC.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
myMath/C/CMakeFiles/MathC.dir/build: myMath/C/libMathC.a
.PHONY : myMath/C/CMakeFiles/MathC.dir/build

myMath/C/CMakeFiles/MathC.dir/clean:
	cd /d D:\Git_Project\github\robot_module\build\myMath\C && $(CMAKE_COMMAND) -P CMakeFiles\MathC.dir\cmake_clean.cmake
.PHONY : myMath/C/CMakeFiles/MathC.dir/clean

myMath/C/CMakeFiles/MathC.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Git_Project\github\robot_module D:\Git_Project\github\robot_module\myMath\C D:\Git_Project\github\robot_module\build D:\Git_Project\github\robot_module\build\myMath\C D:\Git_Project\github\robot_module\build\myMath\C\CMakeFiles\MathC.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : myMath/C/CMakeFiles/MathC.dir/depend
