//
// Created by Fedor Shubin on 5/19/13.
//


#include "PurchaseWithVirtualItemX.h"

namespace soomla {
    PurchaseWithVirtualItem *PurchaseWithVirtualItem::create(cocos2d::CCString *itemId, cocos2d::CCInteger *amount) {
        PurchaseWithVirtualItem *ret = new PurchaseWithVirtualItem();
        ret->autorelease();
        ret->init(itemId, amount);
        return ret;
    }

    bool PurchaseWithVirtualItem::init(cocos2d::CCString *itemId, cocos2d::CCInteger *amount) {
        setItemId(itemId);
        setAmount(amount);

        return true;
    }

    PurchaseWithVirtualItem::~PurchaseWithVirtualItem() {
        CC_SAFE_RELEASE(mItemId);
        CC_SAFE_RELEASE(mAmount);
    }
}
