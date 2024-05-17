#include "ConnectionPool.h"
#include "./jsoncpp/json.h"
#include <fstream>
#include <thread>
#include <algorithm>
#include <chrono>


using namespace Json;
using std::ifstream;

ConnectionPool::ConnectionPool(/* args */)
{
    //加载配置文件
    if(!parseJsonFile()){
        return;
    }
    for (size_t i = 0; i < m_minsize; ++i){
        addConnection();
    }
    //创建两个线程，一个负责创建新的连接，另一个负责销毁连接
    std::thread producer(&ConnectionPool::produceConnection,this);
    std::thread recycle(&ConnectionPool::recycleConnection,this);
    /* detach是使主线程不用等待子线程可以继续往下执行，但即使主线程终止了，子线程也不一定终止 */
    producer.detach();
    recycle.detach();
}

bool ConnectionPool::parseJsonFile()
{
    //读文件
    ifstream ifs("dbconf.json");
    Reader rd;
    Value root;
    rd.parse(ifs,root);//第一个参数是文件流对象，第二个参数是传出参数Value值
    //判断是否为Json对象
    if(root.isObject()){
        m_ip = root["ip"].asString();
        m_user = root["userName"].asString();
        m_passwd= root["password"].asString();
        m_port = root["port"].asInt();
        m_dbName = root["dbName"].asString();
        m_minsize = root["minsize"].asInt();
        m_maxsize = root["maxsize"].asInt();
        m_timeout = root["timeout"].asInt();
        m_maxIdleTime = root["maxIdleTime"].asInt();

        return true;
    }
    return false;
}

void ConnectionPool::produceConnection()
{
    while(true){
        std::unique_lock<std::mutex> locker(m_mutexQ);
        while(m_connectionQ.size() >= m_maxsize){
            m_cond.wait(locker);
        }
        addConnection();
        //通过条件变量唤醒对应的生产函数
        m_cond.notify_all();
    }
}

// void ConnectionPool::recycleConnection()
// {
//     /* recycleConnection() 方法有一个无限循环，但缺乏正确的退出条件。它应该继续回收连接，但也要考虑优雅地退出的条件 */
//     while(true){
//         //休眠一定的时长
//         std::this_thread::sleep_for(std::chrono::milliseconds(500));
//         //由locker对象来维护互斥锁的加锁和解锁操作
//         //std::unique_lock<std::mutex> locker(m_mutexQ);
//         std::lock_guard<std::mutex> locker(m_mutexQ);
//         while(m_connectionQ.size() > m_minsize){
//             MysqlConnect* conn = m_connectionQ.front();
//             if(conn->getAliveTime() >= m_maxIdleTime){
//                 m_connectionQ.pop();
//                 delete conn;
//             }
//             else{
//                 break;
//             }
//         }
//     }
// }

void ConnectionPool::recycleConnection() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        {
            std::lock_guard<std::mutex> locker(m_mutexQ);
            while (!m_connectionQ.empty()) {
                MysqlConnect* conn = m_connectionQ.front();
                if (conn->getAliveTime() >= m_maxIdleTime) {
                    m_connectionQ.pop();
                    delete conn;
                } else {
                    break;
                }
            }
        }
    }
}

void ConnectionPool::addConnection()
{
    MysqlConnect* conn = new MysqlConnect;
    conn->connect(m_user,m_passwd,m_dbName,m_ip,m_port);
    //当数据库连接成功之后记录这个时间戳
    conn->refreshAliveTime();
    //入队
    m_connectionQ.push(conn);
}

ConnectionPool::~ConnectionPool()
{
    if(!m_connectionQ.empty()){
        MysqlConnect* conn = m_connectionQ.front();
        m_connectionQ.pop();
        delete conn;
    }
}

ConnectionPool *ConnectionPool::getConnectionPool()
{
    static ConnectionPool pool;
    return &pool;
}

//通过智能指针实现数据库连接回收的功能
// std::shared_ptr<MysqlConnect> ConnectionPool::getConnection()
// {
//     //互斥锁
//     std::unique_lock<std::mutex> locker(m_mutexQ);
//     while(m_connectionQ.empty()){
//         if(std::cv_status::timeout == m_cond.wait_for(locker,std::chrono::milliseconds(m_timeout))){
//             //说明任务队列依旧为空
//             if(m_connectionQ.empty()){
//                 //return nullptr
//                 continue;//跳过本次循环 执行下一次循环
//             }
//         }
//     }
//     //std::shared_ptr<MysqlConnect>共享的智能指针
//     std::shared_ptr<MysqlConnect> conn_ptr(m_connectionQ.front(),[this](MysqlConnect* conn){
//         //m_mutexQ.lock();
//         std::lock_guard<std::mutex> locker(m_mutexQ);
//         conn->refreshAliveTime();
//         m_connectionQ.push(conn);
//     });
//     m_connectionQ.pop();
//     m_cond.notify_all();
//     return conn_ptr;
// }

std::shared_ptr<MysqlConnect> ConnectionPool::getConnection() {
    std::unique_lock<std::mutex> locker(m_mutexQ);
    if (m_connectionQ.empty()) {
        if (m_cond.wait_for(locker, std::chrono::milliseconds(m_timeout)) == std::cv_status::timeout) {
            // 超时到达，返回 nullptr 或抛出异常
            return nullptr;
        }
    }
    std::shared_ptr<MysqlConnect> conn_ptr(m_connectionQ.front(), [this](MysqlConnect* conn) {
        std::lock_guard<std::mutex> locker(m_mutexQ);
        conn->refreshAliveTime();
        m_connectionQ.push(conn);
    });
    m_connectionQ.pop();
    m_cond.notify_all();
    return conn_ptr;
}
