# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /root/code/2024CPP/0516Mysql_C++/v2_thread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/code/2024CPP/0516Mysql_C++/v2_thread/build

# Include any dependencies generated for this target.
include CMakeFiles/MyProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyProject.dir/flags.make

CMakeFiles/MyProject.dir/main.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/main.cpp.o: ../main.cpp
CMakeFiles/MyProject.dir/main.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/2024CPP/0516Mysql_C++/v2_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyProject.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/main.cpp.o -MF CMakeFiles/MyProject.dir/main.cpp.o.d -o CMakeFiles/MyProject.dir/main.cpp.o -c /root/code/2024CPP/0516Mysql_C++/v2_thread/main.cpp

CMakeFiles/MyProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/2024CPP/0516Mysql_C++/v2_thread/main.cpp > CMakeFiles/MyProject.dir/main.cpp.i

CMakeFiles/MyProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/2024CPP/0516Mysql_C++/v2_thread/main.cpp -o CMakeFiles/MyProject.dir/main.cpp.s

CMakeFiles/MyProject.dir/ConnectionPool.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/ConnectionPool.cpp.o: ../ConnectionPool.cpp
CMakeFiles/MyProject.dir/ConnectionPool.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/2024CPP/0516Mysql_C++/v2_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyProject.dir/ConnectionPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/ConnectionPool.cpp.o -MF CMakeFiles/MyProject.dir/ConnectionPool.cpp.o.d -o CMakeFiles/MyProject.dir/ConnectionPool.cpp.o -c /root/code/2024CPP/0516Mysql_C++/v2_thread/ConnectionPool.cpp

CMakeFiles/MyProject.dir/ConnectionPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/ConnectionPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/2024CPP/0516Mysql_C++/v2_thread/ConnectionPool.cpp > CMakeFiles/MyProject.dir/ConnectionPool.cpp.i

CMakeFiles/MyProject.dir/ConnectionPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/ConnectionPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/2024CPP/0516Mysql_C++/v2_thread/ConnectionPool.cpp -o CMakeFiles/MyProject.dir/ConnectionPool.cpp.s

CMakeFiles/MyProject.dir/MysqlConnect.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/MysqlConnect.cpp.o: ../MysqlConnect.cpp
CMakeFiles/MyProject.dir/MysqlConnect.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/2024CPP/0516Mysql_C++/v2_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyProject.dir/MysqlConnect.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/MysqlConnect.cpp.o -MF CMakeFiles/MyProject.dir/MysqlConnect.cpp.o.d -o CMakeFiles/MyProject.dir/MysqlConnect.cpp.o -c /root/code/2024CPP/0516Mysql_C++/v2_thread/MysqlConnect.cpp

CMakeFiles/MyProject.dir/MysqlConnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/MysqlConnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/2024CPP/0516Mysql_C++/v2_thread/MysqlConnect.cpp > CMakeFiles/MyProject.dir/MysqlConnect.cpp.i

CMakeFiles/MyProject.dir/MysqlConnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/MysqlConnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/2024CPP/0516Mysql_C++/v2_thread/MysqlConnect.cpp -o CMakeFiles/MyProject.dir/MysqlConnect.cpp.s

CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o: ../jsoncpp/jsoncpp.cpp
CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/2024CPP/0516Mysql_C++/v2_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o -MF CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o.d -o CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o -c /root/code/2024CPP/0516Mysql_C++/v2_thread/jsoncpp/jsoncpp.cpp

CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/2024CPP/0516Mysql_C++/v2_thread/jsoncpp/jsoncpp.cpp > CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.i

CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/2024CPP/0516Mysql_C++/v2_thread/jsoncpp/jsoncpp.cpp -o CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.s

# Object files for target MyProject
MyProject_OBJECTS = \
"CMakeFiles/MyProject.dir/main.cpp.o" \
"CMakeFiles/MyProject.dir/ConnectionPool.cpp.o" \
"CMakeFiles/MyProject.dir/MysqlConnect.cpp.o" \
"CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o"

# External object files for target MyProject
MyProject_EXTERNAL_OBJECTS =

MyProject: CMakeFiles/MyProject.dir/main.cpp.o
MyProject: CMakeFiles/MyProject.dir/ConnectionPool.cpp.o
MyProject: CMakeFiles/MyProject.dir/MysqlConnect.cpp.o
MyProject: CMakeFiles/MyProject.dir/jsoncpp/jsoncpp.cpp.o
MyProject: CMakeFiles/MyProject.dir/build.make
MyProject: CMakeFiles/MyProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/code/2024CPP/0516Mysql_C++/v2_thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable MyProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyProject.dir/build: MyProject
.PHONY : CMakeFiles/MyProject.dir/build

CMakeFiles/MyProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyProject.dir/clean

CMakeFiles/MyProject.dir/depend:
	cd /root/code/2024CPP/0516Mysql_C++/v2_thread/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/code/2024CPP/0516Mysql_C++/v2_thread /root/code/2024CPP/0516Mysql_C++/v2_thread /root/code/2024CPP/0516Mysql_C++/v2_thread/build /root/code/2024CPP/0516Mysql_C++/v2_thread/build /root/code/2024CPP/0516Mysql_C++/v2_thread/build/CMakeFiles/MyProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyProject.dir/depend

