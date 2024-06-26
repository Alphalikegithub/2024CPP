#include "socket.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>//memcpy()的头文件
#include <stdlib.h>//free()的头文件
#include <unistd.h>

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
    int ret1 = bind(lfd,&addr,sizeof(addr));
    if(ret1 == -1){
        perror("bind");
        return -1;
    }
    //设置监听
    int ret2 = listen(lfd,128);
    if(ret2 == -1){
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

int connectToHost(int fd, unsigned short port, const char *ip)
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
    while(left)
    {
        readBytes = read(fd,ptr,left);
        if(readBytes == -1)
        {
            if(errno == EINTR)
            {
                readBytes = 0;
            }
            else
            {
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

bool sendMessage(int fd, const char *buffer, int length, enum Type t)
{
    //待发送的数据占用的存储空间有多大呢？
    //dataLen = length(数据长度) + 1(enum Type类型占用1字节) + sizeof(int) (4字节的数据头)
    int dataLen = length + 1 + sizeof(int);
    //申请堆内存
    char* data  = (char*)malloc(dataLen);
    if(data == NULL){
        return false;
    }
    //在发送数据是需要转换为网络字节序
    int netlen = htonl(length + 1);
    memcpy(data,&netlen,sizeof(int));
    char* ch = t == Heart ? "H" : "M";
    memcpy(data + sizeof(int),ch,sizeof(char));//data + sizeof(int)是为了让指针向后偏移sizeof(int)个字节
    //data + sizeof(int) + 1此时+1是指，让指针向后偏移enum Type个字节，从而让指针指向数据缓冲区
    memcpy(data + sizeof(int) + 1,buffer,length);

    int ret = writen(fd,data,dataLen);
    free(data);
    return ret == dataLen;
}

int recvMesssage(int fd, char **buffer, enum Type *t)
{
    int dataLen = 0;
    int ret = readn(fd,(char*)&dataLen,sizeof(int));
    if(ret == -1)
    {
        *buffer = NULL;
        return -1;
    }
    dataLen = ntohl(dataLen);
    char ch ;
    readn(fd,&ch,1);
    *t = ch == 'H' ? Heart : Message;
    char* tempbuf = (char*)calloc(dataLen,sizeof(char));//为enum Type类型申请空间
    if(tempbuf == NULL)
    {
        *buffer = NULL;
        return -1;
    }
    ret = readn(fd,tempbuf,dataLen -1);//这里-1是要去掉enum Type占用的字节数
    if(ret != dataLen -1){
        free(tempbuf);
        *buffer = NULL;
        return -1;
    }
    *buffer = tempbuf;
    return ret;
}