//
// Created by Fedor Shubin on 5/19/13.
//


#include "PurchaseWithMarketX.h"

namespace soomla {
    PurchaseWithMarket *PurchaseWithMarket::create(MarketItem *marketItem) {
        PurchaseWithMarket *ret = new PurchaseWithMarket();
        ret->autorelease();
        ret->init(marketItem);
        return ret;
    }

    bool PurchaseWithMarket::init(MarketItem *marketItem) {
        bool res = PurchaseType::init();
        if (res) {
            setMarketItem(marketItem);
            return true;
        } else {
            return false;
        }
    }
}
