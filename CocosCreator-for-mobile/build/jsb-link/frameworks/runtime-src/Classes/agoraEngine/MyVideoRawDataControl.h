//
// Created by zhangtao@agora.io on 2019-12-23.
//

#ifndef PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H
#define PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H

#include "include/agora/IAgoraRtcEngine.h"
#include "include/agora/IAgoraMediaEngine.h"
#include "include/agora/AgoraBase.h"
#include "include/agora/IAgoraService.h"
#include "CacheVideoFrame.h"
#include "OpenGLES2Render.h"
#include "include/libyuv.h"
#include <mutex>
#include <list>
#include <map>

namespace agora
{
    namespace cocos
    {
        class MyVideoRawDataControl : public agora::media::IVideoFrameObserver
        {
        private:
            std::mutex _mapMutex;
            std::map<unsigned int, agora::cocos::CacheVideoFrame*> _userMap;
            OpenGLES2Render* _openGLES2Render;

        public:
            MyVideoRawDataControl();
            ~MyVideoRawDataControl();
            bool onCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& videoFrame);
            bool onRenderVideoFrame(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame& videoFrame);
            void cacheVideoFrameForUser(unsigned int uid, VideoFrame& videoFrame);
//            virtual agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE getVideoFormatPreference();
//            virtual bool getRotationApplied();
//            virtual bool getMirrorApplied();
            CacheVideoFrame* getVideoFrame(unsigned int uid);
            int updateTexture(unsigned int glid, unsigned int uid);
            void clearData();
            void convertVideoFrameFromI420ToABGR(const uint8_t* src_y, int src_stride_y,
                                                 const uint8_t* src_u, int src_stride_u,
                                                 const uint8_t* src_v, int src_stride_v,
                                                 uint8_t* dst_argb, int dst_stride_argb,
                                                 int width, int height);
            void rotateVideoFrame(uint8_t* data, int stride, int width, int height);
        };
    }
}
#endif //PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H
