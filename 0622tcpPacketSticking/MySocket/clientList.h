#pragma once
#include <stdbool.h>
#include <pthread.h>

//定义链表的结点
struct ClientInfo
{
    int fd;//用于通信的文件描述符
    int count;//用于通信的文件描述符数量
    pthread_t pid;
    struct ClientInfo* next;//后继结点
};

//函数：创建一个链表，带头结点。并返回头结点
struct ClientInfo* createList();
//添加一个节点（头插法），返回这个结点的地址
struct ClientInfo* prependNode(struct ClientInfo* head,int fd);
//删除指定的结点
bool removeNode(struct ClientInfo* head,int fd);
//释放链表资源（销毁链表）
void freeClientList(struct ClientInfo* head);
