//
// Created by zhangtao@agora.io on 2019-12-23.
//

#include "MyVideoRawDataControl.h"

namespace agora
{
    namespace cocos
    {
        MyVideoRawDataControl::MyVideoRawDataControl()
        {
            _openGLES2Render = new OpenGLES2Render();
        }

        MyVideoRawDataControl::~MyVideoRawDataControl()
        {
            clearData();
            if (_openGLES2Render)
            {
                delete _openGLES2Render;
                _openGLES2Render = NULL;
            }
        }

        int MyVideoRawDataControl::updateTexture(unsigned int glid, unsigned int uid)
        {
            _mapMutex.lock();
            CacheVideoFrame* cacheVideoFrame = getVideoFrame(uid);
            int ret = _openGLES2Render->updateTexture(glid, cacheVideoFrame);
            _mapMutex.unlock();
            return ret;
        }

        bool MyVideoRawDataControl::onCaptureVideoFrame(agora::media::IVideoFrameObserver::VideoFrame& videoFrame)
        {
            _mapMutex.lock();
            printf("c++ onCaptureVideoFrame ");
            cacheVideoFrameForUser(0, videoFrame);
            _mapMutex.unlock();
            return true;
        }

        bool MyVideoRawDataControl::onRenderVideoFrame(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame& videoFrame)
        {
            _mapMutex.lock();
            cacheVideoFrameForUser(uid, videoFrame);
            _mapMutex.unlock();
            return true;
        }

//        agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE MyVideoRawDataControl::getVideoFormatPreference()
//        {
//            return agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE::FRAME_TYPE_RGBA;
//        }
//
//        bool MyVideoRawDataControl::getRotationApplied()
//        {
//            return true;
//        }
//
//        bool MyVideoRawDataControl::getMirrorApplied()
//        {
//            return true;
//        }

        void MyVideoRawDataControl::cacheVideoFrameForUser(unsigned int uid, agora::media::IVideoFrameObserver::VideoFrame& videoFrame)
        {
            std::map<unsigned int, CacheVideoFrame *>::iterator it;
            it = _userMap.find(uid);
            if (it == _userMap.end())
            {
                //no user cached before, so create
                CacheVideoFrame *cacheVideoFrame = new CacheVideoFrame(videoFrame.width, videoFrame.height);
                //memcpy(cacheVideoFrame->_data, videoFrame.yBuffer, videoFrame.width * videoFrame.height * 4);
                 printf("c++ cacheVideoFrameForUser ");
                convertVideoFrameFromI420ToABGR((uint8_t*)videoFrame.yBuffer, videoFrame.yStride, (uint8_t*)videoFrame.uBuffer, videoFrame.uStride, (uint8_t*)videoFrame.vBuffer, videoFrame.vStride, (uint8_t*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                if ((videoFrame.rotation % 360) == 180) {
                    rotateVideoFrame((uint8_t*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                }
                _userMap[uid] = cacheVideoFrame;
                printf("cacheVideoFrameForUser 11--");
            }
            else
            {
                CacheVideoFrame* cacheVideoFrame = _userMap[uid];
                if (cacheVideoFrame->_width != videoFrame.width || cacheVideoFrame->_height != videoFrame.height) {
                    delete cacheVideoFrame;
                    cacheVideoFrame = NULL;
                    cacheVideoFrame = new CacheVideoFrame(videoFrame.width, videoFrame.height);
                    _userMap[uid] = cacheVideoFrame;
                }
                //memcpy(cacheVideoFrame->_data, videoFrame.yBuffer, videoFrame.width * videoFrame.height *4);
                convertVideoFrameFromI420ToABGR((uint8_t*)videoFrame.yBuffer, videoFrame.yStride, (uint8_t*)videoFrame.uBuffer, videoFrame.uStride, (uint8_t*)videoFrame.vBuffer, videoFrame.vStride, (uint8_t*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                if ((videoFrame.rotation % 360) == 180) {
                    rotateVideoFrame((uint8_t*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                }
            }
        }

        CacheVideoFrame* MyVideoRawDataControl::getVideoFrame(unsigned int uid)
        {

            std::map<unsigned int, CacheVideoFrame *>::iterator it;
            it = _userMap.find(uid);
            if (it == _userMap.end())
            {
                return NULL;
            }
            else
            {
                return (it->second);
            }
        }

        void MyVideoRawDataControl::clearData()
        {
            std::map<unsigned int, CacheVideoFrame*>::iterator userIterator;
            for(userIterator=_userMap.begin(); userIterator!=_userMap.end(); userIterator++)
            {
                CacheVideoFrame* cacheVideoFrame = userIterator->second;
                if (cacheVideoFrame)
                {
                    delete cacheVideoFrame;
                    cacheVideoFrame = NULL;
                    _userMap.erase(userIterator);
                }
            }
        }

        void MyVideoRawDataControl::convertVideoFrameFromI420ToABGR(const uint8_t* src_y, int src_stride_y,
                                             const uint8_t* src_u, int src_stride_u,
                                             const uint8_t* src_v, int src_stride_v,
                                             uint8_t* dst_argb, int dst_stride_argb,
                                             int width, int height)
        {
            printf("convertVideoFrameFromI420ToABGR");
            libyuv::I420ToABGR(src_y, src_stride_y,
                               src_u, src_stride_u,
                               src_v, src_stride_v,
                               dst_argb, dst_stride_argb,
                               width, height);
        }

        void MyVideoRawDataControl::rotateVideoFrame(uint8_t* data, int stride, int width, int height)
        {
            libyuv::RotationMode mode = libyuv::kRotate180;
            libyuv::ARGBRotate(data, stride, data, stride, width, height, mode);
        }
    }
}
