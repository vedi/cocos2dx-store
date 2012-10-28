//
//  cocos2dx_StoreInventory.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/24/12.
//
//

#include "cocos2dx_StoreInventory.h"
#include "JniHelpers.h"

int cocos2dx_StoreInventory::getCurrencyBalance(string currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"getCurrencyBalance", 
		"com/soomla/store/StoreInventoryBridge", 
		currencyItemId.c_str()
	); 
}

int cocos2dx_StoreInventory::addCurrencyAmount(string currencyItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"addCurrencyAmount", 
		"com/soomla/store/StoreInventoryBridge", 
		currencyItemId.c_str(),
		amount
	); 
}

int cocos2dx_StoreInventory::removeCurrencyAmount(string currencyItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"removeCurrencyAmount", 
		"com/soomla/store/StoreInventoryBridge", 
		currencyItemId.c_str(),
		amount
	); 
}

int cocos2dx_StoreInventory::getGoodBalance(string goodItemId)  throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"getGoodBalance", 
		"com/soomla/store/StoreInventoryBridge", 
		goodItemId.c_str()
	);
}

int cocos2dx_StoreInventory::addGoodAmount(string goodItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"addGoodAmount", 
		"com/soomla/store/StoreInventoryBridge", 
		goodItemId.c_str(),
		amount
	);
}

int cocos2dx_StoreInventory::removeGoodAmount(string goodItemId, int amount)  throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"removeGoodAmount", 
		"com/soomla/store/StoreInventoryBridge", 
		goodItemId.c_str(),
		amount
	);
}
