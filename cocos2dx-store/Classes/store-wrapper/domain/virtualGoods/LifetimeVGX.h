//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __LifetimeVGX_H_
#define __LifetimeVGX_H_

#include "VirtualGoodX.h"

namespace soomla {
    class LifetimeVG: public VirtualGood {
    public:
        static LifetimeVG *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        static LifetimeVG *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};

#endif //__LifetimeVGX_H_
