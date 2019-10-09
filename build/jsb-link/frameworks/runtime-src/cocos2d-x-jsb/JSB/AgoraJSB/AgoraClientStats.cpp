//
//  AgoraClientStats.cpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/4/17.
//

#include "AgoraClientStats.hpp"
#include "cocos2d.h"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.hpp"

using namespace se;
USING_NS_AGORA;
USING_NS_CC;

static se::Object* __jsb_hh_AgoraClientStats_proto = nullptr;
static se::Class* __jsb_hh_AgoraClientStats_class = nullptr;

NS_AGORA_BEGIN

AgoraClientStats::AgoraClientStats()
{
    this->uid = 0;
    this->width = 0;
    this->height = 0;
    this->receivedBitrate = 0;
    this->receivedFrameRate = 0;
}

AgoraClientStats::~AgoraClientStats()
{
    CCLOG("~AgoraClientStats");
}

NS_AGORA_END

//static bool js_AgoraClientStats_finalize(se::State& s)
//{
//    agora::AgoraClientStats* cobj = (agora::AgoraClientStats*)s.nativeThisObject();
//    delete cobj;
//    return true;
//}
//SE_BIND_FINALIZE_FUNC(js_AgoraClientStats_finalize)
//
//static bool js_AgoraClientStats_constructor(se::State& s)
//{
//    AgoraClientStats* cobj = new AgoraClientStats();
//    s.thisObject()->setPrivateData(cobj);
//    return true;
//}
//SE_BIND_CTOR(js_AgoraClientStats_constructor, __jsb_hh_AgoraClientStats_class, js_AgoraClientStats_finalize)

static bool js_AgoraClientStats_get_uid(se::State& s)
{
    AgoraClientStats* cobj = (AgoraClientStats*)s.nativeThisObject();
    int32_t ret = cobj->uid;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraClientStats_get_uid)

static bool js_AgoraClientStats_get_width(se::State& s)
{
    AgoraClientStats* cobj = (AgoraClientStats*)s.nativeThisObject();
    int32_t ret = cobj->width;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraClientStats_get_width)

static bool js_AgoraClientStats_get_height(se::State& s)
{
    AgoraClientStats* cobj = (AgoraClientStats*)s.nativeThisObject();
    int32_t ret = cobj->height;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraClientStats_get_height)

static bool js_AgoraClientStats_get_receivedBitrate(se::State& s)
{
    AgoraClientStats* cobj = (AgoraClientStats*)s.nativeThisObject();
    int32_t ret = cobj->receivedBitrate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraClientStats_get_receivedBitrate)

static bool js_AgoraClientStats_get_receivedFrameRate(se::State& s)
{
    AgoraClientStats* cobj = (AgoraClientStats*)s.nativeThisObject();
    int32_t ret = cobj->receivedFrameRate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraClientStats_get_receivedFrameRate)

bool js_register_hh_AgoraClientStats(se::Object* global)
{
    // 保证 namespace 对象存在
    se::Value hhVal;
    if (!global->getProperty(NS_AGORA_JSBNS, &hhVal))
    {
        // 不存在则创建一个 JS 对象，相当于 var ns = {};
        se::HandleObject jsobj(se::Object::createPlainObject());
        hhVal.setObject(jsobj);
        
        // 将 hh 对象挂载到 global 对象中，名称为 ns
        global->setProperty(NS_AGORA_JSBNS, hhVal);
    }
    se::Object* hh = hhVal.toObject();
    
    // 创建一个 Class 对象，开发者无需考虑 Class 对象的释放，其交由 ScriptEngine 内部自动处理
    auto cls = se::Class::create("AgoraClientStats", hh, nullptr, nullptr); // 如果无构造函数，最后一个参数可传入 nullptr，则这个类在 JS 中无法被 new AgoraClientStats()出来
    
    // 使用_SE 宏包装一下具体的函数名称
    cls->defineProperty("uid", _SE(js_AgoraClientStats_get_uid), nullptr);
    cls->defineProperty("width", _SE(js_AgoraClientStats_get_width), nullptr);
    cls->defineProperty("height", _SE(js_AgoraClientStats_get_height), nullptr);
    cls->defineProperty("receivedBitrate", _SE(js_AgoraClientStats_get_receivedBitrate), nullptr);
    cls->defineProperty("receivedFrameRate", _SE(js_AgoraClientStats_get_receivedFrameRate), nullptr);
    
    //    cls->defineProperty("xxx", _SE(js_AgoraClientStats_get_xxx), _SE(js_AgoraClientStats_set_xxx));
    //    cls->defineFinalizeFunction(_SE(js_AgoraClientStats_finalize));
    
    // 注册类型到 JS VirtualMachine 的操作
    cls->install();
    
    // JSBClassType 为 Cocos 引擎绑定层封装的类型注册的辅助函数，此函数不属于 ScriptEngine 这层
    JSBClassType::registerClass<AgoraClientStats>(cls);
    
    // 保存注册的结果，便于其他地方使用，比如类继承
    __jsb_hh_AgoraClientStats_proto = cls->getProto();
    __jsb_hh_AgoraClientStats_class = cls;
    
    // 清空异常
    se::ScriptEngine::getInstance()->clearException();
    return true;
}
