//
// Created by 张涛 on 2019-12-23.
//
#include "AGVideoRawDataControl.h"

namespace agora
{
    namespace cocos
    {
        AGVideoRawDataControl::AGVideoRawDataControl()
        {
            
        }

        AGVideoRawDataControl::~AGVideoRawDataControl()
        {
            _mapMutex.lock();
            clearData();
            _mapMutex.unlock();
        }
        
        bool AGVideoRawDataControl::getRotationApplied()
        {
            return true;
        }

        bool AGVideoRawDataControl::onCaptureVideoFrame(AGORA_VIDEO_FRAME& videoFrame)
        {
            _mapMutex.lock();
            cacheVideoFrameForUser(0, videoFrame);
            _mapMutex.unlock();
            return true;
        }

        bool AGVideoRawDataControl::onRenderVideoFrame(UINT32 uid, AGORA_VIDEO_FRAME& videoFrame)
        {
            _mapMutex.lock();
            cacheVideoFrameForUser(uid, videoFrame);
            _mapMutex.unlock();
            return true;
        }

        void AGVideoRawDataControl::cacheVideoFrameForUser(UINT32 uid, AGORA_VIDEO_FRAME& videoFrame)
        {
            std::map<UINT32, CacheVideoFrame *>::iterator it;
            it = _cacheVideoFrameMap.find(uid);
            if (it == _cacheVideoFrameMap.end())
            {   // cache video frame
                CacheVideoFrame *cacheVideoFrame = new CacheVideoFrame(videoFrame.width, videoFrame.height);
                _cacheVideoFrameMap[uid] = cacheVideoFrame;
                // convert video frame from I420 to RGBA32
                convertVideoFrameFromI420ToABGR((uint8*)videoFrame.yBuffer, videoFrame.yStride, (uint8*)videoFrame.uBuffer, videoFrame.uStride, (uint8*)videoFrame.vBuffer, videoFrame.vStride, (uint8*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                
                CCLOG("%s videoframe rotation = %d", AGORA_TAG, videoFrame.rotation);
                // check wheather need to rotate video
                if ((videoFrame.rotation % 360) == 180) {
                    rotateVideoFrame((uint8*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                }
                
                // cache texture for js
                COCOS_TEXTURE *selfTexture = new COCOS_TEXTURE;
                _cacheTextureMap[uid] = selfTexture;
                CCLOG("%s new Texture for uid %u", AGORA_TAG, uid);
            }
            else
            {
                CacheVideoFrame* cacheVideoFrame = _cacheVideoFrameMap[uid];
                /*
                 * if video frame size is changed, we need to reCreate the cacheVideoFrame pointer.
                 */
                if (cacheVideoFrame->_width != videoFrame.width || cacheVideoFrame->_height != videoFrame.height)
                {
                    CCLOG("%s size change for uid %u , before width = %d & height = %d , now width = %d & height = %d", AGORA_TAG, uid, cacheVideoFrame->_width, cacheVideoFrame->_height, videoFrame.width, videoFrame.height);
                    delete cacheVideoFrame;
                    cacheVideoFrame = NULL;
                    cacheVideoFrame = new CacheVideoFrame(videoFrame.width, videoFrame.height);
                    _cacheVideoFrameMap[uid] = cacheVideoFrame;

                    COCOS_TEXTURE* texture = _cacheTextureMap[uid];
                    if (texture)
                    {
                        CC_SAFE_RELEASE(texture);
                        texture = NULL;
                        texture = new COCOS_TEXTURE;
                        _cacheTextureMap[uid] = texture;
                    }
                }

                convertVideoFrameFromI420ToABGR((uint8*)videoFrame.yBuffer, videoFrame.yStride, (uint8*)videoFrame.uBuffer, videoFrame.uStride, (uint8*)videoFrame.vBuffer, videoFrame.vStride, (uint8*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                if ((videoFrame.rotation % 360) == 180) {
                    rotateVideoFrame((uint8*)cacheVideoFrame->_data, cacheVideoFrame->_width * 4, cacheVideoFrame->_width, cacheVideoFrame->_height);
                }
            }
        }

        CacheVideoFrame* AGVideoRawDataControl::getVideoFrame(UINT32 uid)
        {
            std::map<UINT32, CacheVideoFrame *>::iterator it;
            it = _cacheVideoFrameMap.find(uid);
            if (it == _cacheVideoFrameMap.end())
            {
                return NULL;
            }
            else
            {
                return (it->second);
            }
        }
        
        COCOS_TEXTURE* AGVideoRawDataControl::getTexture(UINT32 uid)
        {
            std::map<UINT32, COCOS_TEXTURE*>::iterator it;
            it = _cacheTextureMap.find(uid);
            if (it == _cacheTextureMap.end())
            {
                CCLOGERROR("%s No Texture found for user %u", AGORA_TAG, uid);
                return NULL;
            }
            else
            {
                return (it->second);
            }
        }
        
        // For Render video frame by openGLES2 in Cocos Creator 2.0.
        int AGVideoRawDataControl::updateTexture(UINT32 glid, UINT32 uid)
        {
            _mapMutex.lock();
            CacheVideoFrame* cacheVideoFrame = getVideoFrame(uid);
            int ret = 0;
            _mapMutex.unlock();
            return ret;
        }
        
        COCOS_TEXTURE* AGVideoRawDataControl::updateTexture(UINT32 uid)
        {
            _mapMutex.lock();
            COCOS_TEXTURE* texture = getTexture(uid);
            CacheVideoFrame* cacheVideoFrame = getVideoFrame(uid);
            if (texture && cacheVideoFrame)
            {
                if (texture->getName() == 0)
                {
                    texture->initWithData(cacheVideoFrame->_data, cacheVideoFrame->_width * cacheVideoFrame->_height * 4,  COCOS_TEXTURE::PixelFormat::RGBA8888, cacheVideoFrame->_width, cacheVideoFrame->_height, cocos2d::Size(cacheVideoFrame->_width, cacheVideoFrame->_height));
                }
                else
                {
                    texture->updateWithData(cacheVideoFrame->_data, 0, 0, cacheVideoFrame->_width, cacheVideoFrame->_height);
                }
                _mapMutex.unlock();
                return texture;
            }
            else
            {
                _mapMutex.unlock();
                return NULL;
            }
        }
        
        void AGVideoRawDataControl::convertVideoFrameFromI420ToABGR(const uint8* src_y, int src_stride_y,
                                                                     const uint8* src_u, int src_stride_u,
                                                                     const uint8* src_v, int src_stride_v,
                                                                     uint8* dst_argb, int dst_stride_argb,
                                                                     int width, int height)
        {
            libyuv::I420ToABGR(src_y, src_stride_y,
                               src_u, src_stride_u,
                               src_v, src_stride_v,
                               dst_argb, dst_stride_argb,
                               width, height);
            
        }
        
        void AGVideoRawDataControl::rotateVideoFrame(uint8* data, int stride, int width, int height)
        {
            libyuv::RotationMode mode = libyuv::kRotate180;
            libyuv::ARGBRotate(data, stride, data, stride, width, height, mode);
        }

        void AGVideoRawDataControl::clearData()
        {
            std::map<UINT32, CacheVideoFrame*>::iterator videoFrameIterator;
            for(videoFrameIterator=_cacheVideoFrameMap.begin(); videoFrameIterator!=_cacheVideoFrameMap.end(); videoFrameIterator++)
            {
                CacheVideoFrame* cacheVideoFrame = videoFrameIterator->second;
                if (cacheVideoFrame)
                {
                    delete cacheVideoFrame;
                    cacheVideoFrame = NULL;
                    _cacheVideoFrameMap.erase(videoFrameIterator);
                }
            }
            
            std::map<UINT32, COCOS_TEXTURE*>::iterator textureIterator;
            for (textureIterator=_cacheTextureMap.begin(); textureIterator!=_cacheTextureMap.end(); textureIterator++)
            {
                COCOS_TEXTURE* cacheTexture = textureIterator->second;
                if (cacheTexture)
                {
                    CC_SAFE_RELEASE(cacheTexture);
                    cacheTexture = NULL;
                    _cacheTextureMap.erase(textureIterator);
                }
            }
        }
    }
}
