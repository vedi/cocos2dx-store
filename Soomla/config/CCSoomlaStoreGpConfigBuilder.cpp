//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaStoreGpConfigBuilder.h"

using namespace soomla;

CCSoomlaStoreGpConfigBuilder::CCSoomlaStoreGpConfigBuilder() : CCSoomlaConfigBuilder() {

}

CCSoomlaStoreGpConfigBuilder* CCSoomlaStoreGpConfigBuilder::create() {
    return new CCSoomlaStoreGpConfigBuilder();
}

CCSoomlaStoreGpConfigBuilder* CCSoomlaStoreGpConfigBuilder::setAndroidPublicKey(const char *androidPublicKey) {
    return this->appendConfigParameter("androidPublicKey", cocos2d::__String::create(androidPublicKey)) ? this : NULL;
}

CCSoomlaStoreGpConfigBuilder* CCSoomlaStoreGpConfigBuilder::setTestPurchases(bool isTestPurchases) {
    return this->appendConfigParameter("testPurchases", cocos2d::__Bool::create(isTestPurchases)) ? this : NULL;
}

CCSoomlaStoreGpConfigBuilder* CCSoomlaStoreGpConfigBuilder::activateFraudProtection(const char *clientId, const char *clientSecret, const char *refreshToken, bool verifyOnServerFailure) {
    return this->appendConfigParameter("clientId", cocos2d::__String::create(clientId))
            && this->appendConfigParameter("clientSecret", cocos2d::__String::create(clientSecret))
            && this->appendConfigParameter("refreshToken", cocos2d::__String::create(refreshToken))
            && this->appendConfigParameter("verifyOnServerFailure", cocos2d::__Bool::create(verifyOnServerFailure))
            ? this : NULL;
}