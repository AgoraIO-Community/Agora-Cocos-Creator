//
// Created by 张涛 on 2019-12-23.
//

#ifndef PROJ_ANDROID_STUDIO_CACHEVIDEOFRAME_H
#define PROJ_ANDROID_STUDIO_CACHEVIDEOFRAME_H
namespace agora
{
    namespace cocos
    {
        class CacheVideoFrame
        {
        public:
            CacheVideoFrame(int width, int height);
            ~CacheVideoFrame();

            int _width;
            int _height;
            void* _data;
        };
    }
}

#endif //PROJ_ANDROID_STUDIO_CACHEVIDEOFRAME_H
