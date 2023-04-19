#include "apue.h"
#include <stdio.h>
int main(void)
{
    int c;
    while((c = getc(stdin))!=EOF)
    {
        if (putc(c, stdout) == EOF)
        {
            err_sys("output error");
        }
        if (ferror(stdin))
        {
            err_sys("input error");
        }
        exit(0);
    }
}

// getc 读到终端输入最后一个字符是EOF
