//
// Created by Fedor on 04/06/14.
//


#include "CCReward.h"

#ifndef __CCSequenceReward_H_
#define __CCSequenceReward_H_

#include "cocos2d.h"
#include "CCSoomlaMacros.h"
#include "CCAggregateReward.h"

namespace soomla {
    class CCSequenceReward : public CCAggregateReward {
    public:
        CCSequenceReward() : CCAggregateReward() {
        };

        static CCSequenceReward *create(
                cocos2d::__String *rewardId,
                cocos2d::__String *name,
                cocos2d::__Bool *repeatable,
                cocos2d::__Array *rewards);

        SL_CREATE_WITH_DICTIONARY(CCSequenceReward);

        virtual ~CCSequenceReward();

        virtual const char *getType() override;
    };
}

#endif //__CCSequenceReward_H_
