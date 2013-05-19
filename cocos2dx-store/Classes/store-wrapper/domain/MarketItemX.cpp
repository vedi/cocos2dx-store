//
// Created by Fedor Shubin on 5/19/13.
//


#include "MarketItemX.h"

USING_NS_CC;

namespace soomla {

    MarketItem *MarketItem::create(CCString *productId, CCInteger *consumable, CCDouble *price) {
        MarketItem *ret = new MarketItem();
        ret->autorelease();
        ret->init(productId, consumable, price);
        return ret;
    }

    MarketItem *MarketItem::createWithDictionary(CCDictionary *dict) {
        MarketItem *ret = new MarketItem();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool MarketItem::init(CCString *productId, CCInteger *consumable, CCDouble *price) {
        setProductId(productId);
        setConsumable(consumable);
        setPrice(price);

        return true;
    }

    bool MarketItem::initWithDictionary(CCDictionary *dict) {
        fillProductIdFromDict(dict);
        fillConsumableFromDict(dict);
        fillPriceFromDict(dict);

        return true;
    }

    MarketItem::~MarketItem() {
        CC_SAFE_RELEASE(mProductId);
        CC_SAFE_RELEASE(mConsumable);
        CC_SAFE_RELEASE(mPrice);
    }

    CCDictionary *MarketItem::toDictionary() {
        CCDictionary *dict = CCDictionary::create();

        putProductIdToDict(dict);
        putConsumableToDict(dict);
        putPriceToDict(dict);

        return dict;
    }
};

