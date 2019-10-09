//
//  AGQueueManager.m
//  Agora-iOS-Cocos
//
//  Created by Agora on 2018/8/16.
//

#import "AGQueueManager.h"
#import "AGVideoBuffer.h"

#import <CoreGraphics/CoreGraphics.h>
#import <string.h>

#include "convert_argb.h"
#include "scale_argb.h"
#include "convert_from_argb.h"
#include "rotate_argb.h"
#include "TimeUtil.hpp"
#include <mach/mach_time.h>
#import "AgoraManager.h"

@interface AGQueueManager () <NSCopying> {
    dispatch_queue_t _queue;
}

@end

@implementation AGQueueManager

static AGQueueManager *_shareManager;
+ (instancetype)shareManager {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (_shareManager == nil) {
            _shareManager = [[self alloc] init];
        }
    });
    return _shareManager;
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _shareManager = [super allocWithZone:zone];
    });
    return _shareManager;
}

- (id)copyWithZone:(NSZone *)zone {
    return _shareManager;
}

- (instancetype)init {
    if (self = [super init]) {
        _queue = dispatch_queue_create("videoQueue.agora.cn", DISPATCH_QUEUE_SERIAL);
    }
    return self;
}

- (dispatch_queue_t)getQueue {
    return _queue;
}

+ (void)updateVideoFrame:(AGVideoBuffer *)videoBuffer {

    static int videoCount = 0;
    
    if (videoCount > 15) return;
    
    videoCount ++;
    dispatch_async([[AGQueueManager shareManager] getQueue], ^{
        [AGQueueManager notififation:videoBuffer];
        if (videoCount > 0) {
            videoCount --;
        }
    });
}

//1.I420ToARGB
//2.ARGBRotate
//3.ARGBToRGBA
//4.大小端转换
+ (void)notififation:(AGVideoBuffer *)videoBuffer {
    int width = videoBuffer.width;
    int height = videoBuffer.height;
    
    unsigned int uid = videoBuffer.uid;
    
    if (uid == 0) {
        uid = [[AgoraManager share] localUid];
    }
    
    int argb_bitsperpixel = 32;//一个像素用几位表示
    int argb_bytesperpixel = argb_bitsperpixel / 8;//一个像素在几个字节的存储空间
    int argb_stride_argb = width * argb_bytesperpixel;
    int argb_length = (width * height * argb_bytesperpixel);
    
    uint8* argb_data = (uint8*)calloc(argb_length, sizeof(uint8));
    int res = libyuv::I420ToARGB(videoBuffer.yBuffer, videoBuffer.yStride, videoBuffer.uBuffer, videoBuffer.uStride, videoBuffer.vBuffer, videoBuffer.vStride, argb_data, argb_stride_argb, width, height);
    if (res == 0) {
        //        CULog(@"成功");
    }
    
    CGSize tSize = [[AgoraManager share] getTextureSize:uid];
    
    if (width != tSize.width && height != tSize.height) {
        int width_src = width;
        int height_src = height;
        width = (width > tSize.width ? width : tSize.width);
        height = (height > tSize.height ? height : tSize.height);
        int argb_stride_argb_src = argb_stride_argb;
        argb_stride_argb = width * argb_bytesperpixel;
        argb_length = (width * height * argb_bytesperpixel);
        uint8* argb_data_dst = (uint8* )calloc(argb_length, sizeof(uint8));
        libyuv::ARGBScale(argb_data, argb_stride_argb_src, width_src, height_src, argb_data_dst, argb_stride_argb, width, height, libyuv::kFilterNone);
        free(argb_data);
        argb_data = argb_data_dst;
    }
    
    if ((videoBuffer.rotation % 360) == 180) {
        libyuv::RotationMode mode = libyuv::kRotate180;
        libyuv::ARGBRotate(argb_data, argb_stride_argb, argb_data, argb_stride_argb, width, height, mode);
    }
    
    uint8 temp;
    for (int i = 0; i < argb_length / 4; i++) {
        temp = argb_data[i * 4];
        argb_data[i * 4] = argb_data[i * 4 + 2];
        argb_data[i * 4 + 2] = temp;
    }
    
    [[AgoraManager share] nitificationWithUid:uid rgbaBuffer:argb_data rgbaStride:argb_stride_argb dataLen:argb_length width:width height:height rotation:videoBuffer.rotation];
    
    free(argb_data);
}

@end
