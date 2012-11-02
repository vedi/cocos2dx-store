//
//  cocos2dx_EventHandler.cpp
//  cocos2dx-store
//
//  Created by Refael Dakar on 11/2/12.
//
//

#include "cocos2dx_EventHandler.h"
#include "StoreAScene.h"
#include "StoreBScene.h"

void cocos2dx_EventHandler::marketPurchase(string& productId) {
	StoreBScene::setCurrencyBalanceLabel();
}

void cocos2dx_EventHandler::marketRefund(string& productId) {
	StoreBScene::setCurrencyBalanceLabel();
}

void cocos2dx_EventHandler::virtualGoodPurchased(string& itemId) {
	StoreAScene::setPriceBalanceLabel(itemId.c_str());
	StoreAScene::setCurrencyBalanceLabel();
}

void cocos2dx_EventHandler::virtualGoodEquipped(string& itemId) {
	
}

void cocos2dx_EventHandler::virtualGoodUnequipped(string& itemId) {
	
}

void cocos2dx_EventHandler::billingSupported() {
	
}

void cocos2dx_EventHandler::billingNotSupported() {
	
}

void cocos2dx_EventHandler::marketPurchaseProcessStarted(string& productId) {
	
}

void cocos2dx_EventHandler::goodsPurchaseProcessStarted() {
	
}

void cocos2dx_EventHandler::closingStore() {
	
}

void cocos2dx_EventHandler::unexpectedErrorInStore() {
	
}

void cocos2dx_EventHandler::openingStore() {
	
}