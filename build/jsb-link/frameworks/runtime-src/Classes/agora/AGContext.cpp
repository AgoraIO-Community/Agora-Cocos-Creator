//
//  AGContext.cpp
//  zhangtao@agora.io
//
//  Created by 张涛 on 2019/12/31.
//

#include "AGContext.hpp"

namespace agora
{
    namespace cocos
    {
        AGContext::AGContext():_rtcEngine(NULL),_refObj(NULL),_videoRawDataControl(NULL),_rtcEngineEventHandler(NULL)
        {
            
        }
        
        AGContext::~AGContext()
        {
            if (_videoRawDataControl)
            {
                CCLOG("%s AGContext::~AGContext ", AGORA_TAG);
                delete _videoRawDataControl;
                _videoRawDataControl = NULL;
            }
            
            if (_rtcEngineEventHandler)
            {
                delete _rtcEngineEventHandler;
                _rtcEngineEventHandler = NULL;
            }
        }
    }
}
