package com.soomla.cocos2dx.store;

import com.soomla.store.data.StoreInfo;
import com.soomla.store.domain.data.VirtualCurrencyPack;
import com.soomla.store.domain.data.VirtualGood;
import com.soomla.store.exceptions.VirtualItemNotFoundException;

/**
 * This bridge is used to let cocos2dx functions retrieve data from StoreInfo (through JNI).
 *
 * You can see the documentation of every function in {@link StoreInfo}
 */
public class StoreInfoBridge {

    static String getPackProductId(String itemId) throws VirtualItemNotFoundException {
        VirtualCurrencyPack pack = StoreInfo.getInstance().getPackByItemId(itemId);
        return pack.getProductId();
    }

    static String getPackName(String itemId) throws VirtualItemNotFoundException {

        VirtualCurrencyPack pack = StoreInfo.getInstance().getPackByItemId(itemId);

        return pack.getName();
    }

    static String getPackDescription(String itemId) throws VirtualItemNotFoundException {

        VirtualCurrencyPack pack = StoreInfo.getInstance().getPackByItemId(itemId);

        return pack.getDescription();
    }

    static double getPackPrice(String itemId) throws VirtualItemNotFoundException {

        VirtualCurrencyPack pack = StoreInfo.getInstance().getPackByItemId(itemId);

        return pack.getPrice();
    }

    static String getGoodName(String itemId) throws VirtualItemNotFoundException {

        VirtualGood good = StoreInfo.getInstance().getVirtualGoodByItemId(itemId);

        return good.getName();
    }

    static String getGoodDescription(String itemId) throws VirtualItemNotFoundException {

        VirtualGood good = StoreInfo.getInstance().getVirtualGoodByItemId(itemId);

        return good.getDescription();
    }

    static int getGoodPriceForCurrency(String goodItemId, String currencyItemId) throws VirtualItemNotFoundException {

        VirtualGood good = StoreInfo.getInstance().getVirtualGoodByItemId(goodItemId);

        return good.getCurrencyValues().get(currencyItemId);
    }
}
