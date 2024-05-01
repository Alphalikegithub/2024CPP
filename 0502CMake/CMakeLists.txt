cmake_minimum_required(VERSION 3.21)
project(test)
add_executable(app add.cpp sub.cpp multi.cpp div.cpp main.cpp)
set(CMAKE_CXX_STANDARD 11)
