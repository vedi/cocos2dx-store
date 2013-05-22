//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCSoomlaEasyNdkBridge_H_
#define __CCSoomlaEasyNdkBridge_H_

#include "cocos2d.h"

namespace soomla {
    class CCSoomlaEasyNdkBridge {
    public:
        static cocos2d::CCObject *callNative(cocos2d::CCDictionary *params);
    };
};


#endif //__CCSoomlaEasyNdkBridge_H_
