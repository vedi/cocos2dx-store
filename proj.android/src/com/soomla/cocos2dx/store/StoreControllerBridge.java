package com.soomla.cocos2dx.store;

import android.app.Activity;
import android.util.Log;
import com.soomla.store.*;
import com.soomla.store.data.StoreInfo;
import com.soomla.store.domain.PurchasableVirtualItem;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import com.soomla.store.purchaseTypes.PurchaseWithMarket;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

/**
 * This bridge is used to let cocos2dx functions perform actions on StoreController (through JNI).
 *
 * You can see the documentation of every function in {@link StoreController}
 */
public class StoreControllerBridge {
    private static Activity mActivity          = null;
    private static IStoreAssets mStoreAssets   = null;
    private static String mPublicKey           = "";
    private static EventHandlerBridge mEventHandler = null;

    public static void initialize(Cocos2dxGLSurfaceView mGLView,
                                  IStoreAssets storeAssets,
                                  String publicKey,
                                  Activity activity) {
        mStoreAssets = storeAssets;
        mPublicKey   = publicKey;
        mActivity    = activity;


        mEventHandler = new EventHandlerBridge(mGLView);
    }

    public static void setActivity(Activity activity) {
        mActivity = activity;
    }

    public static void initialize(String customSecret) {
        Log.d("SOOMLA", "initialize is called from java !");
        StoreController.getInstance().initialize(mStoreAssets, mPublicKey, customSecret);
    }

    public static void storeOpening() {
        Log.d("SOOMLA", "storeOpening is called from java !");
        StoreController.getInstance().storeOpening(mActivity);
    }

    public static void storeClosing() {
        Log.d("SOOMLA", "storeClosing is called from java !");
        StoreController.getInstance().storeClosing();
    }

    public static void buyWithGooglePlay(String productId) throws VirtualItemNotFoundException {
        Log.d("SOOMLA", "buyWithGooglePlay is called from java with productId: " + productId + " !");
        PurchasableVirtualItem pvi = StoreInfo.getPurchasableItem(productId);
        if(pvi.getPurchaseType() instanceof PurchaseWithMarket) {
            StoreController.getInstance().buyWithGooglePlay(((PurchaseWithMarket)pvi.getPurchaseType()).getGoogleMarketItem(), "");
        } else {
            throw new VirtualItemNotFoundException("productId", productId);
        }
    }

    public static void restoreTransactions() {
        Log.d("SOOMLA", "restoreTransactions is called from java !");
        StoreController.getInstance().restoreTransactions();
    }

    public static boolean transactionsAlreadyRestored() {
        Log.d("SOOMLA", "transactionsAlreadyRestored is called from java !");
        return StoreController.getInstance().transactionsAlreadyRestored();
    }

    public static void setAndroidTestMode(boolean testMode) {
        Log.d("SOOMLA", "setAndroidTestMode is called from java !");
        StoreController.getInstance().setTestMode(testMode);
    }

    public static void setStoreAssetsBridge(StoreAssetsBridge storeAssetsBridge) {
        StoreControllerBridge.mStoreAssets = storeAssetsBridge;
    }

    public static void setSoomSec(String soomSec) {
        Log.d("SOOMLA", "setSoomSec is called from java !");
        StoreConfig.SOOM_SEC = soomSec;
    }


    private static String TAG = "StoreControllerBridge";

    public static void setPublicKey(String publicKey) {
        StoreControllerBridge.mPublicKey = publicKey;
    }
}
