#define LOG_TAG "demoClient"
#include <atom/hardware/demo/1.0/IDemo.h>
#include <log/log.h>

using atom::hardware::demo::V1_0::IDemo;
using android::sp;


int main(){
    sp<IDemo> service = IDemo::getService();
    if( service == nullptr ){
        ALOGE("Can't find demo service...");
        return -1;
    }
    ALOGD("client test");
    service->test();
    return 0;
}
