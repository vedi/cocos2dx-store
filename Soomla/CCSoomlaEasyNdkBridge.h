//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCSoomlaEasyNdkBridge_H_
#define __CCSoomlaEasyNdkBridge_H_

#include "cocos2d.h"
#include "CCSoomlaError.h"

namespace soomla {
    class CCSoomlaEasyNdkBridge {
    public:
        static cocos2d::CCObject *callNative(cocos2d::CCDictionary *params, CCSoomlaError **pError);
    };
};


#endif //__CCSoomlaEasyNdkBridge_H_
