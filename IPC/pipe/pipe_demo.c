
/**
 * 管道（pipe）的特点：
 * 1. 半双工，数据只能向一个方向流动，需要双方通信时，需要建立两个管道。
 * 2. 只能用于父子进程或兄弟进程之间（具有亲缘关系的进程）。
 * 3. 单独构成一种独立的文件系统，并且只存在于内存中。
 */
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
    int fd[4];
    int res = pipe(fd);
    if (res < 0) {
        printf("create pipe filed<%s>!\n", strerror(errno));
        return -1;
    }

    for (int i = 0; i < 4; i++) {
        printf("%d\n", fd[i]);
    }
    return 0;
}
