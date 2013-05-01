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
#include "StoreBridge/Includes.h"

void EventHandler::billingSupported() {
	
}
void EventHandler::billingNotSupported() {
	
}
void EventHandler::closingStore() {
	
}
void EventHandler::currencyBalanceChanged(string &itemId, int balance, int amountAdded) {
	StoreBScene::setCurrencyBalanceLabel();
    StoreAScene::setCurrencyBalanceLabel();
}
void EventHandler::goodBalanceChanged(string &itemId, int balance, int amountAdded) {
	StoreAScene::setPriceBalanceLabel(itemId.c_str());
}
void EventHandler::goodEquipped(string& itemId) {
	
}
void EventHandler::goodUnequipped(string& itemId) {
	
}
void EventHandler::goodUpgrade(string& itemId, string& upgradeItemId) {
	
}
void EventHandler::itemPurchased(string& itemId) {
	
}
void EventHandler::itemPurchaseStarted() {
	
}
void EventHandler::openingStore() {
	
}
void EventHandler::marketPurchaseCancelled(string& itemId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    __android_log_write(ANDROID_LOG_ERROR, "SOOMLA JNI", "Market purchase cancelled by user!");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    iOSHelper::LogMessage("Market purchase cancelled by user!");
#endif
}
void EventHandler::marketPurchase(string& itemId) {
	
}
void EventHandler::marketPurchaseStarted(string& itemId) {
	
}
void EventHandler::marketRefund(string& itemId) {
	
}
void EventHandler::restoreTransactions(bool success) {
	
}
void EventHandler::restoreTransactionsStarted() {
	
}
void EventHandler::unexpectedErrorInStore() {
	
}




