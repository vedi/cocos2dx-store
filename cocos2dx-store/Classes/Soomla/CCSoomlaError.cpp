//
// Created by Fedor Shubin on 5/21/13.
//


#include "CCSoomlaError.h"
#include "CCStoreUtils.h"

namespace soomla {
    #define TAG "CCSoomlaError"
    
    CCSoomlaError *CCSoomlaError::createVirtualItemNotFoundException() {
        CCSoomlaError *ret = new CCSoomlaError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_ITEM_NOT_FOUND);
        return ret;
    }

    CCSoomlaError *CCSoomlaError::createInsufficientFundsException() {
        CCSoomlaError *ret = new CCSoomlaError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS);
        return ret;
    }

    CCSoomlaError *CCSoomlaError::createNotEnoughGoodsException() {
        CCSoomlaError *ret = new CCSoomlaError();
        ret->autorelease();
        ret->init(SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS);
        return ret;
    }

    bool CCSoomlaError::init(int code) {
        mCode = code;

        if (code == SOOMLA_EXCEPTION_ITEM_NOT_FOUND) {
            CCStoreUtils::logDebug(TAG, "SOOMLA/UNITY Got VirtualItemNotFoundException exception");
            mInfo = "VirtualItemNotFoundException()";
        }

        if (code == SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS) {
            CCStoreUtils::logDebug(TAG, "SOOMLA/UNITY Got InsufficientFundsException exception");
            mInfo = "InsufficientFundsException()";
        }

        if (code == SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS) {
            CCStoreUtils::logDebug(TAG, "SOOMLA/UNITY Got NotEnoughGoodsException exception");
            mInfo = "NotEnoughGoodsException()";
        }

        return true;
    }
}
