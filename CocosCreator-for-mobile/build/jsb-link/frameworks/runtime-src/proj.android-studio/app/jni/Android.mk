LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#============== agora creator include so ====================
LOCAL_MODULE := agora-rtc
LOCAL_SRC_FILES := $(LOCAL_PATH)/agoraEngine/$(TARGET_ARCH_ABI)/libagora-rtc-sdk-jni.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/agoraEngine/include
include $(PREBUILT_SHARED_LIBRARY)
#============== agora creator include so ====================

#============== agora creator include libyuv so ====================
include $(CLEAR_VARS)
LOCAL_MODULE := libyuv
LOCAL_SRC_FILES := $(LOCAL_PATH)/libyuv/$(TARGET_ARCH_ABI)/libyuv.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/libyuv/include
include $(PREBUILT_SHARED_LIBRARY)
#============== agora creator include libyuv so ====================

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := hellojavascript/main.cpp \
				   ../../../Classes/AppDelegate.cpp \
				   ../../../Classes/jsb_module_register.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

LOCAL_LDLIBS := -llog -landroid -lGLESv2 -lEGL

#========== agora creator js bridge===========
LOCAL_SRC_FILES += ../../../Classes/agoraEngine/AgoraManager.cpp \
        ../../../Classes/agoraEngine/jsb_agoraCreator.cpp \
        ../../../Classes/agoraEngine/CacheVideoFrame.cpp \
        ../../../Classes/agoraEngine/MyVideoRawDataControl.cpp \
        ../../../Classes/agoraEngine/OpenGLES2Render.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/agoraEngine \
        $(LOCAL_PATH)/agoraEngine/include
LOCAL_SHARED_LIBRARIES := agora-rtc libyuv
#========== agora creator js bridge===========
        
LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)
