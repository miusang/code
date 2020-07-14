
/**
 * 信号signal:
 * 本质是对中断的一种模拟,异步通信机制.
 *
 * 信号来源:
 * 1. 程序错误,如非法访问内存;
 * 2. 外部信号,Ctrl+C;
 * 3. 通过kill或sigqueue向另外一个进程发送信号
 *
 * 信号的注册:
 * 1. singal
 *    typedef void (*sighandler_t)(int); // 信号处理函数
 *    signal(int signum, sighandler_t handler); // signum 信号编号
 *
 * 2. sigaction(推荐)
 *    int sigaction(int signum, struct sigaction *act, struct sigaction *oldact);
 *    act 指定信号新的处理方式
 *    oldact 旧的处理方式
 *    struct sigaction {
 *        void (*sa_handler)(int);
 *        void (*sa_sigaction)(int, siginfo_t *, void *);
 *        sigset_t sa_mask;
 *        int sa_flags;
 *        void (*sa_restorer)(void);
 *    }
 * 3. 区别
 *    1). signal是指以前的老的signal函数,现在大多数系统都用sigaction重新实现了signal函数.
 *    2). signal在调用handler之前先把信号的handler指针恢复;
 *        sigaction调用之后不会恢复handler指针,直到再次调用sigaction修改handler指针.
 *    3). 后续补充
 *
 * 信号的发送
 * 1. kill
 * 2. raise
 * 3. sigqueue(推荐)
 * 4. alarm
 * 5. settimer
 * 6. abort
 *
 */

#include <signal.h>
#include <stdio.h>

int main_quit = 0;
void sig_process(int sig_no) {
    printf("process signal\n");
    if (sig_no == SIGINT) {
        printf("get SIGINT\n");
        main_quit = 1;
    }
}

/*
 * 运行:
 * ./demo &
 * kill -2 pid
 */
int main(int argc, char** argv) {
    printf("main start...\n");

    struct sigaction usr_sig;
    usr_sig.sa_handler = sig_process;
    usr_sig.sa_flags = 0;
    sigaction(SIGINT, &usr_sig, NULL);
    
    while (1) {
        printf("wait signal INT ...\n");
        usleep(1000*1000);
        if (main_quit == 1) {
            break;
        }
    }
    printf("main end...\n");
    return 0;
}
