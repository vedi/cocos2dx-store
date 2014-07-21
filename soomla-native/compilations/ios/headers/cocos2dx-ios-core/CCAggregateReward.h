//
// Created by Fedor on 03/06/14.
//


#ifndef __CCAggregateReward_H_
#define __CCAggregateReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCCommonConsts.h"
#include "CCReward.h"

namespace soomla {
    class CCAggregateReward : public CCReward {
        SL_SYNTHESIZE_RETAIN_WITH_DICT(cocos2d::__Array *, mRewards, Rewards, CCCommonConsts::JSON_REWARDS);
    public:
        CCAggregateReward() : CCReward(), mRewards(NULL) {
        };

        virtual bool init(
                cocos2d::__String *rewardId,
                cocos2d::__String *name,
                cocos2d::__Bool *repeatable,
                cocos2d::__Array *rewards);

        virtual bool initWithDictionary(cocos2d::__Dictionary *dict);

        virtual cocos2d::__Dictionary *toDictionary();

        virtual ~CCAggregateReward();
    };
}

#endif //__CCAggregateReward_H_
