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
#include "CCNdkBridge.h"
#include "CCStoreUtils.h"
#include "CCStoreInfo.h"
#include "CCStoreEventDispatcher.h"
#include "CCVirtualItemReward.h"

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

    void soomla::CCStoreService::initShared(CCStoreAssets *gameAssets, cocos2d::CCDictionary *storeParams) {
        CCStoreService *storeService = CCStoreService::getInstance();
        if (!storeService->init(gameAssets, storeParams)) {
            exit(1);
        }
    }

    soomla::CCStoreService::CCStoreService() {

    }

    bool soomla::CCStoreService::init(CCStoreAssets *gameAssets, cocos2d::CCDictionary *storeParams) {

        CCStoreEventDispatcher::getInstance();    // to get sure it's inited

        CCDomainFactory *domainFactory = CCDomainFactory::getInstance();
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_ITEM, (SEL_DomainCreator) CCVirtualItem::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_MARKET_ITEM, (SEL_DomainCreator) CCMarketItem::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_NON_CONSUMABLE_ITEM, (SEL_DomainCreator) CCNonConsumableItem::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_PURCHASABLE_VIRTUAL_ITEM, (SEL_DomainCreator) CCPurchasableVirtualItem::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CATEGORY, (SEL_DomainCreator) CCVirtualCategory::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY, (SEL_DomainCreator) CCVirtualCurrency::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_CURRENCY_PACK, (SEL_DomainCreator) CCVirtualCurrencyPack::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_EQUIPPABLE_VG, (SEL_DomainCreator) CCEquippableVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_LIFETIME_VG, (SEL_DomainCreator) CCLifetimeVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_PACK_VG, (SEL_DomainCreator) CCSingleUsePackVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_SINGLE_USE_VG, (SEL_DomainCreator) CCSingleUseVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_UPGRADE_VG, (SEL_DomainCreator) CCUpgradeVG::createWithDictionary);
        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_VIRTUAL_GOOD, (SEL_DomainCreator) CCVirtualGood::createWithDictionary);

        domainFactory->registerCreator(CCStoreConsts::JSON_JSON_TYPE_ITEM, (SEL_DomainCreator) CCVirtualItemReward::createWithDictionary);

        CCString *customSecret = dynamic_cast<CCString *>(storeParams->objectForKey("customSecret"));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CCString *androidPublicKey = dynamic_cast<CCString *>(storeParams->objectForKey("androidPublicKey"));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        CCBool *SSV = dynamic_cast<CCBool *>(storeParams->objectForKey("SSV"));
#endif

        if (customSecret == NULL) {
            customSecret = CCString::create("");
        }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        if (androidPublicKey == NULL) {
            androidPublicKey = CCString::create("");
        }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        if (SSV == NULL) {
            SSV = CCBool::create(false);
        }
#endif
        checkParams(storeParams);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCSoomlaStore::setAndroidPublicKey"), "method");
            params->setObject(androidPublicKey, "androidPublicKey");
            CCNdkBridge::callNative (params, NULL);
        }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCSoomlaStore::setSSV"), "method");
            params->setObject(SSV, "ssv");
            CCNdkBridge::callNative (params, NULL);
        }
#endif

        CCStoreInfo::createShared(gameAssets);

        {
            CCDictionary *params = CCDictionary::create();
            params->setObject(CCString::create("CCStoreService::init"), "method");
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

    void soomla::CCStoreService::checkParams(cocos2d::CCDictionary *storeParams) {
        CCDictElement* el = NULL;
        CCDICT_FOREACH(storeParams, el) {
                std::string key = el->getStrKey();
                if (!(key.compare("androidPublicKey") == 0 ||
                        key.compare("SSV") == 0 ||
                        key.compare("customSecret") == 0)) {

                    CCString *message = CCString::createWithFormat("WARNING!! Possible typo in member of storeParams: %s", key.c_str());
                    CCStoreUtils::logError(TAG, message->getCString());
                }
            }
    }

}
