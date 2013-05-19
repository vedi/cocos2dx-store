//
// Created by Fedor Shubin on 5/19/13.
//


#include "SingleUsePackVGX.h"

USING_NS_CC;

namespace soomla {
    SingleUsePackVG *SingleUsePackVG::create(CCString *goodItemId, CCInteger *goodAmount, CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        SingleUsePackVG *ret = new SingleUsePackVG();
        ret->autorelease();
        ret->init(goodItemId, goodAmount, name, description, itemId, purchaseType);
        return ret;
    }

    SingleUsePackVG *SingleUsePackVG::createWithDictionary(CCDictionary *dict) {
        SingleUsePackVG *ret = new SingleUsePackVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool SingleUsePackVG::init(CCString *goodItemId, CCInteger *goodAmount, CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        bool res = VirtualGood::init(name, description, itemId, purchaseType);
        if (res) {
            setGoodItemId(goodItemId);
            setGoodAmount(goodAmount);
            return true;
        } else {
            return false;
        }
    }

    bool SingleUsePackVG::initWithDictionary(CCDictionary *dict) {
        bool res = VirtualGood::initWithDictionary(dict);
        if (res) {
            fillGoodItemIdFromDict(dict);
            fillGoodAmountFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    CCDictionary *SingleUsePackVG::toDictionary() {
        CCDictionary *dict = VirtualGood::toDictionary();

        putGoodItemIdToDict(dict);
        putGoodAmountToDict(dict);

        return dict;
    }

    SingleUsePackVG::~SingleUsePackVG() {
        CC_SAFE_RELEASE(mGoodItemId);
        CC_SAFE_RELEASE(mGoodAmount);
    }
}