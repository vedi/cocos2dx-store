//
// Created by Fedor Shubin on 5/19/13.
//


#include "VirtualCategoryX.h"

USING_NS_CC;

namespace soomla {
    VirtualCategory *VirtualCategory::create(CCString *name, CCArray *goodItemIds) {
        VirtualCategory *ret = new VirtualCategory();
        ret->autorelease();
        ret->init(name, goodItemIds);
        return ret;
    }

    VirtualCategory *VirtualCategory::createWithDictionary(CCDictionary *dict) {
        VirtualCategory *ret = new VirtualCategory();
        ret->autorelease();
        ret->initWithDictionary(dict);
        return ret;
    }

    bool VirtualCategory::init(CCString *name, CCArray *goodItemIds) {
        setName(name);
        setGoodItemIds(goodItemIds);

        return true;
    }

    bool VirtualCategory::initWithDictionary(CCDictionary *dict) {
        fillNameFromDict(dict);
        fillGoodItemIdsFromDict(dict);

        return true;
    }

    CCDictionary *VirtualCategory::toDictionary() {
        CCDictionary *dict = CCDictionary::create();

        putNameToDict(dict);
        putGoodItemIdsToDict(dict);

        return dict;
    }

    VirtualCategory::~VirtualCategory() {
        CC_SAFE_RELEASE(mName);
        CC_SAFE_RELEASE(mGoodItemIds);
    }
}
