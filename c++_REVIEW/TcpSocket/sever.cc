#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


int main()
{
    //1、创建监听的套接字
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("socket");
        return -1;
    }
    //2、绑定本地IP和端口号
    struct  sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY; //0.0.0.0 代表任意的ip地址
    saddr.sin_family = AF_INET;
    int ret = bind(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(-1 == ret)
    {
        perror("bind");
        return -1;
    }
    
    //3、设置监听
    ret = listen(fd,128);
    if(-1 == ret)
    {
        perror("listen");
        return -1;
    }
    //4、阻塞并等待客户端连接
    // struct sockaddr_in caddr;
    // int addrlen = sizeof(caddr);
    // int cfd =accept(fd,(struct sockaddr*)&caddr,&addrlen);
    struct sockaddr_in caddr;
    socklen_t addrlen = sizeof(caddr);
    int cfd = accept(fd, (struct sockaddr*)&caddr, &addrlen);
    if(-1 == cfd)
    {
        perror("accept");
        return -1;
    }

    //连接建立成功，打印客户端的ip+port
    char ip[32];
    printf("客户端IP:%s,端口： %d\n",inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip)),
    ntohs(caddr.sin_port));
    printf("客户端IP:%s,端口：%d\n", inet_ntop(AF_INET, &caddr.sin_addr, ip, sizeof(ip)), ntohs(caddr.sin_port));

    //5、通信
    while(1)
    {
        //接收数据
        char buff[1024];
        int len = recv(cfd,buff,sizeof(buff),0);
        if(len > 0)
        {
            printf("client say : %s\n",buff);
        }
        else if(0 == len)
        {
            printf("客户端断开连接……\n");
            break;
        }
        else{
            perror("recv");
            break;
        }
    }
    //关闭文件描述符
    close(fd);
    close(cfd);
    return 0;
}