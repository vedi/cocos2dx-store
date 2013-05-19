//
// Created by Fedor Shubin on 5/19/13.
//


#include "VirtualGoodX.h"

USING_NS_CC;

namespace soomla {
    VirtualGood *VirtualGood::create(CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        VirtualGood *ret = new VirtualGood();
        ret->autorelease();
        ret->init(name, description, itemId, purchaseType);
        return ret;
    }

    VirtualGood *VirtualGood::createWithDictionary(CCDictionary *dict) {
        VirtualGood *ret = new VirtualGood();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }
}