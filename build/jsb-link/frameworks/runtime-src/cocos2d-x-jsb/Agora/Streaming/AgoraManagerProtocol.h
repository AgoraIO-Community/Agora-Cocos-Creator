//
//  AgoraManagerProtocol.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 05/03/2018.
//

#import <Foundation/Foundation.h>

@protocol AgoraManagerProtocol <NSObject>

- (void)loadAgoraKitByChannelByAppId:(NSString *)appId
                         channelName:(NSString *)channelName
                                 uid:(unsigned int)uid
                        videoProfile:(NSString *)videoProfile
                      channelProfile:(int)channelProfile
                          clientRole:(int)clientRole
                               agora:(int)agora;

- (int)rtcJoinChannel;

- (void)leaveChannel;

- (void)rtcLeaveChannel;

- (void)muteLocalAudio;

- (void)unmuteLocalAudio;

- (void)muteLocalVideo;

- (void)unmuteLocalVideo;

- (void)closeAudio;

- (void)muteRemoteVideo:(unsigned int)uid;

- (void)unmuteRemoteVideo:(unsigned int)uid;

- (void)muteRemoteAudio:(unsigned int)uid;

- (void)unmuteRemoteAudio:(unsigned int)uid;

- (void)setEnableSpeakerphone:(BOOL)enableSpeaker;

- (void)nitificationWithUid:(unsigned int)uid
                 rgbaBuffer:(void *)rgbaBuffer
                 rgbaStride:(int)rgbaStride
                    dataLen:(ssize_t )dataLen
                      width:(int)width
                     height:(int)height
                   rotation:(int)rotation;

- (unsigned int)localUid;

- (CGSize)getTextureSize:(unsigned int)uid;

- (NSString *)getLogFilePath;

@end
