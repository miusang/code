#include <stdio.h>
#include <mutex>
#include <thread>
#include <unistd.h>

static void loop1(int &num, std::mutex &lock);
static void loop2(int &num, std::mutex &lock);


int main() {

    std::mutex mutex;
    int count = 0;
    std::thread t1(loop1, std::ref(count), std::ref(mutex));
    std::thread t2(loop2, std::ref(count), std::ref(mutex));

    t1.join();
    t2.join();
    return 0;
}

static void loop1(int &num, std::mutex &lock) {
    for (int i = 0; i < 20; i++) {
        lock.lock();
        printf("loop1 num: %d\n", num++);
        lock.unlock();
        usleep(10 * 1000);
    }
}

static void loop2(int &num, std::mutex &lock) {
    for (int i = 0; i < 10; i++) {
        lock.lock();
        printf("loop2 num: %d\n", num++);
        lock.unlock();
        usleep(10 * 1000);
    }
}
