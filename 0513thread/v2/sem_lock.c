#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
/* 资源总数为1的时候可以不用加互斥锁 */
//生产者的信号量
sem_t semp;
//消费者的信号量
sem_t semc;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 初始化互斥锁
pthread_mutex_t mutex;

// 链表的节点类型
struct Node
{
    int number;
    struct Node* next;  
};

// 链表头节点
struct Node *head = NULL;

/* 生产者 */
void *producer(void *arg){
    while(1){
        
        sem_wait(&semp);
        pthread_mutex_lock(&mutex);
        // 创建新节点
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        // 初始化节点
        newNode->number = rand() % 1000; // 获取一个1000以内的随机值
        newNode->next = head; // 往头节点之前插入数据
        head = newNode;
        printf("生产者, id: %ld, number: %d\n", pthread_self(), newNode->number);
        pthread_mutex_unlock(&mutex);
        sem_post(&semc);
        // 生产者生成出新的产品后就唤醒消费者进程
        
        sleep(rand() % 3);
    }
    return NULL;
}

/* 消费者 */
void *consumer(void *arg){
    while(1){
        
        sem_wait(&semc);
        pthread_mutex_lock(&mutex);
        // 从链表的头部取出一个指针
        struct Node *node = head;
        printf("消费者, id: %ld, number: %d\n", pthread_self(), node->number);
        // 把头节点从链表中删除掉，再移动头节点到后面一个位置
        head = head->next;
        free(node);
        pthread_mutex_unlock(&mutex);
        sem_post(&semp);
        
        sleep(rand() % 3);
        // 如果链表中的节点全部被取出需要做进一步操作，不能取空节点
        
    }
    return NULL;

}

int main(int argc, const char* argv[])
{
    //生产者
    sem_init(&semp,0,5);//资源数量修改为5,此时需要做线程同步
    //消费者--->资源数量初始化为0 ,消费者线程一启动就阻塞了
    sem_init(&semc,0,0);
    pthread_mutex_init(&mutex,NULL);
    pthread_t p1[5], p2[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&p1[i], NULL, producer, NULL);
    }
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&p2[i], NULL, consumer, NULL);
    }
    // 线程阻塞 等待子线程结束
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(p1[i], NULL);
    }
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(p2[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&semc);
    sem_destroy(&semp);
    return 0;
}
