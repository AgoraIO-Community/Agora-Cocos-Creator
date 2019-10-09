//
//  OCHomeAgora.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/1/16.
//

#include <stdio.h>
#include <string>
#include "PlatformMacros.h"

NS_AGORA_BEGIN

void objcHAJoin(std::string appId,
                std::string channelName,
                unsigned int uid,
                std::string videoProfile,
                unsigned int channelProfile,
                unsigned int clientRole,
                unsigned int agora);
void objcHALeave();
void objcHAMuteLocalAudio();
void objcHAUnmuteLocalAudio();

void objcHAMuteLocalVideo();
void objcHAUnmuteLocalVideo();

void objcHAMuteRemoteVideo(unsigned int uid);
void objcHAUnmuteRemoteVideo(unsigned int uid);

void objcHAMuteRemoteAudio(unsigned int uid);
void objcHAUnmuteRemoteAudio(unsigned int uid);

NS_AGORA_END


