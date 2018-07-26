
//线程的同步与互斥问题
//售票系统

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <pthread.h>

int tickets = 100;

//定义一把互斥锁,并初始化
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 


void* ticket(void* arg)
{
    char* id = (char*)arg;
    while(1)
    {
        //加锁
        pthread_mutex_lock(&mutex); 
        if(tickets > 0)
        {
            usleep(100000);
            printf("%s sell tickets %d\n", id, tickets);
            tickets--;
            //解锁
            pthread_mutex_unlock(&mutex); 
        }
        else
        {
            //解锁
            pthread_mutex_unlock(&mutex); 
            break;
        }
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3, t4;

    //初始化互斥锁
    //pthread_mutex_init(&mutex,NULL);    

    //创建4个线程抢票
    pthread_create(&t1, NULL, ticket, "thread 1");    
    pthread_create(&t2, NULL, ticket, "thread 2");    
    pthread_create(&t3, NULL, ticket, "thread 3");    
    pthread_create(&t4, NULL, ticket, "thread 4");

    pthread_join(t1, NULL);    
    pthread_join(t2, NULL);    
    pthread_join(t3, NULL);    
    pthread_join(t4, NULL); 
}
