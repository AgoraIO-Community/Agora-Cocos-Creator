//
//  AgoraManagerProtocol.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 05/03/2018.
//

#import <Foundation/Foundation.h>

#import "AGVideoProcessing.h"

#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

#import <AgoraRtcEngineKit/IAgoraRtcEngine.h>
#import <AgoraRtcEngineKit/IAgoraMediaEngine.h>
#import <string.h>

#import "AGVideoBuffer.h"

#import "libyuv.h"
#import "AGQueueManager.h"

class AgoraVideoFrameObserver : public agora::media::IVideoFrameObserver
{
public:
    virtual bool onCaptureVideoFrame(VideoFrame& videoFrame) override
    {
        AGVideoBuffer *videoBuffer = [[AGVideoBuffer alloc] initWithUId:0
                                                                yBuffer:videoFrame.yBuffer
                                                                uBuffer:videoFrame.uBuffer
                                                                vBuffer:videoFrame.vBuffer
                                                                yStride:videoFrame.yStride
                                                                uStride:videoFrame.uStride
                                                                vStride:videoFrame.vStride
                                                                  width:videoFrame.width
                                                                 height:videoFrame.height
                                                               rotation:videoFrame.rotation];
        [AGQueueManager updateVideoFrame:videoBuffer];
        return true;
    }
    
    virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame) override
    {
        AGVideoBuffer *videoBuffer = [[AGVideoBuffer alloc] initWithUId:(unsigned int)uid
                                                                yBuffer:videoFrame.yBuffer
                                                                uBuffer:videoFrame.uBuffer
                                                                vBuffer:videoFrame.vBuffer
                                                                yStride:videoFrame.yStride
                                                                uStride:videoFrame.uStride
                                                                vStride:videoFrame.vStride
                                                                  width:videoFrame.width
                                                                 height:videoFrame.height
                                                               rotation:videoFrame.rotation];
        [AGQueueManager updateVideoFrame:videoBuffer];
        return true;
    }
private:
    
};

static AgoraVideoFrameObserver s_videoFrameObserver;

@implementation AGVideoProcessing
+ (int) registerVideoPreprocessing: (AgoraRtcEngineKit*) kit
{
    if (!kit) {
        return -1;
    }
    
    agora::rtc::IRtcEngine* rtc_engine = (agora::rtc::IRtcEngine*)kit.getNativeHandle;
    agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
    mediaEngine.queryInterface(rtc_engine, agora::AGORA_IID_MEDIA_ENGINE);
    if (mediaEngine)
    {
        mediaEngine->registerVideoFrameObserver(&s_videoFrameObserver);
    }
    return 0;
}

+ (int) deregisterVideoPreprocessing: (AgoraRtcEngineKit*) kit
{
    if (!kit) {
        return -1;
    }
    
    agora::rtc::IRtcEngine* rtc_engine = (agora::rtc::IRtcEngine*)kit.getNativeHandle;
    agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
    mediaEngine.queryInterface(rtc_engine, agora::AGORA_IID_MEDIA_ENGINE);
    if (mediaEngine)
    {
        mediaEngine->registerVideoFrameObserver(NULL);
    }
    return 0;
}
@end
