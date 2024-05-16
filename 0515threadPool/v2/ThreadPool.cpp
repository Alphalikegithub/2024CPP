/* #pragma once
#ifndef _THREADPOOL_H
#define _THREADPOOL_H */

#include <iostream>
#include <pthread.h>
#include "TaskQueue.h"

class ThreadPool
{
public:
    //创建线程池并初始化
    ThreadPool(int min,int max);
    //销毁线程池
    ~ThreadPool();

    //给线程池添加任务的函数
    void addTask(Task task);

    //获取线程池中工作的线程的个数
    int getBusyNum();

    //获取线程池中活着的线程的个数
    int getAliveNum();

private:
    //工作线程
    void * worker(void * arg);
    //管理者线程
    void * manager(void *arg);
    //单个线程退出
    void threadExit();
private:
    TaskQueue* taskQ;        //任务队列
    

    pthread_t managerID; //管理者线程ID
    pthread_t *threadIDs;//工作的线程ID

    int minNum;         //最小线程数
    int maxNum;         //最大线程数
    int busyNum; 
    int liveNum;
    int exitNum;
    pthread_mutex_t mutexPool;//锁整个的线程池
    
    pthread_cond_t notEmpty;  //任务队列是不是空了

    bool shutdown;       //是不是要销毁线程池，销毁为1，不销毁为0
};

/* #endif //_THREADPOOL_H */