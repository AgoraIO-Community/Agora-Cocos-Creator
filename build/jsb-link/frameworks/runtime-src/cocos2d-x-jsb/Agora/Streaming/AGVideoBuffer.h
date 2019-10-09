//
//  AgoraManagerProtocol.h
//  Agora-iOS-Cocos
//
//  Created by Agora on 05/03/2018.
//

#import <Foundation/Foundation.h>

@interface AGVideoBuffer : NSObject
@property (assign, nonatomic) unsigned char *yBuffer;
@property (assign, nonatomic) unsigned char *uBuffer;
@property (assign, nonatomic) unsigned char *vBuffer;
@property (assign, nonatomic) int yStride;
@property (assign, nonatomic) int uStride;
@property (assign, nonatomic) int vStride;
@property (assign, nonatomic) int width;
@property (assign, nonatomic) int height;
@property (assign, nonatomic) int rotation;
@property (assign, nonatomic) unsigned int uid;

- (instancetype)initWithUId:(unsigned int)uid
                    yBuffer:(void *)yBuffer
                    uBuffer:(void *)uBuffer
                    vBuffer:(void *)vBuffer
                    yStride:(int)yStride
                    uStride:(int)uStride
                    vStride:(int)vStride
                      width:(int)width
                     height:(int)height
                   rotation:(int)rotation;

+ (unsigned char *)copy:(void *)buffer size:(int)size;

- (void)updateWithYBuffer:(void *)yBuffer
                  uBuffer:(void *)uBuffer
                  vBuffer:(void *)vBuffer
                  yStride:(int)yStride
                  uStride:(int)uStride
                  vStride:(int)vStride
                    width:(int)width
                   height:(int)height
                 rotation:(int)rotation;

- (unsigned char *)yuvData;
@end
