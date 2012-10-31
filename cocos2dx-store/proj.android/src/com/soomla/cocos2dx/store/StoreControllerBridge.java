package com.soomla.cocos2dx.store;

import android.app.Activity;
import android.os.Handler;
import android.util.Log;
import com.soomla.cocos2dx.example.MuffinRushAssets;
import com.soomla.store.IStoreAssets;
import com.soomla.store.StoreController;
import com.soomla.store.StoreEventHandlers;
import com.soomla.store.exceptions.InsufficientFundsException;
import com.soomla.store.exceptions.NotEnoughGoodsException;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class StoreControllerBridge {

    private static Activity mActivity   = null;
    private static Handler  mHandler    = null;
    private static IStoreAssets mStoreAssets   = null;
    private static String mPublicKey           = "";

    public static void initialize(Activity activity, Handler handler,
                                  Cocos2dxGLSurfaceView mGLView, IStoreAssets storeAssets, String publicKey) {
        mActivity   = activity;
        mHandler    = handler;
        mStoreAssets = storeAssets;
        mPublicKey = publicKey;

        StoreEventHandlers.getInstance().addEventHandler(new EventHandlerBridge(mGLView));
    }

    static void initialize(boolean debug) {
        Log.d("SOOMLA", "initialize is called from java !");
        StoreController.getInstance().initialize(mActivity, mStoreAssets, mPublicKey, debug);
    }

    static void storeOpening() {
        Log.d("SOOMLA", "storeOpening is called from java !");
        StoreController.getInstance().storeOpening(mActivity, mHandler);
    }

    static void storeClosing() {
        Log.d("SOOMLA", "storeClosing is called from java !");
        StoreController.getInstance().storeClosing();
    }

    static void buyCurrencyPack(String productId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "buyCurrencyPack is called from java with productId: " + productId + " !");
        StoreController.getInstance().buyCurrencyPack(productId);
    }

    static void buyVirtualGood(String itemId) throws VirtualItemNotFoundException, InsufficientFundsException {
        Log.d("SOOMLA", "buyVirtualGood is called from java with itemId: " + itemId + " !");
        StoreController.getInstance().buyVirtualGood(itemId);
    }

    static void buyManagedItem(String productId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "buyManagedItem is called from java with productId: " + productId + " !");
        StoreController.getInstance().buyManagedItem(productId);
    }

    static void equipVirtualGood(String itemId) throws NotEnoughGoodsException, VirtualItemNotFoundException {
        Log.d("SOOMLA", "equipVirtualGood is called from java with itemId: " + itemId + " !");
        StoreController.getInstance().equipVirtualGood(itemId);
    }

    static void unequipVirtualGood(String itemId) throws VirtualItemNotFoundException{
        Log.d("SOOMLA", "unequipVirtualGood is called from java with itemId: " + itemId + " !");
        StoreController.getInstance().unequipVirtualGood(itemId);
    }

}
