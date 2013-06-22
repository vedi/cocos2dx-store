//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCSoomlaNdkBridge.h"
#include "EasyNDK/NDKHelper.h"
#include "CCSoomlaError.h"

namespace soomla {

    #define SOOMLA_EASY_NDK_METHOD_NAME "soomla_easyNDK"

    cocos2d::CCObject *CCSoomlaNdkBridge::callNative(cocos2d::CCDictionary *params, CCSoomlaError **pError) {
        CCObject *retParams = NDKHelper::sendMessageWithParams(SOOMLA_EASY_NDK_METHOD_NAME, params);

        CCSoomlaError *error = CCSoomlaError::createWithObject(retParams);
        if (error != NULL) {
            *pError = error;
        }

        return retParams;
    }
}
