//
// Created by Fedor Shubin on 5/19/13.
//


#include "EquippableVGX.h"

USING_NS_CC;

namespace soomla {
    EquippableVG *EquippableVG::create(CCInteger *equippingModel, CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        EquippableVG *ret = new EquippableVG();
        ret->autorelease();
        ret->init(equippingModel, name, description, itemId, purchaseType);
        return ret;
    }

    EquippableVG *EquippableVG::createWithDictionary(CCDictionary *dict) {
        EquippableVG *ret = new EquippableVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool EquippableVG::init(CCInteger *equippingModel, CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        bool res = PurchasableVirtualItem::init(name, description, itemId, purchaseType);
        if (res) {
            setEquippingModel(equippingModel);
            return true;
        } else {
            return false;
        }
    }

    bool EquippableVG::initWithDictionary(CCDictionary *dict) {
        bool res = PurchasableVirtualItem::initWithDictionary(dict);
        if (res) {
            fillEquippingModelFromDict(dict);

            return true;
        } else {
            return false;
        }
    }

    CCDictionary *EquippableVG::toDictionary() {
        CCDictionary *dict = PurchasableVirtualItem::toDictionary();

        putEquippingModelToDict(dict);

        return dict;
    }

    EquippableVG::~EquippableVG() {
        CC_SAFE_RELEASE(mEquippingModel);
    }
}

