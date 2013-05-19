//
// Created by Fedor Shubin on 5/19/13.
//

#ifndef __SingleUsePackVGX_H_
#define __SingleUsePackVGX_H_

#include "VirtualGoodX.h"
#include "SoomlaMacros.h"

namespace soomla {
    class SingleUsePackVG: public VirtualGood {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mGoodItemId, GoodItemId, JSON_VGP_GOOD_ITEMID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mGoodAmount, GoodAmount, JSON_VGP_GOOD_AMOUNT);
    public:
        SingleUsePackVG(): VirtualGood(), mGoodItemId(NULL), mGoodAmount(NULL) {};
        static SingleUsePackVG *create(cocos2d::CCString* goodItemId, cocos2d::CCInteger* goodAmount,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        static SingleUsePackVG *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCString* goodItemId, cocos2d::CCInteger* goodAmount,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~SingleUsePackVG();
    };
};

#endif //__SingleUsePackVGX_H_
