package com.soomla.cocos2dx.store;

import android.util.Log;
import com.soomla.store.StoreInventory;
import com.soomla.store.exceptions.VirtualItemNotFoundException;

/**
 * This bridge is used to let cocos2dx functions perform actions on StoreInventory (through JNI).
 *
 * You can see the documentation of every function in {@link StoreInventory}
 */
public class StoreInventoryBridge {

    static int getCurrencyBalance(String currencyItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "getCurrencyBalance is called from java !");
        return StoreInventory.getCurrencyBalance(currencyItemId);
    }

    static int addCurrencyAmount(String currencyItemId, int amount) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "addCurrencyAmount is called from java !");
        return StoreInventory.addCurrencyAmount(currencyItemId, amount);
    }

    static int removeCurrencyAmount(String currencyItemId, int amount) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "removeCurrencyAmount is called from java !");
        return StoreInventory.removeCurrencyAmount(currencyItemId, amount);
    }

    static int getGoodBalance(String goodItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "getGoodBalance is called from java !");
        return StoreInventory.getGoodBalance(goodItemId);
    }

    static int addGoodAmount(String goodItemId, int amount) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "addGoodAmount is called from java !");
        return StoreInventory.addGoodAmount(goodItemId, amount);
    }

    static int removeGoodAmount(String goodItemId, int amount) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "removeGoodAmount is called from java !");
        return StoreInventory.removeGoodAmount(goodItemId, amount);
    }
}
