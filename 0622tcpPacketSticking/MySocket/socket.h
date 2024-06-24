#pragma once
#include <arpa/inet.h>
#include <stdbool.h>
//1.创建一个用于通信的套接字
//2.绑定本地的IP和端口号
//3.设置监听
//4.accept等待客户端的连接（若连接成功，则解除阻塞）
//5.开始通信
//6.关闭套接字

/* ****数据包类型**** */
enum Type{Heart,Message};
//数据包类型：'H':心跳包,'M':数据块
//数据包格式：数据长度 数据包类型  数据块
//             int      char     char*
//            4字节     1字节     N字节

//初始化通信套接字
int initSocket();
//初始化Sockaddr结构体
void initSockaddr(struct sockaddr* addr,unsigned short port,const char* ip);
//设置监听
int setListen(int lfd,unsigned short port);
//阻塞等待客户端连接
int acceptConnect(int lfd, struct sockaddr* addr);

//客户端连接到服务器
void connectToHost(int fd,unsigned short port,const char* ip);//fd客户端通信套接字

//读取数据
int readn(int fd,char* buffer,int size);
//写入数据
int writen(int fd,const char* buffer,int length);



bool sendMessage(int fd,const char* buffer,int length,enum Type t);
//char** buffer 指向一级指针的char* buffer地址
//enum Type* t 指向枚举类型变量的地址
int readMesssge(int fd,char** buffer,enum Type* t);