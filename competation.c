#include "apue.h"
static void charatatime(char *);
int main(void)
{
    pid_t pid;
    if ((pid = fork()) <0) // 创建子进程失败
    {
        printf("fork error");
    }
    else if (pid == 0) // 子进程
    {
        charatatime("output from child\n");
    }
    else { // 父进程
        charatatime("output from parent\n");
    }
    exit(0);
}
static void charatatime(char *str)
{
    char *ptr;
    int c;
    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr++) != 0;)
        putc(c, stdout);
}
