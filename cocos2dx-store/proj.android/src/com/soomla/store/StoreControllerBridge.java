package com.soomla.store;

import android.app.Activity;
import android.os.Handler;
import android.util.Log;
import com.soomla.example.MuffinRushAssets;
import com.soomla.store.exceptions.InsufficientFundsException;
import com.soomla.store.exceptions.NotEnoughGoodsException;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class StoreControllerBridge {

    private static Activity        mActivity   = null;
    private static Handler         mHandler    = null;

    public static void initialize(Activity activity, Handler handler, Cocos2dxGLSurfaceView mGLView) {
        mActivity   = activity;
        mHandler    = handler;

        StoreEventHandlers.getInstance().addEventHandler(new EventHandlerBridge(mGLView));
    }

    static void initialize(boolean debug) {
        Log.d("SOOMLA", "initialize is called from java !");
        StoreController.getInstance().initialize(mActivity, new MuffinRushAssets(),
                "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAndHbBVrbynZ9LOQhRCA/+dzYyQeT7qcbo6BD16O+7ltau6JLy78emOo4615" +
                        "+N3dl5RJ3FBlRw14aS+KhNAf0gMlrk3RBQA5d+sY/8oD22kC8Gn7blwsmk3LWYqOiGGXFtRxUyBxdibjFo0+qBz+BXJzfKY" +
                        "V+Y3wSDz0RBUoY9+akbF3EHuB6d02fXLeeIAswB28OlAM4PUuHSbj9lDNFefJwawQ7kgUALETJ98ImKlPUzG0jVh1t9vUOa" +
                        "rsIZdzWmVu69+Au3mniqzcGY9gZyfYf0n7cNR3isSDfNOjeisDpfNpY/ljf71/6ns3/WjDwtXB2eDal5fz7fbsLEWRkSwID" +
                        "AQAB", debug);
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
