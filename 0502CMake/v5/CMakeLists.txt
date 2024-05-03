cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
#file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB SRC  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
message("==========")
#在删除之前，先把SRC中的内容打印出来
message(${SRC})
list(REMOVE_ITEM SRC ${PROJECT_SOURCE_DIR}/src/main.cpp)
message("==========")
message(${SRC})
message("==========")

set(CMAKE_CXX_STANDARD 11)
# 设置动态库生成路径
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(calc SHARED ${SRC})
#add_library(calc STATIC ${SRC})
set(LIBRARY_OUTPUT_PATH /root/code/2024CPP/0502CMake/v2/libary)

set(tmp hello world)
set(tmp1 ${tmp} ${SRC})
message(${tmp})
message(${tmp1})
list(APPEND tmp "xxx1" "sss2" ${SRC})
message(${tmp})
#如何从得到的字符串里面删除其中的一个子字符串