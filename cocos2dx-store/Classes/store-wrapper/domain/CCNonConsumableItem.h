//
// Created by Fedor Shubin on 5/19/13.
//

#ifndef __NonConsumableItemX_H_
#define __NonConsumableItemX_H_

#include "CCPurchasableVirtualItem.h"

namespace soomla {
    class CCNonConsumableItem : public CCPurchasableVirtualItem {
    public:
        CCNonConsumableItem(): CCPurchasableVirtualItem() {}

        static CCNonConsumableItem * create(cocos2d::CCString* name, cocos2d::CCString* description, cocos2d::CCString* itemId,
            CCPurchaseType *purchaseType);
        static CCNonConsumableItem * createWithDictionary(cocos2d::CCDictionary* dict);
    };
};

#endif //__NonConsumableItemX_H_
