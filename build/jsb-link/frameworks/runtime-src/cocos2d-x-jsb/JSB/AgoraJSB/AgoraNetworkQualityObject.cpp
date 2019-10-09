//
//  AgoraNetworkQualityObject.cpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/9/20.
//

#include "AgoraNetworkQualityObject.hpp"
#include "cocos2d.h"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.hpp"

using namespace se;
USING_NS_AGORA;
USING_NS_CC;
static se::Object* __jsb_hh_AgoraNetworkQualityObject_proto = nullptr;
static se::Class* __jsb_hh_AgoraNetworkQualityObject_class = nullptr;

NS_AGORA_BEGIN

AgoraNetworkQualityObject::AgoraNetworkQualityObject()
{
    this->uid = 0;
    this->txquality = 0;
    this->rxquality = 0;
}

AgoraNetworkQualityObject::~AgoraNetworkQualityObject()
{
    CCLOG("~AgoraNetworkQualityObject");
}

void AgoraNetworkQualityObject::updateNetworkQuality(unsigned int uid,
                                                     unsigned int txquality,
                                                     unsigned int rxquality) {
    this->uid = uid;
    this->txquality = txquality;
    this->rxquality = rxquality;
}

NS_AGORA_END

static bool js_AgoraNetworkQualityObject_get_uid(se::State& s)
{
    AgoraNetworkQualityObject* cobj = (AgoraNetworkQualityObject*)s.nativeThisObject();
    int32_t ret = cobj->uid;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraNetworkQualityObject_get_uid)

static bool js_AgoraNetworkQualityObject_get_txquality(se::State& s)
{
    AgoraNetworkQualityObject* cobj = (AgoraNetworkQualityObject*)s.nativeThisObject();
    int32_t ret = cobj->txquality;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraNetworkQualityObject_get_txquality)

static bool js_AgoraNetworkQualityObject_get_rxquality(se::State& s)
{
    AgoraNetworkQualityObject* cobj = (AgoraNetworkQualityObject*)s.nativeThisObject();
    int32_t ret = cobj->rxquality;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraNetworkQualityObject_get_rxquality)

bool js_register_hh_AgoraNetworkQualityObject(se::Object* global)
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
    auto cls = se::Class::create("AgoraNetworkQualityObject", hh, nullptr, nullptr); // 如果无构造函数，最后一个参数可传入 nullptr，则这个类在 JS 中无法被 new AgoraNetworkQualityObject()出来
    
    // 使用_SE 宏包装一下具体的函数名称
    cls->defineProperty("uid", _SE(js_AgoraNetworkQualityObject_get_uid), nullptr);
    cls->defineProperty("txquality", _SE(js_AgoraNetworkQualityObject_get_txquality), nullptr);
    cls->defineProperty("rxquality", _SE(js_AgoraNetworkQualityObject_get_rxquality), nullptr);
    
    //    cls->defineProperty("xxx", _SE(js_AgoraNetworkQualityObject_get_xxx), _SE(js_AgoraNetworkQualityObject_set_xxx));
    //    cls->defineFinalizeFunction(_SE(js_AgoraNetworkQualityObject_finalize));
    
    // 注册类型到 JS VirtualMachine 的操作
    cls->install();
    
    // JSBClassType 为 Cocos 引擎绑定层封装的类型注册的辅助函数，此函数不属于 ScriptEngine 这层
    JSBClassType::registerClass<AgoraNetworkQualityObject>(cls);
    
    // 保存注册的结果，便于其他地方使用，比如类继承
    __jsb_hh_AgoraNetworkQualityObject_proto = cls->getProto();
    __jsb_hh_AgoraNetworkQualityObject_class = cls;
    
    // 清空异常
    se::ScriptEngine::getInstance()->clearException();
    return true;
}
