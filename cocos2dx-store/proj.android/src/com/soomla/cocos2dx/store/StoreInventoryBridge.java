package com.soomla.cocos2dx.store;

import android.util.Log;
import com.soomla.store.StoreInventory;
import com.soomla.store.exceptions.InsufficientFundsException;
import com.soomla.store.exceptions.VirtualItemNotFoundException;

/**
 * This bridge is used to let cocos2dx functions perform actions on StoreInventory (through JNI).
 *
 * You can see the documentation of every function in {@link StoreInventory}
 */
public class StoreInventoryBridge {

    public static void buy(String itemId) throws VirtualItemNotFoundException, InsufficientFundsException {
        Log.d("SOOMLA", "buy is called from java !");
        StoreInventory.buy(itemId);
    }

    public static int getItemBalance(String itemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "getCurrencyBalance is called from java !");
        return StoreInventory.getVirtualItemBalance(itemId);
    }

    public static void giveItem(String itemId, int amount) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "addCurrencyAmount is called from java !");
        StoreInventory.giveVirtualItem(itemId, amount);
    }

    public static void takeItem(String itemId, int amount) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "removeCurrencyAmount is called from java !");
        StoreInventory.takeVirtualItem(itemId, amount);
    }

    public static void equipVirtualGood(String goodItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "equipVirtualGood is called from java !");
        StoreInventory.equipVirtualGood(goodItemId);
    }

    public static void unEquipVirtualGood(String goodItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "unEquipVirtualGood is called from java !");
        StoreInventory.unEquipVirtualGood(goodItemId);
    }

    public static boolean isVirtualGoodEquipped(String goodItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "isVirtualGoodEquipped is called from java !");
        return StoreInventory.isVirtualGoodEquipped(goodItemId);
    }

    public static int getGoodUpgradeLevel(String goodItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "getGoodUpgradeLevel is called from java !");
        return StoreInventory.getGoodUpgradeLevel(goodItemId);
    }

    public static String getGoodCurrentUpgrade(String goodItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "removeGoodAmount is called from java !");
        return StoreInventory.getGoodCurrentUpgrade(goodItemId);
    }

    public static void upgradeVirtualGood(String goodItemId) throws VirtualItemNotFoundException, InsufficientFundsException {
        Log.d("SOOMLA", "upgradeVirtualGood is called from java !");
        StoreInventory.upgradeVirtualGood(goodItemId);
    }

    public static void removeUpgrades(String goodItemId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "removeUpgrades is called from java !");
        StoreInventory.removeUpgrades(goodItemId);
    }

    public static boolean nonConsumableItemExists(String nonConsItemId) throws VirtualItemNotFoundException, ClassCastException {
        Log.d("SOOMLA", "nonConsumableItemExists is called from java !");
        return StoreInventory.nonConsumableItemExists(nonConsItemId);
    }

    public static void addNonConsumableItem(String nonConsItemId) throws VirtualItemNotFoundException, ClassCastException {
        Log.d("SOOMLA", "addNonConsumableItem is called from java !");
        StoreInventory.addNonConsumableItem(nonConsItemId);
    }

    public static void removeNonConsumableItem(String nonConsItemId) throws VirtualItemNotFoundException, ClassCastException {
        Log.d("SOOMLA", "removeNonConsumableItem is called from java !");
        StoreInventory.removeNonConsumableItem(nonConsItemId);
    }

}
