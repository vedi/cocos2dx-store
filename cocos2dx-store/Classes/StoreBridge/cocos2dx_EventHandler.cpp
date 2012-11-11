/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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