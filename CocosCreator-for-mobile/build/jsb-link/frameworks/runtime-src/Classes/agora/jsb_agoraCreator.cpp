//
//  jsb_agoraCreator.cpp
//  zhangtao@agora.io
//
//  Created by 张涛 on 2019/12/31.
//

#include "jsb_agoraCreator.hpp"
using namespace agora::rtc;
using namespace agora::media;
using namespace agora::util;
using namespace agora::cocos;

AGORA_EXPORT_C
{
    #define CHECK_ENGINE()    \
    if (!(_context->_rtcEngine)) \
    {                           \
        CCLOG("%s did not initialize agora rtc engine yet, please initialize it first!", AGORA_TAG);\
        return false;          \
    }
    
    AGORA_STATIC_BOOL js_agoraCreator_finalize(se::State& s){
        CCLOGINFO("%s : js_agoraCreator_finalize", AGORA_TAG);
        if (_context)
        {
            if (_context->_rtcEngine)
            {
                _context->_rtcEngine->release();
                _context->_rtcEngine = NULL;
            }
            
            if (_context->_rtcEngineEventHandler)
            {
                delete _context->_rtcEngineEventHandler;
                _context->_rtcEngineEventHandler = NULL;
            }
            delete _context;
            _context = NULL;
        }
        return true;
    }
    SE_BIND_FINALIZE_FUNC(js_agoraCreator_finalize)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_constructor(se::State& s)
    {
        if (_context == NULL)
        {
            _context = new AGContext();
            _context->_rtcEngine = createAgoraRtcEngine();
        }
        se::Object* obj = s.thisObject();
        _context->_refObj = obj;
        if (obj)
        {
            obj->setPrivateData(_context);
            se::Value func;
            if (obj->getProperty("_ctor", &func)) {
                func.toObject()->call(se::EmptyValueArray, obj);
            }
        }
        return true;
    }
    SE_BIND_CTOR(js_cocos2dx_extension_agoraCreator_constructor, js_cocos2dx_agoraCreator_class, js_agoraCreator_finalize)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_joinChannel(se::State& s)
    {
        CHECK_ENGINE();
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 4) {
            std::string token;
            ok &= seval_to_std_string(args[0], &token);
            
            std::string channelId;
            ok &= seval_to_std_string(args[1], &channelId);
            
            std::string info;
            ok &= seval_to_std_string(args[2], &info);
            
            uint32_t uid;
            ok &= seval_to_uint32(args[3], &uid);
            
            int ret = _context->_rtcEngine->joinChannel(token.c_str(), channelId.c_str(), info.c_str(), uid);
            int32_to_seval(ret, &s.rval());
            CCLOG("%s js_cocos2dx_extension_agoraCreator_joinChannel ret = %d", AGORA_TAG, ret);
            return true;
        }
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
        CCLOGERROR("%s error js_cocos2dx_extension_agoraCreator_joinChannel ", AGORA_TAG);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_joinChannel)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_initialize(se::State& s)
    {
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 1)
        {
            std::string appId;
            ok &= seval_to_std_string(args[0], &appId);
            SE_PRECONDITION2(ok, false, "js_cocos2dx_extension_agoraCreator_initialize : Error processing arguments");
            _context->_rtcEngineEventHandler = new AGRtcEngineEventHandler(_context);
            RtcEngineContext ctx;
            ctx.appId = appId.c_str();
            ctx.eventHandler = _context->_rtcEngineEventHandler;
            _context->_rtcEngine->initialize(ctx);
            CCLOG("%s js_cocos2dx_extension_agoraCreator_initialize appId = %s", AGORA_TAG, appId.c_str());
            return true;
        }
        CCLOGERROR("%s error js_cocos2dx_extension_agoraCreator_initialize please input your appId", AGORA_TAG);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_initialize)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_leaveChannel(se::State& s)
    {
        CHECK_ENGINE();
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 0) {
            int ret = _context->_rtcEngine->leaveChannel();
            ok &= int32_to_seval(ret, &s.rval());
            SE_PRECONDITION2(ok, false, "js_cocos2dx_extension_agoraCreator_leaveChannel : Error processing arguments");
            CCLOG("%s api call js_cocos2dx_extension_agoraCreator_leaveChannel()  ret = %d", AGORA_TAG, ret);
            return true;
        }
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
        CCLOGERROR("%s error api call js_cocos2dx_extension_agoraCreator_leaveChannel()  argc = %u", AGORA_TAG, argc);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_leaveChannel)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_enableVideoObserver(se::State& s) {
        CHECK_ENGINE();
        if (!(_context->_videoRawDataControl))
        {
            _context->_videoRawDataControl = new AGVideoRawDataControl();
        }

        agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
        mediaEngine.queryInterface(_context->_rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);
        int ret = -100;
        if (mediaEngine)
        {
            ret = mediaEngine->registerVideoFrameObserver(_context->_videoRawDataControl);
            int32_to_seval(ret, &s.rval());
        }
        CCLOG("%s js_cocos2dx_extension_agoraCreator_enableVideoObserver() ret = %d", AGORA_TAG, ret);
        return true;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_enableVideoObserver)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_disableVideoObserver(se::State& s) {
        CHECK_ENGINE();
        agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
        mediaEngine.queryInterface(_context->_rtcEngine, agora::AGORA_IID_MEDIA_ENGINE);
        int ret = mediaEngine->registerVideoFrameObserver(NULL);
        
        if (_context->_videoRawDataControl)
        {
            CCLOG("%s js_cocos2dx_extension_agoraCreator_disableVideoObserver ", AGORA_TAG);
            delete _context->_videoRawDataControl;
            _context->_videoRawDataControl= NULL;
        }
        int32_to_seval(ret, &s.rval());
        CCLOG("%s api call js_cocos2dx_extension_agoraCreator_disableVideoObserver()  ret = %d", AGORA_TAG, ret);
        return true;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_disableVideoObserver)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_setParameters(se::State& s)
    {
        CHECK_ENGINE();
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 1) {
            std::string parameters;
            ok &= seval_to_std_string(args[0], &parameters);
            
            int ret = _context->_rtcEngine->setParameters(parameters.c_str());
            int32_to_seval(ret, &s.rval());
            CCLOG("%s js_cocos2dx_extension_agoraCreator_setParameters ret = %d", AGORA_TAG, ret);
            return true;
        }
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
        CCLOGERROR("%s error js_cocos2dx_extension_agoraCreator_setParameters ", AGORA_TAG);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_setParameters)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_enableVideo(se::State& s)
    {
        CHECK_ENGINE();
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 0)
        {
            int ret = _context->_rtcEngine->enableVideo();
            int32_to_seval(ret, &s.rval());
            CCLOG("%s js_cocos2dx_extension_agoraCreator_setParameters ret = %d", AGORA_TAG, ret);
            return true;
        }
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
        CCLOGERROR("%s error js_cocos2dx_extension_agoraCreator_setParameters ", AGORA_TAG);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_enableVideo)

    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_disableVideo(se::State& s)
    {
        CHECK_ENGINE();
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (argc == 0)
        {
            int ret = _context->_rtcEngine->enableVideo();
            int32_to_seval(ret, &s.rval());
            CCLOG("%s js_cocos2dx_extension_agoraCreator_setParameters ret = %d", AGORA_TAG, ret);
            return true;
        }
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
        CCLOGERROR("%s error js_cocos2dx_extension_agoraCreator_setParameters ", AGORA_TAG);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_disableVideo)
    
    AGORA_STATIC_BOOL js_cocos2dx_extension_agoraCreator_updateTexture(se::State& s)
    {
        CHECK_ENGINE();
        const auto& args = s.args();
        size_t argc = args.size();
        CC_UNUSED bool ok = true;
        if (!(_context->_videoRawDataControl))
        {
            ok = false;
            return ok;
        }
        
        if (argc == 1)
        {
            UINT32 uid;
            ok = seval_to_uint32(args[0], &uid);
            SE_PRECONDITION2(ok, false, "Error processing arguments");
            COCOS_TEXTURE* ret = _context->_videoRawDataControl->updateTexture(uid);
            if (ret)
            {
                const char* typeName = typeid(*ret).name();
                ok &= native_ptr_to_seval<COCOS_TEXTURE>(ret, &s.rval());
                SE_PRECONDITION2(ok, false, "js_HomeAgora_getTexture : Error processing arguments");
            }
            return true;
        }
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
        return false;
    }
    SE_BIND_FUNC(js_cocos2dx_extension_agoraCreator_updateTexture)

    bool js_register_cocos2dx_extension_agoraCreator(se::Object* obj)
    {
        auto cls = se::Class::create("agoraCreator", obj, nullptr, _SE(js_cocos2dx_extension_agoraCreator_constructor));
        cls->defineFunction("initialize", _SE(js_cocos2dx_extension_agoraCreator_initialize));
        cls->defineFunction("leaveChannel", _SE(js_cocos2dx_extension_agoraCreator_leaveChannel));
        cls->defineFunction("joinChannel", _SE(js_cocos2dx_extension_agoraCreator_joinChannel));
        cls->defineFunction("enableVideoObserver", _SE(js_cocos2dx_extension_agoraCreator_enableVideoObserver));
        cls->defineFunction("disableVideoObserver", _SE(js_cocos2dx_extension_agoraCreator_disableVideoObserver));
        cls->defineFunction("setParameters", _SE(js_cocos2dx_extension_agoraCreator_setParameters));
        cls->defineFunction("enableVideo", _SE(js_cocos2dx_extension_agoraCreator_enableVideo));
        cls->defineFunction("disableVideo", _SE(js_cocos2dx_extension_agoraCreator_disableVideo));
        cls->defineFunction("updateTexture", _SE(js_cocos2dx_extension_agoraCreator_updateTexture));
        cls->defineFinalizeFunction(_SE(js_agoraCreator_finalize));
        cls->install();
        js_cocos2dx_agoraCreator_prototype = cls->getProto();
        js_cocos2dx_agoraCreator_class = cls;
        se::ScriptEngine::getInstance()->clearException();
        CCLOG("%s api call js_register_cocos2dx_extension_agoraCreator()", AGORA_TAG);
        return true;
    }

    bool register_jsb_agoraCreator(se::Object* obj)
    {
        return js_register_cocos2dx_extension_agoraCreator(obj);
    }
}
