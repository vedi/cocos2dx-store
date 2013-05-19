//
// Created by Fedor Shubin on 5/19/13.
//


#include "UpgradeVGX.h"

USING_NS_CC;

namespace soomla {
    UpgradeVG *UpgradeVG::create(CCString *goodItemId, CCString *prevItemId, CCString *nextItemId, CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        UpgradeVG *ret = new UpgradeVG();
        ret->autorelease();
        ret->init(goodItemId, prevItemId, nextItemId, name, description, itemId, purchaseType);
        return ret;
    }

    UpgradeVG *UpgradeVG::createWithDictionary(CCDictionary *dict) {
        UpgradeVG *ret = new UpgradeVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool UpgradeVG::init(CCString *goodItemId, CCString *prevItemId, CCString *nextItemId, CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        bool res = VirtualGood::init(name, description, itemId, purchaseType);
        if (res) {
            setGoodItemId(goodItemId);
            setPrevItemId(prevItemId);
            setNextItemId(nextItemId);
            return true;
        } else {
            return false;
        }
    }

    bool UpgradeVG::initWithDictionary(CCDictionary *dict) {
        bool res = VirtualGood::initWithDictionary(dict);
        if (res) {
            fillGoodItemIdFromDict(dict);
            fillPrevItemIdFromDict(dict);
            fillNextItemIdFromDict(dict);
            return true;
        } else {
            return false;
        }
    }

    CCDictionary *UpgradeVG::toDictionary() {
        CCDictionary *dict = VirtualGood::toDictionary();

        putGoodItemIdToDict(dict);
        if (mPrevItemId != NULL) {
            putPrevItemIdToDict(dict);
        } else {
            dict->setObject(CCString::create(""), JSON_VGU_PREV_ITEMID);
        }
        if (mNextItemId != NULL) {
            putNextItemIdToDict(dict);
        } else {
            dict->setObject(CCString::create(""), JSON_VGU_NEXT_ITEMID);
        }

        return dict;
    }

    UpgradeVG::~UpgradeVG() {
        CC_SAFE_RELEASE(mGoodItemId);
        CC_SAFE_RELEASE(mPrevItemId);
        CC_SAFE_RELEASE(mNextItemId);
    }
}
