#pragma once
#include <queue>
#include <pthread.h>

using callback = void(*)(void *arg);
//任务结构体
struct Task
{
    Task(){
        function = nullptr;
        arg = nullptr;
    }
    Task(callback func,void *arg){
        this->arg = arg;
        function = func;
    }
    callback function;
    void *arg;
};

class TaskQueue
{
private:
    std::queue<Task> m_taskQ;
    pthread_mutex_t m_mutex;
public:
    TaskQueue(/* args */);
    ~TaskQueue();

    //添加任务
    void addTask(Task task);
    //重载函数
    void addTask(callback f,void *arg);
    //取出一个任务
    Task takeTask();
    //获取当前任务的个数
    inline int taskNumber(){
        return m_taskQ.size();
    }

};


