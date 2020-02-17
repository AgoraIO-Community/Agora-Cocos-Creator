//
//  jsb_agoraCreator.h
//
//  Created by zhangtao@agora.io on 2020/2/11.


#ifndef jsb_Agora_h
#define jsb_Agora_h

#pragma once
#include "base/ccConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "MyVideoRawDataControl.h"

extern se::Object *js_cocos2dx_agoraCreator_prototype;
extern se::Class *js_cocos2dx_agoraCreator_class;

bool js_register_cocos2dx_extension_agoraCreator(se::Object* obj);
bool register_jsb_agoraCreator(se::Object* obj);

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#endif /* jsb_Agora_h */



