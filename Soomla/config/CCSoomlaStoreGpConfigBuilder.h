//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#ifndef COCOS2DXSTORE_CCSOOMLASTOREGPCONFIGBUILDER_H
#define COCOS2DXSTORE_CCSOOMLASTOREGPCONFIGBUILDER_H

#include "CCSoomlaConfigBuilder.h"

namespace soomla {
    class CCSoomlaStoreGpConfigBuilder : public CCSoomlaConfigBuilder {
    public:
        CCSoomlaStoreGpConfigBuilder();
        static CCSoomlaStoreGpConfigBuilder *create();
        CCSoomlaStoreGpConfigBuilder *setAndroidPublicKey(const char *androidPublicKey);
        CCSoomlaStoreGpConfigBuilder *setTestPurchases(bool isTestPurchases);
        CCSoomlaStoreGpConfigBuilder *activateFraudProtection(const char *clientId, const char *clientSecret, const char *refreshToken, bool verifyOnServerFailure);
    };
}


#endif //COCOS2DXSTORE_CCSOOMLASTOREGPCONFIGBUILDER_H
