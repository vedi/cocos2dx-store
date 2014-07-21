//
// Created by Fedor on 03/06/14.
//


#ifndef __CCRandomReward_H_
#define __CCRandomReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCAggregateReward.h"

namespace soomla {
    class CCRandomReward : public CCAggregateReward {
    public:
        CCRandomReward() : CCAggregateReward() {
        };

        static CCRandomReward *create(
                cocos2d::__String *rewardId,
                cocos2d::__String *name,
                cocos2d::__Bool *repeatable,
                cocos2d::__Array *rewards);

        SL_CREATE_WITH_DICTIONARY(CCRandomReward);

        virtual ~CCRandomReward();

        virtual const char *getType() override;
    };
}

#endif //__CCRandomReward_H_
