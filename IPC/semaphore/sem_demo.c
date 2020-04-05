/*
 * 信号量
 * 本质是一个计数器,不以传输数据为主要目的,只要用来保护共享资源,使得资源在同一
 * 时刻,只有一个进程或线程独享.
 *
 * #include <sys/types.h> <sys/ipc.h> <sys/sem.h>
 *
 * int semget(key_t key, int nsems, int flags);
 * nsem 信号量的数目
 * flags: IPC_CREAT IPC_EXCL
 *
 * int semctl(int semid, int sem_num, int cmd, ...);
 * semid semget返回值
 * sem_num 信号量索引
 * cmd SETVAL 初始化信号量
 *     IPC_RMID 删除信号量标识符
 * union semun {
 *     int val; // demo 使用val.
 *     srtuct semid_ds *buf;
 *     unsigned short array;
 *     struct seminfo *__buf;
 * }
 *
 * int semop(int semid, struct sembuf *sops, size_t nops);
 * nops 要操作的信号量的个数
 * sops struct sembuf {
 *          short sem_num;
 *          short sem_op; // -1 P 等待操作; +1 V 发送操作
 *          short sem_flg; // 通常为SEM_UNDO
 *      }
 */

#include <sys/sem.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

int sem_p(int semid) {
    struct sembuf mbuf;
    mbuf.sem_num = 0;
    mbuf.sem_op = -1; // p
    mbuf.sem_flg = SEM_UNDO;
    return semop(semid, &mbuf, 1);
}

int sem_v(int semid) {
    struct sembuf mbuf;
    mbuf.sem_num = 0;
    mbuf.sem_op = 1; // v
    mbuf.sem_flg = SEM_UNDO;
    return semop(semid, &mbuf, 1);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("pid %d main start...\n", getpid());

        int semid = semget((key_t)1234, 1, 0666 | IPC_CREAT);
        if (semid < 0) {
            printf("create semid error<%s>\n", strerror(errno));
            return -1;
        }

        union semun msem;
        msem.val = 1;
        semctl(semid, 0, SETVAL, msem);
        
        int count = 0;
        while (1) {
            printf("pid %d wait sem...\n", getpid());
            sem_p(semid);
            printf("pid %d count[%d] hold sem 500ms ...\n", 
                    getpid(), count);
            usleep(100*1000);
            count++;
            sem_v(semid);

            if (count > 5) {
                break;
            }
        }

        printf("pid %d delete sem...\n", getpid());
        semctl(semid, 0, IPC_RMID);
        printf("pid %d end...\n", getpid());
    } else {
        printf("pid %d main start...\n", getpid());

        int semid = semget((key_t)1234, 1, 0666 | IPC_CREAT);
        if (semid < 0) {
            printf("create semid error<%s>\n", strerror(errno));
            return -1;
        }

        int count = 0;
        while (1) {
            printf("pid %d wait sem...\n", getpid());
            sem_p(semid);
            printf("pid %d count[%d] hold sem 1000ms ...\n",
                    getpid(), count);
            usleep(1000*1000);
            count++;
            sem_v(semid);

            if (count > 3) {
                break;
            }
        }
        printf("pid %d end...\n", getpid());
    }

    return 0;
}
