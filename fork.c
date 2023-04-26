#include "apue.h"
int glob = 6;
char buf[] = "a write to stdout\n";
int main(void)
{
    int var;
    pid_t pid;
    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        //err_sys("write error");
        printf("write error");
    printf("before fork\n");
    if ((pid = fork()) <0 ) //出错
    {
        //err_sys("fork error");
        printf("fork error");
    }
    else if (pid == 0) // 子进程
    {
        glob++;
        var++;
    }
    else { //父进程
    
        sleep(2);
    }
    printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
    exit(0);
}
// output:
// a write to stdout
// before fork
// pid = 407, glob = 7, var = 89
// pid = 404, glob = 6, var = 88
// 结果分析 子进程对局部变量还是全局变量的操作都不影响父进程的值，是两份拷贝
