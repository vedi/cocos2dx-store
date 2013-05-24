//
// Created by Fedor Shubin on 5/21/13.
//

#ifndef __CCSoomlaError_H_
#define __CCSoomlaError_H_

#include "cocos2d.h"

#define SOOMLA_NO_ERROR 0
#define SOOMLA_EXCEPTION_ITEM_NOT_FOUND -1
#define SOOMLA_EXCEPTION_INSUFFICIENT_FUNDS -2
#define SOOMLA_EXCEPTION_NOT_ENOUGH_GOODS -3

namespace soomla {
    class CCSoomlaError: public cocos2d::CCObject {
        CC_SYNTHESIZE_READONLY(int, mCode, Code);
    public:
        static CCSoomlaError *createWithObject(CCObject *obj);

        static CCSoomlaError *createVirtualItemNotFoundException();
        static CCSoomlaError *createInsufficientFundsException();
        static CCSoomlaError *createNotEnoughGoodsException();

        const char *getInfo() {return mInfo.c_str();};
    private:
        std::string mInfo;

        CCSoomlaError():
            mCode(0),
            mInfo("") {}

        bool init(int code);
    };
};


#endif //__CCSoomlaError_H_
