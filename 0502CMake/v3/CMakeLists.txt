cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
#file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(CMAKE_CXX_STANDARD 11)
link_libraries(calc)
link_directories(${CMAKE_SOURCE_DIR}/lib1)
add_executable(app ${SRC_LIST})


