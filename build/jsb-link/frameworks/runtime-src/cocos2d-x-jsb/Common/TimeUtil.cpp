//
//  TimeUtil.cpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 25/12/2017.
//

//start = mach_absolute_time();
//stop =mach_absolute_time();
//current= subtractTimes(stop,start);
//printf("Timefor iteration: %1.12lf",current);

#include "TimeUtil.hpp"

static double subtractTimes(uint64_t endTime, uint64_t startTime);

static TimeUtil *s_SharedTimeUtil = nullptr;

TimeUtil* TimeUtil::getInstance()
{
    if (!s_SharedTimeUtil)
    {
        s_SharedTimeUtil = new (std::nothrow) TimeUtil;
    }
    
    return s_SharedTimeUtil;
}

void TimeUtil::subtractStart()
{
    _times.push(mach_absolute_time());
}

double TimeUtil::subtractEnd()
{
    if (_times.size() == 0) {
        printf("出错啦");
        return 0;
    }
    uint64_t stop = mach_absolute_time();
    uint64_t start = _times.top();
    double res = subtractTimes(stop, start);
    _times.pop();
    return res;
}

static double subtractTimes(uint64_t endTime, uint64_t startTime)
{
    uint64_t difference = endTime - startTime;
    static double conversion = 0.0;
    if (conversion == 0.0)
    {
        mach_timebase_info_data_t info;
        //Convert the timebaseinto seconds
        kern_return_t err = mach_timebase_info(&info);
        if(err == 0)
            conversion = 1e-9 * (double) info.numer / (double) info.denom;
    }
    return conversion * (double)difference;
}
