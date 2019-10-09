//
//  AgoraNetworkQualityObject.hpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/9/20.
//

#ifndef AgoraNetworkQualityObject_hpp
#define AgoraNetworkQualityObject_hpp

#include "cocos2d.h"
#include "PlatformMacros.h"

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

class AgoraNetworkQualityObject
{
public:
    AgoraNetworkQualityObject();
    ~AgoraNetworkQualityObject();
    unsigned int uid;
    unsigned int txquality;
    unsigned int rxquality;
    void updateNetworkQuality(unsigned int uid,
                              unsigned int txquality,
                              unsigned int rxquality);
};

NS_AGORA_END

bool js_register_hh_AgoraNetworkQualityObject(se::Object* global);

#endif /* AgoraNetworkQualityObject_hpp */
