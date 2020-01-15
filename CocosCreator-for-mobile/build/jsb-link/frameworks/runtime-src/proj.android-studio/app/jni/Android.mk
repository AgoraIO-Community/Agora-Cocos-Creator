LOCAL_PATH := $(call my-dir)

#============== agora creator include so ====================
include $(CLEAR_VARS)
LOCAL_MODULE := agora-rtc
LOCAL_SRC_FILES := $(LOCAL_PATH)/agora/$(TARGET_ARCH_ABI)/libagora-rtc-sdk-jni.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/agora/include
include $(PREBUILT_SHARED_LIBRARY)
#============== agora creator include so ====================

#============== agora creator include libyuv so ====================
include $(CLEAR_VARS)
LOCAL_MODULE := libyuv
LOCAL_SRC_FILES := $(LOCAL_PATH)/libyuv/$(TARGET_ARCH_ABI)/libyuv.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/libyuv/include
include $(PREBUILT_SHARED_LIBRARY)
#============== agora creator include libyuv so ====================

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

#============== agora creator js bridge ====================
LOCAL_SRC_FILES = ../../../Classes/agora/jsb_agoraCreator.cpp \
                   ../../../Classes/agora/AGRtcEngineEventHandler.cpp \
                   ../../../Classes/agora/AGContext.cpp \
                   ../../../Classes/agora/videoStream/AGVideoRawDataControl.cpp \
                   ../../../Classes/agora/videoStream/CacheVideoFrame.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/agora/include
#============== agora creator js bridge ====================

LOCAL_SRC_FILES += hellojavascript/main.cpp \
				   ../../../Classes/AppDelegate.cpp \
				   ../../../Classes/jsb_module_register.cpp \

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes

ifeq ($(USE_ANY_SDK),1)
LOCAL_SRC_FILES += ../../../Classes/anysdk/SDKManager.cpp \
				   ../../../Classes/anysdk/jsb_anysdk_basic_conversions.cpp \
				   ../../../Classes/anysdk/manualanysdkbindings.cpp \
				   ../../../Classes/anysdk/jsb_anysdk_protocols_auto.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/anysdk

LOCAL_WHOLE_STATIC_LIBRARIES := PluginProtocolStatic
endif

#============== agora creator include shared libraries ====================
LOCAL_SHARED_LIBRARIES := agora-rtc libyuv
#============== agora creator include shared libraries ====================

LOCAL_STATIC_LIBRARIES := cocos2d_js_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module, scripting/js-bindings/proj.android)
