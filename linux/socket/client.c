#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define EXIT "exit"
#define MAX_LINE 4096
#define SERVER_IP "127.0.0.1"

int main(int argc, char *args[]) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("crate socket failed.\n");
        return 0;
    }
    struct sockaddr_in s_addr;
    bzero(&s_addr, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(12698);
    int ret = inet_pton(AF_INET, SERVER_IP, &s_addr.sin_addr);
    if (ret < 0) {
        perror("inet_pton failed.\n");
        goto exit;
    }

    printf("client start connect...\n");
    ret = connect(fd, (struct sockaddr *)&s_addr, sizeof(s_addr));
    if (ret < 0) {
        perror("connect failed. reason");
        goto exit;
    }
    
    printf("client connect success.\n");
    char send_line[MAX_LINE];
    while (1) {
        fgets(send_line, sizeof(send_line), stdin);
        if (strncasecmp(send_line, "exit", strlen(EXIT)) == 0) {
            goto exit;
        }
        printf("client send msg to server: %s\n", send_line);
        ret = send(fd, send_line, strlen(send_line), 0);
        if (ret < 0) {
            perror("client send failed.\n");
            goto exit;
        }
    }


exit:
    close(fd);
    return 0;
}
