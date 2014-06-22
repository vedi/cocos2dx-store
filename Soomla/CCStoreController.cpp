/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

// Created by Fedor Shubin on 5/20/13.

#include "CCStoreController.h"
#include "CCNdkBridge.h"

using namespace cocos2d;

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCStoreController *s_SharedStoreController = NULL;

    CCStoreController *CCStoreController::sharedStoreController() {
        if (!s_SharedStoreController)
        {
            s_SharedStoreController = new CCStoreController();
            s_SharedStoreController->retain();
        }
        return s_SharedStoreController;
    }

    CCStoreController::CCStoreController() {
    }

    CCStoreController::~CCStoreController() {

    }

    void CCStoreController::buyMarketItem(const char *productId, const char *payload, CCError **error) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::buyMarketItem"), "method");
        params->setObject(__String::create(productId), "productId");
        // NOTE: payload is not supported on iOS !
        params->setObject(__String::create(payload), "payload");
        CCNdkBridge::callNative (params, error);
    }

    void CCStoreController::restoreTransactions() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::restoreTransactions"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

    void CCStoreController::refreshInventory() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::refreshInventory"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    bool CCStoreController::transactionsAlreadyRestored() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::transactionsAlreadyRestored"), "method");
        __Dictionary *retParams = (__Dictionary *) CCNdkBridge::callNative (params, NULL);
        __Bool *retValue = (__Bool *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    void CCStoreController::refreshMarketItemsDetails(CCError **error) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::refreshMarketItemsDetails"), "method");
        CCNdkBridge::callNative (params, error);
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void CCStoreController::startIabServiceInBg() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::startIabServiceInBg"), "method");
        CCNdkBridge::callNative (params, NULL);
    }

    void CCStoreController::stopIabServiceInBg() {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::stopIabServiceInBg"), "method");
        CCNdkBridge::callNative (params, NULL);
    }
#endif
}
