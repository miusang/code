/*
 * 共享内存:允许多个进程共享一定的存储区.
 *
 * 特点:
 * 1. 生命周期随内核,即使所有访问共享内存的进程都已经正常结束,
 *    共享内存对象仍然存在内核中,除非显式删除共享内存对象.
 * 2. 共享内存并未提供同步机制.
 *
 * 接口:
 * #include <sys/shm.h>
 *
 * int shmget(ket_t key, size_t size, int shmflg);
 * key 非0长整型,系统建立IPC通讯时必须指定的一个id,通常情况下,该
 *     id值通过ftok函数得到,由内核变成标识符,要想让两个进程看到同
 *     一个信号集,只需设置key值不变即可.
 * size 共享内存大小,一般为一页大小的整数倍.
 * shmflg 创建一个新的共享内存,IPC_CREAT表示不存在则创建,存在则打开.
 *
 * int shmctl(int shm_id, int cmd, struct shid_ds *buf);
 * shm_id shmget函数返回的共享内存标识符.
 * cmd IPC_STAT: 用共享内存的当前关联值覆盖shmid_ds的值
 *     IPC_SET: 如果进程权限满足,则把共享内存的当前关联值设置为shid_ds
 *              给出的值.
 *     IPC_RMID: 删除共享内存.
 *
 * buf 结构体指针.
 *     struct shmid_ds {
 *         uid_t shm_perm.uid;
 *         uid_t shm_perm.gid;
 *         mode_t shm_perm.mode;
 *     }
 *
 * void *shmat(int shm_id, const void *shm_addr, int shmflg);
 * shm_addr 指定共享内存连接到当前进程中的地址位置,通常为空,表示让系统
 *          来选择共享内存的地址.
 *
 * int shmdt(const void *shmaddr);
 * shmaddr shmat的返回值.
 */

#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    printf("shm write start...\n");

    int shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);
    if (shmid < 0) {
        printf("create shm error<%s>\n", strerror(errno));
        return -1;
    }

    char *data = shmat(shmid, NULL, 0);
    sprintf(data, "%d write data", getpid());
    
    int ret = shmdt(data);
    if (ret < 0) {
        printf("shmdt error\n");
    }

    printf("shm write end..\n");
    return 0;
}
