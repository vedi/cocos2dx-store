//
// Created by Fedor Shubin on 5/19/13.
//

#ifndef __EquippableVGX_H_
#define __EquippableVGX_H_


#include "CCLifetimeVG.h"

namespace soomla {
    class CCEquippableVG : public CCLifetimeVG {
    public:
        typedef enum {
            kLocal = 0,
            kCategory = 1,
            kGlobal = 2
        } EquippingModel;

        SL_SYNTHESIZE_RETAIN_WITH_DICT_DCL(cocos2d::CCInteger *, mEquippingModel, EquippingModel);
    public:
        CCEquippableVG(): CCLifetimeVG(), mEquippingModel(NULL) {};
        static CCEquippableVG *create(cocos2d::CCInteger *equippingModel, cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        static CCEquippableVG *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCInteger *equippingModel, cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, CCPurchaseType * purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~CCEquippableVG();
    };
};


#endif //__EquippableVGX_H_
