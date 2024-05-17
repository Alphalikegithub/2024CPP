#include "MysqlConnect.h"


MysqlConnect::MysqlConnect()
{
    m_conn = mysql_init(nullptr);
}

MysqlConnect::~MysqlConnect()
{
    if(m_conn != nullptr){
        mysql_close(m_conn);
    }
    freeResult();
}

bool MysqlConnect::connect(string user, string passwd, string dbName, string ip, unsigned short port)
{
    MYSQL *ptr = mysql_real_connect(m_conn,ip.c_str(),user.c_str(),passwd.c_str(),dbName.c_str(),port,nullptr,0);
    return ptr != nullptr;//如果不为空就返回true,若为空就返回false
}

bool MysqlConnect::update(string sql)
{
    if(mysql_query(m_conn,sql.c_str())){
        return false;
    }
    return true;
}

bool MysqlConnect::query(string sql)
{
    //清空上次的查询结果
    freeResult();
    if(mysql_query(m_conn,sql.c_str())){
        return false;
    }
    m_result = mysql_store_result(m_conn);
    return true;
}

bool MysqlConnect::next()
{
    if(m_result != nullptr){
        m_row = mysql_fetch_row(m_result);
    }
    return false;
}

string MysqlConnect::value(int index)
{
    //当前的记录里面字段的数量numberOfFields
    int fieldsCount = mysql_num_fields(m_result);
    if(index >= fieldsCount || index < 0){
        return string();
    }
    char * value = m_row[index];
    //得到该字段值的长度
    unsigned long length =  mysql_fetch_lengths(m_result)[index];
    return string(value,length);//把value对应的那块内存中长度为length的数据转换为string类型
}

bool MysqlConnect::transaction()
{
    return mysql_autocommit(m_conn,false);
}

bool MysqlConnect::commit()
{
    return mysql_commit(m_conn);
}

bool MysqlConnect::rollback()
{
    return mysql_rollback(m_conn);
}

void MysqlConnect::refreshAliveTime()
{
    m_aliveTime = std::chrono::steady_clock::now();
}

long long MysqlConnect::getAliveTime()
{
    /* 
    std::chrono::nanoseconds ns(1234567890);
    
    // 获取总的纳秒数
    long long total_ns = ns.count();
    std::cout << "Total nanoseconds: " << total_ns << std::endl;
    
    // 转换为秒
    std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(ns);
    std::cout << "Seconds: " << sec.count() << std::endl;
     */
    std::chrono::nanoseconds ns = std::chrono::steady_clock::now() - m_aliveTime;
    //转换为ms
    std::chrono::milliseconds millsec = std::chrono::duration_cast<std::chrono::milliseconds>(ns);
    //返回这个时间段里面毫秒的数量
    return millsec.count();
}

void MysqlConnect::freeResult()
{
    if(m_result){
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}
