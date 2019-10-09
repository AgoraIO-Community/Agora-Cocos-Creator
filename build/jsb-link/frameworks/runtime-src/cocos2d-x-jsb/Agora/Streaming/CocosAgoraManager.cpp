//
//  CocosAgoraManager.cpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 20/12/2017.
//

#include <string>

#include "CocosAgoraManager.h"
#include "cocos2d.h"

using namespace std;

NS_AGORA_BEGIN

static CocosAgoraManager *s_SharedCocosAgoraManager = nullptr;

CocosAgoraManager* CocosAgoraManager::getInstance()
{
    if (!s_SharedCocosAgoraManager)
    {
        s_SharedCocosAgoraManager = new (std::nothrow) CocosAgoraManager;
    }
    
    return s_SharedCocosAgoraManager;
}

CocosAgoraManager::CocosAgoraManager() {
    _chatRoom = NULL;
}

void CocosAgoraManager::setChatRoom(HomeAgora *chatRoom)
{
    _chatRoom = chatRoom;
}

void CocosAgoraManager::localJoinCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->localJoinCallback(res);
    }
}

void CocosAgoraManager::localLeaveCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->localLeaveCallback(res);
    }
}

void CocosAgoraManager::muteLocalAudioCallback(string res) {
    if (_chatRoom != NULL) {
        _chatRoom->muteLocalAudioCallback(res);
    }
}

void CocosAgoraManager::unmuteLocalAudioCallback(string res) {
    if (_chatRoom != NULL) {
        _chatRoom->unmuteLocalAudioCallback(res);
    }
}

void CocosAgoraManager::muteLocalVideoCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->muteLocalVideoCallback(res);
    }
}

void CocosAgoraManager::unmuteLocalVideoCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->unmuteLocalVideoCallback(res);
    }
}

void CocosAgoraManager::muteRemoteVideoCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->muteRemoteVideoCallback(res);
    }
}

void CocosAgoraManager::unmuteRemoteVideoCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->unmuteRemoteVideoCallback(res);
    }
}

void CocosAgoraManager::muteRemoteAudioCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->muteRemoteAudioCallback(res);
    }
}

void CocosAgoraManager::unmuteRemoteAudioCallback(string res)
{
    if (_chatRoom != NULL) {
        _chatRoom->unmuteRemoteAudioCallback(res);
    }
}

void CocosAgoraManager::remoteLeaveCallback(unsigned int uid)
{
    if (_chatRoom != NULL) {
        _chatRoom->remoteLeaveCallback(uid);
    }
}

void CocosAgoraManager::remoteJoinCallback(unsigned int uid)
{
    if (_chatRoom != NULL) {
        _chatRoom->remoteJoinCallback(uid);
    }
}

void CocosAgoraManager::updateFrame(unsigned int uid, void *rgbaBuffer, int rgbsStride, ssize_t dataLen, int width, int height, int rotation)
{
    if (_chatRoom != NULL) {
        _chatRoom->updateFrame(uid, rgbaBuffer, dataLen, width, height);
    }
}

cocos2d::Size CocosAgoraManager::getTextureSize(unsigned int uid)
{
    if (_chatRoom != NULL) {
        return _chatRoom->getTextureSize(uid);
    }
    return cocos2d::Size(0, 0);
}

void CocosAgoraManager::updateAudioLevel(unsigned int uid, unsigned int audioLevel)
{
    if (_chatRoom != NULL) {
        return _chatRoom->updateAudioLevel(uid, audioLevel);
    }
}

void CocosAgoraManager::updateRtcStats(unsigned int duration,
                                       unsigned int txBytes,
                                       unsigned int rxBytes,
                                       unsigned int txAudioKBitrate,
                                       unsigned int rxAudioKBitrate,
                                       unsigned int txVideoKBitrate,
                                       unsigned int rxVideoKBitrate,
                                       unsigned int userCount,
                                       double cpuAppUsage,
                                       double cpuTotalUsage)
{
    if (_chatRoom != NULL) {
        _chatRoom->updateRtcStats(duration,
                                  txBytes,
                                  rxBytes,
                                  txAudioKBitrate,
                                  rxAudioKBitrate,
                                  txVideoKBitrate,
                                  rxVideoKBitrate,
                                  userCount,
                                  cpuAppUsage,
                                  cpuTotalUsage);
    }
}

void CocosAgoraManager::updateLocalVideoStats(unsigned int sentBitrate,
                                              unsigned int sentFrameRate) {
    if (_chatRoom != NULL) {
        _chatRoom->updateLocalVideoStats(sentBitrate,
                                         sentFrameRate);
    }
}

void CocosAgoraManager::updateClientStats(unsigned int uid,
                                          unsigned int width,
                                          unsigned int height,
                                          unsigned int receivedBitrate,
                                          unsigned int receivedFrameRate) {
    if (_chatRoom != NULL) {
        _chatRoom->updateClientStats(uid,
                                     width,
                                     height,
                                     receivedBitrate,
                                     receivedFrameRate);
    }
}

void CocosAgoraManager::updateNetworkQuality(unsigned int uid,
                                             unsigned int txquality,
                                             unsigned int rxquality) {
    if (_chatRoom != NULL) {
        _chatRoom->updateNetworkQuality(uid,
                                        txquality,
                                        rxquality);
    }
}

NS_AGORA_END
