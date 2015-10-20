//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXSTORE_CCSOOMLASTORECONFIGBUILDER_H
#define COCOS2DXSTORE_CCSOOMLASTORECONFIGBUILDER_H

#include "CCSoomlaConfigBuilder.h"
#include "CCSoomlaStoreIosConfigBuilder.h"
#include "CCSoomlaStoreGpConfigBuilder.h"

namespace soomla {
    class CCSoomlaStoreConfigBuilder : public CCSoomlaConfigBuilder {
    public:
        CCSoomlaStoreConfigBuilder();
        static CCSoomlaStoreConfigBuilder *create();
        CCSoomlaStoreConfigBuilder *setIosConfiguration(CCSoomlaStoreIosConfigBuilder *iosConfig);
        CCSoomlaStoreConfigBuilder *setGpConfiguration(CCSoomlaStoreGpConfigBuilder *gpConfig);
    };
}


#endif //COCOS2DXSTORE_CCSOOMLASTORECONFIGBUILDER_H
