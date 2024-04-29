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
    //2.bind 绑定IP和端口号(服务器端的)
    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));//初始化结构体数组
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));//atoi()将字符串转换成数字Convert a string to an integer
    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = bind(listenfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret < 0){
        perror("bind\n");
        close(listenfd);
        return -1;
    }
    //3.listen 让服务器处于监听状态
    cout << "sever is listening ..." << endl;
    int ret1 = listen(listenfd,128);
    if(ret1 < 0){
        perror("listen\n");
        close(listenfd);
        return -1;
    }
    //4.accept 阻塞等待客户端的连接
#if 0
    struct sockaddr_in caddr;
    memset(&caddr,0,sizeof(caddr));
    caddr.sin_family = AF_INET;
    socklen_t length = sizeof(caddr);
    accept(listenfd,(struct sockaddr*)&caddr,&length);
#endif
    int cfd = accept(listenfd,nullptr,nullptr);
    if(cfd < 0){
        perror("accept\n");
        close(listenfd);
        return -1;
    }
    //5.进行通信 read/write 或者recv/send
    while(1){
        char buf[128] = {};
        int len = recv(cfd,buf,sizeof(buf),0);
        if(len < 0){
            cout << "服务器接收数据失败" << endl;
        }else if(0 == len){
            cout << "len == 0" << endl;
        }else{
            cout << "recv message from client:" << buf << endl;
        }
        cout << "我还想发送数据给客户端" << endl;
        string line;
        //std::cin >> line;
        /* 
        std::getline函数将读取整行文本，包括空格和换行符。
        std::cin >>运算符只会读取单个单词或数字，并在遇到第一个空格或换行符时停止读取 
        */
        getline(std::cin,line);
        int len2 = send(cfd,line.c_str(),line.size(),0);
        //c_str() Return const pointer to contents,(or in C++17 the non-const @c str.data() overload).
        if(len2 < 0){
            cout << "服务器发送出错" << endl;
        }else if(0 == len2){
            cout << "len2 == 0" << endl;
        }else{
            cout << "服务器发送正常" << endl;
        }
    }
    //6.关闭对应的文件描述符
    close(listenfd);
    close(cfd);
    return 0;
}