#include <iostream>
#include <memory>
#include "MysqlConnect.h"
#include "ConnectionPool.h"

using std::cout;
using std::cin;
using std::endl;

int query(){
    MysqlConnect conn;
    conn.connect("root","9c57029624e3768a","testdb","127.0.0.1");
    //string sql = "insert into person values(5,24,'man','david')";
    //string sql = "insert into person values(6,25,'woman','lisa')";
    //string sql = "insert into person values(7,26,'man','baoqiang')";
    string sql = "insert into person values(8,27,'man','xiaoniao')";
    bool flag = conn.update(sql);
    cout << "flag value:" << flag << endl;

    sql = "select * from person";
    conn.query(sql);
    while(conn.next()){
        cout << conn.value(0) << ","
             << conn.value(1) << ","
             << conn.value(2) << ","
             << conn.value(3) << endl;

    }
    return 0;
}

int main(int argc, char** argv){ // 注意参数类型应该是 char** 而不是 void**  
    int result = query(); // 调用query函数  
    return result; // 返回query函数的返回值  
}