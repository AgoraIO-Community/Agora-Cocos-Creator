//
// Created by zhangtao@agora.io on 2019-12-24.
//

#ifndef PROJ_ANDROID_STUDIO_OPENGLES2RENDER_H
#define PROJ_ANDROID_STUDIO_OPENGLES2RENDER_H

#if defined(__ANDROID__)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES/gl.h>
#else
#endif

#if defined(__APPLE__)
#include <OpenGLES/ES2/gl.h>
#else
#endif

#include "include/agora/IAgoraMediaEngine.h"
#include "CacheVideoFrame.h"
namespace agora
{
    namespace cocos
    {
        class OpenGLES2Render
        {
        public:
            int updateTexture(unsigned int glId, CacheVideoFrame* videoFrame);
        };
    }
}
#endif //PROJ_ANDROID_STUDIO_OPENGLES2RENDER_H
