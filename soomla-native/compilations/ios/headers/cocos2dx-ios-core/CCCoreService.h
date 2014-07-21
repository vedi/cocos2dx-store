//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCCoreService_H_
#define __CCCoreService_H_

#include "cocos2d.h"
#include "CCError.h"
#include "CCReward.h"

namespace soomla {

    class CCCoreService: public cocos2d::Ref {
    public:
		/**
		   This class is singleton, use this function to access it.
		*/
        static CCCoreService* getInstance();

        static void initShared();

        CCCoreService();

        virtual bool init();

    };
};

#endif // !__CCCoreService_H_
