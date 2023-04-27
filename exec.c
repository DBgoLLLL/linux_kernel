#include "apue.h"
#include<sys/wait.h>
char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};
int main(void)
{
    pid_t pid;
    if ((pid = fork())<0) // 创建子进程失败
    {
        printf("fork error");
    }
    else if (pid == 0) // 子进程
    {
        if (execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init)<0)
            printf("execle error");
    }
    if (waitpid(pid, NULL, 0)<0) // 父进程等待子进程结束
        printf("wait error");

    if ((pid = fork())<0)  //创建第二个子进程
    {
        printf("fork error");
    }
    else if (pid ==0 ) // 执行第二个子进程
    {
        if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0 )
            printf("execlp error")
    }
    exit(0);
}
