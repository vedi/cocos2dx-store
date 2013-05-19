//
// Created by Fedor Shubin on 5/19/13.
//


#include "CCPurchaseWithMarket.h"

namespace soomla {
    CCPurchaseWithMarket *CCPurchaseWithMarket::create(CCMarketItem *marketItem) {
        CCPurchaseWithMarket *ret = new CCPurchaseWithMarket();
        ret->autorelease();
        ret->init(marketItem);
        return ret;
    }

    bool CCPurchaseWithMarket::init(CCMarketItem *marketItem) {
        bool res = CCPurchaseType::init();
        if (res) {
            setMarketItem(marketItem);
            return true;
        } else {
            return false;
        }
    }
}
