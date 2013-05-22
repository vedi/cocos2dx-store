//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCStoreController_H_
#define __CCStoreController_H_

#include "cocos2d.h"
#include "CCIStoreAssets.h"

namespace soomla {
    class CCStoreController: public cocos2d::CCObject {
    public:
        static CCStoreController* sharedStoreController();

        CCStoreController(void);
        virtual ~CCStoreController(void);
        virtual bool init(CCIStoreAssets *storeAssets);

        void buyMarketItem(char const *productId);
        void storeOpening();
        void storeClosing();
        void restoreTransactions();
        bool transactionsAlreadyRestored();
    };
};

#endif //__CCStoreController_H_
