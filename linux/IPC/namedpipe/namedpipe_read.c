
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
    char* file_path = "./data_file";

    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        printf("%d open pipe file fail<%s>\n", getpid(), strerror(errno));
    }

    char buf[1024];
    while(1) {
        int len = read(fd, buf, 1024);
        if (len <= 0) {
            continue;
        }
        printf("%d read data: \" %s \"\n", getpid(), buf);
    }

    return 0;
}
