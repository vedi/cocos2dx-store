//
// Created by Fedor Shubin on 5/19/13.
//



#ifndef __VirtualCurrencyPackX_H_
#define __VirtualCurrencyPackX_H_

#include "SoomlaMacros.h"
#include "PurchasableVirtualItemX.h"

namespace soomla {
    class VirtualCurrencyPack: public PurchasableVirtualItem {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mCurrencyAmount, CurrencyAmount, JSON_CURRENCYPACK_CURRENCYAMOUNT);
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCString *, mCurrencyItemId, CurrencyItemId, JSON_CURRENCYPACK_CURRENCYITEMID);
    public:
        VirtualCurrencyPack(): PurchasableVirtualItem(), mCurrencyAmount(NULL), mCurrencyItemId(NULL) {};
        static VirtualCurrencyPack *create(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, cocos2d::CCInteger* currencyAmount, cocos2d::CCString* currencyItemId,
                PurchaseType* purchaseType);
        static VirtualCurrencyPack *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, cocos2d::CCInteger* currencyAmount, cocos2d::CCString* currencyItemId,
                PurchaseType* purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~VirtualCurrencyPack();
    };
};


#endif //__VirtualCurrencyPackX_H_
