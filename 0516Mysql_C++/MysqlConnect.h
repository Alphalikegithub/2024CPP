#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include </www/server/mysql/include/mysql.h>
#include <chrono>
/* find / -name mysql.h */




using std::cout;
using std::cin;
using std::endl;
using std::string;
class MysqlConnect
{
private:
    /* data */
public:
    
    
    //初始化数据库连接
    MysqlConnect(/* args */);
    //释放数据库连接
    ~MysqlConnect();
    //连接数据库
    bool connect(string user,string passwd,string dbName,string ip,unsigned short port = 3306);
    //更新数据库 insert update delete
    bool update(string sql);
    //查询数据库
    bool query(string sql);
    //遍历查询得到的结果集
    bool next();
    //得到结果集中的字段值
    string value(int index);
    //事务操作
    bool transaction();
    //事务提交
    bool commit();
    //事务回滚
    bool rollback();
    /* 记录线程空闲时刻的时间点，该时间点可能是线程创建之初的时刻，
    也可能是线程使用完毕后归还到线程池，并重新回归空闲状态的时刻 */
    //刷新数据库连接起始的空闲时间点
    void refreshAliveTime();
    //计算存活的总时长
    long long getAliveTime();

private:
    void freeResult();

    MYSQL *m_conn = nullptr;
    MYSQL_RES *m_result = nullptr;
    MYSQL_ROW m_row = nullptr;//指向结果集中的数据
    std::chrono::steady_clock::time_point m_aliveTime;
    /* 
    std::chrono::steady_clock  决不会调整的单调时钟
    成员类型	 定义
    rep	        表示时钟时长中计次数的算术类型
    period	    表示时钟计次周期的 std::ratio 类型，单位为秒
    duration	std::chrono::duration<rep, period>
    time_point	std::chrono::time_point<std::chrono::steady_clock>
     */
};

