#include <kernel/signal.c>
typedef void (*__sighandler_t)(int);
#define SIG_DFL ((__sighandler_t) 0) // 缺省信号处理
#define SIG_IGN ((__sighandler_t) 1) // 忽略信号
#define SIG_ERR ((__sighandler_t) -1) // 从信号返回错误
struct sigaction{
    __sighandler_t sa_handler; //处理函数指针
    sigset_t sa_mask; //信号掩码
    unsigned long sa_flags; // SA_ONESHORT 默认操作 ;SA_NOMASK 忽略sa_mask域
    void (*sa_restorer)(void);
};

int sys_sigaction(int signum, const struct sigaction * action, struct sigaction * oldaction)
{
    struct sigaction new_sa, *p;

    if (signum<1 || signum>32)
        return -EINVAL;
    /* 信号的值不在 1～32 之间，则出错 */

    if (signum==SIGKILL || signum==SIGSTOP)
        return -EINVAL;
    /*SIGKILL 和 SIGSTOP 不能设置信号处理程序 */

    p = signum - 1 + current->sig->action;
    /*在当前进程中，指向信号 signum 的 action 的指针 */
    if (action) 
    {
        int err = verify_area(VERIFY_READ, action, sizeof(*action));
        /* 验证给 action 在用户空间分配的地址的有效性 */
        if (err)
            return err;
        memcpy_fromfs(&new_sa, action, sizeof(struct sigaction));
        /* 把 actoin 的内容从用户空间拷贝到内核空间*/
        new_sa.sa_mask |= _S(signum);
        /* 把信号 signum 加到掩码中 */
        if (new_sa.sa_flags & SA_NOMASK)
            new_sa.sa_mask &= ~_S(signum);
        /* 如果标志为 SA_NOMASK，当信号 signum 出现时，将它的操作置为默认操作 */
        new_sa.sa_mask &= _BLOCKABLE;
        /* 不能阻塞 SIGKILL 和 SIGSTOP */
        if (new_sa.sa_handler != SIG_DFL && new_sa.sa_handler !=SIG_IGN) 
        {
            err = verify_area(VERIFY_READ, new_sa.sa_handler, 1);
            /* 当处理程序不是信号默认的处理操作，并且 signum 信号不能被忽略时，验证给信号处理程序分配
            空间的有效性 */
            if (err)
                return err; 
        }
    }
    if (oldaction) 
    {
        int err = verify_area(VERIFY_WRITE, oldaction, sizeof(*oldaction));
        if (err)
            return err;
        memcpy_tofs(oldaction, p, sizeof(struct sigaction));
        /* 恢复原来的信号处理程序 */
    }
    if (action) 
    {
        *p = new_sa;
        check_pending(signum);
    }
    return 0;
}
