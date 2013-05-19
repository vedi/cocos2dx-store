//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __PurchaseWithVirtualItemX_H_
#define __PurchaseWithVirtualItemX_H_

#include "CCPurchaseType.h"

namespace soomla {

    class CCPurchaseWithVirtualItem : public CCPurchaseType {
        CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, mItemId, ItemId);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCInteger *, mAmount, Amount);
    public:
        CCPurchaseWithVirtualItem(): mItemId(NULL), mAmount(NULL) {}

        static CCPurchaseWithVirtualItem * create(cocos2d::CCString *itemId, cocos2d::CCInteger *amount);

        virtual bool init(cocos2d::CCString *itemId, cocos2d::CCInteger *amount);

        virtual ~CCPurchaseWithVirtualItem();
    };

};

#endif //__PurchaseWithVirtualItemX_H_
