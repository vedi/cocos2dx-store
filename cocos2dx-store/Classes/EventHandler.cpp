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

#include "EventHandler.h"
#include "StoreAScene.h"
#include "StoreBScene.h"

void EventHandler::marketPurchase(string& productId) {
	
}

void EventHandler::marketRefund(string& productId) {
	
}

void EventHandler::virtualGoodPurchased(string& itemId) {
	
}

void EventHandler::virtualGoodEquipped(string& itemId) {
	
}

void EventHandler::virtualGoodUnequipped(string& itemId) {

}

void EventHandler::billingSupported() {

}

void EventHandler::billingNotSupported() {

}

void EventHandler::marketPurchaseProcessStarted(string& productId) {

}

void EventHandler::goodsPurchaseProcessStarted() {

}

void EventHandler::closingStore() {

}

void EventHandler::unexpectedErrorInStore() {

}

void EventHandler::openingStore() {

}

void EventHandler::currencyBalanceChanged(string &itemId, int balance) {
	StoreBScene::setCurrencyBalanceLabel();
    StoreAScene::setCurrencyBalanceLabel();
}

void EventHandler::goodBalanceChanged(string &itemId, int balance) {
	StoreAScene::setPriceBalanceLabel(itemId.c_str());
}

