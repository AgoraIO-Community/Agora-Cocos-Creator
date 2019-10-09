//
//  VideoProfile.hpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2019/3/11.
//

#ifndef VideoProfile_hpp
#define VideoProfile_hpp

#include <stdio.h>
#include <string>
#include "PlatformMacros.h"

NS_AGORA_BEGIN
struct VideoProfile {
    int width = 480;
    int height = 360;
    int frameRate = 15;
    int bitrate = 500;
    static VideoProfile createVideoProfile(std::string videoProfile);
};
NS_AGORA_END
#endif /* VideoProfile_hpp */
