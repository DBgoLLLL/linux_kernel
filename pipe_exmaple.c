#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main(void) {
	int fd[2], nbytes;
	pid_t childpid;
	char string[] = "hello, world!\n";
	char readbuffers[80];
	pipe(fd);
	if ((childpid = fork()) == -1)
	{
		printf("Error: fork");
		exit(1);
	}
	if (childpid == 0)// 子进程负责写管道
	{
		printf("this son process\n");
		close(fd[0]);// 关闭读fd
		write(fd[1], string, strlen(string));
		exit(0);
	}
	else // 父进程负责读管道
	{
		printf("this father process\n");
		close(fd[1]); // 关闭写fd
		nbytes = read(fd[0], readbuffers, sizeof(readbuffers));
		printf("Received string: %s", readbuffers);
	}
	return 0;
}
