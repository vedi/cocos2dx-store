//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __VirtualGoodX_H_
#define __VirtualGoodX_H_

#include "CCPurchasableVirtualItem.h"

namespace soomla {
    class CCVirtualGood : public CCPurchasableVirtualItem {
    public:
        static CCVirtualGood *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        static CCVirtualGood *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};


#endif //__VirtualGoodX_H_
