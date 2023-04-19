#include "apue.h"
#include <stdlib.h>
#include <unistd.h>
#define BUFFSIZE 4096
int main(void)
{
    int n;
    char buf[BUFFSIZE];
    while((n = read(STDIN_FILENO, buf, BUFFSIZE))>0)
    {
        if (write(STDOUT_FILENO, buf, n)!=n)
        {
            err_sys("write, error");

        }
    }
    if (n<0)
        err_sys("read error");
    exit(0);
}

// ./a.out < infile > outfile  将infile文件的内容复制到outfile
// ./a.out >outfile  将终端输入复制到文件outfile
