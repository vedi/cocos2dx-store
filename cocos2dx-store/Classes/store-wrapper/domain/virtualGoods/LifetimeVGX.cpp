//
// Created by Fedor Shubin on 5/19/13.
//


#include "LifetimeVGX.h"


namespace soomla {
    USING_NS_CC;
    LifetimeVG *LifetimeVG::create(CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        LifetimeVG *ret = new LifetimeVG();
        ret->autorelease();
        ret->init(name, description, itemId, purchaseType);
        return ret;
    }

    LifetimeVG *LifetimeVG::createWithDictionary(CCDictionary *dict) {
        LifetimeVG *ret = new LifetimeVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }
}
