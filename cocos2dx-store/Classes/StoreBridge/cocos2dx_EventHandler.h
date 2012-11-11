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

#ifndef __cocos2dx_store__cocos2dx_EventHandler__
#define __cocos2dx_store__cocos2dx_EventHandler__

#include <string>

using namespace std;

class cocos2dx_EventHandler {

public:
	    
    static void marketPurchase(string& productId);

    static void marketRefund(string& productId);

    static void virtualGoodPurchased(string& itemId);

    static void virtualGoodEquipped(string& itemId);

    static void virtualGoodUnequipped(string& itemId);

    static void billingSupported();

    static void billingNotSupported();

    static void marketPurchaseProcessStarted(string& productId);
    
    static void goodsPurchaseProcessStarted();
    
    static void closingStore();
    
    static void unexpectedErrorInStore();

    static void openingStore();
};

#endif /* defined(__cocos2dx_store__cocos2dx_EventHandler__) */
