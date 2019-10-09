//
//  VideoProfile.cpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2019/3/11.
//

#include "VideoProfile.hpp"
NS_AGORA_BEGIN

VideoProfile VideoProfile::createVideoProfile(std::string videoProfile) {
    VideoProfile vp;
    if (videoProfile.compare("120p") == 0 || videoProfile.compare("120p_1") == 0) {
        vp.width = 160;
        vp.height = 120;
        vp.frameRate = 15;
        vp.bitrate = 65;
    } else if (videoProfile.compare("120p_3") == 0) {
        vp.width = 120;
        vp.height = 120;
        vp.frameRate = 15;
        vp.bitrate = 50;
    } else if (videoProfile.compare("180p") == 0 || videoProfile.compare("180p_1") == 0) {
        vp.width = 320;
        vp.height = 180;
        vp.frameRate = 15;
        vp.bitrate = 140;
    } else if (videoProfile.compare("180p_3") == 0) {
        vp.width = 180;
        vp.height = 180;
        vp.frameRate = 15;
        vp.bitrate = 100;
    } else if (videoProfile.compare("180p_4") == 0) {
        vp.width = 240;
        vp.height = 180;
        vp.frameRate = 15;
        vp.bitrate = 120;
    } else if (videoProfile.compare("240p") == 0 || videoProfile.compare("240p_1") == 0) {
        vp.width = 320;
        vp.height = 240;
        vp.frameRate = 15;
        vp.bitrate = 200;
    } else if (videoProfile.compare("240p_3") == 0) {
        vp.width = 240;
        vp.height = 240;
        vp.frameRate = 15;
        vp.bitrate = 140;
    } else if (videoProfile.compare("240p_4") == 0) {
        vp.width = 424;
        vp.height = 240;
        vp.frameRate = 15;
        vp.bitrate = 220;
    } else if (videoProfile.compare("360p") == 0 || videoProfile.compare("360p_1") == 0) {
        vp.width = 640;
        vp.height = 360;
        vp.frameRate = 15;
        vp.bitrate = 400;
    } else if (videoProfile.compare("360p_3") == 0) {
        vp.width = 360;
        vp.height = 360;
        vp.frameRate = 15;
        vp.bitrate = 260;
    } else if (videoProfile.compare("360p_4") == 0) {
        vp.width = 640;
        vp.height = 360;
        vp.frameRate = 30;
        vp.bitrate = 600;
    } else if (videoProfile.compare("360p_6") == 0) {
        vp.width = 360;
        vp.height = 360;
        vp.frameRate = 30;
        vp.bitrate = 400;
    } else if (videoProfile.compare("360p_7") == 0) {
        vp.width = 480;
        vp.height = 360;
        vp.frameRate = 15;
        vp.bitrate = 320;
    } else if (videoProfile.compare("360p_8") == 0) {
        vp.width = 480;
        vp.height = 360;
        vp.frameRate = 30;
        vp.bitrate = 490;
    } else if (videoProfile.compare("360p_9") == 0) {
        vp.width = 640;
        vp.height = 360;
        vp.frameRate = 15;
        vp.bitrate = 800;
    } else if (videoProfile.compare("360p_10") == 0) {
        vp.width = 640;
        vp.height = 360;
        vp.frameRate = 24;
        vp.bitrate = 800;
    } else if (videoProfile.compare("360p_11") == 0) {
        vp.width = 640;
        vp.height = 360;
        vp.frameRate = 24;
        vp.bitrate = 1000;
    } else if (videoProfile.compare("480p") == 0 || videoProfile.compare("480p_1") == 0) {
        vp.width = 640;
        vp.height = 480;
        vp.frameRate = 15;
        vp.bitrate = 500;
    } else if (videoProfile.compare("480p_2") == 0) {
        vp.width = 648;
        vp.height = 480;
        vp.frameRate = 30;
        vp.bitrate = 1000;
    } else if (videoProfile.compare("480p_3") == 0) {
        vp.width = 480;
        vp.height = 480;
        vp.frameRate = 15;
        vp.bitrate = 400;
    } else if (videoProfile.compare("480p_4") == 0) {
        vp.width = 640;
        vp.height = 480;
        vp.frameRate = 30;
        vp.bitrate = 750;
    } else if (videoProfile.compare("480p_6") == 0) {
        vp.width = 480;
        vp.height = 480;
        vp.frameRate = 30;
        vp.bitrate = 600;
    } else if (videoProfile.compare("480p_8") == 0) {
        vp.width = 848;
        vp.height = 480;
        vp.frameRate = 15;
        vp.bitrate = 610;
    } else if (videoProfile.compare("480p_9") == 0) {
        vp.width = 848;
        vp.height = 480;
        vp.frameRate = 30;
        vp.bitrate = 930;
    } else if (videoProfile.compare("480p_10") == 0) {
        vp.width = 640;
        vp.height = 480;
        vp.frameRate = 10;
        vp.bitrate = 400;
    } else if (videoProfile.compare("720p") == 0 || videoProfile.compare("720p_1") == 0) {
        vp.width = 1280;
        vp.height = 720;
        vp.frameRate = 15;
        vp.bitrate = 1130;
    } else if (videoProfile.compare("720p_2") == 0) {
        vp.width = 1280;
        vp.height = 720;
        vp.frameRate = 15;
        vp.bitrate = 2080;
    } else if (videoProfile.compare("720p_3") == 0) {
        vp.width = 1280;
        vp.height = 720;
        vp.frameRate = 30;
        vp.bitrate = 1710;
    } else if (videoProfile.compare("720p_5") == 0) {
        vp.width = 960;
        vp.height = 720;
        vp.frameRate = 15;
        vp.bitrate = 910;
    } else if (videoProfile.compare("720p_6") == 0) {
        vp.width = 960;
        vp.height = 720;
        vp.frameRate = 30;
        vp.bitrate = 1380;
    } else if (videoProfile.compare("1080p") == 0 || videoProfile.compare("1080p_1") == 0) {
        vp.width = 1920;
        vp.height = 1080;
        vp.frameRate = 15;
        vp.bitrate = 2080;
    } else if (videoProfile.compare("1080p_2") == 0) {
        vp.width = 1920;
        vp.height = 1080;
        vp.frameRate = 30;
        vp.bitrate = 3000;
    } else if (videoProfile.compare("1080p_3") == 0) {
        vp.width = 1920;
        vp.height = 1080;
        vp.frameRate = 30;
        vp.bitrate = 3150;
    } else if (videoProfile.compare("1080p_5") == 0) {
        vp.width = 1920;
        vp.height = 1080;
        vp.frameRate = 60;
        vp.bitrate = 4780;
    } else if (videoProfile.compare("1440p") == 0 || videoProfile.compare("1440p_1") == 0) {
        vp.width = 2560;
        vp.height = 1440;
        vp.frameRate = 30;
        vp.bitrate = 4850;
    } else if (videoProfile.compare("1440p_2") == 0) {
        vp.width = 2560;
        vp.height = 1440;
        vp.frameRate = 60;
        vp.bitrate = 7350;
    } else if (videoProfile.compare("4K") == 0 || videoProfile.compare("4K_1") == 0) {
        vp.width = 3840;
        vp.height = 2160;
        vp.frameRate = 30;
        vp.bitrate = 8910;
    } else if (videoProfile.compare("4K_3") == 0) {
        vp.width = 3840;
        vp.height = 2160;
        vp.frameRate = 60;
        vp.bitrate = 13500;
    }
    return vp;
}
NS_AGORA_END
