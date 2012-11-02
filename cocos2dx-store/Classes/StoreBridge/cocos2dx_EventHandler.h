//
//  cocos2dx_EventHandler.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 11/2/12.
//
//

#ifndef __cocos2dx_store__cocos2dx_EventHandler__
#define __cocos2dx_store__cocos2dx_EventHandler__

#include <string>

using namespace std;

class cocos2dx_EventHandler {

public:
	    
    static void marketPurchase(string& productId);

    static void marketRefund(string& productId);

    static void virtualGoodPurchased(string& itemId);

    static void virtualGoodEquipped(string& itemId);

    static void virtualGoodUnequipped(string& itemId);

    static void billingSupported();

    static void billingNotSupported();

    static void marketPurchaseProcessStarted(string& productId);
    
    static void goodsPurchaseProcessStarted();
    
    static void closingStore();
    
    static void unexpectedErrorInStore();

    static void openingStore();
};

#endif /* defined(__cocos2dx_store__cocos2dx_EventHandler__) */
