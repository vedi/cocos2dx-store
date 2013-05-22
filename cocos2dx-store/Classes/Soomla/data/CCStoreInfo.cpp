//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCStoreInfo.h"
#include "CCSingleUseVG.h"
#include "CCEquippableVG.h"
#include "CCSingleUsePackVG.h"
#include "CCUpgradeVGX.h"
#include "CCSoomlaEasyNdkBridge.h"
#include "CCStoreUtils.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCNonConsumableItem.h"

namespace soomla {

    #define TAG "SOOMLA StoreInfo"

    USING_NS_CC;

    static CCStoreInfo *s_SharedCCStoreInfo = NULL;

    CCStoreInfo *CCStoreInfo::sharedStoreController() {
        return s_SharedCCStoreInfo;
    }

    void CCStoreInfo::createShared(CCIStoreAssets *storeAssets) {
        CCStoreInfo *ret = new CCStoreInfo();
        if (ret->init(storeAssets)) {
            s_SharedCCStoreInfo = ret;
        } else {
            delete ret;
        }
    }

    bool CCStoreInfo::init(CCIStoreAssets *storeAssets) {
//			StoreUtils.LogDebug(TAG, "Adding currency");
        CCArray *currencies = storeAssets->getCurrencies();

//			StoreUtils.LogDebug(TAG, "Adding packs");
        CCArray *packs = storeAssets->getCurrencyPacks();

//			StoreUtils.LogDebug(TAG, "Adding goods");
        CCArray *suGoods = CCArray::create();
        CCArray *ltGoods = CCArray::create();
        CCArray *eqGoods = CCArray::create();
        CCArray *upGoods = CCArray::create();
        CCArray *paGoods = CCArray::create();

        CCObject *obj;
        CCARRAY_FOREACH(storeAssets->getGoods(), obj) {
                if (dynamic_cast<CCSingleUseVG *>(obj)) {
                    suGoods->addObject(obj);
                } else if (dynamic_cast<CCEquippableVG *>(obj)) {
                    eqGoods->addObject(obj);
                } else if (dynamic_cast<CCLifetimeVG *>(obj)) {
                    ltGoods->addObject(obj);
                } else if (dynamic_cast<CCSingleUsePackVG *>(obj)) {
                    paGoods->addObject(obj);
                } else if (dynamic_cast<CCUpgradeVG *>(obj)) {
                    upGoods->addObject(obj);
                }
            }

        CCDictionary *goods = CCDictionary::create();
        goods->setObject(suGoods, JSON_STORE_GOODS_SU);
        goods->setObject(ltGoods, JSON_STORE_GOODS_LT);
        goods->setObject(eqGoods, JSON_STORE_GOODS_EQ);
        goods->setObject(upGoods, JSON_STORE_GOODS_UP);
        goods->setObject(paGoods, JSON_STORE_GOODS_PA);

//			StoreUtils.LogDebug(TAG, "Adding categories");
        CCArray *categories = storeAssets->getCategories();

//			StoreUtils.LogDebug(TAG, "Adding nonConsumables");
        CCArray *nonConsumables = storeAssets->getNonConsumableItems();

//			StoreUtils.LogDebug(TAG, "Preparing StoreAssets  JSONObject");
        CCDictionary *storeAssetsObj = CCDictionary::create();
        storeAssetsObj->setObject(categories, JSON_STORE_CATEGORIES);
        storeAssetsObj->setObject(currencies, JSON_STORE_CURRENCIES);
        storeAssetsObj->setObject(packs, JSON_STORE_CURRENCYPACKS);
        storeAssetsObj->setObject(goods, JSON_STORE_GOODS);
        storeAssetsObj->setObject(nonConsumables, JSON_STORE_NONCONSUMABLES);

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreAssets::init"), "method");
        params->setObject(CCInteger::create(storeAssets->getVersion()), "version");
        params->setObject(storeAssetsObj, "storeAssets");
        CCSoomlaEasyNdkBridge::callNative(params);


        return true;
    }

    CCVirtualItem *CCStoreInfo::getItemByItemId(char const *itemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("Trying to fetch an item with itemId: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getItemByItemId"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        return CCVirtualItem::createWithDictionary(retParams);
    }

    CCPurchasableVirtualItem *CCStoreInfo::getPurchasableItemWithProductId(char const *productId) {

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getPurchasableItemWithProductId"), "method");
        params->setObject(CCString::create(productId), "productId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        return CCPurchasableVirtualItem::createWithDictionary(retParams);
    }

    CCVirtualCategory *CCStoreInfo::getCategoryForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getCategoryForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        return CCVirtualCategory::createWithDictionary(retParams);
    }

    CCUpgradeVG *CCStoreInfo::getFirstUpgradeForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getFirstUpgradeForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        return CCUpgradeVG::createWithDictionary(retParams);
    }

    CCUpgradeVG *CCStoreInfo::getLastUpgradeForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getLastUpgradeForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        return CCUpgradeVG::createWithDictionary(retParams);
    }

    CCArray *CCStoreInfo::getUpgradesForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getUpgradesForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params);
        CCArray *retModels = CCArray::create();

        CCObject *obj;
        CCDictionary *dict;
        CCARRAY_FOREACH(retParams, obj) {
                dict = dynamic_cast<CCDictionary *>(obj);
                CC_ASSERT(dict);
                retModels->addObject(CCUpgradeVG::createWithDictionary(dict));
            }
        return retModels;
    }

    CCArray *CCStoreInfo::getVirtualCurrencies() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getVirtualCurrencies"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params);
        CCArray *retModels = CCArray::create();

        CCObject *obj;
        CCDictionary *dict;
        CCARRAY_FOREACH(retParams, obj) {
                dict = dynamic_cast<CCDictionary *>(obj);
                CC_ASSERT(dict);
                retModels->addObject(CCVirtualCurrency::createWithDictionary(dict));
            }
        return retModels;
    }

    CCArray *CCStoreInfo::getVirtualGoods() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getVirtualGoods"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params);
        CCArray *retModels = CCArray::create();

        CCObject *obj;
        CCDictionary *dict;
        CCARRAY_FOREACH(retParams, obj) {
                dict = dynamic_cast<CCDictionary *>(obj);
                CC_ASSERT(dict);
                retModels->addObject(CCVirtualGood::createWithDictionary(dict));
            }
        return retModels;
    }

    CCArray *CCStoreInfo::getVirtualCurrencyPacks() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getVirtualCurrencyPacks"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params);
        CCArray *retModels = CCArray::create();

        CCObject *obj;
        CCDictionary *dict;
        CCARRAY_FOREACH(retParams, obj) {
                dict = dynamic_cast<CCDictionary *>(obj);
                CC_ASSERT(dict);
                retModels->addObject(CCVirtualCurrencyPack::createWithDictionary(dict));
            }
        return retModels;
    }

    CCArray *CCStoreInfo::getNonConsumableItems() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getNonConsumableItems"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params);
        CCArray *retModels = CCArray::create();

        CCObject *obj;
        CCDictionary *dict;
        CCARRAY_FOREACH(retParams, obj) {
                dict = dynamic_cast<CCDictionary *>(obj);
                CC_ASSERT(dict);
                retModels->addObject(CCNonConsumableItem::createWithDictionary(dict));
            }
        return retModels;
    }

    CCArray *CCStoreInfo::getVirtualCategories() {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("StoreInfo::getVirtualCategories"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params);
        CCArray *retModels = CCArray::create();

        CCObject *obj;
        CCDictionary *dict;
        CCARRAY_FOREACH(retParams, obj) {
                dict = dynamic_cast<CCDictionary *>(obj);
                CC_ASSERT(dict);
                retModels->addObject(CCVirtualCategory::createWithDictionary(dict));
            }
        return retModels;
    }

}

