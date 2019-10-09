//
//  AGQueueManager.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/8/16.
//

#import <Foundation/Foundation.h>

@class AGVideoBuffer;

@interface AGQueueManager : NSObject

+ (instancetype)shareManager;

+ (void)updateVideoFrame:(AGVideoBuffer *)videoBuffer;

@end
