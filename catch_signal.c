#include "apue.h"
static void sig_usr(int );
// 只设置处理两个信号，没有对应处理函数的信号会使用默认方法
int main(void)
{
    if (signal(SIGUSR1,sig_usr) == SIG_ERR)
        printf("cant' catch SIGUSR1");
    if (signal(SIGUSR2,sig_usr) == SIG_ERR)
        printf("can't catch SIGUSR2");
    for (;;)
        pause();
}
static void sig_usr(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        printf("received signal %d\n", signo);
}
