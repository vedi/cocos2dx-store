//
// Created by Fedor Shubin on 5/19/13.
//

#ifndef __NonConsumableItemX_H_
#define __NonConsumableItemX_H_

#include "PurchasableVirtualItemX.h"

namespace soomla {
    class NonConsumableItem: public PurchasableVirtualItem {
    public:
        NonConsumableItem(): PurchasableVirtualItem() {}

        static NonConsumableItem* create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId,
            PurchaseType *purchaseType);
        static NonConsumableItem* createWithDictionary(cocos2d::CCDictionary* dict);
    };
};

#endif //__NonConsumableItemX_H_
