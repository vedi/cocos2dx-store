//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCStoreController.h"
#include "CCSoomla.h"
#include "CCStoreUtils.h"
#include "CCSoomlaNdkBridge.h"
#include "data/CCStoreInfo.h"
#include "CCSoomlaError.h"

namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCStoreController *s_SharedStoreController = NULL;

    CCStoreController *CCStoreController::sharedStoreController() {
        return s_SharedStoreController;
    }

    void CCStoreController::createShared(CCIStoreAssets *storeAssets) {
        CCStoreController *ret = new CCStoreController();
        if (ret->init(storeAssets)) {
            s_SharedStoreController = ret;
        } else {
            delete ret;
        }
    }

    CCStoreController::CCStoreController() {

    }

    CCStoreController::~CCStoreController() {

    }

    bool CCStoreController::init(CCIStoreAssets *storeAssets) {
        CCSoomla *soomla = CCSoomla::sharedSoomla();
        if (soomla->getCustomSecret().empty() || soomla->getSoomSec().empty()) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX MISSING customSecret or soomSec !!! Stopping here !!");
            return false;
        }

        if (soomla->getCustomSecret().compare(SOOMLA_ONLY_ONCE_DEFAULT) == 0||
                soomla->getSoomSec().compare(SOOMLA_ONLY_ONCE_DEFAULT) == 0) {

            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX You have to change customSecret and soomSec !!! Stopping here !!");
            return false;
        }

        //init SOOM_SEC

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (soomla->getAndroidPublicKey().empty()) {
            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX MISSING publickKey !!! Stopping here !!");
            return false;
        }

        if (soomla->getAndroidPublicKey().compare(SOOMLA_AND_PUB_KEY_DEFAULT)) {

            CCStoreUtils::logError(TAG, "SOOMLA/COCOS2DX You have to change android publicKey !!! Stopping here !!");
            return false;
        }
#endif

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setSoomSec"), "method");
            params->setObject(CCString::create(soomla->getSoomSec()), "soomSec");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }

        CCStoreInfo::createShared(storeAssets);

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::init"), "method");
            params->setObject(CCString::create(CCSoomla::sharedSoomla()->getCustomSecret()), "customSecret");
            params->setObject(CCString::create(CCSoomla::sharedSoomla()->getAndroidPublicKey()), "androidPublicKey");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setAndroidTestMode"), "method");
            params->setObject(CCBool::create(CCSoomla::sharedSoomla()->getAndroidTestMode()), "testMode");
            CCSoomlaNdkBridge::callNative(params, NULL);
        }

        return true;
    }

    void CCStoreController::buyMarketItem(const char *productId, CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::buyMarketItem"), "method");
        params->setObject(CCString::create(productId), "productId");
        CCSoomlaNdkBridge::callNative(params, soomlaError);
    }

    void CCStoreController::storeOpening() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::storeOpening"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    void CCStoreController::storeClosing() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::storeClosing"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    void CCStoreController::restoreTransactions() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::restoreTransactions"), "method");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }

    bool CCStoreController::transactionsAlreadyRestored() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::transactionsAlreadyRestored"), "method");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaNdkBridge::callNative(params, NULL);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    void setAndroidTestMode(bool testMode) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::setAndroidTestMode"), "method");
        params->setObject(CCBool::create(testMode), "testMode");
        CCSoomlaNdkBridge::callNative(params, NULL);
    }
}