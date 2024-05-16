#pragma once
#include <queue>
#include <pthread.h>
#include <stdio.h>

using callback = void(*)(void *arg);
//任务结构体
template <typename T>
struct Task
{
    Task<T>(){
        function = nullptr;
        arg = nullptr;
    }
    Task<T>(callback func,void *arg){
        this->arg = (T*)arg;
        function = func;
    }
    callback function;
    T *arg;
};

template <typename T>
class TaskQueue
{
private:
    std::queue<Task<T>> m_taskQ;
    pthread_mutex_t m_mutex;
public:
    TaskQueue(/* args */);
    ~TaskQueue();

    //添加任务
    void addTask(Task<T> task);
    //重载函数
    void addTask(callback f,void *arg);
    //取出一个任务
    Task<T> takeTask();
    //获取当前任务的个数
    inline size_t taskNumber(){
        return m_taskQ.size();
    }

};


