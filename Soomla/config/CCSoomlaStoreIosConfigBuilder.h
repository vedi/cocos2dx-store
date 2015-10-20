//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXSTORE_CCSOOMLASTOREIOSCONFIGBUILDER_H
#define COCOS2DXSTORE_CCSOOMLASTOREIOSCONFIGBUILDER_H

#include "CCSoomlaConfigBuilder.h"

namespace soomla {
    class CCSoomlaStoreIosConfigBuilder : public CCSoomlaConfigBuilder {
    public:
        CCSoomlaStoreIosConfigBuilder();
        static CCSoomlaStoreIosConfigBuilder *create();
        CCSoomlaStoreIosConfigBuilder *activateFraudProtection(bool verifyOnServerFailure);
    };
}


#endif //COCOS2DXSTORE_CCSOOMLASTOREIOSCONFIGBUILDER_H
