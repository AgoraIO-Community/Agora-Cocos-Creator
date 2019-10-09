//
//  CocosAgoraManager.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 20/12/2017.
//

#ifndef CocosAgoraManager_hpp
#define CocosAgoraManager_hpp

#include <stdio.h>
#include "HomeAgora.hpp"
#include "PlatformMacros.h"

USING_NS_AGORA;

NS_AGORA_BEGIN

class CocosAgoraManager
{
public:
    static CocosAgoraManager* getInstance();
    
    void setChatRoom(HomeAgora *chatRoom);
    void localJoinCallback(string res);
    void localLeaveCallback(string res);
    void muteLocalAudioCallback(string res);
    void unmuteLocalAudioCallback(string res);
    void muteLocalVideoCallback(string res);
    void unmuteLocalVideoCallback(string res);
    void muteRemoteVideoCallback(string res);
    void unmuteRemoteVideoCallback(string res);
    void muteRemoteAudioCallback(string res);
    void unmuteRemoteAudioCallback(string res);
    void remoteJoinCallback(unsigned int uid);
    void remoteLeaveCallback(unsigned int uid);
    void updateFrame(unsigned int uid, void *rgbaBuffer, int rgbsStride, ssize_t dataLen, int width, int height, int rotation);
    cocos2d::Size getTextureSize(unsigned int uid);
    void updateAudioLevel(unsigned int uid, unsigned int audioLevel);
    void updateRtcStats(unsigned int duration,
                        unsigned int txBytes,
                        unsigned int rxBytes,
                        unsigned int txAudioKBitrate,
                        unsigned int rxAudioKBitrate,
                        unsigned int txVideoKBitrate,
                        unsigned int rxVideoKBitrate,
                        unsigned int userCount,
                        double cpuAppUsage,
                        double cpuTotalUsage);
    void updateLocalVideoStats(unsigned int sentBitrate,
                               unsigned int sentFrameRate);
    void updateClientStats(unsigned int uid,
                           unsigned int width,
                           unsigned int height,
                           unsigned int receivedBitrate,
                           unsigned int receivedFrameRate);
    void updateNetworkQuality(unsigned int uid,
                              unsigned int txquality,
                              unsigned int rxquality);
private:
    CocosAgoraManager();
    HomeAgora *_chatRoom;
};

NS_AGORA_END
#endif /* CocosAgoraManager_hpp */
