#include "socket.h"
#include <stdio.h>
#include <errno.h>

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

void connectToHost(int fd, unsigned short port, const char *ip)
{
    //声明/创建结构体
    struct sockaddr addr;
    //初始化结构体
    initSockaddr(&addr ,port,ip); 
    int ret = connect(fd,&addr,sizeof(addr));
    if(ret == -1){
        perror("connect");
        return -1;
    }
    return 0;
}

int readn(int fd, char *buffer, int size)
{
    int left = size;
    int readBytes = 0;
    char* ptr = buffer;
    while(left){
        readBytes = read(fd,ptr,left);
        if(readBytes == -1){
            if(errno == EINTR){
                readBytes = 0;
            }else{
                perror("read");
                return -1;
            }
        }
        else if(readBytes == 0)//多加一个分支判断、
        {
            printf("对方主动断开了连接...\n");
            return -1;
        }
        left -= readBytes;
        ptr += readBytes;
    }
    return size - left;
}

int writen(int fd,const char *buffer, int length)//此时写缓冲区必须要用const限定修饰符
{
    int left = length;
    int writeBytes = 0;
    const char* ptr = buffer;//用一个指针可以记录，缓冲区哪些数据已被获取，哪些待获取
    while(left)//当left不为空时
    {
        writeBytes = write(fd,ptr,left);
        if(writeBytes <= 0){
            if(errno == EINTR){
                writeBytes = 0;
            }else{
                perror("write");
                return -1;
            }
        }
        ptr += writeBytes;
        left -= writeBytes;//移动指针的位置
    }
    return length;
}
