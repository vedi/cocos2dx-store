package com.soomla.cocos2dx.store;

import com.soomla.store.BusProvider;
import com.soomla.store.domain.data.GoogleMarketItem;
import com.soomla.store.domain.data.VirtualCurrency;
import com.soomla.store.domain.data.VirtualGood;
import com.soomla.store.events.*;
import com.squareup.otto.Subscribe;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

/**
 * This bridge is used to populate events from the store to cocos2dx (through JNI).
 */
public class EventHandlerBridge {

    private Cocos2dxGLSurfaceView mGLThread;

    public EventHandlerBridge(Cocos2dxGLSurfaceView glThread) {
        mGLThread = glThread;

        BusProvider.getInstance().register(this);
    }

    @Subscribe
    public void onMarketPurchase(final MarketPurchaseEvent marketPurchaseEvent) {

        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                marketPurchase(marketPurchaseEvent.getGoogleMarketItem().getProductId());
            }
        });

    }

    @Subscribe
    public void onMarketRefund(final MarketRefundEvent marketRefundEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                marketRefund(marketRefundEvent.getGoogleMarketItem().getProductId());
            }
        });
    }

    @Subscribe
    public void onVirtualGoodPurchased(final GoodPurchasedEvent goodPurchasedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                virtualGoodPurchased(goodPurchasedEvent.getGood().getItemId());
            }
        });
    }

    @Subscribe
    public void onVirtualGoodEquipped(final VirtualGoodEquippedEvent virtualGoodEquippedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                virtualGoodEquipped(virtualGoodEquippedEvent.getGood().getItemId());
            }
        });
    }

    @Subscribe
    public void onVirtualGoodUnequipped(final VirtualGoodUnEquippedEvent virtualGoodUnEquippedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                virtualGoodUnequipped(virtualGoodUnEquippedEvent.getGood().getItemId());
            }
        });
    }

    @Subscribe
    public void onBillingSupported(BillingSupportedEvent billingSupportedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                billingSupported();
            }
        });
    }

    @Subscribe
    public void onBillingNotSupported(BillingNotSupportedEvent billingNotSupportedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                billingNotSupported();
            }
        });
    }

    @Subscribe
    public void onMarketPurchaseProcessStarted(final MarketPurchaseStartedEvent marketPurchaseStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                marketPurchaseProcessStarted(marketPurchaseStartedEvent.getGoogleMarketItem().getProductId());
            }
        });
    }
	
    @Subscribe
    public void onMarketPurchaseCancelled(final MarketPurchaseCancelledEvent marketPurchaseCancelledEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                marketPurchaseCancelled(marketPurchaseCancelledEvent.getGoogleMarketItem().getProductId());
            }
        });
    }

    @Subscribe
    public void onGoodsPurchaseProcessStarted(GoodPurchaseStartedEvent goodPurchaseStartedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                goodsPurchaseProcessStarted();
            }
        });
    }

    @Subscribe
    public void onClosingStore(ClosingStoreEvent closingStoreEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                closingStore();
            }
        });
    }

    @Subscribe
    public void onUnexpectedErrorInStore(UnexpectedStoreErrorEvent unexpectedStoreErrorEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                unexpectedErrorInStore();
            }
        });
    }

    @Subscribe
    public void onOpeningStore(OpeningStoreEvent openingStoreEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                openingStore();
            }
        });
    }

    @Subscribe
    public void onCurrencyBalanceChanged(final CurrencyBalanceChangedEvent currencyBalanceChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                currencyBalanceChanged(currencyBalanceChangedEvent.getCurrency().getItemId(), currencyBalanceChangedEvent.getBalance());
            }
        });
    }

    @Subscribe
    public void onGoodBalanceChanged(final GoodBalanceChangedEvent goodBalanceChangedEvent) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                goodBalanceChanged(goodBalanceChangedEvent.getGood().getItemId(), goodBalanceChangedEvent.getBalance());
            }
        });
    }

    native void marketPurchase(String productId);
    native void marketRefund(String productId);
    native void virtualGoodPurchased(String itemId);
    native void virtualGoodEquipped(String itemId);
    native void virtualGoodUnequipped(String itemId);
    native void billingSupported();
    native void billingNotSupported();
    native void marketPurchaseProcessStarted(String productId);
    native void marketPurchaseCancelled(String productId);
    native void goodsPurchaseProcessStarted();
    native void closingStore();
    native void unexpectedErrorInStore();
    native void openingStore();
    native void currencyBalanceChanged(String itemId, int balance);
    native void goodBalanceChanged(String itemId, int balance);
}
