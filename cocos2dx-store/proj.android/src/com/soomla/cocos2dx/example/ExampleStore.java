/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.soomla.cocos2dx.example;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.util.Log;
import com.easyndk.classes.AndroidNDKHelper;
import com.soomla.cocos2dx.store.StoreAssetsBridge;
import com.soomla.cocos2dx.store.StoreControllerBridge;
import com.soomla.cocos2dx.store.StoreInfoBridge;
import com.soomla.cocos2dx.store.StoreInventoryBridge;
import com.soomla.store.exceptions.InsufficientFundsException;
import com.soomla.store.exceptions.VirtualItemNotFoundException;
import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxRenderer;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * This class holds the OpenGL view of cocosedx.
 */
public class ExampleStore extends Cocos2dxActivity{
    private Cocos2dxGLSurfaceView mGLView;

    private StoreAssetsBridge storeAssetsBridge = null;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        AndroidNDKHelper.setNDKReceiver(this);

        if (detectOpenGLES20()) {
            // get the packageName,it's used to set the resource path
//            String packageName = getApplication().getPackageName();
//            super.setPackageName(packageName);

            // FrameLayout
//            ViewGroup.LayoutParams framelayout_params =
//                    new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
//                            ViewGroup.LayoutParams.FILL_PARENT);
//            FrameLayout framelayout = new FrameLayout(this);
//            framelayout.setLayoutParams(framelayout_params);

            // Cocos2dxEditText layout
//            ViewGroup.LayoutParams edittext_layout_params =
//                    new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
//                            ViewGroup.LayoutParams.WRAP_CONTENT);
//            Cocos2dxEditText edittext = new Cocos2dxEditText(this);
//            edittext.setLayoutParams(edittext_layout_params);

            // ...add to FrameLayout
//            framelayout.addView(edittext);

            // Cocos2dxGLSurfaceView
            mGLView = new Cocos2dxGLSurfaceView(this);

            // ...add to FrameLayout
//            framelayout.addView(mGLView);

            mGLView.setEGLContextClientVersion(2);
            mGLView.setCocos2dxRenderer(new Cocos2dxRenderer());
//            mGLView.setTextField(edittext);

            // Set framelayout as the content view
//            setContentView(framelayout);
        }
        else {
            Log.d("activity", "don't support gles2.0");
            finish();
        }

        /**
         * initialize the StoreControllerBridge
         * You'll need to provide an implementation of IStoreAssets and your public key from Google Play.
         */
        StoreControllerBridge.initialize(mGLView,
                new MuffinRushAssets(), "AAA", this);
    }

    protected void onPause() {
        super.onPause();
        mGLView.onPause();
    }

    protected void onResume() {
        super.onResume();
        mGLView.onResume();
    }

    private boolean detectOpenGLES20()
    {
        ActivityManager am =
                (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();
        return (info.reqGlEsVersion >= 0x20000);
    }

    public void soomla_easyNDKTest(JSONObject params) {
        Log.v("soomla_easyNDKTest", "soomla_easyNDKTest called");
        Log.v("soomla_easyNDKTest", "Passed params are : " + params.toString());
        Log.v("soomla_easyNDKTest", "Send them back to native code");
        AndroidNDKHelper.sendMessageWithParameters("soomla_easyNDKCallBackTest", params);
    }

    public JSONObject soomla_easyNDK(JSONObject params) {
        Log.v("soomla_easyNDK", "soomla_easyNDK called");
        Log.v("soomla_easyNDK", "Passed params are : " + params.toString());

        JSONObject retParams = new JSONObject();

        try {
            String methodName = params.getString("method");
            if (methodName.equals("StoreAssets::init")) {
                int version = params.getInt("version");
                JSONObject storeAssetsJson = params.getJSONObject("storeAssets");
                storeAssetsBridge = new StoreAssetsBridge(version, storeAssetsJson);
            } else if (methodName.equals("CCStoreController::buyMarketItem")) {
                String productId = params.getString("productId");
                StoreControllerBridge.buyWithGooglePlay(productId);
            } else if (methodName.equals("CCStoreController::storeOpening")) {
                StoreControllerBridge.storeOpening();
            } else if (methodName.equals("CCStoreController::storeClosing")) {
                StoreControllerBridge.storeClosing();
            } else if (methodName.equals("CCStoreController::restoreTransactions")) {
                StoreControllerBridge.restoreTransactions();
            } else if (methodName.equals("CCStoreController::transactionsAlreadyRestored")) {
                boolean retValue = StoreControllerBridge.transactionsAlreadyRestored();
                retParams.put("return", retValue);
            } else if (methodName.equals("CCStoreController::setAndroidTestMode")) {
                Boolean testMode = params.getBoolean("testMode");
                StoreControllerBridge.setAndroidTestMode(testMode);
            } else if (methodName.equals("CCStoreController::setSoomSec")) {
                String soomSec = params.getString("soomSec");
                StoreControllerBridge.setSoomSec(soomSec);
            } else if (methodName.equals("CCStoreInventory::buyItem")) {
                String itemId = params.getString("itemId");
                StoreInventoryBridge.buy(itemId);
            } else if (methodName.equals("CCStoreInventory::getItemBalance")) {
                String itemId = params.getString("itemId");
                int retValue = StoreInventoryBridge.getItemBalance(itemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("CCStoreInventory::giveItem")) {
                String itemId = params.getString("itemId");
                Integer amount = params.getInt("amount");
                StoreInventoryBridge.giveItem(itemId, amount);
            } else if (methodName.equals("CCStoreInventory::takeItem")) {
                String itemId = params.getString("itemId");
                Integer amount = params.getInt("amount");
                StoreInventoryBridge.takeItem(itemId, amount);
            } else if (methodName.equals("CCStoreInventory::equipVirtualGood")) {
                String itemId = params.getString("itemId");
                StoreInventoryBridge.equipVirtualGood(itemId);
            } else if (methodName.equals("CCStoreInventory::unEquipVirtualGood")) {
                String itemId = params.getString("itemId");
                StoreInventoryBridge.unEquipVirtualGood(itemId);
            } else if (methodName.equals("CCStoreInventory::isVirtualGoodEquipped")) {
                String itemId = params.getString("itemId");
                boolean retValue = StoreInventoryBridge.isVirtualGoodEquipped(itemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("CCStoreInventory::getGoodUpgradeLevel")) {
                String goodItemId = params.getString("goodItemId");
                Integer retValue = StoreInventoryBridge.getGoodUpgradeLevel(goodItemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("CCStoreInventory::getGoodCurrentUpgrade")) {
                String goodItemId = params.getString("goodItemId");
                String retValue = StoreInventoryBridge.getGoodCurrentUpgrade(goodItemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("CCStoreInventory::upgradeGood")) {
                String itemId = params.getString("goodItemId");
                StoreInventoryBridge.upgradeVirtualGood(itemId);
            } else if (methodName.equals("CCStoreInventory::removeGoodUpgrades")) {
                String itemId = params.getString("goodItemId");
                StoreInventoryBridge.upgradeVirtualGood(itemId);
            } else if (methodName.equals("CCStoreInventory::nonConsumableItemExists")) {
                String nonConsItemId = params.getString("nonConsItemId");
                boolean retValue = StoreInventoryBridge.nonConsumableItemExists(nonConsItemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("CCStoreInventory::addNonConsumableItem")) {
                String nonConsItemId = params.getString("nonConsItemId");
                StoreInventoryBridge.addNonConsumableItem(nonConsItemId);
            } else if (methodName.equals("CCStoreInventory::removeNonConsumableItem")) {
                String nonConsItemId = params.getString("nonConsItemId");
                StoreInventoryBridge.removeNonConsumableItem(nonConsItemId);
            } else if (methodName.equals("StoreInfo::getItemByItemId")) {
                String itemId = params.getString("itemId");
                JSONObject retValue = StoreInfoBridge.getItemByItemId(itemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getPurchasableItemWithProductId")) {
                String productId = params.getString("productId");
                JSONObject retValue = StoreInfoBridge.getPurchasableItemWithProductId(productId);
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getCategoryForVirtualGood")) {
                String goodItemId = params.getString("goodItemId");
                JSONObject retValue = StoreInfoBridge.getCategoryForVirtualGood(goodItemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getFirstUpgradeForVirtualGood")) {
                String goodItemId = params.getString("goodItemId");
                JSONObject retValue = StoreInfoBridge.getFirstUpgradeForVirtualGood(goodItemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getLastUpgradeForVirtualGood")) {
                String goodItemId = params.getString("goodItemId");
                JSONObject retValue = StoreInfoBridge.getLastUpgradeForVirtualGood(goodItemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getUpgradesForVirtualGood")) {
                String goodItemId = params.getString("goodItemId");
                JSONArray retValue = StoreInfoBridge.getUpgradesForVirtualGood(goodItemId);
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getVirtualCurrencies")) {
                JSONArray retValue = StoreInfoBridge.getVirtualCurrencies();
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getVirtualGoods")) {
                JSONArray retValue = StoreInfoBridge.getVirtualGoods();
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getVirtualCurrencyPacks")) {
                JSONArray retValue = StoreInfoBridge.getVirtualCurrencyPacks();
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getNonConsumableItems")) {
                JSONArray retValue = StoreInfoBridge.getNonConsumableItems();
                retParams.put("return", retValue);
            } else if (methodName.equals("StoreInfo::getVirtualCategories")) {
                JSONArray retValue = StoreInfoBridge.getVirtualCategories();
                retParams.put("return", retValue);
            } else {
                throw new UnsupportedOperationException();
            }
        } catch (JSONException e) {
            throw new IllegalArgumentException(e);
        } catch (VirtualItemNotFoundException e) {
            throw new IllegalArgumentException(e);
        } catch (InsufficientFundsException e) {
            throw new IllegalArgumentException(e);
        }

        return retParams;
    }

    static {
        System.loadLibrary("hellocpp");
    }

}
