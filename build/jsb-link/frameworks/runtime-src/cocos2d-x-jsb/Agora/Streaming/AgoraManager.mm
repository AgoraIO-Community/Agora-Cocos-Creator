//
//  AgoraManager.m
//  Agora-iOS-Cocos
//
//  Created by Agora on 20/12/2017.
//

#import "AgoraManager.h"
#import "platform/ios/CCEAGLView-ios.h"
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>
#import "AGVideoProcessing.h"
#import "JSBCallbackResponse.h"

#include "CocosAgoraManager.h"
#include "audio/include/AudioEngine.h"
#include "cocos2d.h"
#import "audio/apple/AudioEngineManager.h"
#include "VideoProfile.hpp"

@interface AgoraManager () <AgoraRtcEngineDelegate> {
    AgoraRtcEngineKit *_rtcEngine;
    unsigned int _localUid;
    unsigned int _uid;
    NSString *_channelName;
    dispatch_queue_t _agoraManagerqueue;
}
@end

@implementation AgoraManager

+ (instancetype)share
{
    static AgoraManager *share = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        share = [[AgoraManager alloc] init];
    });
    return share;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _agoraManagerqueue = dispatch_queue_create("cn.agora.AgoraManager", NULL);
    }
    return self;
}

- (void)loadAgoraKitByChannelByAppId:(NSString *)appId
                         channelName:(NSString *)channelName
                                 uid:(unsigned int)uid
                        videoProfile:(NSString *)videoProfile
                      channelProfile:(int)channelProfile
                          clientRole:(int)clientRole
                          agora:(int)agora;

{
    dispatch_sync(_agoraManagerqueue, ^{
        _rtcEngine = [AgoraRtcEngineKit sharedEngineWithAppId:appId
                                                    delegate:self];
        [[AudioEngineManager shareAudioEngineManager] setAudioEngineManagerProtocol:(id<AudioEngineManagerProtocol>)self];
        [[AudioEngineManager shareAudioEngineManager] setAgora:agora];
        [_rtcEngine setParameters:@"{\"che.audio.keep.audiosession\":true}"];//通话断开的时候会恢复到进入之前的category
        [_rtcEngine setParameters:@"{\"che.audio.enable.aec\": true}"];//软件回声消除
        [_rtcEngine setParameters:@"{\"rtc.force_unified_communication_mode\": true}"];//手动打开通信模式下的优化模式
        [_rtcEngine setParameters:@"{\"che.video.moreFecSchemeEnable\":true}"];
        AgoraChannelProfile cp = [self getChannelProfile:channelProfile];
        [_rtcEngine setChannelProfile:cp];//设置房间模式
        if (cp == AgoraChannelProfileLiveBroadcasting) {
            [_rtcEngine setClientRole:[self getClientRole:clientRole]];//设置直播场景里的用户角色
        }
        [_rtcEngine setVideoQualityParameters:YES];//保证流畅度优先
        [_rtcEngine setMixedAudioFrameParametersWithSampleRate:441000
                                                samplesPerCall:1024];//设置音频
        [_rtcEngine enableAudio];//开启音频
        [_rtcEngine enableVideo];//开启视频
        agora::VideoProfile vp = agora::VideoProfile::createVideoProfile([videoProfile cStringUsingEncoding: NSUTF8StringEncoding]);
        AgoraVideoEncoderConfiguration *avc = [[AgoraVideoEncoderConfiguration alloc] initWithWidth:vp.width height:vp.height frameRate:(AgoraVideoFrameRate)vp.frameRate bitrate:0 orientationMode:AgoraVideoOutputOrientationModeFixedLandscape];
        [_rtcEngine setVideoEncoderConfiguration:avc];
        [_rtcEngine setAudioProfile:AgoraAudioProfileDefault
                        scenario:(AgoraAudioScenarioEducation)];//设置音频模式
        [_rtcEngine adjustRecordingSignalVolume:200];//设置录入声音
        [_rtcEngine enableAudioVolumeIndication:500 smooth:3];//设置音量大小回调，500毫秒，平滑系数默认3
        [_rtcEngine enableWebSdkInteroperability:YES];//设置web互通
        [_rtcEngine enableDualStreamMode:NO];
        [_rtcEngine setRemoteDefaultVideoStreamType:AgoraVideoStreamTypeHigh];
        [_rtcEngine setDefaultMuteAllRemoteAudioStreams:YES];
        [_rtcEngine setDefaultMuteAllRemoteVideoStreams:YES];
        _uid = uid;
        _channelName = channelName;
        int code = [self rtcJoinChannel];
        if (code == 0) {
            [_rtcEngine setEnableSpeakerphone:YES];
            [AGVideoProcessing registerVideoPreprocessing:_rtcEngine];
        }
    });
}

- (AgoraChannelProfile)getChannelProfile:(int)channelProfile
{
    AgoraChannelProfile res;
    switch (channelProfile) {
        case 0: {
            res = AgoraChannelProfileCommunication;
        }
            break;
        case 1: {
            res = AgoraChannelProfileLiveBroadcasting;
        }
            break;
        case 2: {
            res = AgoraChannelProfileGame;
        }
            break;
        default: {
            res = AgoraChannelProfileLiveBroadcasting;
        }
            break;
    }
    return res;
}

- (AgoraClientRole)getClientRole:(int)clientRole
{
    AgoraClientRole res;
    switch (clientRole) {
        case 1: {
            res = AgoraClientRoleBroadcaster;
        }
            break;
        case 2: {
            res = AgoraClientRoleAudience;
        }
            break;
        default: {
            res = AgoraClientRoleBroadcaster;
        }
            break;
    }
    return res;
}

- (int)rtcJoinChannel {
    [self resetAVAudioSessionCategory];
    int code = [_rtcEngine joinChannelByToken:nil
                                    channelId:_channelName
                                         info:nil
                                          uid:_uid
                                  joinSuccess:nil];//加入房间
    return code;
}

- (void)rtcLeaveChannel {
//    [self resetAVAudioSessionCategory];
    [_rtcEngine leaveChannel:nil];
}

- (void)resetAVAudioSessionCategory {
    NSError *error = nil;
    BOOL success = [[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error: &error];
    if (!success) {

    } else {
        [[AVAudioSession sharedInstance] setActive:YES error:&error];
    }
}

- (void)leaveChannel {
    dispatch_sync(_agoraManagerqueue, ^{
        [self rtcLeaveChannel];
        [AGVideoProcessing deregisterVideoPreprocessing:_rtcEngine];
        //该方法需要在子线程中操作
        //该方法为同步调用。 App 不得在 SDK 生成的回调中调用该方法，不然 SDK 只能等候该回调返回才能重新获取相应的对象资源造成死锁。
        [AgoraRtcEngineKit destroy];
        _rtcEngine = nil;
        [[AudioEngineManager shareAudioEngineManager] setAudioEngineManagerProtocol:(id<AudioEngineManagerProtocol>)nil];
        _localUid = 0;
    });
}

- (void)muteLocalAudio
{
    int res = [_rtcEngine muteLocalAudioStream:YES];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed message:@"成功" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteLocalAudioCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail message:@"失败" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteLocalAudioCallback(str);
    }
}

- (void)unmuteLocalAudio
{
    int res = [_rtcEngine muteLocalAudioStream:NO];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed message:@"成功" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteLocalAudioCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail message:@"失败" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteLocalAudioCallback(str);
    }
}

- (void)muteLocalVideo
{
    int res = [_rtcEngine muteLocalVideoStream:YES];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed message:@"成功" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteLocalVideoCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail message:@"失败" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteLocalVideoCallback(str);
    }
}

- (void)unmuteLocalVideo
{
    int res = [_rtcEngine muteLocalVideoStream:NO];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed message:@"成功" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteLocalVideoCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail message:@"失败" data:nil];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteLocalVideoCallback(str);
    }
}

- (void)closeAudio
{
    [_rtcEngine disableAudio];
    [_rtcEngine disableVideo];
}

- (void)muteRemoteVideo:(unsigned int)uid
{
    int res = [_rtcEngine muteRemoteVideoStream:uid mute:YES];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                     message:@"成功"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteRemoteVideoCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail
                                                                     message:@"失败"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteRemoteVideoCallback(str);
    }
}

- (void)unmuteRemoteVideo:(unsigned int)uid
{
    int res = [_rtcEngine muteRemoteVideoStream:uid mute:NO];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                     message:@"成功"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteRemoteVideoCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail
                                                                     message:@"失败"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteRemoteVideoCallback(str);
    }
}

- (void)muteRemoteAudio:(unsigned int)uid
{
    int res = [_rtcEngine muteRemoteAudioStream:uid mute:YES];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                     message:@"成功"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteRemoteAudioCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail
                                                                     message:@"失败"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->muteRemoteAudioCallback(str);
    }
}

- (void)unmuteRemoteAudio:(unsigned int)uid
{
    int res = [_rtcEngine muteRemoteAudioStream:uid mute:NO];
    if (res == 0) {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                     message:@"成功"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteRemoteAudioCallback(str);
    } else {
        JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeFail
                                                                     message:@"失败"
                                                                        data:@{
                                                                               @"uid": @(uid)
                                                                               }];
        string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
        CocosAgoraManager::getInstance()->unmuteRemoteAudioCallback(str);
    }
}

- (void)nitificationWithUid:(unsigned int)uid
                  rgbaBuffer:(void *)rgbaBuffer
                 rgbaStride:(int)rgbaStride
                    dataLen:(ssize_t )dataLen
                      width:(int)width
                     height:(int)height
                   rotation:(int)rotation {
    if (uid == 0) {
        uid = _localUid;
    }
    CocosAgoraManager::getInstance()->updateFrame(uid, rgbaBuffer, rgbaStride, dataLen, width, height, rotation);
}

- (CGSize)getTextureSize:(unsigned int)uid {
    cocos2d::Size size = CocosAgoraManager::getInstance()->getTextureSize(uid);
    return CGSizeMake(size.width, size.height);
}

- (unsigned int)localUid
{
    return _localUid;
}

- (void)setEnableSpeakerphone:(BOOL)enableSpeaker
{
    if (_rtcEngine) {
        [_rtcEngine setEnableSpeakerphone:(!enableSpeaker)];
        [_rtcEngine setEnableSpeakerphone:enableSpeaker];
    }
}

#pragma mark - AgoraRtcEngineDelegate
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed
{
    [self setEnableSpeakerphone:YES];
    [_rtcEngine muteLocalAudioStream:NO];
    [_rtcEngine muteLocalVideoStream:NO];
    _localUid = (unsigned int)uid;
    JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                 message:@"成功"
                                                                    data:@{
                                                                           @"uid": @(uid)
                                                                           }];
    string str=[[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
    CocosAgoraManager::getInstance()->localJoinCallback(str);
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed
{
    _localUid = (unsigned int)uid;
    JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                 message:@"成功"
                                                                    data:@{
                                                                           @"uid": @(uid)
                                                                           }];
    string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
    CocosAgoraManager::getInstance()->localJoinCallback(str);
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didLeaveChannelWithStats:(AgoraChannelStats * _Nonnull)stats
{
    _localUid = 0;
    JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                 message:@"成功"
                                                                    data:nil];
    string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
    CocosAgoraManager::getInstance()->localLeaveCallback(str);
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed
{
    [_rtcEngine setRemoteVideoStream:uid type:AgoraVideoStreamTypeHigh];
//    [engine muteRemoteAudioStream:uid mute:YES];
//    [engine muteRemoteVideoStream:uid mute:YES];
    CocosAgoraManager::getInstance()->remoteJoinCallback((unsigned int)uid);
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(AgoraUserOfflineReason)reason
{
    CocosAgoraManager::getInstance()->remoteLeaveCallback((unsigned int)uid);
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSUInteger)uid
{
    JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                 message:@"成功"
                                                                    data:@{
                                                                           @"uid": @(uid)
                                                                           }];
    string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
    if (muted) {
        CocosAgoraManager::getInstance()->muteRemoteAudioCallback(str);
    } else {
        CocosAgoraManager::getInstance()->unmuteRemoteAudioCallback(str);
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid
{
    JSBCallbackResponse *res = [[JSBCallbackResponse alloc] initWithCode:JSBCallbackResponseCodeSucceed
                                                                 message:@"成功"
                                                                    data:@{
                                                                           @"uid": @(uid)
                                                                           }];
    string str = [[res getJsonString] cStringUsingEncoding: NSUTF8StringEncoding];
    if (muted) {
        CocosAgoraManager::getInstance()->muteRemoteVideoCallback(str);
    } else {
        CocosAgoraManager::getInstance()->unmuteRemoteVideoCallback(str);
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didLocalVideoEnabled:(BOOL)enabled byUid:(NSUInteger)uid
{
    
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine
   networkQuality:(NSUInteger)uid
        txQuality:(AgoraNetworkQuality)txQuality
        rxQuality:(AgoraNetworkQuality)rxQuality
{
    if (uid == 0) {
        uid = _localUid;
    }
    CocosAgoraManager::getInstance()->updateNetworkQuality((unsigned int)uid,
                                                           (unsigned int)txQuality,
                                                           (unsigned int)rxQuality);
}

//音量提示回调getAudioLevel
- (void)rtcEngine:(AgoraRtcEngineKit *)engine
reportAudioVolumeIndicationOfSpeakers:(NSArray*)speakers
      totalVolume:(NSInteger)totalVolume
{
    for (AgoraRtcAudioVolumeInfo *info in speakers) {
        unsigned int uid = (unsigned int)info.uid;
        if (info.uid == 0) {
            uid = _localUid;
        }
        CocosAgoraManager::getInstance()->updateAudioLevel(uid, (unsigned int)info.volume);
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine reportRtcStats:(AgoraChannelStats * _Nonnull)stats
{
    CocosAgoraManager::getInstance()->updateRtcStats((unsigned int)stats.duration,
                                                     (unsigned int)stats.txBytes,
                                                     (unsigned int)stats.rxBytes,
                                                     (unsigned int)stats.txAudioKBitrate,
                                                     (unsigned int)stats.rxAudioKBitrate,
                                                     (unsigned int)stats.txVideoKBitrate,
                                                     (unsigned int)stats.rxVideoKBitrate,
                                                     (unsigned int)stats.userCount,
                                                     stats.cpuAppUsage,
                                                     stats.cpuTotalUsage);
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine localVideoStats:(AgoraRtcLocalVideoStats*)stats {
    CocosAgoraManager::getInstance()->updateLocalVideoStats((unsigned int)stats.sentBitrate,
                                                            (unsigned int)stats.sentFrameRate);
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine
 remoteVideoStats:(AgoraRtcRemoteVideoStats*)stats {
    CocosAgoraManager::getInstance()->updateClientStats((unsigned int)stats.uid,
                                                        (unsigned int)stats.width,
                                                        (unsigned int)stats.height,
                                                        (unsigned int)stats.receivedBitrate,
                                                        (unsigned int)stats.receivedFrameRate);
}

#pragma mark AudioEngineManagerProtocol
- (int)audioPlayEffect:(int)soundId filePath:(NSString *)filePath loop:(BOOL)loop gain:(double)gain {
    int loopCount = 0;
    if (loop) {
        loopCount = -1;
    }
    return [_rtcEngine playEffect:soundId filePath:filePath loopCount:loopCount pitch:1.0 pan:0 gain:gain publish:NO];
}

- (int)audioSetVolumeOfEffect:(int)soundId volume:(double)volume {
    return [_rtcEngine setVolumeOfEffect:soundId withVolume:volume];
}

- (int)audioStopEffect:(int)soundId {
    return [_rtcEngine stopEffect:soundId];
}

- (int)audioStopAllEffects {
    return [_rtcEngine stopAllEffects];
}

- (int)audioPauseEffect:(int)soundId {
    return [_rtcEngine pauseEffect:soundId];
}

- (int)audioPauseAllEffects {
    return [_rtcEngine pauseAllEffects];
}

- (int)audioResumeEffect:(int)soundId {
    return [_rtcEngine resumeEffect:soundId];
}

- (int)audioResumeAllEffects {
    return [_rtcEngine resumeAllEffects];
}

- (double)audioGetEffectsVolume {
    return [_rtcEngine getEffectsVolume];
}

- (void)rtcEngineDidAudioEffectFinish:(AgoraRtcEngineKit *)engine soundId:(NSInteger)soundId {
    [[AudioEngineManager shareAudioEngineManager] audioEffectFinishWithSoundId:soundId];
}

@end
