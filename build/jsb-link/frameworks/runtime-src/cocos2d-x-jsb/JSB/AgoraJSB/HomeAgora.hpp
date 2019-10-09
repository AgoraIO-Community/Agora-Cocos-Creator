//
//  HomeAgora.hpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 26/12/2017.
//

#ifndef HomeAgora_hpp
#define HomeAgora_hpp

#include "cocos2d.h"
#include "PlatformMacros.h"
#include "AgoraStats.hpp"
#include "AgoraNetworkQualityObject.hpp"

using namespace std;

namespace se {
    class Object;
    class Class;
}

NS_AGORA_BEGIN
    class HomeAgora
    {
    public:
        HomeAgora();
        ~HomeAgora();
        
        //local
        void join(std::string appId,
                  string name,
                  unsigned int uid,
                  string videoProfile,
                  int channelProfile,
                  int clientRole,
                  int agora);
        void setLocalJoinCallback(const std::function<void(string)>& cb);
        void localJoinCallback(string res);
        
        void leave();
        void setLocalLeaveCallback(const std::function<void(string)>& cb);
        void localLeaveCallback(string res);
        
        void muteLocalAudio();
        void setMuteLocalAudioCallback(const std::function<void(string)>& cb);
        void muteLocalAudioCallback(string res);

        void unmuteLocalAudio();
        void setUnmuteLocalAudioCallback(const std::function<void(string)>& cb);
        void unmuteLocalAudioCallback(string res);
        
        void muteLocalVideo();
        void setMuteLocalVideoCallback(const std::function<void(string)>& cb);
        void muteLocalVideoCallback(string res);
        
        void unmuteLocalVideo();
        void setUnmuteLocalVideoCallback(const std::function<void(string)>& cb);
        void unmuteLocalVideoCallback(string res);
        
        //remote
        void muteRemoteVideo(unsigned int uid);
        void setMuteRemoteVideoCallback(const std::function<void(string)>& cb);
        void muteRemoteVideoCallback(string res);
        
        void unmuteRemoteVideo(unsigned int uid);
        void setUnmuteRemoteVideoCallback(const std::function<void(string)>& cb);
        void unmuteRemoteVideoCallback(string res);

        void muteRemoteAudio(unsigned int uid);
        void setMuteRemoteAudioCallback(const std::function<void(string)>& cb);
        void muteRemoteAudioCallback(string res);
        
        void unmuteRemoteAudio(unsigned int uid);
        void setUnmuteRemoteAudioCallback(const std::function<void(string)>& cb);
        void unmuteRemoteAudioCallback(string res);
        
        void setRemoteJoinCallback(const std::function<void(unsigned int)>& cb);
        void remoteJoinCallback(unsigned int uid);
        
        void setRemoteLeaveCallback(const std::function<void(unsigned int)>& cb);
        void remoteLeaveCallback(unsigned int uid);
        
        cocos2d::Texture2D* getTexture(unsigned int uid);
        void updateFrame(unsigned int uid, const void *data, ssize_t dataLen, int pixelsWide, int pixelsHigh);
        cocos2d::Size getTextureSize(unsigned int uid);
        
        unsigned int getAudioLevel(unsigned int uid);
        void updateAudioLevel(unsigned int uid, unsigned int audioLevel);
        
        AgoraStats* getStats();
        void updateRtcStats(unsigned int duration,
                            unsigned int txBytes,
                            unsigned int rxBytes,
                            unsigned int txAudioKBitrate,
                            unsigned int rxAudioKBitrate,
                            unsigned int txVideoKBitrate,
                            unsigned int rxVideoKBitrate,
                            unsigned int userCount,
                            double cpuAppUsage,
                            double cpuTotalUsage);
        void updateLocalVideoStats(unsigned int sentBitrate,
                                   unsigned int sentFrameRate);
        void updateClientStats(unsigned int uid,
                               unsigned int width,
                               unsigned int height,
                               unsigned int receivedBitrate,
                               unsigned int receivedFrameRate);
        AgoraNetworkQualityObject* getNetworkQuality(unsigned int uid);
        void updateNetworkQuality(unsigned int uid,
                                  unsigned int txquality,
                                  unsigned int rxquality);
    private:
        std::function<void(string)> _localJoinCallback;
        std::function<void(string)> _localLeaveCallback;
        std::function<void(string)> _muteLocalAudioCallback;
        std::function<void(string)> _unmuteLocalAudioCallback;
        std::function<void(string)> _muteLocalVideoCallback;
        std::function<void(string)> _unmuteLocalVideoCallback;
        std::function<void(string)> _muteRemoteVideoCallback;
        std::function<void(string)> _unmuteRemoteVideoCallback;
        std::function<void(string)> _muteRemoteAudioCallback;
        std::function<void(string)> _unmuteRemoteAudioCallback;
        std::function<void(unsigned int)> _remoteLeaveCallback;
        std::function<void(unsigned int)> _remoteJoinCallback;
        std::map<unsigned int, unsigned int> _audioLevels;
        AgoraStats* _status;
        std::map<unsigned int, AgoraNetworkQualityObject*> *_networkQualitys;
    };

NS_AGORA_END

bool js_register_hh_HomeAgora(se::Object* global);

static cocos2d::Map<unsigned int, cocos2d::Texture2D*> *_textures = new cocos2d::Map<unsigned int, cocos2d::Texture2D*>;

#endif /* HomeAgora_hpp */
