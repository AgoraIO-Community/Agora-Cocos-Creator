//
// Created by 张涛 on 2019-12-23.
//
#include "CacheVideoFrame.h"
#include <stdlib.h> // pulls in declaration of malloc, free
#include <string.h>

namespace agora
{
    namespace cocos
    {
        CacheVideoFrame::CacheVideoFrame(int width, int height)
        {
            _width = width;
            _height = height;
            _data = malloc(width * height * 4);
        }

        CacheVideoFrame::~CacheVideoFrame()
        {
            if (_data)
            {
                free(_data);
                _data = NULL;
            }
        }
    }
}
