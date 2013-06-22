//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCSoomlaNdkBridge_H_
#define __CCSoomlaNdkBridge_H_

#include "cocos2d.h"
#include "CCSoomlaError.h"

namespace soomla {
    class CCSoomlaNdkBridge {
    public:
        static cocos2d::CCObject *callNative(cocos2d::CCDictionary *params, CCSoomlaError **pError);
    };
};


#endif //__CCSoomlaNdkBridge_H_
