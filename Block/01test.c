#include <stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/timerfd.h>
#include<stdint.h>
#include<errno.h>
#include<sys/select.h>
#define N 4

void handler(int s)
{
    printf("recv %d\n",s);
}
int main(void)
{
    int tfd = timerfd_create(CLOCK_MONOTONIC,TFD_CLOEXEC);
    if(tfd == -1)perror("timerfd_create"),exit(1);
    struct itimerspec isp;
    memset(&isp,0x00,sizeof isp);
    isp.it_value.tv_sec = 3;
    isp.it_interval.tv_sec = 1;
    timerfd_settime(tfd,0,&isp,NULL);
    int kfd = fileno(stdin);
    int maxfd = tfd > kfd ? tfd : kfd;

    fd_set set;
    while(1)
    {
        FD_ZERO(&set);
        FD_SET(tfd,&set);
        FD_SET(kfd,&set);
        int nready = select(maxfd+1,&set,NULL,NULL,NULL) ;
        if(nready <= 0)
            continue;
        if(FD_ISSET(tfd,&set)){
            uint64_t es;
            int r = read(tfd,&es,sizeof es);
            if(r <= 0)break;
            printf("r=%d\n",r);
        }
        if(FD_ISSET(kfd,&set)){
            char buf[1024] = {};
            int r;
lab:
            r = read(kfd,buf,1024);
            if(r <= 0){
                if(r == -1 && errno == EINTR)
                    goto lab;
                break;
            }
            printf("buf=[%s]\n",buf);
        }
    }
}
//int main(void)
//{
//    struct sigaction act;
//    act.sa_handler = handler;
//    act.sa_flags = 0;
//    sigemptyset(&act.sa_mask);
//    sigaction(SIGALRM,&act,NULL);
//    
//    struct itimerval tm;
//    memset(&tm,0x00,sizeof tm);
//    tm.it_value.tv_sec = 4;
//    tm.it_interval.tv_sec = 1;
//
//    setitimer(ITIMER_REAL,&tm,NULL);
//    for(;;)
//    pause();
//}
void ganran(int arr[][N],int i ,int j)
{
    if(i < 0 || i >= N || j <0 || j >= N || arr[i][j] != 1)
        return;
    arr[i][j]++;
    ganran(arr,i-1,j);
    ganran(arr,i+1,j);
    ganran(arr,i,j-1);
    ganran(arr,i,j+1);
}
int land(int arr[][N],int m,int n)
{
    int i = 0;
    int j = 0;
    int island = 0;
    for(i = 0;i < N;i++){
        for(j = 0;j < N;j++){
            if(island == 1)
                island++;
        }
    }
}
void rotate(int arr[N][N],int a,int b,int c,int d)
{
    int i = 0;
    for(i = 0; i < d-b;i++){
        int tmp = arr[a][b+i];
        arr[a][b+i] = arr[c-i][b];
        arr[c-i][b] = arr[c][d-i];
        arr[c][d-i] = arr[a+i][d];
        arr[a+i][d] = tmp;
    }
}
void rotateArr(int arr[N][N])
{
    int a = 0;
    int b = 0;
    int c = N-1;
    int d = N-1;
    while(a < c)
    {
        rotate(arr,a++,b++,c--,d--);
    }
}
void show(int arr[N][N])
{
    int i = 0;
    int j = 0;
    for(i = 0;i < N;i++){
        for(j = 0;j < N;j++)
            printf("%-3d",arr[i][j]);
        printf("\n");
    }
}
//int main()
//{
//    int arr[N][N] = {
//        1,1,1,0,1,0,
//        1,0,0,0,1,1,
//        1,0,0,0,1,0,
//        0,0,1,1,1,0,
//        0,0,0,0,0,0,
//        0,0,1,1,1,1,
//    };
//
    //一个彩色的9，9乘法表
//    int i = 0;
//    for(i = 1;i <= 8;i++){
//        printf("\033[3%dm",i-1);
//        int j = 0;
//        for(j = 1;j <= 8;j++){
//            if(j <= i)
//                printf("%dx%d =%-3d",j,i,i*j);
//        }
//        printf("\033[0m\n");
//    }
//


//    旋转一个二维数组
//    int arr[N][N];
//    int num = 1;
//    int i = 0;
//    int j = 0;
//    for(i = 0;i < N;i++){
//        for(j = 0;j < N;j++){
//            arr[i][j] = num++;
//        }
//    }
//    show(arr);
//    rotateArr(arr);
//    printf("\n");
//    show(arr);
//}
