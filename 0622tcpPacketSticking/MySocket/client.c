#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>//free()的头文件
#include <unistd.h>//close()的头文件
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
    struct FdInfo *info = (struct FdInfo*)arg;
    while(1){
        char* buffer;
        enum Type t;
        recvMesssage(info->fd,&buffer,&t);
        if(buffer == NULL){
            //如果接收数据失败，可以进行再次的尝试
            continue;
        }
        else
        {
            if(t == Heart)
            {
                printf("心跳包: %s\n", buffer);
                pthread_mutex_lock(&mutex);
                info->count = 0;
                pthread_mutex_unlock(&mutex);
            }
            else
            {
                printf("数据包: %s\n", buffer);
            }
            free(buffer);
        }
    }
    return NULL;
}

//回调函数2
void* HeratBeat(void* arg)
{
    struct FdInfo *info = (struct FdInfo*)arg;
    //1.给服务器发送心跳包数据
    //2.在子线程中检测心跳包数据，看看能否收到服务器回复的数据
    while(1)
    {
        pthread_mutex_lock(&mutex);
        info->count ++;//count = 0的时候，默认没收到服务器回复的心跳包数据
        printf("fd = %d, count = %d\n", info->fd, info->count);
        if(info->count > 5)
        {
            //客户端和服务器断开了连接
            printf("客户端和服务器断开了连接...\n");
            close(info->fd);
            //释放套接字资源，退出客户端程序
            exit(0);
        }
        pthread_mutex_unlock(&mutex);
        sendMessage(info->fd,"hello",5,Heart);
        sleep(3);
    }
    return NULL;
}


int main(){
    //在main 函数中初始化互斥锁
    pthread_mutex_init(&mutex,NULL);

    struct FdInfo info;
    unsigned short port = 8987;
    const char* ip = "127.0.0.1";
    info.fd = initSocket();
    info.count = 0;
    connectToHost(info.fd,port,ip);

    //=创建接收数据的子线程
    pthread_t pid;
    //创建线程
    //该函数的第二个参数是指线程属性，一般情况下，是不需要设置的，第四个参数要放置回调函数中使用什么参数
    pthread_create(&pid,NULL,parseRecvMessage,&info);

    //添加心跳包子线程
    pthread_t pid1;
    pthread_create(&pid1,NULL,HeratBeat,&info);

    //进行数据通信 应该是一个持久的动作
    while(1){
        const char* data = "再次回顾tcp粘包的问题...";
        //发送数据
        //计算字符串的长度需要用到strlen
        sendMessage(info.fd,data,strlen(data),Message);
        sleep(2);//让Message数据每2秒钟发送一次
    }
    //释放子线程资源
    pthread_join(pid,NULL);
    pthread_join(pid1,NULL);
    //释放互斥锁资源
    pthread_mutex_destroy(&mutex);
    
    return 0;
}