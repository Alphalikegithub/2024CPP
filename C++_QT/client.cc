#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sstream>
#include <string>
 
using std::cout;
using std::endl;
int main()
{
    //第一步 创建通信套接字
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    // inet_pton(AF_INET,"192.168.138.128",&saddr.sin_addr.s_addr);
    inet_pton(AF_INET,"127.0.0.1",&saddr.sin_addr.s_addr);
    //第二步
    
    int ret = connect(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret == -1)
    {
        perror("connect");
        return -1;
    }
   int number = 0;
    //3.通信
    while (1)
    {
        //接收数据
        char buff[1024];
        // std::ostringstream oss;
        // oss << "你好,这是我用C++写的网络通信" << number ++;
        // std::string str = oss.str();
        // const char* buff = str.c_str();
        // send(fd,buff,sizeof(buff)+1,0);

        // memset(buff,0,sizeof(buff));

        #if 1
        std::ostringstream oss;
        oss << "这是我用C++写的网络通信...这简直是太不可思议了 " << number++;
        std::string str = oss.str();

        // 使用 c_str() 获取字符串的C风格表示并发送
        send(fd, str.c_str(), str.length(), 0);

        memset(buff, 0, sizeof(buff));
        #endif
        // sprintf(buff, "这是我用C++写的网络通信...这简直是太不可思议了 %d \n", number++);
        // send(fd,buff,sizeof(buff)+1,0);

        // memset(buff,0,sizeof(buff));
        int len = recv(fd,buff,sizeof(buff),0);
        if(len > 0)
        {
            cout << "服务器说" << buff << endl;
            
        }
        else if (len == 0)
        {
            cout << "服务器断开了连接" << endl;
            break;
        }
        else{
            perror("recv");
            break;
        }
        sleep(1);//让客户端发数据发的慢一点 
    }
    //第六步 关闭文件描述符
    close(fd);
    
    
    return 0;
}