#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

using std::cout;
using std::endl;
int main()
{
    //第一步
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    //第二步
    saddr.sin_addr.s_addr = INADDR_ANY;//绑定本地任意的IP地址
    int ret = bind(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }
    //第三步 设置监听
    ret = listen(fd,128);
    if(ret == -1)
    {
        perror("listen");
        return -1; 
    }
    //第四步 阻塞并等待客户端的连接
    struct sockaddr_in caddr;
    socklen_t addrlen = sizeof(caddr); // 修改为 socklen_t 类型
    int cfd = accept(fd, (struct sockaddr*)&caddr, &addrlen);
    char ip[32];
    cout << "客户端地址" << inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip)) 
         << "客户端端口号" << ntohs(caddr.sin_port) << endl;

    while (1)
    {
        //接收数据
        char buff[1024];
        int len = recv(cfd,buff,sizeof(buff),0);
        if(len > 0)
        {
            cout << "客户端说" << buff << endl;
            send(cfd,buff,len,0);
        }
        else if (len == 0)
        {
            cout << "客户端断开了连接" << endl;
            break;
        }
        else{
            perror("recv");
            break;
        }
        
    }
    //第六步 关闭文件描述符
    close(fd);
    close(cfd);
    
    return 0;
}