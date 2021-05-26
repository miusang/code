#ifndef _DEMO_H_
#define _DEMO_H_
#include <binder/IInterface.h>

using namespace android;
class IDemo : public IInterface {
public:
    DECLARE_META_INTERFACE(Demo);
    virtual void test() = 0;
    enum {
        TEST = 0,
    };
};

class BnDemo : public BnInterface<IDemo> {
public:
    BnDemo();
    status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
    virtual void test();
    ~BnDemo();
};

class BpDemo : public BpInterface<IDemo> {
public:
    BpDemo(const sp<IBinder>& impl);
    virtual void test();
    ~BpDemo();
};
#endif
