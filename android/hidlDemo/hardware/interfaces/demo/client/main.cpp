#define LOG_TAG "demoClient"
#include <atom/hardware/demo/1.0/IDemo.h>
#include <hidlmemory/mapping.h>
#include <log/log.h>

using ::android::hidl::memory::V1_0::IMemory; 

using atom::hardware::demo::V1_0::IDemo;
using atom::hardware::demo::V1_0::MemoryBlock;
using android::sp;


int main(){
    sp<IDemo> service = IDemo::getService();
    if( service == nullptr ){
        ALOGE("Can't find demo service...");
        return -1;
    }
    ALOGD("client test");
    service->test();
    service->getMem([](MemoryBlock block) {
        sp<IMemory> memory = mapMemory(block.mem);
        uint8_t* data = static_cast<uint8_t*>(static_cast<void*>(memory->getPointer()));
        ALOGD("data:%d", data[50]);
    });
    return 0;
}
