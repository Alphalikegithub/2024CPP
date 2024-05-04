cmake_minimum_required(VERSION 3.5)

project(SORTTEST)
aux_source_directory(./ SRC)
include_directories(${HEADPATH})
set(EXECUTABLE_OUTPUT_PATH ${EXECPATH})
link_directories(${LIBPATH})
add_executable(${APPNAME2} ${SRC})
target_link_libraries(${APPNAME2} ${SORTLIB})
