//
// Created by Fedor Shubin on 1/22/14.
//


#ifndef __JSBinding_H_
#define __JSBinding_H_

#include "cocos2d.h"
#include "ScriptingCore.h"

// Define a namespace to manage your code and make your code clearly
namespace Soomla {
    class JSBinding: public cocos2d::CCObject
    {
    public:
        static void callNative(const char *params, std::string &result);
        static void callCallback(CCDictionary *params);
    };
}

#endif //__JSBinding_H_
