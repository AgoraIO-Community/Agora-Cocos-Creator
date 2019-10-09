//
//  OCHomeAgora.m
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/1/16.
//

#import "OCHomeAgora.h"
#import <Foundation/Foundation.h>
#import "AgoraManager.h"

NS_AGORA_BEGIN

void objcHAJoin(std::string appId,
                std::string channelName,
                unsigned int uid,
                std::string videoProfile,
                unsigned int channelProfile,
                unsigned int clientRole,
                unsigned int agora) {
    NSString *ocAppId = [NSString stringWithCString:appId.c_str() encoding:NSUTF8StringEncoding];
    NSString *ocChannelName = [NSString stringWithCString:channelName.c_str() encoding:NSUTF8StringEncoding];
    NSString *ocVideoProfile = [NSString stringWithCString:videoProfile.c_str() encoding:NSUTF8StringEncoding];

    [[AgoraManager share] loadAgoraKitByChannelByAppId:ocAppId
                                                       channelName:ocChannelName
                                                               uid:uid
                                                      videoProfile:ocVideoProfile
                                                    channelProfile:channelProfile
                                                        clientRole:clientRole
                                                agora:agora];
}

void objcHALeave() {
    [[AgoraManager share] leaveChannel];
}

void objcHAMuteLocalAudio() {
    [[AgoraManager share] muteLocalAudio];
}

void objcHAUnmuteLocalAudio() {
    [[AgoraManager share] unmuteLocalAudio];
}

void objcHAMuteLocalVideo() {
    [[AgoraManager share] muteLocalVideo];
}

void objcHAUnmuteLocalVideo() {
    [[AgoraManager share] unmuteLocalVideo];
}

void objcHAMuteRemoteVideo(unsigned int uid) {
    [[AgoraManager share] muteRemoteVideo:uid];
}

void objcHAUnmuteRemoteVideo(unsigned int uid) {
    [[AgoraManager share] unmuteRemoteVideo:uid];
}

void objcHAMuteRemoteAudio(unsigned int uid) {
    [[AgoraManager share] muteRemoteAudio:uid];
}

void objcHAUnmuteRemoteAudio(unsigned int uid) {
    [[AgoraManager share] unmuteRemoteAudio:uid];
}

NS_AGORA_END
