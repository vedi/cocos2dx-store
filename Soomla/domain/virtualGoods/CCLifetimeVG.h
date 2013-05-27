//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __LifetimeVGX_H_
#define __LifetimeVGX_H_

#include "CCVirtualGood.h"

namespace soomla {
    class CCLifetimeVG : public CCVirtualGood {
    public:
        static CCLifetimeVG *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        static CCLifetimeVG *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};

#endif //__LifetimeVGX_H_
