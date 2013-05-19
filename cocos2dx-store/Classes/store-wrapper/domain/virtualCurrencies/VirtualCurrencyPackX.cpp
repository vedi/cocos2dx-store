//
// Created by Fedor Shubin on 5/19/13.
//


#include "VirtualCurrencyPackX.h"

USING_NS_CC;

namespace soomla {
    VirtualCurrencyPack *VirtualCurrencyPack::create(CCString *name, CCString *description, CCString *itemId, CCInteger *currencyAmount, CCString *currencyItemId, PurchaseType *purchaseType) {
        VirtualCurrencyPack *ret = new VirtualCurrencyPack();
        ret->autorelease();
        ret->init(name, description, itemId, currencyAmount, currencyItemId, purchaseType);
        return ret;
    }

    VirtualCurrencyPack *VirtualCurrencyPack::createWithDictionary(CCDictionary *dict) {
        VirtualCurrencyPack *ret = new VirtualCurrencyPack();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool VirtualCurrencyPack::init(CCString *name, CCString *description, CCString *itemId, CCInteger *currencyAmount, CCString *currencyItemId, PurchaseType *purchaseType) {
        bool res = PurchasableVirtualItem::init(name, description, itemId, purchaseType);
        if (res) {
            setCurrencyAmount(currencyAmount);
            setCurrencyItemId(currencyItemId);
            return true;
        } else {
            return false;
        }
    }

    bool VirtualCurrencyPack::initWithDictionary(CCDictionary *dict) {
        bool res = PurchasableVirtualItem::initWithDictionary(dict);
        if (res) {
            fillCurrencyAmountFromDict(dict);
            fillCurrencyItemIdFromDict(dict);

            return true;
        } else {
            return false;
        }
    }

    CCDictionary *VirtualCurrencyPack::toDictionary() {
        CCDictionary *dict = PurchasableVirtualItem::toDictionary();

        putCurrencyAmountToDict(dict);
        putCurrencyItemIdToDict(dict);

        return dict;
    }

    VirtualCurrencyPack::~VirtualCurrencyPack() {
        CC_SAFE_RELEASE(mCurrencyAmount);
        CC_SAFE_RELEASE(mCurrencyItemId);
    }
}    
