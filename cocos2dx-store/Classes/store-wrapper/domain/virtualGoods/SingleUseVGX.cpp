//
// Created by Fedor Shubin on 5/19/13.
//


#include "SingleUseVGX.h"

namespace soomla {
    USING_NS_CC;
    SingleUseVG *SingleUseVG::create(CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        SingleUseVG *ret = new SingleUseVG();
        ret->autorelease();
        ret->init(name, description, itemId, purchaseType);
        return ret;
    }

    SingleUseVG *SingleUseVG::createWithDictionary(CCDictionary *dict) {
        SingleUseVG *ret = new SingleUseVG();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }
}
