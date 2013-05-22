//
// Created by Fedor Shubin on 5/20/13.
//

#ifndef __CCStoreUtils_H_
#define __CCStoreUtils_H_

namespace soomla {
    #define SOOMLA_DEBUG true

    class CCStoreUtils {
    public:
        static void logDebug(const char *tag, const char *message);
        static void logError(const char *tag, const char *message);
    };
};

#endif //__CCStoreUtils_H_
