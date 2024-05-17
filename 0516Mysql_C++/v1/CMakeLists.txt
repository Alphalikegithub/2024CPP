cmake_minimum_required(VERSION 3.10)

# 在命令行编译的命令：
# g++ main.cpp ConnectionPool.cpp MysqlConnect.cpp ./jsoncpp/jsoncpp.cpp -lpthread -L/www/server/mysql/lib -lmysqlclient  -std=c++11 -o app
# g++ main.cpp ConnectionPool.cpp MysqlConnect.cpp ./jsoncpp/jsoncpp.cpp -lpthread -L/www/server/mysql/lib -lmysqlclient -I/www/server/mysql/include  -std=c++11 -o app

# 设置项目名称
project(MyProject)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加源文件
set(SOURCES
    main.cpp
    ConnectionPool.cpp
    MysqlConnect.cpp
    jsoncpp/jsoncpp.cpp
)

# 添加包含目录
include_directories(
    ${CMAKE_SOURCE_DIR}
    /www/server/mysql/include
)

# 添加库目录
link_directories(
    /www/server/mysql/lib
)

# 指定生成目标
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接库
target_link_libraries(${PROJECT_NAME}
    pthread
    mysqlclient
)
