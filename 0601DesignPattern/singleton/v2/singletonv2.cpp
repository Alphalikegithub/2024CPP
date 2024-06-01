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
        //双重检查锁定虽然只在最外层多了一个if条件判断，但其实是很 妙 的一种做法
        TaskQueue* task = m_taskQ.load();//从原子变量中加载任务队列实例
        if(task == nullptr){
            m_mutex.lock();//如果是多个线程就会阻塞在这把互斥锁上
            task = m_taskQ.load();//重新通过原子变量加载实例对象，方便下一步判空操作
            if(task == nullptr){
                task = new TaskQueue;
                m_taskQ.store(task);//存储
            }
            m_mutex.unlock();
        }
        return task;
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
    //static TaskQueue* m_taskQ;
    static std::mutex m_mutex;//互斥锁
    //原子变量会让计算机在底层按照正确顺序的机器指令去执行程序
    static std::atomic<TaskQueue*> m_taskQ;//原子变量
};
//注意：静态成员变量需要在类外进行初始化
//TaskQueue* TaskQueue::m_taskQ = nullptr;
std::mutex TaskQueue::m_mutex;//虽然m_mutex已经是一个被实例化的对象，但仍然需要在类外声明
std::atomic<TaskQueue*> TaskQueue::m_taskQ ;//虽然不需要初始化，但仍然需要被声明
#endif


int main(int argc,char** argv){
    TaskQueue* obj = TaskQueue::getInstance();
    obj->print();
    return 0;
}