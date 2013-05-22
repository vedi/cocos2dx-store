//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCStoreInventory.h"
#include "CCStoreUtils.h"
#include "CCSoomlaEasyNdkBridge.h"


namespace soomla {
#define TAG "SOOMLA StoreController"

    USING_NS_CC;

    static CCStoreInventory *s_SharedStoreInventory = NULL;

    CCStoreInventory *CCStoreInventory::sharedStoreInventory() {
        return s_SharedStoreInventory;
    }

    CCStoreInventory::CCStoreInventory() {

    }

    CCStoreInventory::~CCStoreInventory() {

    }

    bool CCStoreInventory::init() {
        return true;
    }

    void CCStoreInventory::buyItem(char const *itemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling buyItem with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::buyItem"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    int CCStoreInventory::getItemBalance(char const *itemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling getItemBalance with: %s", itemId)->getCString());
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::getItemBalance"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    void CCStoreInventory::giveItem(char const *itemId, int amount) {
        CCStoreUtils::logDebug(TAG, CCString::createWithFormat(
                "SOOMLA/UNITY Calling giveItem with itedId: %s and amount %d", itemId, amount)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::giveItem"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        params->setObject(CCInteger::create(amount), "amount");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    void CCStoreInventory::takeItem(char const *itemId, int amount) {
        CCStoreUtils::logDebug(TAG, CCString::createWithFormat(
                "SOOMLA/UNITY Calling takeItem with itedId: %s and amount %d", itemId, amount)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::takeItem"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        params->setObject(CCInteger::create(amount), "amount");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    void CCStoreInventory::equipVirtualGood(char const *itemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling equipVirtualGood with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::equipVirtualGood"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCSoomlaEasyNdkBridge::callNative(params);
   }

    void CCStoreInventory::unEquipVirtualGood(char const *itemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling unEquipVirtualGood with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::unEquipVirtualGood"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    bool CCStoreInventory::isVirtualGoodEquipped(char const *itemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling isVirtualGoodEquipped with: %s", itemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::isVirtualGoodEquipped"), "method");
        params->setObject(CCString::create(itemId), "itemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    int CCStoreInventory::getGoodUpgradeLevel(char const *goodItemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling getGoodUpgradeLevel with: %s", goodItemId)->getCString());
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::getGoodUpgradeLevel"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        CCInteger *retValue = (CCInteger *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    std::string CCStoreInventory::getGoodCurrentUpgrade(char const *goodItemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling getGoodCurrentUpgrade with: %s", goodItemId)->getCString());
        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::getGoodCurrentUpgrade"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        CCString *retValue = (CCString *) retParams->objectForKey("return");
        return retValue->getCString();
    }

    void CCStoreInventory::upgradeGood(char const *goodItemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling upgradeGood with: %s", goodItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::upgradeGood"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    void CCStoreInventory::removeGoodUpgrades(char const *goodItemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling removeGoodUpgrades with: %s", goodItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::removeGoodUpgrades"), "method");
        params->setObject(CCString::create(goodItemId), "goodItemId");
        CCSoomlaEasyNdkBridge::callNative(params);
    }

    bool CCStoreInventory::nonConsumableItemExists(char const *nonConsItemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling nonConsumableItemExists with: %s", nonConsItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::nonConsumableItemExists"), "method");
        params->setObject(CCString::create(nonConsItemId), "nonConsItemId");
        CCDictionary *retParams = (CCDictionary *) CCSoomlaEasyNdkBridge::callNative(params);
        CCBool *retValue = (CCBool *) retParams->objectForKey("return");
        return retValue->getValue();
    }

    void CCStoreInventory::addNonConsumableItem(char const *nonConsItemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling addNonConsumableItem with: %s", nonConsItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::addNonConsumableItem"), "method");
        params->setObject(CCString::create(nonConsItemId), "nonConsItemId");
        CCSoomlaEasyNdkBridge::callNative(params);
   }

    void CCStoreInventory::removeNonConsumableItem(char const *nonConsItemId) {
        CCStoreUtils::logDebug(TAG,
                CCString::createWithFormat("SOOMLA/UNITY Calling removeNonConsumableItem with: %s", nonConsItemId)->getCString());

        CCDictionary *params = CCDictionary::create();
        params->setObject(CCString::create("CCStoreInventory::removeNonConsumableItem"), "method");
        params->setObject(CCString::create(nonConsItemId), "nonConsItemId");
        CCSoomlaEasyNdkBridge::callNative(params);
    }


}