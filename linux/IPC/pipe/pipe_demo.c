
/**
 * 管道（pipe）的特点：
 * 1. 半双工，数据只能向一个方向流动，需要双方通信时，需要建立两个管道。
 * 2. 只能用于父子进程或兄弟进程之间（具有亲缘关系的进程）。
 * 3. 单独构成一种独立的文件系统，并且只存在于内存中。
 *
 * pipe(fd[2])函数:
 *  成功返回0, fd数组创建2个文件描述符,fd[0]指向管道的读端,fd[1]指向管道的写端.
 *  失败返回-1.
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
    int fd[2];
    int res = pipe(fd);
    if (res < 0) {
        printf("create pipe error<%s>!\n", strerror(errno));
        return -1;
    }

    pid_t child1 = fork();
    pid_t child2 = -1;
    if (child1 != 0) {
        child2 = fork();
    }

    if (child1 == 0) {
        int count = 0;
        char buf[255];
        while(1) {
            memset(buf, 0, 10);
            sprintf(buf, "child1 write data %d", count);
            printf("pid %d %s\n", getpid(), buf);
            write(fd[1], buf, 255);
            count++;
            usleep(1000*1000);
        }
    }

    if (child2 == 0) {
        char buf[255];
        while(1) {
            read(fd[0], buf, 255);
            printf("pid %d child2 read data %s\n", getpid(), buf);
            usleep(100*1000);
        }
    }

    if (child1 != 0 && child2 != 0) {
        while(1) {
            printf("father %d waiting stop ...\n", getpid());
            usleep(1000*1000);
        }
    }

    return 0;
}
