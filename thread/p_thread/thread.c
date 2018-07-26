
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>   

void* rout(void* arg)
{
    pid_t thread1_tid;   
    thread1_tid = syscall(SYS_gettid);
    printf("thread1_tid = %d\n", thread1_tid);
    while(1)
    {
        printf("I am thread 1\n");
        sleep(1);
    }
}

int main( void  )
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, rout, NULL);
    if(ret != 0)
    {
        fprintf(stderr, "pthread_create : %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    pid_t main_tid;   
    main_tid = syscall(SYS_gettid);
    printf("main_tid = %d\n", main_tid);


    while(1)
    {
        printf("I am main thread\n");
        sleep(1);
    }

}
