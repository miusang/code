#include "DemoServer.h"

#include <cutils/log.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "BinderDemoServer"
void DemoServer::test() {
    ALOGD("DemoServer process :%s", __func__);
}
