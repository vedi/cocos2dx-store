//
// Created by Fedor Shubin on 5/20/13.
//


#include "CCSoomla.h"
#include "data/CCStoreInfo.h"
#include "CCStoreUtils.h"

namespace soomla {

    USING_NS_CC;

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
		return true;
    }

	void CCSoomla::addEventHandler(CCEventHandler *eventHandler) {
		mEventHandlers.insert(eventHandler);
	}

	void CCSoomla::removeEventHandler(CCEventHandler *eventHandler) {
		mEventHandlers.erase(eventHandler);
	}

    void CCSoomla::easyNDKCallBack(CCDictionary *parameters) {
        CCString *methodName = dynamic_cast<CCString *>(parameters->objectForKey("method"));
        CC_ASSERT(methodName);
		if (methodName->compare("CCEventHandler::onBillingNotSupported") == 0) {
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onBillingNotSupported();
			}
        }
        else if (methodName->compare("CCEventHandler::onBillingSupported") == 0) {
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onBillingSupported();
			}
        }
        else if (methodName->compare("CCEventHandler::onOpeningStore") == 0) {
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onOpeningStore();
			}
        }
        else if (methodName->compare("CCEventHandler::onClosingStore") == 0) {
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onClosingStore();
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onCurrencyBalanceChanged(virtualCurrency, balance->getValue(), amountAdded->getValue());
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onGoodBalanceChanged(virtualGood, balance->getValue(), amountAdded->getValue());
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onGoodEquipped(equippableVG);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onGoodUnEquipped(equippableVG);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onGoodUpgrade(virtualGood, upgradeVG);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onItemPurchased(purchasableVirtualItem);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onItemPurchaseStarted(purchasableVirtualItem);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onMarketPurchaseCancelled(purchasableVirtualItem);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onMarketPurchase(purchasableVirtualItem);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onMarketPurchaseStarted(purchasableVirtualItem);
			}
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
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onMarketRefund(purchasableVirtualItem);
			}
        }
        else if (methodName->compare("CCEventHandler::onRestoreTransactions") == 0) {
            CCBool *success = (CCBool *)(parameters->objectForKey("success"));
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onRestoreTransactions(success->getValue());
			}
        }
        else if (methodName->compare("CCEventHandler::onRestoreTransactionsStarted") == 0) {
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onRestoreTransactionsStarted();
			}
        }
        else if (methodName->compare("CCEventHandler::onUnexpectedErrorInStore") == 0) {
			set<CCEventHandler *>::iterator i;
			for(i = mEventHandlers.begin(); i != mEventHandlers.end(); i++) {
				(*i)->onUnexpectedErrorInStore();
			}
		} else {
            CC_ASSERT(false);
        }
    }
}
