//
// Created by Fedor Shubin on 5/20/13.
//


#include "CCSoomla.h"

namespace soomla {

    USING_NS_CC;

    static CCSoomla *s_SharedSoomla = NULL;

    CCSoomla* CCSoomla::sharedSoomla() {
        if (!s_SharedSoomla) {
            s_SharedSoomla = new CCSoomla();
            s_SharedSoomla->init();
        }

        return s_SharedSoomla;
    }

    CCSoomla::~CCSoomla() {

    }

    bool CCSoomla::init() {
        return true;
    }
}



