#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "my_msg.h"

int main(int argc, char** argv) {
    printf("pid %d rcv main start...\n", getpid());

    int msqid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msqid < 0) {
        printf("msgget error<%s>.\n", strerror(errno));
        return -1;
    }

    Msg msg;
    while (1) {
        usleep(1000*1000);

        int ret = msgrcv(msqid, &msg, sizeof(char)*255, 100, IPC_NOWAIT);
        if (ret < 0) {
            if (errno == ENOMSG) {
                printf("no 100-type msg\n");
            }
            continue;
        }
        printf("100-type msg data: %s\n", msg.data);
        if (strstr(msg.data, "quit")) {
            printf("100-type quit\n");
            break;
        }

        ret = msgrcv(msqid, &msg, sizeof(char)*255, 101, IPC_NOWAIT);
        if (ret < 0) {
            if (errno == ENOMSG) {
                printf("no 101-type msg\n");
            }
            continue;
        }
        printf("101-type msg data: %s\n", msg.data);
        if (strstr(msg.data, "quit")) {
            printf("101-type quit\n");
            break;
        }
    }

    int ret = msgctl(msqid, IPC_RMID, 0);
    if (ret < 0) {
        printf("rm msgqueue error<%s>.\n", strerror(errno));
    }

    printf("rcv end...\n");
    return 0;
}
