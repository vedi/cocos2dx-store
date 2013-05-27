//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __UpgradeVGX_H_
#define __UpgradeVGX_H_

#include "CCVirtualGood.h"
#include "../../SoomlaMacros.h"

namespace soomla {
    class CCUpgradeVG : public CCVirtualGood {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mGoodItemId, GoodItemId, JSON_VGU_GOOD_ITEMID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mPrevItemId, PrevItemId, JSON_VGU_PREV_ITEMID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mNextItemId, NextItemId, JSON_VGU_NEXT_ITEMID);
    public:
        CCUpgradeVG(): CCVirtualGood(), mGoodItemId(NULL), mPrevItemId(NULL), mNextItemId(NULL) {};
        static CCUpgradeVG *create(cocos2d::CCString* goodItemId, cocos2d::CCString* prevItemId, cocos2d::CCString* nextItemId,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        static CCUpgradeVG *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCString* goodItemId, cocos2d::CCString* prevItemId, cocos2d::CCString* nextItemId,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~CCUpgradeVG();
    };
};

#endif //__UpgradeVGX_H_
