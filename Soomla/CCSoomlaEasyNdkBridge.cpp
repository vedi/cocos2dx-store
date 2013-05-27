//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCSoomlaEasyNdkBridge.h"
#include "EasyNDK/NDKHelper.h"
#include "CCSoomlaError.h"

namespace soomla {

    #define SOOMLA_EASY_NDK_METHOD_NAME "soomla_easyNDK"

    cocos2d::CCObject *CCSoomlaEasyNdkBridge::callNative(cocos2d::CCDictionary *params, CCSoomlaError **pError) {
        CCObject *retParams = sendMessageWithParams(SOOMLA_EASY_NDK_METHOD_NAME, params, false);

        CCSoomlaError *error = CCSoomlaError::createWithObject(retParams);
        if (error != NULL) {
            *pError = error;
        }

        return retParams;
    }
}
