//
//  jsb_agoraCreator.hpp
//  zhangtao@agora.io
//
//  Created by 张涛 on 2019/12/30.
//

#ifndef jsb_agoraCreator_hpp
#define jsb_agoraCreator_hpp
#pragma once
#include "include_file.h"
#include "AGContext.hpp"
#include "AGRtcEngineEventHandler.hpp"

extern "C"
{
    static se::Object* js_cocos2dx_agoraCreator_prototype = NULL;
    static se::Class* js_cocos2dx_agoraCreator_class = NULL;
    static agora::cocos::AGContext* _context = NULL;
    
    bool js_register_cocos2dx_extension_agoraCreator(se::Object* obj);
    bool register_jsb_agoraCreator(se::Object* obj);
}
#endif /* jsb_agoraCreator_hpp */
