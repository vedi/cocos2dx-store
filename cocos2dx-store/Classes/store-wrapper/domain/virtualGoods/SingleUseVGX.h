//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __SingleUseVGX_H_
#define __SingleUseVGX_H_

#include <iostream>


#include "VirtualGoodX.h"

namespace soomla {
    class SingleUseVG: public VirtualGood {
    public:
        static SingleUseVG *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        static SingleUseVG *createWithDictionary(cocos2d::CCDictionary *dict);
    };
};

#endif //__SingleUseVGX_H_
