//
// Created by zhangtao@agora.io on 2019-12-24.
//
#include "OpenGLES2Render.h"


#include <map>

namespace agora
{
    namespace cocos
    {
        int OpenGLES2Render::updateTexture(unsigned int glId, CacheVideoFrame* videoFrame)
        {
            if(videoFrame == nullptr) {
                return -1;
            }

            GLint oldTex = 0;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTex);
            glBindTexture(GL_TEXTURE_2D, glId);
            //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, videoFrame->_width, videoFrame->_height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, videoFrame->_data);
            glBindTexture(GL_TEXTURE_2D, oldTex);
            return (videoFrame->_width << 16 | videoFrame->_height);
        }
    }
}
