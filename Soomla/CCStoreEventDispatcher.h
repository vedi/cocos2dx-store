
#ifndef __CCStoreEventDispatcher_H_
#define __CCStoreEventDispatcher_H_

#include "cocos2d.h"
#include "CCVirtualGood.h"
#include "CCVirtualCurrency.h"
#include "CCPurchasableVirtualItem.h"
#include "CCEquippableVG.h"
#include "CCUpgradeVG.h"

namespace soomla {
    class CCStoreEventDispatcher: public cocos2d::CCObject {
    public:
        /**
        This class is singleton, access it with this function.
        */
        static CCStoreEventDispatcher *getInstance();

        bool init();

        /**
         Fired when SOOMLA knows that billing is NOT supported on the device.
         
         Event Name - CCStoreConsts::EVENT_BILLING_NOT_SUPPORTED
         */
        virtual void onBillingNotSupported();

        /**
         Fired when SOOMLA knows that billing IS supported on the device.
         
         Event Name - CCStoreConsts::EVENT_BILLING_SUPPORTED
         */
        virtual void onBillingSupported();

        /**
         Fired when the balance of a specidifc virtual currency has changed.
         
         Event Name - CCStoreConsts::EVENT_CURRENCY_BALANCE_CHANGED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_CURRENCY - CCVirtualCurrency - The currency 
         whose balance has changed.
         CCStoreConsts::DICT_ELEMENT_BALANCE - CCInteger - The balance of the 
         currency.
         CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED - CCInteger - The amount added 
         to the currency.
         */
        virtual void onCurrencyBalanceChanged(CCVirtualCurrency *virtualCurrency, int balance, int amountAdded);

        /**
         Fired when the balance of a specific virtual good has changed.
         
         Event Name - CCStoreConsts::EVENT_GOOD_BALANCE_CHANGED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_GOOD - CCVirtualGood - The good whose
         balance has changed.
         CCStoreConsts::DICT_ELEMENT_BALANCE - CCInteger - The balance of the 
         good.
         CCStoreConsts::DICT_ELEMENT_AMOUNT_ADDED - CCInteger - The amount added 
         to the good.
         */
        virtual void onGoodBalanceChanged(CCVirtualGood *virtualGood, int balance, int amountAdded);

        /**
         Fired when a specific equippable virtual good has been equipped.
         
         Event Name - CCStoreConsts::EVENT_GOOD_EQUIPPED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG - CCEquippableVG - The good 
         that is being equipped.
         */
        virtual void onGoodEquipped(CCEquippableVG *equippableVG);

        /**
         Fired when a specific equippable virtual good has been equipped.
         
         Event Name - CCStoreConsts::EVENT_GOOD_UNEQUIPPED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_EQUIPPABLEVG - CCEquippableVG - The good 
         that is being unequipped.
         */
        virtual void onGoodUnEquipped(CCEquippableVG *equippableVG);

        /**
         Fired when a specific virtual good has been upgraded.
         
         Event Name - CCStoreConsts::EVENT_GOOD_UPGRADE
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_GOOD - CCVirtualGood - The virtual good 
         that is being upgraded.
         CCStoreConsts::DICT_ELEMENT_UPGRADEVG - CCUpgradeVG - The upgrade.
         */
        virtual void onGoodUpgrade(CCVirtualGood *virtualGood, CCUpgradeVG *upgradeVG);

        /**
         Fired when when a specific virtual good has been purchased.
         
         Event Name - CCStoreConsts::EVENT_ITEM_PURCHASED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem - 
         The item being purchased.
         CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD - CCString - The developer
         payload.
         */
        virtual void onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *payload);
        
        virtual void onItemPurchased(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *payload, bool alsoPush);

        /**
         Fired when a purchase process has started.
         
         Event Name - CCStoreConsts::EVENT_ITEM_PURCHASE_STARTED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem - 
         The item whose purchase has started.
         */
        virtual void onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem);
        
        virtual void onItemPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem, bool alsoPush);

        /**
         Fired when a market (App Store, Google Play, etc..) purchase has been 
         cancelled.
         
         Event Name - CCStoreConsts::EVENT_MARKET_PURCHASE_CANCELED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem -
         the item whose purchase is being cancelled.
         */
        virtual void onMarketPurchaseCancelled(CCPurchasableVirtualItem *purchasableVirtualItem);

        /**
         Fired when a market item from the store (App Store, Google Play, etc..) 
         has been purchased.
         
         Event Name - CCStoreConsts::EVENT_MARKET_PURCHASE
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem - The market item being purchased.
         CCStoreConsts::DICT_ELEMENT_DEVELOPERPAYLOAD - CCString - The developer payload.
         CCStoreConsts::DICT_ELEMENT_EXTRA_INFO - contains platform specific information about the market purchase
            Android: The "extra" dictionary will contain: 'token', 'orderId', 'originalJson', 'signature', 'userId'
            iOS: The "extra" dictionary will contain: 'receiptUrl', 'transactionIdentifier', 'receiptBase64',
                'transactionDate', 'originalTransactionDate', 'originalTransactionIdentifier'
        */
        virtual void onMarketPurchase(CCPurchasableVirtualItem *purchasableVirtualItem, cocos2d::CCString *payload,
                cocos2d::CCDictionary *extraInfo);

        /**
         Fired when a purchase process has started, where the item is being 
         purchased from the store (App Store, Google Play, etc..).
         
         Event Name - CCStoreConsts::EVENT_MARKET_PURCHASE_STARTED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem -
         The market item whose purchase has started.
         */
        virtual void onMarketPurchaseStarted(CCPurchasableVirtualItem *purchasableVirtualItem);

        /**
         Fired when a market purchase verification process has started.
         
         Event Name - CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem -
         The market item whose purchase is being verified.
         */
        virtual void onMarketPurchaseVerification(CCPurchasableVirtualItem *purchasableVirtualItem);

        /**
         Fired when a restore transactions process has finished.
         
         Event Name - CCStoreConsts::EVENT_RESTORE_TRANSACTION_FINISHED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_SUCCESS - CCBool - Indicates if the 
         restore transactions process finished successfully.
         */
        virtual void onRestoreTransactionsFinished(bool success);

        /**
         Fired when a restore transactions process has started.
         
         Event Name - CCStoreConsts::EVENT_RESTORE_TRANSACTION_STARTED
         */
        virtual void onRestoreTransactionsStarted();

        /**
         Fired when an unexpected error occurs in the store.
         
         Event Name - CCStoreConsts::EVENT_UNEXPECTED_STORE_ERROR
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_ERROR_CODE - CCInteger -
         The description of the error which occured.
         */
        virtual void onUnexpectedStoreError(cocos2d::CCInteger *errorCode);

        virtual void onUnexpectedStoreError(cocos2d::CCInteger *errorCode, bool alsoPush);

        /**
         Fired when store controller is initialized.
         
         Event Name - CCStoreConsts::EVENT_SOOMLA_STORE_INITIALIZED
         */
        virtual void onSoomlaStoreInitialized();
        
        virtual void onSoomlaStoreInitialized(bool alsoPush);

        /**
         Fired when a market item refreshed process has completed.
         
         Event Name - CCStoreConsts::EVENT_MARKET_ITEMS_REFRESHED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_MARKET_ITEMS - CCArray -
         The market items which were refreshed.
         */
        virtual void onMarketItemsRefreshed(cocos2d::CCArray *marketItems);

/** Android only events*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

        /**
         Fired when a market item is being refunded.
         
         Event Name - CCStoreConsts::EVENT_MARKET_REFUND
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem -
         The item that is being refunded in the market.
         */
        virtual void onMarketRefund(CCPurchasableVirtualItem *purchasableVirtualItem);

        /**
         Fired when a restore transactions process has finished.
         
         Event Name - CCStoreConsts::EVENT_MARKET_PURCHASE_VERIFICATION
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_PURCHASABLE - CCPurchasableVirtualItem -
         The market item whose purchase is being verified.
         */
        virtual void onIabServiceStarted();

        /**
         Fired when in-app billing service is started.
         
         Event Name - CCStoreConsts::EVENT_IAB_SERVICE_STARTED
         */
        virtual void onIabServiceStopped();
#endif

        /**
         Fired when in-app billing service is stopped.
         
         Event Name - CCStoreConsts::EVENT_IAB_SERVICE_STOPPED
         */
        virtual void onMarketItemsRefreshStarted();
        
        /**
         Fired when a market item refreshed process has failed.
         
         Event Name - CCStoreConsts::EVENT_MARKET_ITEMS_REFRESH_FAILED
         Event Data (CCDictionary):
         CCStoreConsts::DICT_ELEMENT_ERROR_MESSAGE - CCString - The error which 
         caused the failure.
         */
        virtual void onMarketItemsRefreshFailed(cocos2d::CCString *errorMessage);

        void handle__EVENT_BILLING_NOT_SUPPORTED(cocos2d::CCDictionary *paramaters);

        void handle__EVENT_BILLING_SUPPORTED(cocos2d::CCDictionary *paramaters);

        void handle__EVENT_CURRENCY_BALANCE_CHANGED(cocos2d::CCDictionary *paramaters);

        void handle__EVENT_GOOD_BALANCE_CHANGED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_GOOD_EQUIPPED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_GOOD_UNEQUIPPED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_GOOD_UPGRADE(cocos2d::CCDictionary *parameters);

        void handle__EVENT_ITEM_PURCHASED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_ITEM_PURCHASE_STARTED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_MARKET_PURCHASE_CANCELED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_MARKET_PURCHASE(cocos2d::CCDictionary *parameters);

        void handle__EVENT_MARKET_PURCHASE_STARTED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_MARKET_ITEMS_REFRESHED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_MARKET_ITEMS_REFRESH_STARTED(cocos2d::CCDictionary *parameters);
        
        void handle__EVENT_MARKET_ITEMS_REFRESH_FAILED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_MARKET_PURCHASE_VERIFICATION(cocos2d::CCDictionary *parameters);

        void handle__EVENT_RESTORE_TRANSACTION_FINISHED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_RESTORE_TRANSACTION_STARTED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_ON_UNEXPECTED_STORE_ERROR(cocos2d::CCDictionary *parameters);

        void handle__EVENT_STORE_CONTROLLER_INITIALIZED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_MARKET_REFUND(cocos2d::CCDictionary *parameters);

        void handle__EVENT_IAB_SERVICE_STARTED(cocos2d::CCDictionary *parameters);

        void handle__EVENT_IAB_SERVICE_STOPPED(cocos2d::CCDictionary *parameters);

    };
}


#endif //__CCStoreEventDispatcher_H_
