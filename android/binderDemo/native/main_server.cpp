
#include "DemoServer.h"

#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <cutils/log.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "BinderDemoServer"
using namespace android;
int main(int argc, char **argv) {
    ALOGD("server start...");
    sp <IServiceManager> sm = defaultServiceManager();
    DemoServer *server = new DemoServer();
    sm->addService(String16("service.binderDemoService"), server);
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    ALOGD("server end...");
    return 0;
}
