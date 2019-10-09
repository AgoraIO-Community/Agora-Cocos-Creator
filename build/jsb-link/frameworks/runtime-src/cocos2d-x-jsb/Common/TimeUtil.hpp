//
//  TimeUtil.hpp
//  Agora-iOS-Cocos
//
//  Created by Agora on 25/12/2017.
//

#ifndef TimeUtil_hpp
#define TimeUtil_hpp

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mach/mach_time.h>
#include <stack>

#define TimeUtil_Start TimeUtil::getInstance()->subtractStart()
#define TimeUtil_End TimeUtil::getInstance()->subtractEnd()

using namespace std;
class TimeUtil
{
public:
    static TimeUtil* getInstance();
    void subtractStart();
    double subtractEnd();
    
private:
    stack<uint64_t> _times;
    
};

#endif /* TimeUtil_hpp */
