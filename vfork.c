#include "apue.h"
int glob = 6;
int main(void)
{
    int var;
    pid_t pid;
    var = 88;
    printf("brefore vfork\n");
    if ((pid = vfork())<0)
    {
        printf("vfork error");
    }
    else if (pid == 0)
    {
        glob++;
        var++;
        _exit(0);
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}

// output
// brefore vfork
// pid = 571, glob = 7, var = 89
// 子进程在父进程的地址空间执行，会改变父进程的变量
