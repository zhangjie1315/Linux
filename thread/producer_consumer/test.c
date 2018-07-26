/*************************************************************************
# File Name: test.c
# Author: rjm
# mail: rjm96@foxmail.com
# Created Time: 2018年04月20日 星期五 11时23分34秒
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CONSUMERS_COUNT 1
#define PRODUCERS_COUNT 1

struct msg
{
    struct msg *next;
    int num;
};

struct msg *head = NULL;

pthread_cond_t cond;
pthread_mutex_t mutex;
pthread_t threads[CONSUMERS_COUNT + PRODUCERS_COUNT];

void *consumer(void *p)
{
    int num = *(int *)p;
    free(p);
    struct msg *mp;
    for ( ; ;  )
    {
        pthread_mutex_lock(&mutex);
        while ( head == NULL  )
        {
            printf("%d 开始等待...\n", num);
            pthread_cond_wait(&cond, &mutex);
        }
        printf("%d 停止等待...\n", num);
        printf("%d 开始消费...\n", num);
        mp = head;
        head = mp->next;
        pthread_mutex_unlock(&mutex);
        printf("消费了:  %d\n", mp->num);
        free(mp);
        printf("%d 停止消费...\n", num);
        sleep(rand() % 5);
    }
}

void *producer(void *p)
{
    struct msg *mp;
    int num = *(int *)p;
    free(p);
    for ( ; ;  )
    {
        printf("%d 开始生产...\n", num);
        mp = (struct msg *)malloc(sizeof(struct msg));
        mp->num = rand() % 1000 + 1;
        printf("生产了:  %d\n", mp->num);
        pthread_mutex_lock(&mutex);
        mp->next = head;
        head = mp;
        printf("%d 停止生产...\n", num);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 5);
    }
}

int main( void )
{
    srand(time(NULL));
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    int i;

    for(i = 0; i < CONSUMERS_COUNT; i++)
    {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        pthread_create(&threads[i], NULL, consumer, (void *)p);
    }

    for(i = 0; i < PRODUCERS_COUNT; i++)
    {
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        pthread_create(&threads[CONSUMERS_COUNT + i], NULL, producer, (void *)p);
    }

    for (i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

