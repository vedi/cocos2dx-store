//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __PurchaseWithMarketX_H_
#define __PurchaseWithMarketX_H_

#include "PurchaseTypeX.h"
#include "MarketItemX.h"

namespace soomla {
    class PurchaseWithMarket: public PurchaseType {
        CC_SYNTHESIZE_RETAIN(MarketItem *, mMarketItem, MarketItem);
    public:
        PurchaseWithMarket(): mMarketItem(NULL) {};
        static PurchaseWithMarket *create(MarketItem *marketItem);
        bool init(MarketItem *marketItem);
    };
};


#endif //__PurchaseWithMarketX_H_
