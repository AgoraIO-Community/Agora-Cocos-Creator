//
//  AgoraStats.cpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/4/16.
//

#include "AgoraStats.hpp"
#include "cocos2d.h"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.hpp"

using namespace se;
USING_NS_AGORA;
USING_NS_CC;

static se::Object* __jsb_hh_AgoraStats_proto = nullptr;
static se::Class* __jsb_hh_AgoraStats_class = nullptr;

NS_AGORA_BEGIN

AgoraStats::AgoraStats()
{
    this->duration = 0;
    this->txBytes = 0;
    this->rxBytes = 0;
    this->txAudioKBitrate = 0;
    this->rxAudioKBitrate = 0;
    this->txVideoKBitrate = 0;
    this->rxVideoKBitrate = 0;
    this->userCount = 0;
    this->cpuAppUsage = 0;
    this->cpuTotalUsage = 0;
    this->sentBitrate = 0;
    this->sentFrameRate = 0;
}

AgoraStats::~AgoraStats()
{
    CCLOG("~AgoraStats");
}

void AgoraStats::updateClientStats(unsigned int uid,
                                   unsigned int width,
                                   unsigned int height,
                                   unsigned int receivedBitrate,
                                   unsigned int receivedFrameRate) {
    AgoraClientStats* client = this->clients.at(uid);
    if (client == NULL) {
        client = new AgoraClientStats();
        this->clients.insert(uid, client);
        CC_SAFE_RELEASE(client);
    }
    client->uid = uid;
    client->width = width;
    client->height = height;
    client->receivedBitrate = receivedBitrate;
    client->receivedFrameRate = receivedFrameRate;
}

NS_AGORA_END

//static bool js_AgoraStats_finalize(se::State& s)
//{
//    agora::AgoraStats* cobj = (agora::AgoraStats*)s.nativeThisObject();
//    delete cobj;
//    return true;
//}
//SE_BIND_FINALIZE_FUNC(js_AgoraStats_finalize)
//
//static bool js_AgoraStats_constructor(se::State& s)
//{
//    AgoraStats* cobj = new AgoraStats();
//    s.thisObject()->setPrivateData(cobj);
//    return true;
//}
//SE_BIND_CTOR(js_AgoraStats_constructor, __jsb_hh_AgoraStats_class, js_AgoraStats_finalize)

static bool js_AgoraStats_get_duration(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->duration;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_duration)

static bool js_AgoraStats_get_txBytes(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->txBytes;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_txBytes)

static bool js_AgoraStats_get_rxBytes(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->rxBytes;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_rxBytes)

static bool js_AgoraStats_get_txAudioKBitrate(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->txAudioKBitrate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_txAudioKBitrate)

static bool js_AgoraStats_get_rxAudioKBitrate(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->rxAudioKBitrate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_rxAudioKBitrate)

static bool js_AgoraStats_get_txVideoKBitrate(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->txVideoKBitrate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_txVideoKBitrate)

static bool js_AgoraStats_get_rxVideoKBitrate(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->rxVideoKBitrate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_rxVideoKBitrate)

static bool js_AgoraStats_get_userCount(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->userCount;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_userCount)

static bool js_AgoraStats_get_cpuAppUsage(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    double ret = cobj->cpuAppUsage;
    s.rval().setNumber(ret);
//    double_to_seval(ret, &s.rval());
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_cpuAppUsage)

static bool js_AgoraStats_get_cpuTotalUsage(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    double ret = cobj->cpuTotalUsage;
    s.rval().setNumber(ret);
//    double_to_seval(ret, &s.rval());
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_cpuTotalUsage)
void int2str(const int &int_temp,string &string_temp)
{
    stringstream stream;
    stream<<int_temp;
    string_temp=stream.str();   //此处也可以用 stream>>string_temp
}

static bool js_AgoraStats_get_sentBitrate(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->sentBitrate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_sentBitrate)

static bool js_AgoraStats_get_sentFrameRate(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    int32_t ret = cobj->sentFrameRate;
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_sentFrameRate)

static bool js_AgoraStats_get_clients(se::State& s)
{
    AgoraStats* cobj = (AgoraStats*)s.nativeThisObject();
    cocos2d::Map<unsigned int, AgoraClientStats*> ret = cobj->clients;
    se::HandleObject obj(se::Object::createPlainObject());
    for(auto iter = ret.begin(); iter != ret.end(); iter++){
        unsigned int u = iter->first;
        stringstream stream;
        stream<<u;
        string string_temp=stream.str();
        AgoraClientStats* stats = iter->second;
        se::HandleObject o(se::Object::createPlainObject());
        o->setProperty("uid", se::Value(stats->uid));
        o->setProperty("width", se::Value(stats->width));
        o->setProperty("height", se::Value(stats->height));
        o->setProperty("receivedBitrate", se::Value(stats->receivedBitrate));
        o->setProperty("receivedFrameRate", se::Value(stats->receivedFrameRate));
        obj->setProperty(string_temp.c_str(), se::Value(o));
    }
    s.rval().setObject(obj);
    return true;
}
SE_BIND_PROP_GET(js_AgoraStats_get_clients)

bool js_register_hh_AgoraStats(se::Object* global)
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
    auto cls = se::Class::create("AgoraStats", hh, nullptr, nullptr); // 如果无构造函数，最后一个参数可传入 nullptr，则这个类在 JS 中无法被 new AgoraStats()出来
    
    // 使用_SE 宏包装一下具体的函数名称
    cls->defineProperty("duration", _SE(js_AgoraStats_get_duration), nullptr);
    cls->defineProperty("txBytes", _SE(js_AgoraStats_get_txBytes), nullptr);
    cls->defineProperty("rxBytes", _SE(js_AgoraStats_get_rxBytes), nullptr);
    cls->defineProperty("txAudioKBitrate", _SE(js_AgoraStats_get_txAudioKBitrate), nullptr);
    cls->defineProperty("rxAudioKBitrate", _SE(js_AgoraStats_get_rxAudioKBitrate), nullptr);
    cls->defineProperty("txVideoKBitrate", _SE(js_AgoraStats_get_txVideoKBitrate), nullptr);
    cls->defineProperty("rxVideoKBitrate", _SE(js_AgoraStats_get_rxVideoKBitrate), nullptr);
    cls->defineProperty("userCount", _SE(js_AgoraStats_get_userCount), nullptr);
    cls->defineProperty("cpuAppUsage", _SE(js_AgoraStats_get_cpuAppUsage), nullptr);
    cls->defineProperty("cpuTotalUsage", _SE(js_AgoraStats_get_cpuTotalUsage), nullptr);
    cls->defineProperty("sentBitrate", _SE(js_AgoraStats_get_sentBitrate), nullptr);
    cls->defineProperty("sentFrameRate", _SE(js_AgoraStats_get_sentFrameRate), nullptr);
    cls->defineProperty("clients", _SE(js_AgoraStats_get_clients), nullptr);

//    cls->defineProperty("xxx", _SE(js_AgoraStats_get_xxx), _SE(js_AgoraStats_set_xxx));
//    cls->defineFinalizeFunction(_SE(js_AgoraStats_finalize));
    
    // 注册类型到 JS VirtualMachine 的操作
    cls->install();
    
    // JSBClassType 为 Cocos 引擎绑定层封装的类型注册的辅助函数，此函数不属于 ScriptEngine 这层
    JSBClassType::registerClass<AgoraStats>(cls);
    
    // 保存注册的结果，便于其他地方使用，比如类继承
    __jsb_hh_AgoraStats_proto = cls->getProto();
    __jsb_hh_AgoraStats_class = cls;
    
    // 清空异常
    se::ScriptEngine::getInstance()->clearException();
    return true;
}
