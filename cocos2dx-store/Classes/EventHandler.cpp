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
#include "CCStoreUtils.h"

void EventHandler::onBillingNotSupported() {

}

void EventHandler::onBillingSupported() {

}

void EventHandler::onOpeningStore() {

}

void EventHandler::onClosingStore() {

}

void EventHandler::onCurrencyBalanceChanged(soomla::CCVirtualCurrency *virtualCurrency, int balance, int amountAdded) {
    StoreBScene::setCurrencyBalanceLabel();
    StoreAScene::setCurrencyBalanceLabel();
}

void EventHandler::onGoodBalanceChanged(soomla::CCVirtualGood *virtualGood, int balance, int amountAdded) {
    StoreAScene::setPriceBalanceLabel(virtualGood->getItemId()->getCString());
}

void EventHandler::onGoodEquipped(soomla::CCEquippableVG *equippableVG) {

}

void EventHandler::onGoodUnEquipped(soomla::CCEquippableVG *equippableVG) {

}

void EventHandler::onGoodUpgrade(soomla::CCVirtualGood *virtualGood, soomla::CCUpgradeVG *upgradeVG) {

}

void EventHandler::onItemPurchased(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {

}

void EventHandler::onItemPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {

}

void EventHandler::onMarketPurchaseCancelled(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {
    soomla::CCStoreUtils::logDebug("EventHandler::onMarketPurchaseCancelled", "Market purchase cancelled by user!");
}

void EventHandler::onMarketPurchase(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {

}

void EventHandler::onMarketPurchaseStarted(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {

}

void EventHandler::onMarketRefund(soomla::CCPurchasableVirtualItem *purchasableVirtualItem) {

}

void EventHandler::onRestoreTransactions(bool success) {

}

void EventHandler::onRestoreTransactionsStarted() {

}

void EventHandler::onUnexpectedErrorInStore() {

}
