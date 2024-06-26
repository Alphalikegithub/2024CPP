#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>//free()的头文件
#include <unistd.h>//close(),sleep()的头文件
#include "clientList.h"
#include "socket.h"
//添加一把互斥锁
pthread_mutex_t mutex;

//fd和count是两个线程共享的资源，用结构体封装起来
struct FdInfo{
    int fd;
    int count;//已经没有收到count次服务器回复的心跳包数据了
};
//回调函数
void* parseRecvMessage(void* arg){
    //arg参数是通过pthread_create中的第四个参数传递的
    // int fd = *(int*)arg;
    struct ClientInfo* info = (struct ClientInfo*)arg;
    while(1)
    {
        char* buffer;
        enum Type t;
        int len = recvMesssage(info->fd,&buffer,&t);
        if(buffer == NULL)
        {
            printf("fd = %d,通信的子线程退出了...",info->fd);
            pthread_exit(NULL);
        }
        else
        {
            if(t == Heart)
            {
                printf("心跳包: %s\n",buffer);
                pthread_mutex_lock(&mutex);
                info->count = 0;
                pthread_mutex_unlock(&mutex);
                //再给客户端回复一条数据（客户端发过来什么，服务端就回复同样的信息）
                sendMessage(info->fd,buffer,len,Heart);
            }
            else
            {
                const char* ptr = "今天中午吃什么？";
                printf("数据包: %s\n",buffer);
                sendMessage(info->fd,ptr,strlen(ptr),Heart);
            }
            free(buffer);
        }
    }
    return NULL;
}

//回调函数2
void* HeratBeat(void* arg)
{
    struct ClientInfo* head = (struct ClientInfo*)arg;
    struct ClientInfo* p = NULL;
    while(1)
    {
        p = head->next;
        while(p)
        {
            //加锁和解锁是针对共享资源count
            pthread_mutex_lock(&mutex);
            p->count ++;//count = 0的时候，默认没收到客户端回复的心跳包数据
            if(p->count > 5)
            {
                //服务器和客户端断开了连接
                printf("服务器和客户端断开了连接...\n");
                close(p->fd);
                //释放套接字资源，退出服务端程序
                //在使用pthread_cancel函数时，需指定要退出的子线程的线程ID，
                //该子线程在遇到一个系统调用时就立马退出，如果没有用到系统调用就不会立即退出
                pthread_cancel(p->pid);
                removeNode(head,p->pid);
            }
            pthread_mutex_unlock(&mutex);
            p = p->next;
        }
    
        sleep(3);
    }
    return NULL;
}


int main(){
    //设置监听
    unsigned short port = 8989;
    int lfd = initSocket();
    setListen(lfd,port);

    //创建一个链表
    struct ClientInfo* head = createList();

    pthread_mutex_init(&mutex,NULL);
    
    //添加心跳包子线程
    pthread_t pid1;
    pthread_create(&pid1,NULL,HeratBeat,head);

    //服务器段的通信套接字数量取决于等待连接的客户端的数量
    while(1)
    {
        int sockfd = acceptConnect(lfd,NULL);
        if(sockfd = -1)
        {
            continue;
        }
        struct ClientInfo* node = prependNode(head,sockfd);
        //创建接收数据的子线程
        pthread_t pid;
        //该函数的第二个参数是指线程属性，一般情况下，是不需要设置的，第四个参数要放置回调函数中使用什么参数
        pthread_create(&node->pid,NULL,parseRecvMessage,node);
        //主线程和子线程分离
        pthread_detach(node->pid);
        /* 注意：什么时候用&pid，什么时候用pid,要看清函数的参数 */

    }
    pthread_join(pid1,NULL);
    //释放互斥锁资源
    pthread_mutex_destroy(&mutex);
    close(lfd);
    
    return 0;
}