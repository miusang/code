#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

void *client_process(void *arg);

int main(int argc, char* args[]) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("create socket fd failed\n");
        return 0;
    }
    struct sockaddr_in addr;
    unsigned short port = 12698;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("binding server to prot:%d\n", port);
    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0) {
        perror("bind failed.\n");
        goto exit;
    }

    ret = listen(fd, 10);
    if (ret < 0) {
        perror("listen failed.\n");
        goto exit;
    }
    
    printf("waiting for client...\n");
    while (1) {
        char c_ip[INET_ADDRSTRLEN] = {0};
        struct sockaddr_in c_addr;
        socklen_t c_addr_len = sizeof(c_addr);
        int conn_fd = accept(fd, (struct sockaddr*)&c_addr, &c_addr_len);
        if (conn_fd < 0) {
            perror("accept failed.\n");
            continue;
        }
        inet_ntop(AF_INET, &c_addr.sin_addr, c_ip, INET_ADDRSTRLEN);
        printf("----------------------------------------------\n");
        printf("client ip:%s, port:%d", c_ip, ntohs(c_addr.sin_port));

        pthread_t tid;
        pthread_create(&tid, NULL, &client_process, &conn_fd);
        pthread_detach(tid);
    }

exit:
    close(fd);
    return 0;
}


/******************************************************************
 * name: void *client_process(void *arg)
 * desc: process client data.
 * param: socket conn fd
 * return: none
 * ***************************************************************/
void *client_process(void *arg) {
    int len;
    char buf[1024] = {0};
    int conn_fd = *(int *)arg;
    
    while ((len = recv(conn_fd, buf, sizeof(buf), 0)) > 0) {
        printf("recv data: %s\n", buf);
        send(conn_fd, buf, len, 0);
    }

    printf("client closed.\n");
    close(conn_fd);
    return NULL;
}
