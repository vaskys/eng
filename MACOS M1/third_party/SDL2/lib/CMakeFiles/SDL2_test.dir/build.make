# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /users/samsi/Downloads/SDL-release-2.28.2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/samsi/Downloads/SDL-release-2.28.2/build

# Include any dependencies generated for this target.
include CMakeFiles/SDL2_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SDL2_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SDL2_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SDL2_test.dir/flags.make

CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_assert.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_assert.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_assert.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_assert.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_common.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_common.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_common.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_common.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_compare.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_compare.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_compare.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_compare.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_crc32.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_crc32.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_crc32.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_crc32.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_font.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_font.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_font.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_font.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_fuzzer.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_fuzzer.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_fuzzer.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_fuzzer.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_harness.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_harness.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_harness.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_harness.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlit.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlit.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlit.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlit.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlitBlend.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlitBlend.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlitBlend.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageBlitBlend.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageFace.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageFace.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageFace.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imageFace.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitives.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitives.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitives.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitives.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitivesBlend.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitivesBlend.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitivesBlend.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_imagePrimitivesBlend.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_log.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_log.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_log.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_log.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_md5.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_md5.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_md5.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_md5.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_memory.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_memory.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_memory.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_memory.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.s

CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o: CMakeFiles/SDL2_test.dir/flags.make
CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o: /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_random.c
CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o: CMakeFiles/SDL2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o -MF CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o.d -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o -c /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_random.c

CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_random.c > CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.i

CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/samsi/Downloads/SDL-release-2.28.2/src/test/SDL_test_random.c -o CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.s

# Object files for target SDL2_test
SDL2_test_OBJECTS = \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o" \
"CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o"

# External object files for target SDL2_test
SDL2_test_EXTERNAL_OBJECTS =

libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_assert.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_common.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_compare.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_crc32.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_font.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_fuzzer.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_harness.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlit.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageBlitBlend.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_imageFace.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitives.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_imagePrimitivesBlend.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_log.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_md5.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_memory.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/src/test/SDL_test_random.c.o
libSDL2_test.a: CMakeFiles/SDL2_test.dir/build.make
libSDL2_test.a: CMakeFiles/SDL2_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking C static library libSDL2_test.a"
	$(CMAKE_COMMAND) -P CMakeFiles/SDL2_test.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL2_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SDL2_test.dir/build: libSDL2_test.a
.PHONY : CMakeFiles/SDL2_test.dir/build

CMakeFiles/SDL2_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SDL2_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SDL2_test.dir/clean

CMakeFiles/SDL2_test.dir/depend:
	cd /Users/samsi/Downloads/SDL-release-2.28.2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/samsi/Downloads/SDL-release-2.28.2 /users/samsi/Downloads/SDL-release-2.28.2 /Users/samsi/Downloads/SDL-release-2.28.2/build /Users/samsi/Downloads/SDL-release-2.28.2/build /Users/samsi/Downloads/SDL-release-2.28.2/build/CMakeFiles/SDL2_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SDL2_test.dir/depend
