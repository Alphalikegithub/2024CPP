#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // 初始化条件变量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 初始化互斥锁

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
        pthread_mutex_lock(&mutex);
        // 创建新节点
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        // 初始化节点
        newNode->number = rand() % 1000; // 获取一个1000以内的随机值
        newNode->next = head; // 往头节点之前插入数据
        head = newNode;
        printf("生产者, id: %ld, number: %d\n", pthread_self(), newNode->number);
        pthread_mutex_unlock(&mutex);
        // 生产者生成出新的产品后就唤醒消费者进程
        pthread_cond_signal(&cond);
        sleep(rand() % 3);
    }
    return NULL;
}

/* 消费者 */
void *consumer(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        while(head == NULL){
            // 阻塞当前的消费者线程
            pthread_cond_wait(&cond, &mutex); // 条件变量+互斥锁
            // 当链表中有节点可取就解除阻塞
        }
        // 从链表的头部取出一个指针
        struct Node *node = head;
        printf("消费者, id: %ld, number: %d\n", pthread_self(), node->number);
        // 把头节点从链表中删除掉，再移动头节点到后面一个位置
        head = head->next;
        free(node);
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);
        // 如果链表中的节点全部被取出需要做进一步操作，不能取空节点
        
    }
    return NULL;

}

int main(int argc, const char* argv[])
{
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
    
    return 0;
}
