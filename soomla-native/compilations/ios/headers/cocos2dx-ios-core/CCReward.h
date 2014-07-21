//
// Created by Fedor on 03/06/14.
//


#ifndef __CCReward_H_
#define __CCReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCDomain.h"
#include "CCCommonConsts.h"

namespace soomla {
    class CCReward : public CCDomain {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mRewardId, RewardId, CCCommonConsts::JSON_REWARD_ID);

        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__String *, mName, Name, CCCommonConsts::JSON_NAME);

        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Bool *, mRepeatable, Repeatable, CCCommonConsts::JSON_REPEATABLE);
    public:
        CCReward() : mRewardId(NULL), mName(NULL), mRepeatable(NULL) {
        };

        virtual bool init(cocos2d::__String *rewardId, cocos2d::__String *name, cocos2d::__Bool *repeatable);

        virtual bool initWithDictionary(cocos2d::__Dictionary *dict);

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCReward();

        virtual const char *getType() = 0;
    };
}

#endif //__CCReward_H_
