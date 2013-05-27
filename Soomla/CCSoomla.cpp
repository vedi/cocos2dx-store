//
// Created by Fedor Shubin on 5/20/13.
//


#include "CCSoomla.h"
#include "EasyNDK/NDKHelper.h"
#include "data/CCStoreInfo.h"
#include "CCStoreUtils.h"

namespace soomla {

    USING_NS_CC;

    #define SEL_GROUP "soomlaCallback"

    static CCSoomla *s_SharedSoomla = NULL;

    CCSoomla* CCSoomla::sharedSoomla() {
        if (!s_SharedSoomla) {
            s_SharedSoomla = new CCSoomla();
            s_SharedSoomla->init();
        }

        return s_SharedSoomla;
    }

    CCSoomla::~CCSoomla() {
    }

    bool CCSoomla::init() {
        NDKHelper::addSelector(SEL_GROUP, "soomla_easyNDKCallBack",
                this, callfuncO_selector(CCSoomla::easyNDKCallBack));
        return true;
    }

    void CCSoomla::easyNDKCallBack(CCDictionary *parameters) {
        CCString *methodName = dynamic_cast<CCString *>(parameters->objectForKey("method"));
        CC_ASSERT(methodName);
        if (methodName->compare("CCEventHandler::onBillingNotSupported") == 0) {
            mEventHandler->onBillingNotSupported();
        }
        else if (methodName->compare("CCEventHandler::onBillingSupported") == 0) {
            mEventHandler->onBillingNotSupported();
        }
        else if (methodName->compare("CCEventHandler::onOpeningStore") == 0) {
            mEventHandler->onOpeningStore();
        }
        else if (methodName->compare("CCEventHandler::onClosingStore") == 0) {
            mEventHandler->onClosingStore();
        }
        else if (methodName->compare("CCEventHandler::onCurrencyBalanceChanged") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCInteger *balance = (CCInteger *)(parameters->objectForKey("balance"));
            CCInteger *amountAdded = (CCInteger *)(parameters->objectForKey("amountAdded"));
            CCSoomlaError *soomlaError = NULL;
            CCVirtualCurrency *virtualCurrency = dynamic_cast<CCVirtualCurrency *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onCurrencyBalanceChanged", soomlaError);
                return;
            }
            CC_ASSERT(virtualCurrency);
            mEventHandler->onCurrencyBalanceChanged(virtualCurrency, balance->getValue(), amountAdded->getValue());
        }
        else if (methodName->compare("CCEventHandler::onGoodBalanceChanged") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCInteger *balance = (CCInteger *)(parameters->objectForKey("balance"));
            CCInteger *amountAdded = (CCInteger *)(parameters->objectForKey("amountAdded"));
            CCSoomlaError *soomlaError = NULL;
            CCVirtualGood *virtualGood = dynamic_cast<CCVirtualGood *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodBalanceChanged", soomlaError);
                return;
            }
            CC_ASSERT(virtualGood);
            mEventHandler->onGoodBalanceChanged(virtualGood, balance->getValue(), amountAdded->getValue());
        }
        else if (methodName->compare("CCEventHandler::onGoodEquipped") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCEquippableVG *equippableVG = dynamic_cast<CCEquippableVG *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodEquipped", soomlaError);
                return;
            }
            CC_ASSERT(equippableVG);
            mEventHandler->onGoodEquipped(equippableVG);
        }
        else if (methodName->compare("CCEventHandler::onGoodUnEquipped") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCEquippableVG *equippableVG = dynamic_cast<CCEquippableVG *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodUnEquipped", soomlaError);
                return;
            }
            CC_ASSERT(equippableVG);
            mEventHandler->onGoodEquipped(equippableVG);
        }
        else if (methodName->compare("CCEventHandler::onGoodUpgrade") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCString *vguItemId = (CCString *)(parameters->objectForKey("vguItemId"));

            CCSoomlaError *soomlaError;

            soomlaError = NULL;
            CCVirtualGood *virtualGood = dynamic_cast<CCVirtualGood *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodUpgrade", soomlaError);
                return;
            }
            CC_ASSERT(virtualGood);

            soomlaError = NULL;
            CCUpgradeVG *upgradeVG = dynamic_cast<CCUpgradeVG *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(vguItemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onGoodUpgrade", soomlaError);
                return;
            }
            CC_ASSERT(upgradeVG);

            mEventHandler->onGoodUpgrade(virtualGood, upgradeVG);
        }
        else if (methodName->compare("CCEventHandler::onItemPurchased") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onItemPurchased", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            mEventHandler->onItemPurchased(purchasableVirtualItem);
        }
        else if (methodName->compare("CCEventHandler::onItemPurchaseStarted") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onItemPurchased", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            mEventHandler->onItemPurchaseStarted(purchasableVirtualItem);
        }
        else if (methodName->compare("CCEventHandler::onMarketPurchaseCancelled") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketPurchaseCancelled", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            mEventHandler->onMarketPurchaseCancelled(purchasableVirtualItem);
        }
        else if (methodName->compare("CCEventHandler::onMarketPurchase") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketPurchase", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            mEventHandler->onMarketPurchase(purchasableVirtualItem);
        }
        else if (methodName->compare("CCEventHandler::onMarketPurchaseStarted") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketPurchaseStarted", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            mEventHandler->onMarketPurchaseStarted(purchasableVirtualItem);
        }
        else if (methodName->compare("CCEventHandler::onMarketRefund") == 0) {
            CCString *itemId = (CCString *)(parameters->objectForKey("itemId"));
            CCSoomlaError *soomlaError = NULL;
            CCPurchasableVirtualItem *purchasableVirtualItem = dynamic_cast<CCPurchasableVirtualItem *>(
                    CCStoreInfo::sharedStoreInfo()->getItemByItemId(itemId->getCString(), &soomlaError));
            if (soomlaError) {
                CCStoreUtils::logException("CCEventHandler::onMarketRefund", soomlaError);
                return;
            }
            CC_ASSERT(purchasableVirtualItem);
            mEventHandler->onMarketRefund(purchasableVirtualItem);
        }
        else if (methodName->compare("CCEventHandler::onRestoreTransactions") == 0) {
            CCBool *success = (CCBool *)(parameters->objectForKey("success"));
            mEventHandler->onRestoreTransactions(success->getValue());
        }
        else if (methodName->compare("CCEventHandler::onRestoreTransactionsStarted") == 0) {
            mEventHandler->onRestoreTransactionsStarted();
        }
        else if (methodName->compare("CCEventHandler::onUnexpectedErrorInStore") == 0) {
            mEventHandler->onUnexpectedErrorInStore();
        } else {
            CC_ASSERT(false);
        }
    }
}

