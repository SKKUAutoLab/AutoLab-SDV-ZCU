# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/Workspace/AutoLab-SDV-ZCU/Camera_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Workspace/AutoLab-SDV-ZCU/Camera_server/build

# Include any dependencies generated for this target.
include CMakeFiles/camera_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/camera_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/camera_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/camera_server.dir/flags.make

CMakeFiles/camera_server.dir/codegen:
.PHONY : CMakeFiles/camera_server.dir/codegen

CMakeFiles/camera_server.dir/main.cpp.o: CMakeFiles/camera_server.dir/flags.make
CMakeFiles/camera_server.dir/main.cpp.o: /root/Workspace/AutoLab-SDV-ZCU/Camera_server/main.cpp
CMakeFiles/camera_server.dir/main.cpp.o: CMakeFiles/camera_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/Workspace/AutoLab-SDV-ZCU/Camera_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/camera_server.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camera_server.dir/main.cpp.o -MF CMakeFiles/camera_server.dir/main.cpp.o.d -o CMakeFiles/camera_server.dir/main.cpp.o -c /root/Workspace/AutoLab-SDV-ZCU/Camera_server/main.cpp

CMakeFiles/camera_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/camera_server.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Workspace/AutoLab-SDV-ZCU/Camera_server/main.cpp > CMakeFiles/camera_server.dir/main.cpp.i

CMakeFiles/camera_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/camera_server.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Workspace/AutoLab-SDV-ZCU/Camera_server/main.cpp -o CMakeFiles/camera_server.dir/main.cpp.s

CMakeFiles/camera_server.dir/Image.cxx.o: CMakeFiles/camera_server.dir/flags.make
CMakeFiles/camera_server.dir/Image.cxx.o: /root/Workspace/AutoLab-SDV-ZCU/Camera_server/Image.cxx
CMakeFiles/camera_server.dir/Image.cxx.o: CMakeFiles/camera_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/Workspace/AutoLab-SDV-ZCU/Camera_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/camera_server.dir/Image.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camera_server.dir/Image.cxx.o -MF CMakeFiles/camera_server.dir/Image.cxx.o.d -o CMakeFiles/camera_server.dir/Image.cxx.o -c /root/Workspace/AutoLab-SDV-ZCU/Camera_server/Image.cxx

CMakeFiles/camera_server.dir/Image.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/camera_server.dir/Image.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Workspace/AutoLab-SDV-ZCU/Camera_server/Image.cxx > CMakeFiles/camera_server.dir/Image.cxx.i

CMakeFiles/camera_server.dir/Image.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/camera_server.dir/Image.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Workspace/AutoLab-SDV-ZCU/Camera_server/Image.cxx -o CMakeFiles/camera_server.dir/Image.cxx.s

CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o: CMakeFiles/camera_server.dir/flags.make
CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o: /root/Workspace/AutoLab-SDV-ZCU/Camera_server/ImagePubSubTypes.cxx
CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o: CMakeFiles/camera_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/Workspace/AutoLab-SDV-ZCU/Camera_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o -MF CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o.d -o CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o -c /root/Workspace/AutoLab-SDV-ZCU/Camera_server/ImagePubSubTypes.cxx

CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/Workspace/AutoLab-SDV-ZCU/Camera_server/ImagePubSubTypes.cxx > CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.i

CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/Workspace/AutoLab-SDV-ZCU/Camera_server/ImagePubSubTypes.cxx -o CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.s

# Object files for target camera_server
camera_server_OBJECTS = \
"CMakeFiles/camera_server.dir/main.cpp.o" \
"CMakeFiles/camera_server.dir/Image.cxx.o" \
"CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o"

# External object files for target camera_server
camera_server_EXTERNAL_OBJECTS =

camera_server: CMakeFiles/camera_server.dir/main.cpp.o
camera_server: CMakeFiles/camera_server.dir/Image.cxx.o
camera_server: CMakeFiles/camera_server.dir/ImagePubSubTypes.cxx.o
camera_server: CMakeFiles/camera_server.dir/build.make
camera_server: /usr/local/lib/libfastrtps.a
camera_server: /usr/local/lib/libfastcdr.a
camera_server: /usr/local/lib/libfoonathan_memory-0.7.3.a
camera_server: /usr/lib/aarch64-linux-gnu/libtinyxml2.so
camera_server: /usr/lib/aarch64-linux-gnu/libtinyxml2.so
camera_server: /usr/lib/aarch64-linux-gnu/libssl.so
camera_server: /usr/lib/aarch64-linux-gnu/libcrypto.so
camera_server: CMakeFiles/camera_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/root/Workspace/AutoLab-SDV-ZCU/Camera_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable camera_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/camera_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/camera_server.dir/build: camera_server
.PHONY : CMakeFiles/camera_server.dir/build

CMakeFiles/camera_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/camera_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/camera_server.dir/clean

CMakeFiles/camera_server.dir/depend:
	cd /root/Workspace/AutoLab-SDV-ZCU/Camera_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Workspace/AutoLab-SDV-ZCU/Camera_server /root/Workspace/AutoLab-SDV-ZCU/Camera_server /root/Workspace/AutoLab-SDV-ZCU/Camera_server/build /root/Workspace/AutoLab-SDV-ZCU/Camera_server/build /root/Workspace/AutoLab-SDV-ZCU/Camera_server/build/CMakeFiles/camera_server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/camera_server.dir/depend

