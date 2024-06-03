#include <iostream>
#include <mutex>
#include <atomic>

using std::cout;
using std::string;
using std::endl;
#if 0
//饿汉模式 非常的如饥似渴，是一种非常迫切的状态，
//在创建类的时候就把类的静态成员变量创建了出来
class TaskQueue{
public:
    TaskQueue(const TaskQueue& rhs) = delete;//拷贝构造函数
    TaskQueue& operator=(const TaskQueue& rhs) = delete;//赋值运算符函数
    static TaskQueue* getInstance(){
        return m_taskQ;
    }
    //测试能否正确创建单例对象
    void print(){
        cout << "我是一个单例对象的成员函数(饿汉模式)" << endl;
    }
private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& rhs) = default;//拷贝构造函数
    // TaskQueue& operator=(const TaskQueue& rhs) = default;//赋值运算符函数
private:
    static TaskQueue* m_taskQ;
};
//注意：静态成员变量需要在类外进行初始化
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
#endif

#if 1
//懒汉模式 在需要的时候才创建对象
class TaskQueue{
public:
    TaskQueue(const TaskQueue& rhs) = delete;//拷贝构造函数
    TaskQueue& operator=(const TaskQueue& rhs) = delete;//赋值运算符函数
    //静态函数内部只能访问静态成员变量
    static TaskQueue* getInstance(){
        static TaskQueue task;
        return &task;
    }
    //测试能否正确创建单例对象
    void print(){
        cout << "我是一个单例对象的成员函数(懒汉模式)" << endl;
    }
private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& rhs) = default;//拷贝构造函数
    // TaskQueue& operator=(const TaskQueue& rhs) = default;//赋值运算符函数
private:
    
};

#endif


int main(int argc,char** argv){
    TaskQueue* obj = TaskQueue::getInstance();
    obj->print();
    return 0;
}