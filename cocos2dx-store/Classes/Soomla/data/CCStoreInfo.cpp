//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCStoreInfo.h"
#include "CCSingleUseVG.h"
#include "CCEquippableVG.h"
#include "CCSingleUsePackVG.h"
#include "CCUpgradeVG.h"
#include "CCSoomlaEasyNdkBridge.h"
#include "CCStoreUtils.h"
#include "CCVirtualCurrency.h"
#include "CCVirtualCurrencyPack.h"
#include "CCNonConsumableItem.h"

namespace soomla {

    #define TAG "SOOMLA StoreInfo"

    USING_NS_CC;

    static CCStoreInfo *s_SharedStoreInfo = NULL;

    CCStoreInfo *CCStoreInfo::sharedStoreInfo() {
        return s_SharedStoreInfo;
    }

    void CCStoreInfo::createShared(CCIStoreAssets *storeAssets) {
        CCStoreInfo *ret = new CCStoreInfo();
        if (ret->init(storeAssets)) {
            s_SharedStoreInfo = ret;
        } else {
            delete ret;
        }
    }

    bool CCStoreInfo::init(CCIStoreAssets *storeAssets) {
//			StoreUtils.LogDebug(TAG, "Adding currency");
//			StoreUtils.LogDebug(TAG, "Adding categories");
        CCArray *currenciesJSON = CCArray::create();
        {
            CCArray *currencies = storeAssets->getCurrencies();
            CCObject *obj;
            CCARRAY_FOREACH(currencies, obj) {
                    currenciesJSON->addObject(((CCVirtualCategory *)obj)->toDictionary());
                }
        }

//			StoreUtils.LogDebug(TAG, "Adding packs");
        CCArray *packsJSON = CCArray::create();
        {
            CCArray *packs = storeAssets->getCurrencyPacks();
            CCObject *obj;
            CCARRAY_FOREACH(packs, obj) {
                    packsJSON->addObject(((CCVirtualCategory *)obj)->toDictionary());
                }
        }

//			StoreUtils.LogDebug(TAG, "Adding goods");
        CCArray *suGoods = CCArray::create();
        CCArray *ltGoods = CCArray::create();
        CCArray *eqGoods = CCArray::create();
        CCArray *upGoods = CCArray::create();
        CCArray *paGoods = CCArray::create();

        CCObject *obj;
        CCARRAY_FOREACH(storeAssets->getGoods(), obj) {
                if (dynamic_cast<CCSingleUseVG *>(obj)) {
                    suGoods->addObject(((CCSingleUseVG *)obj)->toDictionary());
                } else if (dynamic_cast<CCEquippableVG *>(obj)) {
                    eqGoods->addObject(((CCEquippableVG *)obj)->toDictionary());
                } else if (dynamic_cast<CCLifetimeVG *>(obj)) {
                    ltGoods->addObject(((CCLifetimeVG *)obj)->toDictionary());
                } else if (dynamic_cast<CCSingleUsePackVG *>(obj)) {
                    paGoods->addObject(((CCSingleUsePackVG *)obj)->toDictionary());
                } else if (dynamic_cast<CCUpgradeVG *>(obj)) {
                    upGoods->addObject(((CCUpgradeVG *)obj)->toDictionary());
                }
            }

        CCDictionary *goodsJSON = CCDictionary::create();
        goodsJSON->setObject(suGoods, JSON_STORE_GOODS_SU);
        goodsJSON->setObject(ltGoods, JSON_STORE_GOODS_LT);
        goodsJSON->setObject(eqGoods, JSON_STORE_GOODS_EQ);
        goodsJSON->setObject(upGoods, JSON_STORE_GOODS_UP);
        goodsJSON->setObject(paGoods, JSON_STORE_GOODS_PA);

//			StoreUtils.LogDebug(TAG, "Adding categories");
        CCArray *categoriesJSON = CCArray::create();
        {
            CCArray *categories = storeAssets->getCategories();
            CCObject *obj;
            CCARRAY_FOREACH(categories, obj) {
                    categoriesJSON->addObject(((CCVirtualCategory *)obj)->toDictionary());
                }
        }


//			StoreUtils.LogDebug(TAG, "Adding nonConsumables");
        CCArray *nonConsumablesJSON = CCArray::create();
        {
            CCArray *nonConsumables = storeAssets->getNonConsumableItems();
            CCObject *obj;
            CCARRAY_FOREACH(nonConsumables, obj) {
                    nonConsumablesJSON->addObject(((CCNonConsumableItem *)obj)->toDictionary());
                }
        }

//			StoreUtils.LogDebug(TAG, "Preparing StoreAssets  JSONObject");
        CCDictionary *storeAssetsObj = CCDictionary::create();
        storeAssetsObj->setObject(categoriesJSON, JSON_STORE_CATEGORIES);
        storeAssetsObj->setObject(currenciesJSON, JSON_STORE_CURRENCIES);
        storeAssetsObj->setObject(packsJSON, JSON_STORE_CURRENCYPACKS);
        storeAssetsObj->setObject(goodsJSON, JSON_STORE_GOODS);
        storeAssetsObj->setObject(nonConsumablesJSON, JSON_STORE_NONCONSUMABLES);

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreAssets::init"), "method");
        params->setObject(CCInteger::create(storeAssets->getVersion()), "version");
        params->setObject(storeAssetsObj, "storeAssets");
        CCSoomlaEasyNdkBridge::callNative(params, NULL);


        return true;
    }

    CCVirtualItem *CCStoreInfo::getItemByItemId(char const *itemId, CCSoomlaError **soomlaError) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("Trying to fetch an item with itemId: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getItemByItemId"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params, soomlaError);
        if (!soomlaError) {
            return CCVirtualItem::createWithDictionary(retParams);
        } else {
            return NULL;
        }
    }

    CCPurchasableVirtualItem *CCStoreInfo::getPurchasableItemWithProductId(char const *productId, CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getPurchasableItemWithProductId"), "method");
        params->setObject(CCString::create(productId), "productId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params, soomlaError);
        if (!soomlaError) {
            return CCPurchasableVirtualItem::createWithDictionary(retParams);
        } else {
            return NULL;
        }
    }

    CCVirtualCategory *CCStoreInfo::getCategoryForVirtualGood(char const *goodItemId, CCSoomlaError **soomlaError) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getCategoryForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params, soomlaError);
        if (!soomlaError) {
            return CCVirtualCategory::createWithDictionary(retParams);
        } else {
            return NULL;
        }
    }

    CCUpgradeVG *CCStoreInfo::getFirstUpgradeForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getFirstUpgradeForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
        return CCUpgradeVG::createWithDictionary(retParams);
    }

    CCUpgradeVG *CCStoreInfo::getLastUpgradeForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getLastUpgradeForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
        return CCUpgradeVG::createWithDictionary(retParams);
    }

    CCArray *CCStoreInfo::getUpgradesForVirtualGood(char const *goodItemId) {
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInfo::getUpgradesForVirtualGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
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
        params->setObject(CCString::create("CCStoreInfo::getVirtualCurrencies"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
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
        params->setObject(CCString::create("CCStoreInfo::getVirtualGoods"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
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
        params->setObject(CCString::create("CCStoreInfo::getVirtualCurrencyPacks"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
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
        params->setObject(CCString::create("CCStoreInfo::getNonConsumableItems"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
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
        params->setObject(CCString::create("CCStoreInfo::getVirtualCategories"), "method");
        CCArray *retParams = (CCArray *) CCSoomlaEasyNdkBridge::callNative(params, NULL);
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

