//
// Created by Fedor Shubin on 5/19/13.
//

#ifndef __EquippableVGX_H_
#define __EquippableVGX_H_


#include "LifetimeVGX.h"
#include "SoomlaMacros.h"

namespace soomla {
    class EquippableVG: public LifetimeVG {
        typedef enum {
            kLocal = 0,
            kCategory = 1,
            kGlobal = 2
        } EquippingModel;
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::CCInteger *, mEquippingModel, EquippingModel, JSON_EQUIPPABLE_EQUIPPING);
    public:
        EquippableVG(): LifetimeVG(), mEquippingModel(NULL) {};
        static EquippableVG *create(cocos2d::CCInteger *equippingModel, cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        static EquippableVG *createWithDictionary(cocos2d::CCDictionary *dict);

        bool init(cocos2d::CCInteger *equippingModel, cocos2d::CCString* name, cocos2d::CCString* description,
                cocos2d::CCString* itemId, PurchaseType* purchaseType);
        bool initWithDictionary(cocos2d::CCDictionary *dict);

        cocos2d::CCDictionary *toDictionary();

        virtual ~EquippableVG();
    };
};


#endif //__EquippableVGX_H_
