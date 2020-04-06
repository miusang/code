/*
 * socket可用于网络通信.
 *
 * int socket(int domain, int type, int protocol);
 * domain 协议域,有AF_INET,AF_INET6,AF_LOCAL,AF_ROUTE
 * type socket类型,有SOCK_STREAM,SOCK_DGRAM,SOCK_RAW,SOCK_PACKET,SOCK_SEQPACKET
 * protocol 指定协议,有IPPROTO_TCP,IPPTOTO_UDP,IPPRORO_SCTP,IPPROTO_TIPC
 * 
 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
 * sockfd socket的返回值
 * addr 绑定sockfd的协议地址
 * addrlen 地址的长度
 * 注意,绑定地址时,要将地址转换为网络字节序(大端,低位在前)
 *
 * int listen(int sockfd, int backlog);
 * backlog 最大连接个数
 *
 * int connect(int sockfd, const struct cockaddr *addr, socklen_t addrlen);
 *
 * int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
 *
 * ssize_t read(int fd, void *buf, size_t count);
 * ssize_t write(int fd, const void *bufm size_t count);
 *
 * size_t send(int sockfd, const void *buf, size_t len, int flags);
 * size_t recv(int sockfd, void *buf, size_t len, int flags);
 *
 * size_t sendto(int sockfd, const void *buf, size_t len, int flags,
 *               const struct sockaddr *dest_addr, socklen_t addrlen);
 * size_t recvfrom(int sockfd, void *buf, size_t len, int flags,
 *                 struct sockaddr *src_addr, socklen_t *addrlen);
 *
 * size_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
 * size_t recvmsg(int sockfd, struct msghdr *msg, int flags);
 *
 * int close(int fd);
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    printf("socket server main start...\n");

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        printf("create socket error<%s>\n", strerror(errno));
        return -1;
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 系统自动获取本机ip
    servaddr.sin_port = htons(9000);
    int ret = bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (ret < 0) {
        printf ("bind socket error<%s>.\n", strerror(errno));
        return -1;
    }

    ret = listen(sockfd, 1);
    if (ret < 0) {
        printf ("listen socket error<%s>.\n", strerror(errno));
        return -1;
    }

    int connfd = accept(sockfd, NULL, NULL);
    if (connfd < 0) {
        printf ("accept socket error<%s>.\n", strerror(errno));
        return -1;
    }

    char buf[1024];
    while (1) {
        printf("wait msg...\n");
        int len = recv(connfd, buf, 1024, 0);
        if (len <= 0) {
            continue;
        }
        printf("recv msg: %s\n", buf);

        if (strstr(buf, "quit")) {
            printf("recv msg quit!\n");
            break;
        }
    }

    close(connfd);
    close(sockfd);
    printf("socket server main end...\n");
    return 0;
}
