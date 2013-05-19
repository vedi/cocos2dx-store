//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __SingleUseVGX_H_
#define __SingleUseVGX_H_

#include <iostream>


#include "CCVirtualGood.h"

namespace soomla {
    class CCSingleUseVG : public CCVirtualGood {
    public:
        static CCSingleUseVG *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        static CCSingleUseVG *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};

#endif //__SingleUseVGX_H_
