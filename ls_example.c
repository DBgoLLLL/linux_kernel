#include "apue.h"
#include <dirent.h>
int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dirp;
	
	// 必须两个参数 ls和文件名
	if (argc != 2)
		err_quit ("usage: ls directory_name ");
	
	// 打开文件路径，文件描述符dp
	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);
	
	// readdir读取第一个文件名，读完应该跳转到下一个，直到NULL
	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
	exit(0);
}
