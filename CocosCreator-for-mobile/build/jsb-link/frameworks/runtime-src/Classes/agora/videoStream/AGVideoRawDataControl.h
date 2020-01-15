//
// Created by 张涛 on 2019-12-23.
//

#ifndef PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H
#define PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H

#include "../include/libyuv.h"
#include "../include_file.h"
#include "CacheVideoFrame.h"
#include <mutex>
#include <list>
#include <map>

namespace agora
{
    namespace cocos
    {
        class AGVideoRawDataControl : public agora::media::IVideoFrameObserver
        {
        private:
            std::mutex _mapMutex;
            std::map<UINT32, agora::cocos::CacheVideoFrame*> _cacheVideoFrameMap;
            std::map<UINT32, COCOS_TEXTURE*> _cacheTextureMap;
            
        public:
            AGVideoRawDataControl();
            ~AGVideoRawDataControl();
            virtual bool onCaptureVideoFrame(AGORA_VIDEO_FRAME& videoFrame);
            virtual bool onRenderVideoFrame(UINT32 uid, AGORA_VIDEO_FRAME& videoFrame);
            virtual bool getRotationApplied();
            void cacheVideoFrameForUser(UINT32 uid, AGORA_VIDEO_FRAME& videoFrame);
            CacheVideoFrame* getVideoFrame(UINT32 uid);
            COCOS_TEXTURE* getTexture(UINT32 uid);
            int updateTexture(UINT32 glid, UINT32 uid);
            COCOS_TEXTURE* updateTexture(UINT32 uid);
            void convertVideoFrameFromI420ToABGR(const uint8* src_y, int src_stride_y,
                                                  const uint8* src_u, int src_stride_u,
                                                  const uint8* src_v, int src_stride_v,
                                                  uint8* dst_argb, int dst_stride_argb,
                                                  int width, int height);
            void rotateVideoFrame(uint8* data, int stride, int width, int height);
            void clearData();
        };
    }
}
#endif //PROJ_ANDROID_STUDIO_MYVIDEOFRAMEOBSERVER_H
