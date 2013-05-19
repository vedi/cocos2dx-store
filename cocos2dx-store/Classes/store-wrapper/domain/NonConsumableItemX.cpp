//
// Created by Fedor Shubin on 5/19/13.
//


#include "NonConsumableItemX.h"

USING_NS_CC;

namespace soomla {
    NonConsumableItem *NonConsumableItem::create(CCString *name, CCString *description, CCString *itemId, PurchaseType *purchaseType) {
        NonConsumableItem *ret = new NonConsumableItem();
        ret->autorelease();
        ret->init(name, description, itemId, purchaseType);
        return ret;
    }

    NonConsumableItem *NonConsumableItem::createWithDictionary(CCDictionary *dict) {
        NonConsumableItem *ret = new NonConsumableItem();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }
};
