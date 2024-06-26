#include "clientList.h"

#include <stdlib.h>//malloc()的头文件
#include <stdio.h>

struct ClientInfo* createList()
{
    struct ClientInfo* head = (struct ClientInfo*)malloc(sizeof(struct ClientInfo));
    return head;
}

struct ClientInfo *prependNode(struct ClientInfo *head, int fd)
{
    struct ClientInfo* node = (struct ClientInfo*)malloc(sizeof(struct ClientInfo));
    node->fd = fd;
    node->next = head->next;
    head->next = node;
    return node;
}
//在removeNode函数中用到了两个辅助指针p,q
bool removeNode(struct ClientInfo *head, int fd)
{
    struct ClientInfo* p = head;
    struct ClientInfo* q = head->next;
    while(q)//当q指向地址不为空
    {
        if(q->fd == fd)
        {
            p->next = q->next;
            free(q);
            printf("成功将链表中的fd结点删除了,fd = %d\n",fd);
            return true;
        }
        //指针继续往后走，寻找if(q->fd == fd)的条件
        p = p->next;
        q = q->next;
    }
    return false;
}
//在freeClientList函数中用到了一个辅助指针p
void freeClientList(struct ClientInfo *head)
{
    struct ClientInfo*  p = head;
    while(p)
    {
        struct ClientInfo* temp = p;
        p = p->next;
        free(temp);
    }
}
