#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    printf("shm read start...\n");

    int shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);
    if (shmid < 0) {
        printf("shmget error<%s>\n", strerror(errno));
        return -1;
    }

    char *data = shmat(shmid, NULL, 0);
    while (!strstr(data, "write")) {
        printf("wait write...\n");
        usleep(1000*1000);
    }
    printf("read data success.\n");

    printf("shm read end...\n");
    return 0;
}
