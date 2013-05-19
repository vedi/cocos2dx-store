//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __VirtualGoodX_H_
#define __VirtualGoodX_H_

#include "PurchasableVirtualItemX.h"

namespace soomla {
    class VirtualGood: public PurchasableVirtualItem {
    public:
        static VirtualGood *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        static VirtualGood *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};


#endif //__VirtualGoodX_H_
