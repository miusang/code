#include "IDemo.h"

#include <binder/Parcel.h>

#include <cutils/log.h>
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "BinderDemo"

IMPLEMENT_META_INTERFACE(Demo, "android.demo.IDemo"); 
status_t BnDemo::onTransact(uint32_t code, const Parcel& data, Parcel* reply,
            uint32_t flags) {
    switch (code) {
    case TEST:
        test();
        reply->writeInt32(1);
        break;
    defalut:
        break;
     }
    return NO_ERROR;
}

BnDemo::BnDemo() {
}

BnDemo::~BnDemo() {
}

void BnDemo::test() {
    ALOGD("server %s line%d", __func__, __LINE__);
}

BpDemo::BpDemo(const sp<IBinder>& impl):BpInterface<IDemo>(impl) {
}

BpDemo::~BpDemo() {
}

void BpDemo::test() {
    ALOGD("client BpDemo %s line:%d", __func__, __LINE__);
    Parcel data, reply;
    data.writeInterfaceToken(IDemo::getInterfaceDescriptor());
    remote()->transact(TEST, data, &reply);
    ALOGD("client BpDemo recv res: %d", reply.readInt32());
}
