#include "AgoraManager.h"
#include "jsb_agoraCreator.h"
#include "cocos2d.h"

AgoraManager *AgoraManager::_pInstance = nullptr;

AgoraManager::AgoraManager() {}

AgoraManager::~AgoraManager() {}

AgoraManager *AgoraManager::getInstance() {
  if (_pInstance == nullptr) {
    _pInstance = new AgoraManager();
  }
  return _pInstance;
}

void AgoraManager::registerJSBCallback() {
  se::ScriptEngine *se = se::ScriptEngine::getInstance();
  se->addRegisterCallback(register_jsb_agoraCreator);
}