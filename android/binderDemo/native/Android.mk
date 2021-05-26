LOCAL_PATH := $(call my-dir)

##################################
#         server
################################
include $(CLEAR_VARS)
LOCAL_MODULE := binderServer
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
	main_server.cpp \
	DemoServer.cpp \
	IDemo.cpp
	
LOCAL_SHARED_LIBRARIES := \
	libcutils\
	liblog\
	libbinder \
	libutils
include $(BUILD_EXECUTABLE)

###################################
#          client
#####################################
include $(CLEAR_VARS)
LOCAL_MODULE := binderClient
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
	main_client.cpp \
	IDemo.cpp
	
LOCAL_SHARED_LIBRARIES := \
	libcutils\
	liblog\
	libbinder \
	libutils
include $(BUILD_EXECUTABLE)
