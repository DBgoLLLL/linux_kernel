#include "apue.h"
#include <sys/wait.h>

void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%d\n", WTERMSIG(status),
        #ifdef WCOREDUMP  // 定一批了WCOREDUMP且 WCOREDUMP(status)是真，打印core file，否则打印空字符“”
            WCOREDUMP(status) ? " (core file generated)" : "");
        #else
            "");
        #endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
        
}
