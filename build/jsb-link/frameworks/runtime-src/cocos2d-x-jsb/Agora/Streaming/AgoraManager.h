//
//  AgoraManager.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 20/12/2017.
//

#import <Foundation/Foundation.h>
#import "AgoraManager.h"
#import "AgoraManagerProtocol.h"

@interface AgoraManager : NSObject <AgoraManagerProtocol>

+ (instancetype)share;

@end
