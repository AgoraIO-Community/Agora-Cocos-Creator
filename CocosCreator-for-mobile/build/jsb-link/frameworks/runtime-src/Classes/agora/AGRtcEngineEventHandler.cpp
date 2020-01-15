//
//  AGRtcEngineEventHandler.cpp
//
//  Created by 张涛 on 2019/12/31.
//

#include "AGRtcEngineEventHandler.hpp"

namespace agora
{
    namespace cocos
    {
        AGRtcEngineEventHandler::AGRtcEngineEventHandler(AGContext* context)
        {
            _context = context;
        }
        
        AGRtcEngineEventHandler::~AGRtcEngineEventHandler()
        {
            _context = NULL;
        }
        
        void AGRtcEngineEventHandler::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
        {
            CCLOG("%s, onJoinChannelSuccess", AGORA_TAG);
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                se::Value func;
                if (_context->_refObj->getProperty("onJoinChannelSuccess", &func)) {
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
                    se::ValueArray args;
                    args.push_back(se::Value((uid_t)uid));
                    args.push_back(se::Value((int)elapsed));
                    func.toObject()->call(args, _context->_refObj);
                }
            });
        }
        
        void AGRtcEngineEventHandler::onUserJoined(uid_t uid, int elapsed)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                se::Value func;
                if (_context->_refObj->getProperty("onUserJoined", &func)) {
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
                    se::ValueArray args;
                    args.push_back(se::Value((uid_t)uid));
                    args.push_back(se::Value((int)elapsed));
                    func.toObject()->call(args, _context->_refObj);
                }
            });
        }
        
        void AGRtcEngineEventHandler::onUserOffline(uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
        {
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                se::Value func;
                if (_context->_refObj->getProperty("onUserOffline", &func)) {
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
                    se::ValueArray args;
                    args.push_back(se::Value((uid_t)uid));
                    args.push_back(se::Value((int)reason));
                    func.toObject()->call(args, _context->_refObj);
                }
            });
        }
        
        void AGRtcEngineEventHandler::onLeaveChannel(const agora::rtc::RtcStats& stats)
        {
            CCLOG("%s onLeaveChannel", AGORA_TAG);
            cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                se::Value func;
                if(_context->_refObj->getProperty("onLeaveChannel", &func)){
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
                    se::ValueArray args;
                    se::HandleObject obj(se::Object::createPlainObject());
                    se::Value duration = se::Value::Null;
                    se::Value txBytes = se::Value::Null;
                    se::Value rxBytes = se::Value::Null;
                    se::Value txKBitRate = se::Value::Null;
                    se::Value rxKBitRate = se::Value::Null;
                    se::Value txAudioKBitRate = se::Value::Null;
                    se::Value rxAudioKBitRate = se::Value::Null;
                    se::Value cpuTotalUsage = se::Value::Null;
                    se::Value cpuAppUsage = se::Value::Null;
                    se::Value lastmileDelay = se::Value::Null;
                    se::Value userCount = se::Value::Null;

                    uint32_to_seval(stats.duration, &duration);
                    uint32_to_seval(stats.txBytes, &txBytes);
                    uint32_to_seval(stats.rxBytes, &rxBytes);
                    uint16_to_seval(stats.txAudioKBitRate, &txAudioKBitRate);
                    uint16_to_seval(stats.rxAudioKBitRate, &rxAudioKBitRate);
                    double_to_seval(stats.cpuTotalUsage, &cpuTotalUsage);
                    double_to_seval(stats.cpuAppUsage, &cpuAppUsage);
                    uint32_to_seval(stats.userCount, &userCount);

                    obj->setProperty("duration",duration);
                    obj->setProperty("txBytes",txBytes);
                    obj->setProperty("rxBytes", rxBytes);
                    obj->setProperty("txAudioKBitRate", txAudioKBitRate);
                    obj->setProperty("rxAudioKBitRate", rxAudioKBitRate);
                    obj->setProperty("cpuTotalUsage",cpuTotalUsage);
                    obj->setProperty("cpuAppUsage", cpuAppUsage);
                    obj->setProperty("userCount",userCount);
                    args.push_back(se::Value(obj));

                    func.toObject()->call(args, _context->_refObj);
                }
            });
        }
    }
}
