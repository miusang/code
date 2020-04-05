/*
 * 消息队列
 * 本质上是位于空间内核的链表,链表的每个节点都是一条消息.
 * 消息队列克服了信号传递消息少,管道只能承载无格式字节流以及缓冲区
 * 大小受限等缺点.
 *
 * int smgget(key_t key, int flags);
 *
 * int msgsnd(int msqid, const void *msgp, size_t msgz, int msgflg);
 * msqid smgget返回值.
 * msgp 消息数据地址
 * msgz 消息正文部分的大小(不包含消息类型)
 *      struct Mymsg {
 *          log type; // 消息类型,值必须>0.
 *          // 消息正文,usr定.
 *      }
 * msgflag 0 如果消息队列空间不够,msgsnd则会阻塞.
 *         IPC_NOWAIT 直接返回,如果空间不够,则会设置errno为EAGIN.
 *
 * ssize_t msgrcv(int msqid, void *msgp, size_t msgz, long msgtyp, int msgflg);
 * msgtyp 0 表示获取消息队列中的第一条消息
 *        >0 表示获取类型为msgtyp的第一条消息
 *        <0 表述获取<=|msgtyp| 的第一条消息
 *
 * int msgctl(int msqid, int cmd, struct msqid_ds *buf);
 */

#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "my_msg.h"

int main(int argc, char** argv) {
    printf("pid %d write main start...\n", getpid());

    int msqid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msqid < 0) {
        printf("msgget error<%s>\n", strerror(errno));
        return -1;
    }

    Msg msg[3] = {
        {100, "msg_one"},
        {101, "msg_two"},
        {100, "msg_two_with_quit"}
    };

    for (int i = 0; i < 3; i++) {
        int ret = msgsnd(msqid, &msg[i], sizeof(char)*255, 0);
        if (ret < 0) {
            printf("send msg error<%s>.\n", strerror(errno));
        }
    }

    printf("send msg end...\n");
    return 0;
}
