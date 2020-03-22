
/**
 * 命名管道,又称先进先出队列(FIFO),特点:
 * 1. named pipe可以用于任何两个进程间的通信,而不限于同源的两个进程;
 * 2. named pipe作为一种特殊的文件存在于系统中,而不像管道那样存放在内核中.
 *    当进程对命名管道的使用结束后,命名管道依然存在于文件系统中,除非对其进
 *    行删除,否则该命名管道不会自行消失.
 * 3. 命名管道也只能用于数据的单向传输,如果双向传输,建议使用两个单向的命名
 *    管道.
 *
 * 创建命名管道,函数签名:
 * 1. mkfifo(const char *pathname, mode_t mode);
 *    pathname表示用于存放命名管道的文件路径; 
 *    mode表示所创建文件的权限.
 *
 * 2. mknod(char *pathname, mode_t mode, dev_t dev);
 *    前两个参数与mkfifo一样;
 *    dev表示设备号, 在创建命名管道时, dev传递0(表示该文件不是一个设备文件).
 *
 * 3. 创建成功返回0; 失败返回-1.
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv) {

    char* file_path = "./data_file";
    
    int res = mkfifo(file_path, 0666);
    if (res < 0) {
        printf("create pipe file fail<%s>\n", strerror(errno));
        return -1;
    }

    int fd = open(file_path, O_WRONLY);
    if (fd < 0) {
        printf("open pipe file fail<%s>\n", strerror(errno));
    }

    char buf[255];
    int count = 0;
    while(1) {
        memset(buf, 0, 255);
        sprintf(buf, "hi, im %d, my count is: %d", getpid(), count);
        res = write(fd, buf, 255);
        if (res < 0) {
            printf("%d write data fail<%s>\n", getpid(), strerror(errno));
            usleep(1000*1000);
            continue;
        }
        printf("%d write data count(%d) success!\n", getpid(), count);

        count++;
        usleep(1000*1000);
    }

    return 0;
}

