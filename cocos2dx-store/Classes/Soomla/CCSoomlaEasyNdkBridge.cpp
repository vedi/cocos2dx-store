//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCSoomlaEasyNdkBridge.h"
#include "../EasyNDK/NDKHelper.h"
namespace soomla {

    #define SOOMLA_EASY_NDK_METHOD_NAME "soomla_easyNDK"

    CCObject *CCSoomlaEasyNdkBridge::callNative(cocos2d::CCDictionary *params) {
        ret  sendMessageWithParams(SOOMLA_EASY_NDK_METHOD_NAME, params);
    }
}
