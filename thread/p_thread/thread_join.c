#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//线程等待

//线程1
void *thread1( void *arg  ) 
{    
    printf("thread 1 returning...\n");    
    int *p = (int*)malloc(sizeof(int));    
    *p = 1;    
    return (void*)p;  
}

//线程2
void* thread2(void* arg)
{
    printf("thread 2 returning...\n");
    int *p = (int*)malloc(sizeof(int));    
    *p = 2;    
    return (void*)p;  
}

//线程3
void* thread3(void* arg)
{
    while(1)
    {
        printf("thread 3 returning...\n");
        sleep(1);
    }
    return NULL;
}

int main()
{
    //主线程

    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    void *ret;

    //线程1
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_join(tid1, &ret);
    printf("thread 1 return, thread id %lx, return code:%d\n", tid1, *(int *)ret);
    free(ret);

    //线程2
    pthread_create(&tid2, NULL, thread2, NULL);
    pthread_join(tid2, &ret);
    printf("thread 2 return, thread id %lx, return code:%d\n", tid2, *(int *)ret);
    free(ret);

    //线程3
    pthread_create(&tid3, NULL, thread3, NULL);
    sleep(3);
    //终止正在执行的线程
    pthread_cancel(tid3);
    pthread_join(tid3, &ret);
    if ( ret ==  PTHREAD_CANCELED  )
      printf("thread 3 return, thread id %lx, return code:PTHREAD_CANCELED\n", tid3) ;
    else
      printf("thread return, thread id %lx, return code:NULL\n", tid3);
}

