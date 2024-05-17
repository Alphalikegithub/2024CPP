#pragma once
#include <iostream>
#include <queue>
#include <string>
#include <pthread.h>
#include <mutex>
#include <memory> 
#include <condition_variable>
#include "MysqlConnect.h"

using std::cout;
using std::endl;
using std::queue;
using std::string;

class ConnectionPool
{
private:
    //类的构造函数被设置成private,单例模式
    ConnectionPool(/* args */);
    bool parseJsonFile();
    //负责创建新的连接
    void produceConnection();
    //负责销毁连接
    void recycleConnection();
    //添加连接
    void addConnection();
public:
    
    //拷贝构造函数设置为private或=delete
    ConnectionPool(const ConnectionPool& rhs) = delete;
    //移动赋值操作符重载
    ConnectionPool& operator = (const ConnectionPool& rhs) = delete;

    //静态方法 用于访问类对象
    static ConnectionPool*  getConnectionPool(); 
    //获取连接的函数
    std::shared_ptr<MysqlConnect> getConnection();  


private:
    queue<MysqlConnect*> m_connectionQ;

    string m_ip;
    string m_user;
    string m_passwd;
    string m_dbName;
    unsigned short m_port;
    //给数据库连接池设定上下限
    int m_minsize;
    int m_maxsize;
    //超时时长和最大的空闲时长
    int m_timeout;
    int m_maxIdleTime;
    //独占的互斥锁
    std::mutex m_mutexQ;
    std::condition_variable m_cond;
    
};

