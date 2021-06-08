// FIXME: your file license if you have one

#pragma once

#include <atom/hardware/demo/1.0/IDemo.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace atom {
namespace hardware {
namespace demo {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

class Demo : public IDemo {
public:
    Demo();
    // Methods from ::atom::hardware::demo::V1_0::IDemo follow.
    Return<int32_t> test() override;
    Return<void> getMem(getMem_cb _hidl_cb) override;
    MemoryBlock block;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IDemo* HIDL_FETCH_IDemo(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace demo
}  // namespace hardware
}  // namespace atom
