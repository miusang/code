
/**
 * @fork demo
 * @author atom
 * 
 * fork函数通过系统调用可以创建一个与原进程几乎完全相同的进程。
 *
 * 特点：
 * 1. fork()函数返回两次，父进程中返回子进程的pid，
 *    子进程中返回0，出错返回-1.
 * 2. 父子进程共享代码段,但是分别拥有自己的数据段和堆栈段.
 * 3. 一般来说,fork之后的父进程和子进程执行的先后顺序是不确定的,
 *    取决于内核的调度算法.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv) {
    int len = 10;

    pid_t child_pid = fork();
    if (child_pid < 0) {
        printf("fork child process error<%s>\n", strerror(errno));
    }
    
    // child process run
    if (child_pid == 0) {
        printf("child pid is %d\n", getpid());
        for (int i = 0; i < len; i++) {
            printf("child process run at %d ...\n", i);
        }
    }

    if(child_pid > 0) {
        printf("father pid is %d\n", getpid());
        printf("father process run ...\n");
    }

    for (int i = 0; i < 5; i++) {
        printf("%d common run ...\n", getpid());
    }

    return 1;
}
