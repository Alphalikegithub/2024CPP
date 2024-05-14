#include "Thread.h"

/**
 * Thread implementation
 */
Thread::Thread() 
:_thid(0)
,_isRunning(false)
{

}

Thread::~Thread() {
    if(_isRunning){
        //让子线程与主线程分离，主线程不负责子线程的回收
        pthread_detach(_thid);
        _isRunning = false;
    }
}

/**
 * @return void
 */
void Thread::start() {
    int ret = pthread_create(&_thid,nullptr,threadFunc,this);//第四个参数把this指针交给threadFunc函数
    if(ret){
        perror("pthread_create\n");
        return;
    }
    
    _isRunning = true;
}

/**
 * @return void
 */
void Thread::join() {
    if(_isRunning){
        int ret = pthread_join(_thid,nullptr);
        if(ret){
            perror("pthread_join\n");
            return;
        }  
        _isRunning = true;
    }
    
}
    
    

/**
 * @param void *
 * @return void *
 */
void * Thread::threadFunc(void *arg) {
    /**
     * 因为threadFunc()已经是静态函数了，没有this指针
     * 需要通过参数argc把Thread类的this指针传递进来，这样的话Thread类对象就可以正常调用run()方法
     */
    Thread *pthread = static_cast<Thread *>(arg);
    if(pthread){
        pthread->run();//这里体现出多态(基类的指针指向派生类对象,执行派生类的纯虚函数run())
    }
    pthread_exit(nullptr);//让子线程主动退出
}

/**
 * @return void
 */
void Thread::run() {
    return;
}