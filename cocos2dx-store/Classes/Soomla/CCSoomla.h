//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCSoomla_H_
#define __CCSoomla_H_

#include "cocos2d.h"

namespace soomla {

    #define SOOMLA_AND_PUB_KEY_DEFAULT "YOUR GOOGLE PLAY PUBLIC KEY"
    #define SOOMLA_ONLY_ONCE_DEFAULT "SET ONLY ONCE"

    using namespace std;

    class CCSoomla: public cocos2d::CCObject {
        CC_SYNTHESIZE(string, mCustomSecret, CustomSecret);
        CC_SYNTHESIZE(string, mAndroidPublicKey, AndroidPublicKey);
        CC_SYNTHESIZE(bool, mAndroidTestMode, AndroidTestMode);
        CC_SYNTHESIZE(string, mSoomSec, SoomSec);
    public:
        static CCSoomla* sharedSoomla();

        CCSoomla():
            mCustomSecret(SOOMLA_ONLY_ONCE_DEFAULT),
            mAndroidPublicKey(SOOMLA_AND_PUB_KEY_DEFAULT),
            mAndroidTestMode(false),
            mSoomSec(SOOMLA_ONLY_ONCE_DEFAULT)
        {};
        virtual ~CCSoomla(void);
        virtual bool init(void);

        // TODO: Add methods
    };
};

#endif //__CCSoomla_H_
