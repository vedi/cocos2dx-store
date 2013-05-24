//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __PurchaseWithMarketX_H_
#define __PurchaseWithMarketX_H_

#include "CCPurchaseType.h"
#include "CCMarketItem.h"

namespace soomla {
    class CCPurchaseWithMarket : public CCPurchaseType {
        CC_SYNTHESIZE_RETAIN(CCMarketItem *, mMarketItem, MarketItem);
    public:
        CCPurchaseWithMarket(): mMarketItem(NULL) {};
        static CCPurchaseWithMarket *create(cocos2d::CCString *productId, cocos2d::CCDouble *price);
        static CCPurchaseWithMarket *createWithMarketItem(CCMarketItem *marketItem);
        bool initWithMarketItem(CCMarketItem *marketItem);
    };
};


#endif //__PurchaseWithMarketX_H_
