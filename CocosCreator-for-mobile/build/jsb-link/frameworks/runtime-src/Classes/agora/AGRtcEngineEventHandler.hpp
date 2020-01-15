//
//  AGRtcEngineEventHandler.hpp
//  zhangtao@agora.io
//
//  Created by 张涛 on 2019/12/31.
//

#ifndef AGRtcEngineEventHandler_hpp
#define AGRtcEngineEventHandler_hpp

#include "include_file.h"
#include "AGContext.hpp"

namespace agora
{
    namespace cocos
    {
        class AGRtcEngineEventHandler : public agora::rtc::IRtcEngineEventHandler
        {
        private:
            AGContext* _context;
            
        public:
            AGRtcEngineEventHandler(AGContext* context);
            ~AGRtcEngineEventHandler();
            
            virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
            
            virtual void onUserJoined(uid_t uid, int elapsed);
            
            virtual void onUserOffline(uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason);
            
            virtual void onLeaveChannel(const agora::rtc::RtcStats& stats);
        };
    }
}
#endif /* AGRtcEngineEventHandler_hpp */

