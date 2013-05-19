//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCEquippableVG.h"

USING_NS_CC;

namespace soomla {
    CCEquippableVG *CCEquippableVG::create(CCInteger *equippingModel, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        CCEquippableVG *ret = new CCEquippableVG();
        ret->autorelease();
        ret->init(equippingModel, name, description, itemId, purchaseType);
        return ret;
    }

    CCEquippableVG *CCEquippableVG::createWithDictionary(CCDictionary *dict) {
        CCEquippableVG *ret = new CCEquippableVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool CCEquippableVG::init(CCInteger *equippingModel, CCString *name, CCString *description, CCString *itemId, CCPurchaseType *purchaseType) {
        bool res = CCPurchasableVirtualItem::init(name, description, itemId, purchaseType);
        if (res) {
            setEquippingModel(equippingModel);
            return true;
        } else {
            return false;
        }
    }

    bool CCEquippableVG::initWithDictionary(CCDictionary *dict) {
        bool res = CCPurchasableVirtualItem::initWithDictionary(dict);
        if (res) {
            fillEquippingModelFromDict(dict);

            return true;
        } else {
            return false;
        }
    }

    CCDictionary *CCEquippableVG::toDictionary() {
        CCDictionary *dict = CCPurchasableVirtualItem::toDictionary();

        putEquippingModelToDict(dict);

        return dict;
    }

    CCEquippableVG::~CCEquippableVG() {
        CC_SAFE_RELEASE(mEquippingModel);
    }
}

