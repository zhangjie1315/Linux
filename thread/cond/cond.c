/*************************************************************************
# File Name: cond.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月20日 星期五 10时49分38秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//定义一个条件变量
pthread_cond_t cond;
//定义一个互斥量
pthread_mutex_t mutex;

void *r1( void *arg  )
{
    while ( 1 )
    {
        pthread_cond_wait(&cond, &mutex);
        printf("thread1: 我醒了...\n");
    }
}

void *r2(void *arg )
{
    printf("thread2: 我每3s唤醒一次等待\n");
    while ( 1 )
    {
        sleep(1);
        printf("thread2: 1 ...\n");
        sleep(1);
        printf("thread2: 2 ...\n");
        sleep(1);
        printf("thread2: 3 ...\n");
        //唤醒等待
        pthread_cond_signal(&cond);
    }
}

int main( void  )
{
    //定义两个线程id
    pthread_t t1, t2;

    //初始化条件变量和互斥量
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

    //创建两个线程
    pthread_create(&t1, NULL, r1, NULL);
    pthread_create(&t2, NULL, r2, NULL);

    //线程等待
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //销毁互斥量和条件变量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

