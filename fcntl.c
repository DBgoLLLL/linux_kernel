// fcntl函数使用代码例子
#include "apue.h"
#include <fcntl.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    int val;
    if (argc != 2) // 两个参数一个a.out 文件描述符
        err_quit("usage: a.out <descriptor#>");
    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0 ) // 文件char *转成int，fcntl(F_GETFL)是获取文件的文件状态标志
        err_sys("fcntl error for fd %d", atoi(argv[1]));
    switch (val & O_ACCMODE) // O_ACCMODE 掩码宏 0003 = 11，取val的低两位
    {
        case O_RDONLY:  // 00
            printf("read only");
            break;
        case O_WRONLY:  // 01
            printf("write only");
            break;
        case O_RDWR:    // 10
            printf("read write");
            break;
        default:
            err_dump("unknown access mode");
    }
    if (val & O_APPEND)
        printf(", append");
    if (val & O_NONBLOCK)
        printf(", nonblocking");
#if defined(O_SYNC)
    if (val & O_SYNC)
        printf(", synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined (O_FSYNC)
    if (val & O_FSYNC)
        printf(", synchronous writes");
#endif
    putchar('\n');
    exit(0);
    return 0;
}
