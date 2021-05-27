LOCAL_PATH:= $(call my-dir)

#=======================================================
#            server
#======================================================
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	com/atom/binderdemo/IDemo.aidl \
	com/atom/binderdemo/DemoService.java \
	com/atom/binderdemo/DemoServer.java
LOCAL_MODULE := binderServer
include $(BUILD_JAVA_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := binderServer
LOCAL_MODULE := binderServer
LOCAL_MODULE_CLASS := EXECUTABLES
include $(BUILD_PREBUILT)


#=======================================================
#           client
#======================================================
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	com/atom/binderdemo/IDemo.aidl \
	com/atom/binderdemo/DemoClient.java
LOCAL_MODULE := binderClient
include $(BUILD_JAVA_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := binderClient
LOCAL_MODULE := binderClient
LOCAL_MODULE_CLASS := EXECUTABLES
include $(BUILD_PREBUILT)
