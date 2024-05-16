#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void taskFunc(void *arg){
    int num = *(int *)arg;
    printf("thread %ld is working ,number = %d\n",pthread_self(),num);
    sleep(1);
}

int main(){
    //创建线程池
    ThreadPool pool;
    for(int i = 0;i < 100; ++i){
        //建议创建一块堆内存
        int  * num = (int *)malloc(sizeof(int));
        *num = i + 100;
        threadPoolAdd(pool,taskFunc,num);
    }
    //让主线程睡眠一段时间，保证工作的线程执行完毕
    sleep(30);

    threadPoolDestory(pool);
    return 0;
}
