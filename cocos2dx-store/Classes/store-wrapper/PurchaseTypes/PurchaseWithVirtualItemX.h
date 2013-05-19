//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __PurchaseWithVirtualItemX_H_
#define __PurchaseWithVirtualItemX_H_

#include "PurchaseTypeX.h"

namespace soomla {

    class PurchasableVirtualItem;

    class PurchaseWithVirtualItem : public PurchaseType {
        CC_SYNTHESIZE_RETAIN(cocos2d::CCString *, mItemId, ItemId);
        CC_SYNTHESIZE_RETAIN(cocos2d::CCInteger *, mAmount, Amount);
    public:
        PurchaseWithVirtualItem(): mItemId(NULL), mAmount(NULL) {}

        static PurchaseWithVirtualItem* create(cocos2d::CCString *itemId, cocos2d::CCInteger *amount);

        virtual bool init(cocos2d::CCString *itemId, cocos2d::CCInteger *amount);

        virtual ~PurchaseWithVirtualItem();
    };

};

#endif //__PurchaseWithVirtualItemX_H_
