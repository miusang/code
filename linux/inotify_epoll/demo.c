#include <sys/epoll.h>
#include <sys/inotify.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/fanotify.h>

int main() {
    const char* path = "./test";
    int epfd = epoll_create(1);
    int fd = inotify_init();
    int wd = inotify_add_watch(fd, path, IN_DELETE_SELF);
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = fd;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    int count = epoll_wait(epfd, &event, 1, -1);
    printf("count %d\n", count);
    struct inotify_event event2;
    if ((event.data.fd == fd) && (read(fd, &event2, sizeof(event2)) > 0)) {
        int wd2 = event2.wd;
        int flag = wd2 == wd;
        printf("wd2 %d wd %d equal:%d\n", wd2, wd, flag);
        if (flag > 0) {
             printf("%s removed\n", path);
        } else {
            printf("hahahah\n");
        }
    }
    return 0;
}
