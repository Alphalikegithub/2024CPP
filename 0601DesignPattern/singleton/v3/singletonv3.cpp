#include <iostream>
#include <mutex>
#include <atomic>
#include <queue>
#include <thread>


using std::cout;
using std::string;
using std::endl;


#if 1
//饿汉模式 在一开始的时候就创建好对象
class TaskQueue{
public:
    TaskQueue(const TaskQueue& rhs) = delete;//拷贝构造函数
    TaskQueue& operator=(const TaskQueue& rhs) = delete;//赋值运算符函数
    //静态函数内部只能访问静态成员变量
    static TaskQueue* getInstance(){
        return m_taskQ;
    }
    //测试能否正确创建单例对象
    void print(){
        cout << "我是一个单例对象的成员函数(懒汉模式)" << endl;
    }
    //判断任务队列是否为空
    bool isEmpty(){
        std::lock_guard<std::mutex> locker(m_mutex);//互斥锁 可以避免忘记释放unlock锁
        bool flag = m_data.empty();
        // if(flag){
        //     return true;
        // }
        // return false;
        return flag;
    }
    //添加任务
    void addTask(int node){
        std::lock_guard<std::mutex> locker(m_mutex);//互斥锁 可以避免忘记释放unlock锁
        m_data.push(node);
    }
    //删除任务
    bool popTask(){
        std::lock_guard<std::mutex> locker(m_mutex);
        if(m_data.empty()){
            return false;
        }
        m_data.pop();
        return true;
    }
    //取出一个任务（不删除任务）
    int takeTask(){
        std::lock_guard<std::mutex> locker(m_mutex);
        if(m_data.empty()){
            return -1;
        }
        int data = m_data.front();
        return data;
    }
private:
    TaskQueue() = default;
    // TaskQueue(const TaskQueue& rhs) = default;//拷贝构造函数
    // TaskQueue& operator=(const TaskQueue& rhs) = default;//赋值运算符函数
private:
    static TaskQueue* m_taskQ;
    std::mutex m_mutex;
    std::queue<int> m_data;
};
TaskQueue* TaskQueue::m_taskQ = new TaskQueue;
// std::mutex TaskQueue::m_mutex;//声明
#endif


int main(int argc,char** argv){
    TaskQueue* taskQ = TaskQueue::getInstance();
    std::thread t1([=](){
        for (size_t i = 0; i < 10; ++i)
        {
            /* code */
            taskQ->addTask(i + 10);
            cout << "+++ push data" << i + 10 <<",threadId:" <<
                    std::this_thread::get_id() << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });
    std::thread t2([=](){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        while(!taskQ->isEmpty()){
            int num = taskQ->takeTask();
            cout << "+++ take data" << num<<",threadId:" <<
                    std::this_thread::get_id() << endl;
            taskQ->popTask();
            //设置消费者线程休眠时间大于生产者线程，可以让生产者多生产一会
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    });
    //让主线程阻塞等待
    t1.join();
    t2.join();
    
    
    return 0;
}