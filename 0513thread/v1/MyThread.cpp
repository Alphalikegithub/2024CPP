#include "Thread.h"
#include <unistd.h>
#include <memory>

/**
 * MyThread implementation
 */

class MyThread: public Thread {
private: 
    void run() override;
};


/**
 * @return void
 */
void MyThread::run() {
    //run()方法中具体实现逻辑可以自行实现
    while(1){
        std::cout << "MyThread is Running..." << std::endl;
        sleep(1);
    }
    
    /* for (size_t i = 0; i < 5; i++)
    {
        std::cout << "MyThread is Running..." << std::endl;
    } */
    
}

int main(int argc,char **argv){
    MyThread myThread;
    /* myThread.start();
    myThread.run();
    myThread.join(); */

    // Thread *pth = new MyThread();
    std::unique_ptr<Thread> pth(new MyThread());//用基类指针指向派生类对象
    /**
     * 因为派生类构造函数没有实现，所以会自动去执行基类的构造函数,初始化_thid和_isRunning
     * 
     */
    pth->start();
    pth->join();
    return 0;
}
