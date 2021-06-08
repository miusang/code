// FIXME: your file license if you have one

#define LOG_TAG "demoHalService"
#include <log/log.h>
#include "Demo.h"

#include <android/hidl/allocator/1.0/IAllocator.h>
#include <hidlmemory/mapping.h>
namespace atom {
namespace hardware {
namespace demo {
namespace V1_0 {
namespace implementation {
using ::android::hidl::allocator::V1_0::IAllocator;
using ::android::hidl::memory::V1_0::IMemory;

Demo::Demo() {
    sp<IAllocator> allocator = IAllocator::getService("ashmem");
    allocator->allocate(2048, [&](bool success, const hidl_memory& mem)
    {
        if (!success) { /* error */ }
        block.mem = mem;
        sp<IMemory> memory = mapMemory(mem);
        uint8_t* data = static_cast<uint8_t*>(static_cast<void*>(memory->getPointer()));
    ///uint8_t* data = static_cast<uint8_t*>(memory->getPointer());
       memory->update();
        data[50] = 10;
        memory->commit();
    });
}

// Methods from ::atom::hardware::demo::V1_0::IDemo follow.
Return<int32_t> Demo::test() {
    ALOGD("server run test");
    // TODO implement
    return int32_t {};
}

Return<void> Demo::getMem(getMem_cb _hidl_cb) {
    // TODO implement
    _hidl_cb(block);
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//IDemo* HIDL_FETCH_IDemo(const char* /* name */) {
    //return new Demo();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace demo
}  // namespace hardware
}  // namespace atom
