//
//  cocos2dx_StoreInfo.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 10/22/12.
//
//

#include "cocos2dx_StoreInfo.h"
#include "JniHelpers.h"

string cocos2dx_StoreInfo::getPackProductId(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonStringCall(
		"getPackProductId", 
		"com/soomla/store/StoreInfoBridge", 
		itemId
	); 
}

string cocos2dx_StoreInfo::getPackName(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonStringCall(
		"getPackName", 
		"com/soomla/store/StoreInfoBridge", 
		itemId
	); 
}

string cocos2dx_StoreInfo::getPackDescription(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonStringCall(
		"getPackDescription", 
		"com/soomla/store/StoreInfoBridge", 
		itemId
	);
}

double cocos2dx_StoreInfo::getPackPrice(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonDoubleCall(
		"getPackPrice", 
		"com/soomla/store/StoreInfoBridge", 
		itemId
	);
}

string cocos2dx_StoreInfo::getGoodName(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonStringCall(
		"getGoodName", 
		"com/soomla/store/StoreInfoBridge", 
		itemId
	);
}

string cocos2dx_StoreInfo::getGoodDescription(const char* itemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonStringCall(
		"getGoodDescription", 
		"com/soomla/store/StoreInfoBridge", 
		itemId
	);
}

int cocos2dx_StoreInfo::getGoodPriceForCurrency(const char* goodItemId, const char* currencyItemId) throw (cocos2dx_VirtualItemNotFoundException&) {
	return JniHelpers::jniCommonIntCall(
		"getGoodPriceForCurrency", 
		"com/soomla/store/StoreInfoBridge", 
		goodItemId,
		currencyItemId
	);
}



