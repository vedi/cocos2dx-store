//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __UpgradeVGX_H_
#define __UpgradeVGX_H_

#include "VirtualGoodX.h"
#include "SoomlaMacros.h"

namespace soomla {
    class UpgradeVG: public VirtualGood {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mGoodItemId, GoodItemId, JSON_VGU_GOOD_ITEMID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mPrevItemId, PrevItemId, JSON_VGU_PREV_ITEMID);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mNextItemId, NextItemId, JSON_VGU_NEXT_ITEMID);
    public:
        UpgradeVG(): VirtualGood(), mGoodItemId(NULL), mPrevItemId(NULL), mNextItemId(NULL) {};
        static UpgradeVG *create(cocos2d::CCString* goodItemId, cocos2d::CCString* prevItemId, cocos2d::CCString* nextItemId,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        static UpgradeVG *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCString* goodItemId, cocos2d::CCString* prevItemId, cocos2d::CCString* nextItemId,
                cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~UpgradeVG();
    };
};

#endif //__UpgradeVGX_H_
