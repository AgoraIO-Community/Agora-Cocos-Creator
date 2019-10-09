//
//  AgoraManagerProtocol.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 05/03/2018.
//

@class AgoraRtcEngineKit;

@interface AGVideoProcessing : NSObject
+ (int)registerVideoPreprocessing:(AgoraRtcEngineKit*) kit;
+ (int)deregisterVideoPreprocessing:(AgoraRtcEngineKit*) kit;
@end
