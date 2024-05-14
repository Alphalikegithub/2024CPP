#ifndef _THREAD_H
#define _THREAD_H

#include <iostream>
#include <pthread.h>
#include <stdio.h>


class Thread {
public: 
    Thread();
    virtual  ~Thread();
    void start();
    void join();
    
private: 
    pthread_t _thid;//线程id
    bool _isRunning;
    
    /**
     * 线程入口函数
     * @param void *
     */
    static void  *threadFunc(void *);//为了消除this指针
    //现成的执行任务
    virtual void run() = 0;
};

#endif //_THREAD_H