//
//  PlatformMacros.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 12/01/2018.
//

#ifndef PlatformMacros_h
#define PlatformMacros_h

#ifdef __cplusplus
#define NS_AGORA_BEGIN                     namespace agora {
#define NS_AGORA_END                       }
#define USING_NS_AGORA                     using namespace agora
#define NS_AGORA                           ::agora
#define NS_AGORA_JSBNS                     "agora"
#else
#define NS_AGORA_BEGIN
#define NS_AGORA_END
#define USING_NS_AGORA
#define NS_AGORA
#endif

#endif /* PlatformMacros_h */
