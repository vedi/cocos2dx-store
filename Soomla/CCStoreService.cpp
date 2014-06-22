//
// Created by Fedor Shubin on 6/19/14.
//

#include "CCStoreService.h"
#include "CCDomainFactory.h"
#include "CCStoreConsts.h"
#include "CCVirtualItem.h"
#include "CCMarketItem.h"
#include "CCNonConsumableItem.h"
#include "CCVirtualCategory.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCEquippableVG.h"
#include "CCSingleUsePackVG.h"
#include "CCUpgradeVG.h"
#include "CCSingleUseVG.h"
#include "CCDomainHelper.h"
#include "MuffinRushAssets.h"
#include "CCNdkBridge.h"
#include "CCStoreUtils.h"
#include "CCStoreInfo.h"

USING_NS_CC;


namespace soomla {

#define TAG "SOOMLA CCStoreService"

    static CCStoreService *sInstance = NULL;

    soomla::CCStoreService *soomla::CCStoreService::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCStoreService();
            sInstance->retain();
        }
        return sInstance;
    }

    void soomla::CCStoreService::initShared(MuffinRushAssets *gameAssets, cocos2d::__Dictionary *storeParams) {
        CCStoreService *profileService = CCStoreService::getInstance();
        if (!profileService->init(gameAssets, storeParams)) {
            exit(1);
        }
    }

    soomla::CCStoreService::CCStoreService() {

    }

    bool soomla::CCStoreService::init(MuffinRushAssets *gameAssets, cocos2d::__Dictionary *storeParams) {

        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_ITEM, CCVirtualItem::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_MARKET_ITEM, CCMarketItem::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_NON_CONSUMABLE_ITEM, CCNonConsumableItem::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_PURCHASABLE_VIRTUAL_ITEM, CCPurchasableVirtualItem::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CATEGORY, CCVirtualCategory::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY, CCVirtualCurrency::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY_PACK, CCVirtualCurrencyPack::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_EQUIPPABLE_VG, CCEquippableVG::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_LIFETIME_VG, CCLifetimeVG::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_PACK_VG, CCSingleUsePackVG::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_VG, CCSingleUseVG::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_UPGRADE_VG, CCUpgradeVG::createWithDictionary);
        CCDomainFactory::getInstance()->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_GOOD, CCVirtualGood::createWithDictionary);

        __String *customSecret = dynamic_cast<__String *>(storeParams->objectForKey("customSecret"));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        __String *androidPublicKey = dynamic_cast<__String *>(storeParams->objectForKey("androidPublicKey"));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        __Bool *SSV = dynamic_cast<__Bool *>(storeParams->objectForKey("SSV"));
#endif

        if (customSecret == NULL) {
            customSecret = __String::create("");
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (androidPublicKey == NULL) {
            androidPublicKey = __String::create("");
        }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (SSV == NULL) {
            SSV = __Bool::create(false);
        }
#endif
        checkParams(storeParams);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        {
            __Dictionary *params = __Dictionary::create();
            params->setObject(__String::create("CCStoreController::setAndroidPublicKey"), "method");
            params->setObject(androidPublicKey, "androidPublicKey");
            CCNdkBridge::callNative (params, NULL);
        }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        {
            __Dictionary *params = __Dictionary::create();
            params->setObject(__String::create("CCStoreController::setSSV"), "method");
            params->setObject(SSV, "ssv");
            CCNdkBridge::callNative (params, NULL);
        }
#endif

        CCStoreInfo::createShared(gameAssets);

        {
            __Dictionary *params = __Dictionary::create();
            params->setObject(__String::create("CCStoreService::init"), "method");
            params->setObject(customSecret, "customSecret");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            params->setObject(androidPublicKey, "androidPublicKey");
#endif
            CCError *error = NULL;
            CCNdkBridge::callNative (params, &error);

            if (error) {
                CCStoreUtils::logError(TAG, error->getInfo());
                return false;
            }
        }

        return true;
    }

    void soomla::CCStoreService::setSoomSec(const char *soomSec) {
        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCStoreController::setSoomSec"), "method");
        params->setObject(__String::create(soomSec), "soomSec");
        CCNdkBridge::callNative(params, NULL);
    }

    void soomla::CCStoreService::checkParams(cocos2d::__Dictionary *storeParams) {
        DictElement* el = NULL;
        CCDICT_FOREACH(storeParams, el) {
                std::string key = el->getStrKey();
                if (!(key.compare("androidPublicKey") == 0 ||
                        key.compare("SSV") == 0 ||
                        key.compare("customSecret") == 0)) {

                    __String *message = __String::createWithFormat("WARNING!! Possible typo in member of storeParams: %s", key.c_str());
                    CCStoreUtils::logError(TAG, message->getCString());
                }
            }
    }

}
