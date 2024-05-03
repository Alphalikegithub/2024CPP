cmake_minimum_required(VERSION 3.21)
project(test)
#set(SRC add.cpp sub.cpp multi.cpp div.cpp main.cpp)
#第一种搜索文件路径的方式
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
#第二种搜索文件路径的方式（递归搜索）
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH /root/code/2024CPP/0502CMake/v1/aa/bb/cc)
set(CMAKE_CXX_STANDARD 11)
add_executable(pp ${SRC})