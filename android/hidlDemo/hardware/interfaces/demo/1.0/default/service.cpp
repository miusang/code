
#include "impl/Demo.h"
#include <atom/hardware/demo/1.0/IDemo.h>
#include <hidl/HidlTransportSupport.h>
#include <log/log.h>
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "halDemoService"

using namespace android;
using namespace atom::hardware::demo::V1_0::implementation;

int main() {
    ALOGD("service start...");
    android::hardware::configureRpcThreadpool(8, true /* callerWillJoin */);
    sp<Demo> demo = new Demo();
    status_t status = demo->registerAsService();
    if (status != OK) {
        ALOGE("Unable to register log service (%d)", status);
        return -1;
    }
    android::hardware::joinRpcThreadpool();
    return 0;
}
