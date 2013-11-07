//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCStoreController_H_
#define __CCStoreController_H_

#include "cocos2d.h"
#include "CCIStoreAssets.h"
#include "CCSoomlaError.h"

namespace soomla {
	/** \class CCStoreController
		\brief An interface to the native StoreController class.

		An interface to the native StoreController class, use this class to
		access the native StoreController functionality.
	 */
    class CCStoreController: public cocos2d::CCObject {
    public:
		/**
		   This class is singleton, use this function to access it.
		*/
        static CCStoreController* sharedStoreController();

		/**
		   Initialize StoreController on native side and allow using its
		   functions.
		 */
        static void createShared(CCIStoreAssets *storeAssets, cocos2d::CCDictionary *storeParams);

        CCStoreController(void);
        virtual ~CCStoreController(void);
        virtual bool init(CCIStoreAssets *storeAssets, cocos2d::CCDictionary *storeParams);

		/**
		   Buy an item from the App Store or Google Play.
		   \param productId The Product ID of the item in the App Store or Google Play
		   \param soomlaError A CCSoomlaError for error checking.
		 */
        void buyMarketItem(char const *productId, CCSoomlaError **soomlaError);

		/**
		   Tell StoreController you are opening the store.
		 */
        void storeOpening();

		/**
		   Tell StoreController you are closing the store.
		*/
		void storeClosing();

		/**
		   Restore this user's previous transactions.
		 */
        void restoreTransactions();

		/**
		   Find out if the user restored his transactions.
		   \return Whether or not the user restored his transactions.
		*/		
        bool transactionsAlreadyRestored();
    };
};

#endif //__CCStoreController_H_
