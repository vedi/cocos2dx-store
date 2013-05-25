//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __VirtualCurrencyPackX_H_
#define __VirtualCurrencyPackX_H_

#include "../../SoomlaMacros.h"
#include "../CCPurchasableVirtualItem.h"

namespace soomla {
    class CCVirtualCurrencyPack : public CCPurchasableVirtualItem {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mCurrencyAmount, CurrencyAmount, JSON_CURRENCYPACK_CURRENCYAMOUNT);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mCurrencyItemId, CurrencyItemId, JSON_CURRENCYPACK_CURRENCYITEMID);
    public:
        CCVirtualCurrencyPack(): CCPurchasableVirtualItem(), mCurrencyAmount(NULL), mCurrencyItemId(NULL) {};
        static CCVirtualCurrencyPack *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, cocos2d::CCInteger* currencyAmount, cocos2d::CCString* currencyItemId,
                CCPurchaseType * purchaseType);
        static CCVirtualCurrencyPack *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, cocos2d::CCInteger* currencyAmount, cocos2d::CCString* currencyItemId,
                CCPurchaseType * purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~CCVirtualCurrencyPack();
    };
};


#endif //__VirtualCurrencyPackX_H_
