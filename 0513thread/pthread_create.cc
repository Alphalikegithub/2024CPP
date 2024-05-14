#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::cerr;

#define ERROR_CHECK(msg,ret) \
    do{ \
        printf("%s %s\n",msg,strerror(ret)); \
    }while(0);


void *threadFunc(void *arg){
    usleep(10);
    int *pInt = (int *)arg;//(void *arg)强转到(int *)
    printf("I am a child thread,%d\n",*pInt);
    
    //线程主动退出
    pthread_exit(nullptr);
}
/* 
main线程是主线程，主线程执行完毕后，子线程有可能还没来得及执行，所以
一般都需要让主线程等待子线程执行完毕后再退出
 */
int main(int argc,char **argv){
    pthread_t threadId;
    int number = 10;
    int ret = pthread_create(&threadId,nullptr,threadFunc,(void *)&number);//把第四个参数带到线程入口函数threadFunc中
    ERROR_CHECK("pthread_create",ret);
    /* if(ret){
        printf("pthread create: %s\n",strerror(ret));//返回值(ret)是1的时候error，ret = 0---->success
        
    } */
    // usleep(100);

    //线程取消
    int ret1 = pthread_cancel(threadId);
    ERROR_CHECK("pthread_cancel",ret1 );
    //让主线程等待子线程退出
    pthread_join(threadId,nullptr);
    // delete--pthread_self();
    ERROR_CHECK("pthread_join",ret);
    printf("I am a main thread\n");

    /* //如果想让主线程不去等待或者回收子线程，那么可以将子线程设置为分离状态
    int pthread_detach(pthread_t __th); */
    
    return 0;
}