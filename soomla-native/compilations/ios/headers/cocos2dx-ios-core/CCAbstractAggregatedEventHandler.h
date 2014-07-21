//
// Created by Fedor Shubin on 6/19/14.
//


#ifndef __CCAbstractAggregatedEventHandler_H_
#define __CCAbstractAggregatedEventHandler_H_


#include "cocos2d.h"

namespace soomla {

#define FOR_EACH_EVENT_HANDLER(__TYPE__) __SetIterator i;\
    for(i = mEventHandlers->begin(); i != mEventHandlers->end(); i++) {\
        __TYPE__ *eventHandler = dynamic_cast<__TYPE__ *>(*i);\

    template <class T> class CCAbstractAggregatedEventHandler {
    protected:
        cocos2d::__Set *mEventHandlers;
    public:
        CCAbstractAggregatedEventHandler() :
                mEventHandlers(nullptr) {
        }
        virtual bool init() {
            mEventHandlers = cocos2d::__Set::create();
            mEventHandlers->retain();
            return true;
        }

        virtual ~CCAbstractAggregatedEventHandler() {
            CC_SAFE_RELEASE(mEventHandlers);
        }

        /**
        Add an event handler. This retains the event handler.
        \param eventHandler A pointer to the event handler you'd like to add.
        */
        void addEventHandler(T *eventHandler) {
            mEventHandlers->addObject(eventHandler);
        }

        /**
        Remove an event handler. This releases the event handler.
        \param eventHandler A pointer to the event handler you'd like to remove.
        */
        void removeEventHandler(T *eventHandler) {
            mEventHandlers->removeObject(eventHandler);
        }

    };
}

#endif //__CCAbstractAggregatedEventHandler_H_
