package com.soomla.cocos2dx.store;

import android.opengl.GLSurfaceView;
import com.soomla.cocos2dx.common.NdkGlue;
import com.soomla.store.BusProvider;
import com.soomla.store.domain.MarketItem;
import com.soomla.store.events.*;
import com.squareup.otto.Subscribe;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * This bridge is used to populate events from the store to cocos2dx (through JNI).
 */
public class StoreEventHandlerBridge {

    private GLSurfaceView mGLThread;

    public StoreEventHandlerBridge() {
        BusProvider.getInstance().register(this);
    }

    @Subscribe
    public void onBillingNotSupported(BillingNotSupportedEvent billingNotSupportedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onBillingNotSupported");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onBillingSupported(BillingSupportedEvent billingSupportedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onBillingSupported");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }
	
    @Subscribe
    public void onIabServiceStarted(IabServiceStartedEvent iabServiceStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onIabServiceStarted");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }
	
    @Subscribe
    public void onIabServiceStopped(IabServiceStoppedEvent iabServiceStoppedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onIabServiceStopped");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onCurrencyBalanceChanged(final CurrencyBalanceChangedEvent currencyBalanceChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onCurrencyBalanceChanged");
                    parameters.put("itemId", currencyBalanceChangedEvent.getCurrency().getItemId());
                    parameters.put("balance", currencyBalanceChangedEvent.getBalance());
                    parameters.put("amountAdded", currencyBalanceChangedEvent.getAmountAdded());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGoodBalanceChanged(final GoodBalanceChangedEvent goodBalanceChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onGoodBalanceChanged");
                    parameters.put("itemId", goodBalanceChangedEvent.getGood().getItemId());
                    parameters.put("balance", goodBalanceChangedEvent.getBalance());
                    parameters.put("amountAdded", goodBalanceChangedEvent.getAmountAdded());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGoodEquipped(final GoodEquippedEvent goodEquippedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onGoodEquipped");
                    parameters.put("itemId", goodEquippedEvent.getGood().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGoodUnequipped(final GoodUnEquippedEvent goodUnEquippedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onGoodUnEquipped");
                    parameters.put("itemId", goodUnEquippedEvent.getGood().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onGoodUpgrade(final GoodUpgradeEvent goodUpgradeEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onGoodUpgrade");
                    parameters.put("itemId", goodUpgradeEvent.getGood().getItemId());
                    parameters.put("vguItemId", goodUpgradeEvent.getCurrentUpgrade().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onItemPurchased(final ItemPurchasedEvent itemPurchasedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onItemPurchased");
                    parameters.put("itemId", itemPurchasedEvent.getPurchasableVirtualItem().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onItemPurchaseStarted(final ItemPurchaseStartedEvent itemPurchaseStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onItemPurchaseStarted");
                    parameters.put("itemId", itemPurchaseStartedEvent.getPurchasableVirtualItem().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onMarketPurchaseCancelled(final MarketPurchaseCancelledEvent marketPurchaseCancelledEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onMarketPurchaseCancelled");
                    parameters.put("itemId", marketPurchaseCancelledEvent.getPurchasableVirtualItem().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onMarketPurchase(final MarketPurchaseEvent marketPurchaseEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onMarketPurchase");
                    parameters.put("itemId", marketPurchaseEvent.getPurchasableVirtualItem().getItemId());
                    parameters.put("payload", marketPurchaseEvent.getPayload());
                    parameters.put("token", marketPurchaseEvent.getToken());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onMarketPurchaseStarted(final MarketPurchaseStartedEvent marketPurchaseStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onMarketPurchaseStarted");
                    parameters.put("itemId", marketPurchaseStartedEvent.getPurchasableVirtualItem().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onMarketItemsRefreshed(final MarketItemsRefreshFinishedEvent marketItemsRefreshed) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONArray marketItemsJson = new JSONArray();
                    JSONObject marketItemJson;

                    for (MarketItem marketItem : marketItemsRefreshed.getMarketItems()) {
                        marketItemJson = new JSONObject();
                        marketItemJson.put("productId", marketItem.getProductId());
                        marketItemJson.put("marketPrice", marketItem.getMarketPrice());
                        marketItemJson.put("marketTitle", marketItem.getMarketTitle());
                        marketItemJson.put("marketDesc", marketItem.getMarketDescription());
                        marketItemsJson.put(marketItemJson);
                    }
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onMarketItemsRefreshed");
                    parameters.put("marketItems", marketItemsJson);
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onMarketRefund(final MarketRefundEvent playRefundEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onMarketRefund");
                    parameters.put("itemId", playRefundEvent.getPurchasableVirtualItem().getItemId());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onRestoreTransactionsFinished(final RestoreTransactionsFinishedEvent restoreTransactionsEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onRestoreTransactionsFinished");
                    parameters.put("success", restoreTransactionsEvent.isSuccess());
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onRestoreTransactionsStarted(final RestoreTransactionsStartedEvent restoreTransactionsStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onRestoreTransactionsStarted");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onUnexpectedErrorInStore(UnexpectedStoreErrorEvent unexpectedStoreErrorEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onUnexpectedErrorInStore");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    @Subscribe
    public void onStoreControllerInitialized(StoreControllerInitializedEvent storeControllerInitializedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                try {
                    JSONObject parameters = new JSONObject();
                    parameters.put("method", "CCEventHandler::onStoreControllerInitialized");
                    NdkGlue.getInstance().sendMessageWithParameters(parameters);
                } catch (JSONException e) {
                    throw new IllegalStateException(e);
                }
            }
        });
    }

    public void setGlSurfaceView(GLSurfaceView glSurfaceView) {
        this.mGLThread = glSurfaceView;
    }
}
