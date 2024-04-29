#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc,char **argv){
    //1.创建套接字
    int listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd < 0){
        perror("socket\n");
        return -1;
    }
    //2.主动发起请求使用connect函数 需要提前知道服务器的ip和port
    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));//初始化结构体数组
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));//atoi()将字符串转换成数字Convert a string to an integer
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(listenfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret < 0){
        perror("connect\n");
        close(listenfd);
        return -1;
    }
    //3.如果connect函数返回值是ok 可以进行数据收发read/write  recv/send
    while(1){
        char buf[128] = {};
        /* 客户端先发后收，服务端正好与之相反 */
        cout << "发送数据给服务器" << endl;
        string line;
        //std::cin >> line; //std::cin >>运算符只会读取单个单词或数字，并在遇到第一个空格或换行符时停止读取
        getline(std::cin,line);
        int len2 = send(listenfd,line.c_str(),line.size(),0);
        //c_str() Return const pointer to contents,(or in C++17 the non-const @c str.data() overload).
        if(len2 < 0){
            cout << "客户端发送出错" << endl;
        }else if(0 == len2){
            cout << "len2 == 0" << endl;
        }else{
            cout << "客户端发送正常" << endl;
        }
        int len = recv(listenfd,buf,sizeof(buf),0);
        if(len < 0){
            cout << "客户端接收数据失败" << endl;
        }else if(0 == len){
            cout << "len == 0" << endl;
            cout << "服务器断开了连接" << endl;
            break;
        }else{
            cout << "recv message from sever:" << buf << endl;
        }
        
    }
    //4.关闭文件描述符
    close(listenfd);
    return 0;
}