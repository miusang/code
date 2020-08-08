#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;

static void loop1();
static void loop2();
static pthread_mutex_t mutex;

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t pid1;
    pthread_t pid2;
    int ret = pthread_create(&pid1, NULL, (void*)loop1, NULL);
    if (ret < 0) {
        printf("line:%d, pread_create error!<reason: %s>\n", __LINE__, strerror(errno));
    }
    ret = pthread_create(&pid2, NULL, (void*)loop2, NULL);
    if (ret < 0) {
        printf("line:%d, pread_create error!<reason: %s>\n", __LINE__, strerror(errno));
    }

    pthread_join(pid1, NULL);
    pthread_join(pid2, NULL);

    return 0;
}

static void loop1() {
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex);
        count++;
        printf("loop1 change count: %d\n", count);
        pthread_mutex_unlock(&mutex);
        usleep(10 * 1000);
    }
}

static void loop2() {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        count++;
        printf("loop2 change count: %d\n", count);
        pthread_mutex_unlock(&mutex);
        usleep(10 * 1000);
    }
}
