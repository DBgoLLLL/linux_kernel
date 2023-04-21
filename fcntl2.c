// 修改文件的打开模式（状态），增加或者直接修改的代码示例
#include "apue.h"
#include <fcntl.h>
void set_fl(int fd, int flags)
{
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) <0 )  // val保存fd文件的状态
        err_sys("fcntl F_GETFL error");
    val |= flags;  // 如果是val &= ~flags 就是clr_fl函数 val与flag的补码进行逻辑与运算
    if (fcntl (fd, F_SETFL, val) < 0) // 设置文件fd的状态为val
        err_sys("fcntl F_SETFL error");
}
// set_fl(STDOUT_FILENO, O_SYNC) 使每次write等待，知道数据写到磁盘再返回
// val |= O_SYNV的含义 相当于打开文件的格式改为原有属性加上O_SYNV(等待数据和属性写完成)

