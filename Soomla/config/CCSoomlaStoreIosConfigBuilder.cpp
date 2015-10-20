//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaStoreIosConfigBuilder.h"

using namespace soomla;

CCSoomlaStoreIosConfigBuilder::CCSoomlaStoreIosConfigBuilder() : CCSoomlaConfigBuilder() {

}

CCSoomlaStoreIosConfigBuilder* CCSoomlaStoreIosConfigBuilder::create() {
    return new CCSoomlaStoreIosConfigBuilder();
}

CCSoomlaStoreIosConfigBuilder* CCSoomlaStoreIosConfigBuilder::activateFraudProtection(bool verifyOnServerFailure) {
    return (this->appendConfigParameter("SSV", cocos2d::__Bool::create(true))
            && this->appendConfigParameter("verifyOnServerFailure", cocos2d::__Bool::create(verifyOnServerFailure)))
            ? this : NULL;
}