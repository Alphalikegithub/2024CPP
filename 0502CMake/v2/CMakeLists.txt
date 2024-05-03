cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
#file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(CMAKE_CXX_STANDARD 11)
# 设置动态库生成路径
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# add_library(calc SHARED ${SRC_LIST})
add_library(calc STATIC ${SRC_LIST})
set(LIBRARY_OUTPUT_PATH /root/code/2024CPP/0502CMake/v2/libary)

