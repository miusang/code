#include <stdio.h>
#include <mutex>

class MySingleton {
private:
    static std::mutex lock;
    static MySingleton* pInstance;
    MySingleton() {
        printf("construct MySingleton.\n");
    }
    ~MySingleton(){
        printf("destroy MySingleton.\n");
    }

public:
    static MySingleton* getInstance();
};

std::mutex MySingleton::lock;
MySingleton *MySingleton::pInstance = NULL;

/*
 * lazy loading, thread-safe.
 */
MySingleton* MySingleton::getInstance() {
    if (pInstance == NULL) {
        lock.lock();
        if (pInstance == NULL) {
            pInstance = new MySingleton();
        }
        lock.unlock();
    }
    return pInstance;
}

int main() {
    MySingleton *instance = MySingleton::getInstance();
    return 0;
}

