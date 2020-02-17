#ifndef __AGORA_MANAGER_H__
#define __AGORA_MANAGER_H__

// #include "AgentManager.h"

class AgoraManager
{
public:
  static AgoraManager *getInstance();
  static void purge();

  void registerJSBCallback();

private:
  AgoraManager();
  virtual ~AgoraManager();

  static AgoraManager *_pInstance;
};

#endif