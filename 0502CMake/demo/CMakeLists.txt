cmake_minimum_required(VERSION 3.5)

project(test)

#定义变量
#静态库生成路径
set(LIBPATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
#测试程序生成路径
set(EXECPATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#头文件目录
set(HEADPATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
#静态库的名字
set(CALCLIB calc)
set(SORTLIB sort)
#可执行程序的名字
set(APPNAME1 app1)
set(APPNAME2 app2)
#添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)

#根节点对应的文件中主要做了两件事情：定义全局变量和添加子目录


