#include <hiredis/hiredis.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    redisContext *pConnect = redisConnect("127.0.0.1", 6379);
    if (pConnect == NULL || pConnect->err)
    {
        if (pConnect)
        {
            printf("error: %s\n", pConnect->errstr);
            redisFree(pConnect);
            return -1;
        }
        else
        {
            printf("can not allocate redis context\n");
            return -1;
        }
    }
    printf("connect success\n");
    redisReply *pReply = (redisReply *)redisCommand(pConnect, "set %s %d",
                                                    "boldness", 30);
    if (pReply == NULL)
    {
        printf("command error\n");
        redisFree(pConnect);
        return -1;
    }
    if (pReply->type == REDIS_REPLY_NIL)
    {
        printf("command error\n");
    }
    pReply = (redisReply *)redisCommand(pConnect, "get %s ", "boldness");
    if (pReply->type == REDIS_REPLY_NIL)
    {
        printf("get nil\n");
    }
    else if (pReply->type == REDIS_REPLY_STRING)
    {
        printf("get value: %s\n", pReply->str);
    }
    freeReplyObject(pReply);
    redisFree(pConnect);
    return 0;
}