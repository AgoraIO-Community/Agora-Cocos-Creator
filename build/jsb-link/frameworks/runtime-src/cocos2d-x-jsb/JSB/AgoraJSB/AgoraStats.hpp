//
//  AgoraStats.hpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/4/16.
//

#ifndef AgoraStats_hpp
#define AgoraStats_hpp
#include "cocos2d.h"
#include "PlatformMacros.h"
#include "AgoraClientStats.hpp"

using namespace std;

namespace se {
    class Object;
    class Class;
}

NS_AGORA_BEGIN

//__attribute__((visibility("default"))) @interface AgoraRtcLocalVideoStats : NSObject
//@property (assign, nonatomic) NSUInteger sentBitrate;
//@property (assign, nonatomic) NSUInteger sentFrameRate;
//@end

class AgoraStats
{
public:
    AgoraStats();
    ~AgoraStats();
    unsigned int duration;
    unsigned int txBytes;
    unsigned int rxBytes;
    unsigned int txAudioKBitrate;
    unsigned int rxAudioKBitrate;
    unsigned int txVideoKBitrate;
    unsigned int rxVideoKBitrate;
    unsigned int userCount;
    double cpuAppUsage;
    double cpuTotalUsage;
    unsigned int sentBitrate;
    unsigned int sentFrameRate;
    cocos2d::Map<unsigned int, AgoraClientStats*> clients;
    void updateClientStats(unsigned int uid,
                           unsigned int width,
                           unsigned int height,
                           unsigned int receivedBitrate,
                           unsigned int receivedFrameRate);
};

NS_AGORA_END

bool js_register_hh_AgoraStats(se::Object* global);
#endif /* AgoraStats_hpp */
