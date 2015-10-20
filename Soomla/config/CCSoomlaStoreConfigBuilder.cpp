//
// Created by Eugene Butusov on 20/10/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCSoomlaStoreConfigBuilder.h"

using namespace soomla;

CCSoomlaStoreConfigBuilder::CCSoomlaStoreConfigBuilder() : CCSoomlaConfigBuilder() {

}

CCSoomlaStoreConfigBuilder* CCSoomlaStoreConfigBuilder::create() {
    return new CCSoomlaStoreConfigBuilder();
}

CCSoomlaStoreConfigBuilder* CCSoomlaStoreConfigBuilder::setIosConfiguration(CCSoomlaStoreIosConfigBuilder *iosConfig) {
    return this->appendConfigParameter(iosConfig->build()) ? this : NULL;
}

CCSoomlaStoreConfigBuilder* CCSoomlaStoreConfigBuilder::setGpConfiguration(CCSoomlaStoreGpConfigBuilder *gpConfig) {
    return this->appendConfigParameter(gpConfig->build()) ? this : NULL;
}