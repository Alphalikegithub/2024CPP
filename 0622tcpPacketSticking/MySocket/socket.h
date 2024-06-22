#pragma once
#include <arpa/inet.h>
//1.创建一个用于通信的套接字
//2.绑定本地的IP和端口号
//3.设置监听
//4.accept等待客户端的连接（若连接成功，则解除阻塞）
//5.开始通信
//6.关闭套接字

//初始化通信套接字
int initSocket();
//初始化Sockaddr结构体
void initSockaddr(struct sockaddr* addr,unsigned short port,const char* ip);
//设置监听
int setListen(int lfd,unsigned short port);
//阻塞等待客户端连接
int acceptConnect(int lfd, struct sockaddr* addr);