//
//  AGContext.hpp
//  zhangtao@agora.io
//
//  Created by 张涛 on 2019/12/31.
//

#ifndef AgoraContext_hpp
#define AgoraContext_hpp
#include "include_file.h"
#include "videoStream/AGVideoRawDataControl.h"

namespace agora
{
    namespace cocos
    {
        class AGContext
        {
        public:
            agora::rtc::IRtcEngine* _rtcEngine;
            se::Object* _refObj;
            agora::cocos::AGVideoRawDataControl* _videoRawDataControl;
            agora::rtc::IRtcEngineEventHandler* _rtcEngineEventHandler;
            
            AGContext();
            ~AGContext();
        };
    }
}
#endif /* AGContext_hpp */
