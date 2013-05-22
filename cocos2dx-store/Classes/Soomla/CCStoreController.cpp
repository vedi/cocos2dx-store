//
// Created by Fedor Shubin on 5/20/13.
//

#include "CCStoreController.h"
#include "CCSoomla.h"
#include "CCStoreUtils.h"
#include "CCSoomlaEasyNdkBridge.h"
#include "data/CCStoreInfo.h"


namespace soomla {
    #define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCStoreController *s_SharedStoreController = NULL;

    CCStoreController *CCStoreController::sharedStoreController() {
        return s_SharedStoreController;
    }

    CCStoreController::CCStoreController() {

    }

    CCStoreController::~CCStoreController() {

    }

    bool CCStoreController::init(CCIStoreAssets *storeAssets) {
        CCSoomla *soomla = CCSoomla::sharedSoomla();
        if (soomla->getCustomSecret().empty() || soomla->getSoomSec().empty()) {
            CCStoreUtils::logError(TAG, "SOOMLA/UNITY MISSING customSecret or soomSec !!! Stopping here !!");
            return false;
        }

        if (soomla->getCustomSecret().compare(SOOMLA_ONLY_ONCE_DEFAULT) ||
                soomla->getSoomSec().compare(SOOMLA_ONLY_ONCE_DEFAULT)) {

            CCStoreUtils::logError(TAG, "SOOMLA/UNITY You have to change customSecret and soomSec !!! Stopping here !!");
            return false;
        }

        //init SOOM_SEC

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (soomla->getAndroidPublicKey().empty()) {
            CCStoreUtils::logError(TAG, "SOOMLA/UNITY MISSING publickKey !!! Stopping here !!");
            return false;
        }

        if (soomla->getAndroidPublicKey().compare(SOOMLA_AND_PUB_KEY_DEFAULT)) {

            CCStoreUtils::logError(TAG, "SOOMLA/UNITY You have to change android publicKey !!! Stopping here !!");
            return false;
        }
#endif

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setSoomSec"), "method");
            params->setObject(CCString::create(soomla->getSoomSec()), "soomSec");
            CCSoomlaEasyNdkBridge::callNative(params);
        }

        CCStoreInfo::createShared(storeAssets);

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::init"), "method");
            params->setObject(CCString::create(CCSoomla::sharedSoomla()->getCustomSecret()), "customSecret");
            params->setObject(CCString::create(CCSoomla::sharedSoomla()->getAndroidPublicKey()), "androidPublicKey");
            CCSoomlaEasyNdkBridge::callNative(params);
        }

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreController::setAndroidTestMode"), "method");
            params->setObject(CCBool::create(CCSoomla::sharedSoomla()->getAndroidTestMode()), "testMode");
            CCSoomlaEasyNdkBridge::callNative(params);
        }

        return true;
    }

    void CCStoreController::buyMarketItem(const char *productId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::buyMarketItem"), "method");
        params->setObject(CCString::create(productId), "productId");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    void CCStoreController::storeOpening() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::storeOpening"), "method");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    void CCStoreController::storeClosing() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::storeClosing"), "method");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    void CCStoreController::restoreTransactions() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::restoreTransactions"), "method");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    bool CCStoreController::transactionsAlreadyRestored() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::transactionsAlreadyRestored"), "method");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    void setAndroidTestMode(bool testMode) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreController::setAndroidTestMode"), "method");
        params->setObject(CCBool::create(testMode), "testMode");
        CCSoomlaEasyNdkBridge::callNative(params);
    }
}