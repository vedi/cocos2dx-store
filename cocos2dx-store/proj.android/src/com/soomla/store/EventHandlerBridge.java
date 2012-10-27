package com.soomla.store;

import com.soomla.store.domain.data.GoogleMarketItem;
import com.soomla.store.domain.data.VirtualGood;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

public class EventHandlerBridge implements IStoreEventHandler {

    private Cocos2dxGLSurfaceView mGLThread;

    public EventHandlerBridge(Cocos2dxGLSurfaceView glThread) {
        mGLThread = glThread;
    }

    @Override
    public void onMarketPurchase(final GoogleMarketItem googleMarketItem) {

        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                marketPurchase(googleMarketItem.getProductId());
            }
        });

    }

    @Override
    public void onMarketRefund(final GoogleMarketItem googleMarketItem) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                marketRefund(googleMarketItem.getProductId());
            }
        });
    }

    @Override
    public void onVirtualGoodPurchased(final VirtualGood good) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                virtualGoodPurchased(good.getItemId());
            }
        });
    }

    @Override
    public void onVirtualGoodEquipped(final VirtualGood good) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                virtualGoodEquipped(good.getItemId());
            }
        });
    }

    @Override
    public void onVirtualGoodUnequipped(final VirtualGood good) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                virtualGoodUnequipped(good.getItemId());
            }
        });
    }

    @Override
    public void onBillingSupported() {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                billingSupported();
            }
        });
    }

    @Override
    public void onBillingNotSupported() {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                billingNotSupported();
            }
        });
    }

    @Override
    public void onMarketPurchaseProcessStarted(final GoogleMarketItem googleMarketItem) {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                marketPurchaseProcessStarted(googleMarketItem.getProductId());
            }
        });
    }

    @Override
    public void onGoodsPurchaseProcessStarted() {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                goodsPurchaseProcessStarted();
            }
        });
    }

    @Override
    public void onClosingStore() {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                closingStore();
            }
        });
    }

    @Override
    public void onUnexpectedErrorInStore() {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                unexpectedErrorInStore();
            }
        });
    }

    @Override
    public void onOpeningStore() {
        mGLThread.queueEvent(new Runnable() {
            @Override
            public void run() {
                openingStore();
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
    native void goodsPurchaseProcessStarted();
    native void closingStore();
    native void unexpectedErrorInStore();
    native void openingStore();
}
