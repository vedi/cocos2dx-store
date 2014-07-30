//
// Created by Fedor on 04/06/14.
//

#include "CCVirtualItemReward.h"
#include "CCStoreConsts.h"

soomla::CCVirtualItemReward *soomla::CCVirtualItemReward::create(
        cocos2d::CCString *rewardId,
        cocos2d::CCString *name,
        cocos2d::CCBool *repeatable,
        cocos2d::CCInteger *amount,
        cocos2d::CCString *associatedItemId
) {

    CCVirtualItemReward *ret = new CCVirtualItemReward();
    if (ret->init(rewardId, name, repeatable, amount, associatedItemId)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCVirtualItemReward::init(
        cocos2d::CCString *rewardId,
        cocos2d::CCString *name,
        cocos2d::CCBool *repeatable,
        cocos2d::CCInteger *amount,
        cocos2d::CCString *associatedItemId
) {

    bool result = CCReward::init(rewardId, name, repeatable);

    if (result) {
        setAmount(amount);
        setAssociatedItemId(associatedItemId);
        return true;
    } else {
        return false;
    }
}

bool soomla::CCVirtualItemReward::initWithDictionary(cocos2d::CCDictionary *dict) {
    CCReward::initWithDictionary(dict);

    fillAmountFromDict(dict);
    fillAssociatedItemIdFromDict(dict);

    return true;
}

cocos2d::CCDictionary *soomla::CCVirtualItemReward::toDictionary() {
    cocos2d::CCDictionary *dict = CCReward::toDictionary();

    putAmountToDict(dict);
    putAssociatedItemIdToDict(dict);

    return dict;
}

soomla::CCVirtualItemReward::~CCVirtualItemReward() {
    CC_SAFE_RELEASE(mAmount);
    CC_SAFE_RELEASE(mAssociatedItemId);
}

const char *soomla::CCVirtualItemReward::getType() {
    return CCStoreConsts::JSON_JSON_TYPE_ITEM;
}
