LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := kodoc
LOCAL_SRC_FILES := lib/$(TARGET_ARCH_ABI)/libkodoc_static.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := fifi
LOCAL_SRC_FILES := lib/$(TARGET_ARCH_ABI)/libfifi.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cpuid
LOCAL_SRC_FILES := lib/$(TARGET_ARCH_ABI)/libcpuid.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE    := android_test
LOCAL_CPPFLAGS   += -std=c++0x
LOCAL_SRC_FILES := com_steinwurf_dummy_android_MainActivity.cpp
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_STATIC_LIBRARIES := kodoc fifi cpuid
include $(BUILD_SHARED_LIBRARY)