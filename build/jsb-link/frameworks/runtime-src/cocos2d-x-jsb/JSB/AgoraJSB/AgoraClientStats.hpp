//
//  AgoraClientStats.hpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/4/17.
//

#ifndef AgoraClientStats_hpp
#define AgoraClientStats_hpp
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
//
//__attribute__((visibility("default"))) @interface AgoraRtcRemoteVideoStats : NSObject
//@property (assign, nonatomic) NSUInteger uid;
//@property (assign, nonatomic) NSUInteger delay __deprecated;
//@property (assign, nonatomic) NSUInteger width;
//@property (assign, nonatomic) NSUInteger height;
//@property (assign, nonatomic) NSUInteger receivedBitrate;
//@property (assign, nonatomic) NSUInteger receivedFrameRate;
//@property (assign, nonatomic) AgoraVideoStreamType rxStreamType;
//@end

//assert(ret != nullptr);
//se::HandleObject obj(se::Object::createPlainObject());
//obj->setProperty("x", se::Value(v.x));
//obj->setProperty("y", se::Value(v.y));
//obj->setProperty("z", se::Value(v.z));
//obj->setProperty("w", se::Value(v.w));
//ret->setObject(obj);
//
//return true;

class AgoraClientStats : public cocos2d::Ref
{
public:
    AgoraClientStats();
    ~AgoraClientStats();
    unsigned int uid;
    unsigned int width;
    unsigned int height;
    unsigned int receivedBitrate;
    unsigned int receivedFrameRate;
};

NS_AGORA_END

bool js_register_hh_AgoraClientStats(se::Object* global);
#endif /* AgoraClientStats_hpp */
