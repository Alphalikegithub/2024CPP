#pragma once
#ifndef _FINALTHREADPOOL_H
#define _FINALTHREADPOOL_H

#include <iostream>
#include <pthread.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include "TaskQueue.h"
#include "TaskQueue.cpp"

template <typename T>
class ThreadPool
{
public:
    ThreadPool(int min,int max);
    ~ThreadPool();
    void addTask(Task<int> task);
    int getBusyNum();
    int getAliveNum();

private:
    static void * worker(void * arg);
    static void * manager(void *arg);
    void threadExit();

private:
    TaskQueue<T>* taskQ;
    pthread_t managerID;
    pthread_t *threadIDs;
    int minNum;
    int maxNum;
    int busyNum; 
    int liveNum;
    int exitNum;
    pthread_mutex_t mutexPool;
    pthread_cond_t notEmpty;
    bool shutdown;
    static const int NUMBER = 2;
};

#endif //_FINALTHREADPOOL_H
