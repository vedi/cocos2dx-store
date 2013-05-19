//
// Created by Fedor Shubin on 5/19/13.
//



#include "cocos2d.h"
#include "SoomlaMacros.h"
#include "JSONConstsX.h"

#ifndef __VirtualCategoryX_H_
#define __VirtualCategoryX_H_

namespace soomla {
    class CCVirtualCategory : public cocos2d::CCObject {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString*, mName, Name, JSON_CATEGORY_NAME);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCArray*, mGoodItemIds, GoodItemIds, JSON_CATEGORY_GOODSITEMIDS);
    public:
        CCVirtualCategory(): mName(NULL), mGoodItemIds(NULL) {};
        static CCVirtualCategory *create(cocos2d::CCString *name, cocos2d::CCArray *goodItemIds);
        static CCVirtualCategory *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCString *name, cocos2d::CCArray *goodItemIds);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~CCVirtualCategory();
    };
};


#endif //__VirtualCategoryX_H_
