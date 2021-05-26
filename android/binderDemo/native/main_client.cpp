#include "IDemo.h"

#include <binder/IServiceManager.h>
#include <cutils/log.h>
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "BinderDemoClient"

using namespace android;
int main(int argc, char **argv) {
    sp <IServiceManager> sm = defaultServiceManager();
    sp <IBinder> binder = sm->getService(String16("service.binderDemoService"));
    sp <IDemo> cs = interface_cast<IDemo>(binder);
    cs->test();
    return 0;
}
