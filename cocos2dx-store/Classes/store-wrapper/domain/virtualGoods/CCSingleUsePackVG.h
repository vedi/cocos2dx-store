//
// Created by Fedor Shubin on 5/19/13.
//

#ifndef __SingleUsePackVGX_H_
#define __SingleUsePackVGX_H_

#include "CCVirtualGood.h"
#include "SoomlaMacros.h"

namespace soomla {
    class CCSingleUsePackVG : public CCVirtualGood {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mGoodItemId, GoodItemId, JSON_VGP_GOOD_ITEMID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mGoodAmount, GoodAmount, JSON_VGP_GOOD_AMOUNT);
    public:
        CCSingleUsePackVG(): CCVirtualGood(), mGoodItemId(NULL), mGoodAmount(NULL) {};
        static CCSingleUsePackVG *create(cocos2d::CCString* goodItemId, cocos2d::CCInteger* goodAmount,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        static CCSingleUsePackVG *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCString* goodItemId, cocos2d::CCInteger* goodAmount,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~CCSingleUsePackVG();
    };
};

#endif //__SingleUsePackVGX_H_
