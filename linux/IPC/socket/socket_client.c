#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    printf("socket client main start...\n");

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("create socket error<%s>.\n", strerror(errno));
        return -1;
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    int connfd = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (connfd < 0) {
        printf("connect socket error<%s>.\n", strerror(errno));
        return -1;
    }

    char buf[1024];
    sprintf(buf, "hi im client");
    int ret = send(sockfd, buf, sizeof(buf), 0);
    if (ret < 0) {
        printf("client send error\n");
    }
    sprintf(buf, "i will quit.");
    ret = send(sockfd, buf, sizeof(buf), 0);
    if (ret < 0) {
        printf("client send error\n");
    }

    close(sockfd);
    return 0;
}
