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

#ifndef __EventHandler__
#define __EventHandler__

#include <string>
#include "StoreBridge/cocos2dx_EventHandlers.h"

using namespace std;

class EventHandler : public IEventHandler {
public:
    void billingSupported();
    void billingNotSupported();
	void closingStore();
	void currencyBalanceChanged(string &itemId, int balance, int amountAdded);
	void goodBalanceChanged(string &itemId, int balance, int amountAdded);
    void goodEquipped(string& itemId);
    void goodUnequipped(string& itemId);
    void goodUpgrade(string& itemId, string& upgradeItemId);
	void itemPurchased(string& itemId);
	void itemPurchaseStarted();
    void openingStore();
	void marketPurchaseCancelled(string& itemId);
    void marketPurchase(string& itemId);
    void marketPurchaseStarted(string& itemId);
    void marketRefund(string& itemId);
    void restoreTransactions(bool success);
	void restoreTransactionsStarted();
    void unexpectedErrorInStore();
};

#endif
