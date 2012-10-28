//
//  cocos2dx_StoreController.h
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/22/12.
//
//

#ifndef __cocos2dx_store__cocos2dx_StoreController__
#define __cocos2dx_store__cocos2dx_StoreController__

#include <iostream>
#include <string>
#include "cocos2dx_VirtualItemNotFoundException.h"
#include "cocos2dx_InsufficientFundsException.h"
#include "cocos2dx_NotEnoughGoodsException.h"

using namespace std;

class cocos2dx_StoreController {

public:
    
    //iOS + Android
    static void storeOpening();
    static void storeClosing();
    static void initialize(bool debug);
	static void buyCurrencyPack(string productId) throw(cocos2dx_VirtualItemNotFoundException&);
	static void buyVirtualGood(string itemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&);
	static void buyManagedItem(string productId) throw(cocos2dx_VirtualItemNotFoundException&);
	static void equipVirtualGood(string itemId) throw (cocos2dx_NotEnoughGoodsException&, cocos2dx_VirtualItemNotFoundException&);
	static void unequipVirtualGood(string itemId) throw(cocos2dx_VirtualItemNotFoundException&);
	
};

#endif /* defined(__cocos2dx_store__cocos2dx_StoreController__) */
