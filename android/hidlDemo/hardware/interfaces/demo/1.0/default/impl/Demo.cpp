// FIXME: your file license if you have one

#define LOG_TAG "demoHalService"
#include <log/log.h>
#include "Demo.h"

namespace atom {
namespace hardware {
namespace demo {
namespace V1_0 {
namespace implementation {

// Methods from ::atom::hardware::demo::V1_0::IDemo follow.
Return<int32_t> Demo::test() {
    ALOGD("server run test");
    // TODO implement
    return int32_t {};
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
