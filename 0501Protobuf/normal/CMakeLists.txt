cmake_minimum_required(VERSION 3.0)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})

add_executable(test MyTest.cpp Person.pb.cc main.cpp)
target_link_libraries(test ${PROTOBUF_LIBRARIES} pthread)
