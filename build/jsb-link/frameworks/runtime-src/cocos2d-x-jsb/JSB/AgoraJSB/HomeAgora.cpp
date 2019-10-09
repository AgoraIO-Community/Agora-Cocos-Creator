//
//  HomeAgora.cpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 26/12/2017.
//

#include "HomeAgora.hpp"

#include "cocos2d.h"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.hpp"

#include "OCHomeAgora.h"
#include "CocosAgoraManager.h"

using namespace se;
USING_NS_AGORA;
USING_NS_CC;

static se::Object* __jsb_hh_HomeAgora_proto = nullptr;
static se::Class* __jsb_hh_HomeAgora_class = nullptr;

NS_AGORA_BEGIN
    
HomeAgora::HomeAgora()
{
    _remoteLeaveCallback = nullptr;
    _remoteJoinCallback = nullptr;
    _status = new AgoraStats();
    _textures->clear();
    _networkQualitys = new std::map<unsigned int, AgoraNetworkQualityObject*>();
}

HomeAgora::~HomeAgora()
{
    CCLOG("~HomeAgora");
    _textures->clear();
    delete _status;
    _status = NULL;

    auto itEnd = _networkQualitys->end();
    for (auto it = _networkQualitys->begin(); it != itEnd;) {
        delete it->second;
        _networkQualitys->erase(it++);
    }
}

void HomeAgora::join(std::string appId,
                     std::string name,
                     unsigned int uid,
                     string videoProfile,
                     int channelProfile,
                     int clientRole, int agora)
{
    CCLOG("HomeAgora::join");
    agora::objcHAJoin(appId,
                   name,
                   uid,
                   videoProfile,
                   channelProfile,
                   clientRole,
                   agora);
}
void HomeAgora::setLocalJoinCallback(const std::function<void(string)>& cb)
{
    _localJoinCallback = cb;
    if (_localJoinCallback != nullptr) {
        CCLOG("setLocalJoinCallback(cb)\n");
    } else {
        CCLOG("setLocalJoinCallback(nullptr)\n");
    }
}
void HomeAgora::localJoinCallback(string res) {
    if (_localJoinCallback != NULL) {
        _localJoinCallback(res);
    }
}

void HomeAgora::leave()
{
    CCLOG("HomeAgora::leave");
    agora::objcHALeave();
}
void HomeAgora::setLocalLeaveCallback(const std::function<void(string)>& cb)
{
    _localLeaveCallback = cb;
    if (_localLeaveCallback != nullptr) {
        CCLOG("setLocalLeaveCallback(cb)\n");
    } else {
        CCLOG("setLocalLeaveCallback(nullptr)\n");
    }
}

void HomeAgora::localLeaveCallback(string res) {
//    _textures->clear();
    if (_localLeaveCallback != NULL) {
        _localLeaveCallback(res);
    }
}

void HomeAgora::muteLocalAudio()
{
    CCLOG("HomeAgora::muteLocalAudio");
    agora::objcHAMuteLocalAudio();
}

void HomeAgora::setMuteLocalAudioCallback(const std::function<void(string)>& cb)
{
    _muteLocalAudioCallback = cb;
    if (_muteLocalAudioCallback != nullptr) {
        CCLOG("muteLocalAudioCallback(cb)\n");
    } else {
        CCLOG("muteLocalAudioCallback(nullptr)\n");
    }
}

void HomeAgora::muteLocalAudioCallback(string res)
{
    if (_muteLocalAudioCallback != NULL) {
        _muteLocalAudioCallback(res);
    }
}

void HomeAgora::unmuteLocalAudio()
{
    CCLOG("HomeAgora::unmuteLocalAudio");
    agora::objcHAUnmuteLocalAudio();
}

void HomeAgora::setUnmuteLocalAudioCallback(const std::function<void(string)>& cb)
{
    _unmuteLocalAudioCallback = cb;
    if (_unmuteLocalAudioCallback != nullptr) {
        CCLOG("unmuteLocalAudioCallback(cb)\n");
    } else {
        CCLOG("unmuteLocalAudioCallback(nullptr)\n");
    }
}

void HomeAgora::unmuteLocalAudioCallback(string res)
{
    if (_unmuteLocalAudioCallback != NULL) {
        _unmuteLocalAudioCallback(res);
    }
}

//自己开始
void HomeAgora::muteLocalVideo()
{
    CCLOG("HomeAgora::muteLocalVideo");
    agora::objcHAMuteLocalVideo();
}

void HomeAgora::setMuteLocalVideoCallback(const std::function<void(string)>& cb)
{
    _muteLocalVideoCallback = cb;
    if (_muteLocalVideoCallback != nullptr) {
        CCLOG("setMuteLocalVideoCallback(cb)\n");
    } else {
        CCLOG("setMuteLocalVideoCallback(nullptr)\n");
    }
}

void HomeAgora::muteLocalVideoCallback(string res) {
    if (_muteLocalVideoCallback != NULL) {
        _muteLocalVideoCallback(res);
    }
}

void HomeAgora::unmuteLocalVideo()
{
    CCLOG("HomeAgora::unmuteLocalVideo");
    agora::objcHAUnmuteLocalVideo();
}
void HomeAgora::setUnmuteLocalVideoCallback(const std::function<void(string)>& cb)
{
    _unmuteLocalVideoCallback = cb;
    if (_unmuteLocalVideoCallback != nullptr) {
        CCLOG("setUnmuteLocalVideoCallback(cb)\n");
    } else {
        CCLOG("setUnmuteLocalVideoCallback(nullptr)\n");
    }
}

void HomeAgora::unmuteLocalVideoCallback(string res) {
    if (_unmuteLocalVideoCallback != NULL) {
        _unmuteLocalVideoCallback(res);
    }
}

void HomeAgora::muteRemoteVideo(unsigned int uid)
{
    CCLOG("HomeAgora::muteRemoteVideo");
    agora::objcHAMuteRemoteVideo(uid);
}

void HomeAgora::setMuteRemoteVideoCallback(const std::function<void(string)>& cb)
{
    _muteRemoteVideoCallback = cb;
    if (_muteRemoteVideoCallback != nullptr) {
        CCLOG("setMuteRemoteVideoCallback(cb)\n");
    } else {
        CCLOG("setMuteRemoteVideoCallback(nullptr)\n");
    }
}

void HomeAgora::muteRemoteVideoCallback(string res) {
    if (_muteRemoteVideoCallback != NULL) {
        _muteRemoteVideoCallback(res);
    }
}
    
void HomeAgora::unmuteRemoteVideo(unsigned int uid)
{
//    CCLOG("HomeAgora::unmuteRemoteVideo");
    agora::objcHAUnmuteRemoteVideo(uid);
}
void HomeAgora::setUnmuteRemoteVideoCallback(const std::function<void(string)>& cb)
{
    _unmuteRemoteVideoCallback = cb;
    if (_unmuteRemoteVideoCallback != nullptr) {
        CCLOG("setUnmuteRemoteVideoCallback(cb)\n");
    } else {
        CCLOG("setUnmuteRemoteVideoCallback(nullptr)\n");
    }
}

void HomeAgora::unmuteRemoteVideoCallback(string res) {
    if (_unmuteRemoteVideoCallback != NULL) {
        _unmuteRemoteVideoCallback(res);
    }
}

void HomeAgora::muteRemoteAudio(unsigned int uid) {
    CCLOG("HomeAgora::muteRemoteAudio");
    agora::objcHAMuteRemoteAudio(uid);
}

void HomeAgora::setMuteRemoteAudioCallback(const std::function<void(string)>& cb) {
    _muteRemoteAudioCallback = cb;
    if (_muteRemoteAudioCallback != nullptr) {
        CCLOG("setMuteRemoteAudioCallback(cb)\n");
    } else {
        CCLOG("setMuteRemoteAudioCallback(nullptr)\n");
    }
}

void HomeAgora::muteRemoteAudioCallback(string res) {
    if (_muteRemoteAudioCallback != NULL) {
        _muteRemoteAudioCallback(res);
    }
}

void HomeAgora::unmuteRemoteAudio(unsigned int uid) {
    CCLOG("HomeAgora::unmuteRemoteAudio");
    agora::objcHAUnmuteRemoteAudio(uid);
}

void HomeAgora::setUnmuteRemoteAudioCallback(const std::function<void(string)>& cb) {
    _unmuteRemoteAudioCallback = cb;
    if (_unmuteRemoteAudioCallback != nullptr) {
        CCLOG("setUnmuteRemoteAudioCallback(cb)\n");
    } else {
        CCLOG("setUnmuteRemoteAudioCallback(nullptr)\n");
    }
}

void HomeAgora::unmuteRemoteAudioCallback(string res) {
    if (_unmuteRemoteAudioCallback != NULL) {
        _unmuteRemoteAudioCallback(res);
    }
}

void HomeAgora::setRemoteJoinCallback(const std::function<void(unsigned int)>& cb) {
    _remoteJoinCallback = cb;
    if (_remoteJoinCallback != nullptr) {
        CCLOG("setRemoteJoinCallback(cb)\n");
    } else {
        CCLOG("setRemoteJoinCallback(nullptr)\n");
    }
}

void HomeAgora::remoteJoinCallback(unsigned int uid) {
    if (_remoteJoinCallback != NULL) {
        _remoteJoinCallback(uid);
    }
}

//有人离开
void HomeAgora::setRemoteLeaveCallback(const std::function<void(unsigned int)>& cb) {
    _remoteLeaveCallback = cb;
    if (_remoteLeaveCallback != nullptr) {
        CCLOG("setRemoteLeaveCallback(cb)\n");
    } else {
        CCLOG("setRemoteLeaveCallback(nullptr)\n");
    }
}

void HomeAgora::remoteLeaveCallback(unsigned int uid) {
    for(auto iter = _textures->begin(); iter != _textures->end(); iter++){
        unsigned int u = iter->first;
        if (u == uid) {
//            _textures->erase(iter);
            if (_remoteLeaveCallback != NULL) {
                _remoteLeaveCallback((int)uid);
            }
            break;
        }
    }
}

cocos2d::Texture2D* HomeAgora::getTexture(unsigned int uid) {
    cocos2d::Texture2D* res = _textures->at(uid);
    return res;
}
    
void HomeAgora::updateFrame(unsigned int uid, const void *data, ssize_t dataLen, int pixelsWide, int pixelsHigh) {
    unsigned char *temp = (unsigned char *)malloc(dataLen);
    memcpy(temp, data, dataLen);
    dispatch_async(dispatch_get_main_queue(), ^{
        Texture2D* texture = _textures->at(uid);
        if (texture == NULL) {
            Texture2D *texture = new Texture2D;
            bool res = texture->initWithData(temp, dataLen, Texture2D::PixelFormat::RGBA8888, pixelsWide, pixelsHigh, cocos2d::Size(pixelsWide, pixelsHigh));
            if (res) {
                _textures->insert(uid, texture);
            }
            CC_SAFE_RELEASE_NULL(texture);
        } else {
            texture->updateWithData(temp, 0, 0, pixelsWide, pixelsHigh);
        }
        free(temp);
    });
}

cocos2d::Size HomeAgora::getTextureSize(unsigned int uid) {
    Texture2D* texture = _textures->at(uid);
    if (texture == NULL) {
        return cocos2d::Size(0, 0);
    } else {
        return texture->getContentSizeInPixels();
    }
}

unsigned int HomeAgora::getAudioLevel(unsigned int uid) {
    auto iter = _audioLevels.find(uid);
    if (iter != _audioLevels.end())
        return iter->second;
    return 0;
}

void HomeAgora::updateAudioLevel(unsigned int uid, unsigned int audioLevel) {
    _audioLevels[uid] = audioLevel;
}

AgoraStats* HomeAgora::getStats() {
    return _status;
}

void HomeAgora::updateRtcStats(unsigned int duration,
                               unsigned int txBytes,
                               unsigned int rxBytes,
                               unsigned int txAudioKBitrate,
                               unsigned int rxAudioKBitrate,
                               unsigned int txVideoKBitrate,
                               unsigned int rxVideoKBitrate,
                               unsigned int userCount,
                               double cpuAppUsage,
                               double cpuTotalUsage) {
    _status->duration = duration;
    _status->txBytes = txBytes;
    _status->rxBytes = rxBytes;
    _status->txAudioKBitrate = txAudioKBitrate;
    _status->rxAudioKBitrate = rxAudioKBitrate;
    _status->txVideoKBitrate = txVideoKBitrate;
    _status->rxVideoKBitrate = rxVideoKBitrate;
    _status->userCount = userCount;
    _status->cpuAppUsage = cpuAppUsage;
    _status->cpuTotalUsage = cpuTotalUsage;
}

void HomeAgora::updateLocalVideoStats(unsigned int sentBitrate,
                                      unsigned int sentFrameRate) {
    _status->sentBitrate = sentBitrate;
    _status->sentFrameRate = sentFrameRate;
}

void HomeAgora::updateClientStats(unsigned int uid,
                                  unsigned int width,
                                  unsigned int height,
                                  unsigned int receivedBitrate,
                                  unsigned int receivedFrameRate) {
    _status->updateClientStats((unsigned int)uid,
                               (unsigned int)width,
                               (unsigned int)height,
                               (unsigned int)receivedBitrate,
                               (unsigned int)receivedFrameRate);
}

AgoraNetworkQualityObject* HomeAgora::getNetworkQuality(unsigned int uid) {
    auto iter = _networkQualitys->find(uid);
    if (iter != _networkQualitys->end()) {
        return iter->second;
    }
//    return _networkQualitys->at(uid);
    return nullptr;
}

void HomeAgora::updateNetworkQuality(unsigned int uid,
                                     unsigned int txquality,
                                     unsigned int rxquality) {
    auto iter = _networkQualitys->find(uid);
//    AgoraNetworkQualityObject* networkQuality = _networkQualitys->at(uid);
    AgoraNetworkQualityObject* networkQuality;
    if (iter == _networkQualitys->end()) {
        networkQuality = new AgoraNetworkQualityObject();
        _networkQualitys->insert(std::make_pair(uid, networkQuality));
//        _networkQualitys->insert({uid, networkQuality});
//        _networkQualitys->insert(pair<unsigned int, AgoraNetworkQualityObject*>(uid, networkQuality));
//        _networkQualitys->insert(map<unsigned int,AgoraNetworkQualityObject*>::value_type(uid,networkQuality));
    } else {
        networkQuality = iter->second;
    }
    networkQuality->uid = uid;
    networkQuality->txquality = txquality;
    networkQuality->rxquality = rxquality;
}

NS_AGORA_END

static bool js_HomeAgora_finalize(se::State& s) {
    HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
    CocosAgoraManager::getInstance()->setChatRoom(NULL);
    delete cobj;
    return true;
}
SE_BIND_FINALIZE_FUNC(js_HomeAgora_finalize)

static bool js_HomeAgora_constructor(se::State& s) {
    HomeAgora* cobj = new HomeAgora();
    s.thisObject()->setPrivateData(cobj);
    CocosAgoraManager::getInstance()->setChatRoom(cobj);
    return true;
}
SE_BIND_CTOR(js_HomeAgora_constructor, __jsb_hh_HomeAgora_class, js_HomeAgora_finalize)

static bool js_HomeAgora_join(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc >= 4) {
        bool ok = true;
        std::string appId;
        ok = seval_to_std_string(args[0], &appId);
        SE_PRECONDITION2(ok, false, "js_HomeAgora_join appId Error processing arguments");
        
        std::string name;
        ok = seval_to_std_string(args[1], &name);
        SE_PRECONDITION2(ok, false, "js_HomeAgora_join name Error processing arguments");
        
        unsigned int uid;
        ok = seval_to_uint32(args[2], &uid);
        SE_PRECONDITION2(ok, false, "js_HomeAgora_join uid Error processing arguments");
        
        std::string videoProfile = "";
        ok = seval_to_std_string(args[3], &videoProfile);
        SE_PRECONDITION2(ok, false, "js_HomeAgora_join videoProfile Error processing arguments");
        
        int channelProfile = 1;
        if (argc >= 5) {
            ok = seval_to_int32(args[4], &channelProfile);
            SE_PRECONDITION2(ok, false, "js_HomeAgora_join channelProfile Error processing arguments");
        }
        int clientRole = 1;
        if (argc >= 6) {
            ok = seval_to_int32(args[5], &clientRole);
            SE_PRECONDITION2(ok, false, "js_HomeAgora_join clientRole Error processing arguments");
        }
        
        int agora = 1;
        if (argc >= 7) {
            ok = seval_to_int32(args[6], &agora);
            SE_PRECONDITION2(ok, false, "js_HomeAgora_join isAgora Error processing arguments");
        }
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        cobj->join(appId, name, uid, videoProfile, channelProfile, clientRole, agora);
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_join)

static bool js_HomeAgora_setLocalJoinCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1)
    {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setLocalJoinCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setLocalJoinCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setLocalJoinCallback)

static bool js_HomeAgora_leave(se::State& s) {
    HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
    cobj->leave();
    return true;
}
SE_BIND_FUNC(js_HomeAgora_leave)

static bool js_HomeAgora_setLocalLeaveCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1)
    {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setLocalLeaveCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setLocalLeaveCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setLocalLeaveCallback)

static bool js_HomeAgora_muteLocalAudio(se::State& s) {
    HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
    cobj->muteLocalAudio();
    return true;
}
SE_BIND_FUNC(js_HomeAgora_muteLocalAudio)

static bool js_HomeAgora_setMuteLocalAudioCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1) {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setMuteLocalAudioCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setMuteLocalAudioCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setMuteLocalAudioCallback)

static bool js_HomeAgora_unmuteLocalAudio(se::State& s) {
    HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
    cobj->unmuteLocalAudio();
    return true;
}
SE_BIND_FUNC(js_HomeAgora_unmuteLocalAudio)

static bool js_HomeAgora_setUnmuteLocalAudioCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1) {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setUnmuteLocalAudioCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setUnmuteLocalAudioCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setUnmuteLocalAudioCallback)

static bool js_HomeAgora_muteLocalVideo(se::State& s) {
    HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
    cobj->muteLocalVideo();
    return true;
}
SE_BIND_FUNC(js_HomeAgora_muteLocalVideo)

static bool js_HomeAgora_setMuteLocalVideoCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1) {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setMuteLocalVideoCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setMuteLocalVideoCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setMuteLocalVideoCallback)

static bool js_HomeAgora_unmuteLocalVideo(se::State& s) {
    HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
    cobj->unmuteLocalVideo();
    return true;
}
SE_BIND_FUNC(js_HomeAgora_unmuteLocalVideo)

static bool js_HomeAgora_setUnmuteLocalVideoCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1)
    {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setUnmuteLocalVideoCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setUnmuteLocalVideoCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setUnmuteLocalVideoCallback)

static bool js_HomeAgora_muteRemoteVideo(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        bool ok = true;
        
        unsigned int uid;
        ok = seval_to_uint32(args[0], &uid);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        cobj->muteRemoteVideo(uid);
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_muteRemoteVideo)

static bool js_HomeAgora_setMuteRemoteVideoCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1) {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setMuteRemoteVideoCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setMuteRemoteVideoCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setMuteRemoteVideoCallback)

static bool js_HomeAgora_unmuteRemoteVideo(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        bool ok = true;
        
        unsigned int uid;
        ok = seval_to_uint32(args[0], &uid);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        cobj->unmuteRemoteVideo(uid);
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_unmuteRemoteVideo)

static bool js_HomeAgora_setUnmuteRemoteVideoCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1) {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setUnmuteRemoteVideoCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setUnmuteRemoteVideoCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setUnmuteRemoteVideoCallback)

static bool js_HomeAgora_muteRemoteAudio(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        bool ok = true;
        
        unsigned int uid;
        ok = seval_to_uint32(args[0], &uid);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        cobj->muteRemoteAudio(uid);
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_muteRemoteAudio)

static bool js_HomeAgora_setMuteRemoteAudioCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1)
    {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setMuteRemoteAudioCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setMuteRemoteAudioCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setMuteRemoteAudioCallback)

static bool js_HomeAgora_unmuteRemoteAudio(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        bool ok = true;
        
        unsigned int uid;
        ok = seval_to_uint32(args[0], &uid);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        cobj->unmuteRemoteAudio(uid);
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_unmuteRemoteAudio)

static bool js_HomeAgora_setUnmuteRemoteAudioCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1)
    {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setUnmuteRemoteAudioCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setUnmuteRemoteAudioCallback([jsFunc, jsTarget](string res){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(res));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setUnmuteRemoteAudioCallback)

static bool js_HomeAgora_setRemoteJoinCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1)
    {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined())
        {
            cobj->setRemoteJoinCallback(nullptr);
        }
        else
        {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            
            // 如果当前 HomeAgora 是可以被 new 出来的类，我们 使用 se::Object::attachObject 把 jsFunc 和 jsTarget 关联到当前对象中
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            // 如果当前 HomeAgora 类是一个单例类，或者永远只有一个实例的类，我们不能用 se::Object::attachObject 去关联
            // 必须使用 se::Object::root，开发者无需关系 unroot，unroot 的操作会随着 lambda 的销毁触发 jsFunc 的析构，在 se::Object 的析构函数中进行 unroot 操作。
            // js_cocos2dx_EventDispatcher_addCustomEventListener 的绑定代码就是使用此方式，因为 EventDispatcher 始终只有一个实例，
            // 如果使用 s.thisObject->attachObject(jsFunc.toObject);会导致对应的 func 和 target 永远无法被释放，引发内存泄露。
            
            //             jsFunc.toObject()->root();
            //             jsTarget.toObject()->root();
            
            cobj->setRemoteJoinCallback([jsFunc, jsTarget](unsigned int uid){
                
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(uid));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
            
        }
        
        return true;
    }
    
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setRemoteJoinCallback)

static bool js_HomeAgora_setRemoteLeaveCallback(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc >= 1) {
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        
        se::Value jsFunc = args[0];
        se::Value jsTarget = argc > 1 ? args[1] : se::Value::Undefined;
        
        if (jsFunc.isNullOrUndefined()) {
            cobj->setRemoteLeaveCallback(nullptr);
        } else {
            assert(jsFunc.isObject() && jsFunc.toObject()->isFunction());
            s.thisObject()->attachObject(jsFunc.toObject());
            s.thisObject()->attachObject(jsTarget.toObject());
            
            cobj->setRemoteLeaveCallback([jsFunc, jsTarget](unsigned int uid){
                // CPP 回调函数中要传递数据给 JS 或者调用 JS 函数，在回调函数开始需要添加如下两行代码。
                se::ScriptEngine::getInstance()->clearException();
                se::AutoHandleScope hs;
                
                se::ValueArray args;
                args.push_back(se::Value(uid));
                
                se::Object* target = jsTarget.isObject() ? jsTarget.toObject() : nullptr;
                jsFunc.toObject()->call(args, target);
            });
        }
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
SE_BIND_FUNC(js_HomeAgora_setRemoteLeaveCallback)

static bool js_HomeAgora_getTexture(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        bool ok = true;
        unsigned int uid;
        ok = seval_to_uint32(args[0], &uid);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        cocos2d::Texture2D* ret = cobj->getTexture(uid);
        
        ok &= native_ptr_to_seval<cocos2d::Texture2D>((cocos2d::Texture2D*)ret, &s.rval());
        SE_PRECONDITION2(ok, false, "js_HomeAgora_getTexture : Error processing arguments");
        
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_getTexture)

static bool js_HomeAgora_getAudioLevel(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        bool ok = true;
        unsigned int uid;
        ok = seval_to_uint32(args[0], &uid);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        unsigned int ret = cobj->getAudioLevel(uid);
        
        ok &= uint32_to_seval((unsigned int)ret, &s.rval());
        SE_PRECONDITION2(ok, false, "js_HomeAgora_getAudioLevel : Error processing arguments");
        
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_getAudioLevel)

static bool js_HomeAgora_getStats(se::State& s) {
    HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
    AgoraStats* ret = cobj->getStats();
    bool ok = true;
    ok &= native_ptr_to_rooted_seval<AgoraStats>(ret, &s.rval());
//    ok &=  native_ptr_to_seval<AgoraStats>(ret, &s.rval());
    SE_PRECONDITION2(ok, false, "js_HomeAgora_getStats : Error processing arguments");
    return ok;
}
SE_BIND_FUNC(js_HomeAgora_getStats)

static bool js_HomeAgora_getNetworkQuality(se::State& s) {
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        bool ok = true;
        unsigned int uid;
        ok = seval_to_uint32(args[0], &uid);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        
        HomeAgora* cobj = (HomeAgora*)s.nativeThisObject();
        AgoraNetworkQualityObject *ret = cobj->getNetworkQuality(uid);
//        ok &= native_ptr_to_seval<AgoraNetworkQualityObject>(ret, &s.rval());
        ok &=  native_ptr_to_rooted_seval<AgoraNetworkQualityObject>(ret, &s.rval());
        SE_PRECONDITION2(ok, false, "js_HomeAgora_getNetworkQuality : Error processing arguments");
        return true;
    }
    
    SE_REPORT_ERROR("Invalid number of arguments");
    return false;
}
SE_BIND_FUNC(js_HomeAgora_getNetworkQuality)

bool js_register_hh_HomeAgora(se::Object* global) {
    // 保证 namespace 对象存在
    se::Value hhVal;
    if (!global->getProperty(NS_AGORA_JSBNS, &hhVal)) {
        // 不存在则创建一个 JS 对象，相当于 var ns = {};
        se::HandleObject jsobj(se::Object::createPlainObject());
        hhVal.setObject(jsobj);
        
        // 将 hh 对象挂载到 global 对象中，名称为 ns
        global->setProperty(NS_AGORA_JSBNS, hhVal);
    }
    se::Object* hh = hhVal.toObject();
    
    // 创建一个 Class 对象，开发者无需考虑 Class 对象的释放，其交由 ScriptEngine 内部自动处理
    auto cls = se::Class::create("HomeAgora", hh, nullptr, _SE(js_HomeAgora_constructor)); // 如果无构造函数，最后一个参数可传入 nullptr，则这个类在 JS 中无法被 new HomeAgora()出来
    
    // 为这个 Class 对象定义成员函数、属性、静态函数、析构函数
    cls->defineFunction("join", _SE(js_HomeAgora_join));
    cls->defineFunction("setLocalJoinCallback", _SE(js_HomeAgora_setLocalJoinCallback));
    cls->defineFunction("leave", _SE(js_HomeAgora_leave));
    cls->defineFunction("setLocalLeaveCallback", _SE(js_HomeAgora_setLocalLeaveCallback));
    
    cls->defineFunction("muteLocalAudio", _SE(js_HomeAgora_muteLocalAudio));
    cls->defineFunction("setMuteLocalAudioCallback", _SE(js_HomeAgora_setMuteLocalAudioCallback));
    cls->defineFunction("unmuteLocalAudio", _SE(js_HomeAgora_unmuteLocalAudio));
    cls->defineFunction("setUnmuteLocalAudioCallback", _SE(js_HomeAgora_setUnmuteLocalAudioCallback));
    
    cls->defineFunction("muteLocalVideo", _SE(js_HomeAgora_muteLocalVideo));
    cls->defineFunction("setMuteLocalVideoCallback", _SE(js_HomeAgora_setMuteLocalVideoCallback));
    cls->defineFunction("unmuteLocalVideo", _SE(js_HomeAgora_unmuteLocalVideo));
    cls->defineFunction("setUnmuteLocalVideoCallback", _SE(js_HomeAgora_setUnmuteLocalVideoCallback));
    
    cls->defineFunction("muteRemoteVideo", _SE(js_HomeAgora_muteRemoteVideo));
    cls->defineFunction("setMuteRemoteVideoCallback", _SE(js_HomeAgora_setMuteRemoteVideoCallback));
    cls->defineFunction("unmuteRemoteVideo", _SE(js_HomeAgora_unmuteRemoteVideo));
    cls->defineFunction("setUnmuteRemoteVideoCallback", _SE(js_HomeAgora_setUnmuteRemoteVideoCallback));
    
    cls->defineFunction("muteRemoteAudio", _SE(js_HomeAgora_muteRemoteAudio));
    cls->defineFunction("setMuteRemoteAudioCallback", _SE(js_HomeAgora_setMuteRemoteAudioCallback));
    cls->defineFunction("unmuteRemoteAudio", _SE(js_HomeAgora_unmuteRemoteAudio));
    cls->defineFunction("setUnmuteRemoteAudioCallback", _SE(js_HomeAgora_setUnmuteRemoteAudioCallback));
    
    cls->defineFunction("setRemoteLeaveCallback", _SE(js_HomeAgora_setRemoteLeaveCallback));
    cls->defineFunction("setRemoteJoinCallback", _SE(js_HomeAgora_setRemoteJoinCallback));
    
    cls->defineFunction("getTexture", _SE(js_HomeAgora_getTexture));
    
    cls->defineFunction("getAudioLevel", _SE(js_HomeAgora_getAudioLevel));
    
    cls->defineFunction("getStats", _SE(js_HomeAgora_getStats));
    
    cls->defineFunction("getNetworkQuality", _SE(js_HomeAgora_getNetworkQuality));

//    cls->defineProperty("xxx", _SE(js_HomeAgora_get_xxx), _SE(js_HomeAgora_set_xxx));
    
    cls->defineFinalizeFunction(_SE(js_HomeAgora_finalize));
    
    // 注册类型到 JS VirtualMachine 的操作
    cls->install();
    
    // JSBClassType 为 Cocos 引擎绑定层封装的类型注册的辅助函数，此函数不属于 ScriptEngine 这层
    JSBClassType::registerClass<HomeAgora>(cls);
    
    // 保存注册的结果，便于其他地方使用，比如类继承
    __jsb_hh_HomeAgora_proto = cls->getProto();
    __jsb_hh_HomeAgora_class = cls;
    
    // 清空异常
    se::ScriptEngine::getInstance()->clearException();
    return true;
}
