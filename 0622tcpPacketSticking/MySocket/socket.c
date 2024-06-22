#include "socket.h"
#include <stdio.h>

int initSocket()
{
    int lfd = socket(AF_INET,SOCK_STREAM,0);//流式传输协议，0 默认tcp
    if(lfd == -1){
        perror("socket");
        return -1;
    }
    return lfd;
}

void initSockaddr(struct sockaddr *addr, unsigned short port, const char *ip)
{
    struct sockaddr_in* addr_in = (struct sockaddr_in*)addr;//结构体类型转换
    addr_in->sin_family = AF_INET;//地址协议簇
    addr_in->sin_addr.s_addr = inet_addr(ip);
    addr_in->sin_port = htons(port);//主机字节序转网络字节序/大端转小端
}

int setListen(int lfd, unsigned short port)
{
    struct sockaddr addr;
    //调用上面的initSockaddr()函数
    initSockaddr(&addr,port,"0.0.0.0");//"0.0.0.0"等价于INADDR_ANY
    //服务端启动监听和绑定端口号可以放到一个函数中

    //端口复用
    int opt = 1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    //先绑定后监听
    //绑定端口号
    int ret = bind(lfd,&addr,sizeof(addr));
    if(ret == -1){
        perror("bind");
        return -1;
    }
    //设置监听
    int ret = listen(lfd,128);
    if(ret == -1){
        perror("ret");
        return -1;
    }
    
    return 0;
    
}

int acceptConnect(int lfd,struct sockaddr *addr)
{
    int connfd;
    if(addr == NULL){
        connfd = accept(lfd,NULL,NULL);
    }else{
        socklen_t len = sizeof(struct sockaddr);
        connfd = accept(lfd,addr,&len);
    }

    if(connfd == -1){
        perror("accrpt");
        return -1;
    }
    return connfd;
    
}
