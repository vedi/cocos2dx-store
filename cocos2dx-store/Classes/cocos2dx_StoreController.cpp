//
//  cocos2dx_StoreController.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/22/12.
//
//

#include "cocos2dx_StoreController.h"
#include "JniHelpers.h"

void cocos2dx_StoreController::storeOpening() {
	JniHelpers::jniCommonVoidCall(
		"storeOpening", 
		"com/soomla/store/StoreControllerBridge"
	);

}

void cocos2dx_StoreController::storeClosing() {
	JniHelpers::jniCommonVoidCall(
		"storeClosing", 
		"com/soomla/store/StoreControllerBridge"
	);

}

void cocos2dx_StoreController::initialize(bool debug) {
	JniHelpers::jniCommonVoidCall(
		"initialize", 
		"com/soomla/store/StoreControllerBridge", 
		debug
	);
}

void cocos2dx_StoreController::buyCurrencyPack(string productId) throw(cocos2dx_VirtualItemNotFoundException&){
	JniHelpers::jniCommonVoidCall(
		"buyCurrencyPack", 
		"com/soomla/store/StoreControllerBridge", 
		productId.c_str()
	);
}

void cocos2dx_StoreController::buyVirtualGood(string itemId) throw (cocos2dx_VirtualItemNotFoundException&, cocos2dx_InsufficientFundsException&) {
	JniHelpers::jniCommonVoidCall(
		"buyVirtualGood", 
		"com/soomla/store/StoreControllerBridge", 
		itemId.c_str()
	);
}

void cocos2dx_StoreController::buyManagedItem(string productId) throw(cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"buyManagedItem", 
		"com/soomla/store/StoreControllerBridge", 
		productId.c_str()
	);
}

void cocos2dx_StoreController::equipVirtualGood(string itemId) throw (cocos2dx_NotEnoughGoodsException&, cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"equipVirtualGood", 
		"com/soomla/store/StoreControllerBridge", 
		itemId.c_str()
	);
}

void cocos2dx_StoreController::unequipVirtualGood(string itemId) throw(cocos2dx_VirtualItemNotFoundException&) {
	JniHelpers::jniCommonVoidCall(
		"unequipVirtualGood", 
		"com/soomla/store/StoreControllerBridge", 
		itemId.c_str()
	);
}

