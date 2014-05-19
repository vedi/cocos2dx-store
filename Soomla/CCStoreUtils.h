/*
 Copyright (C) 2012-2014 Soomla Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

// Created by Fedor Shubin on 5/19/13.

#ifndef __CCStoreUtils_H_
#define __CCStoreUtils_H_

#include "CCSoomlaError.h"

#ifndef SOOMLA_DEBUG
# define SOOMLA_DEBUG false
#endif

namespace soomla {
	/** 
     \class CCStoreUtils
     \brief This class handles printing of error and debug messages.

     This class handles printing of error and debug messages.
	 */
    class CCStoreUtils {
    public:
		/**
		   Print a debug message.
		   \param tag the message tag.
		   \param message the message.
		 */
        static void logDebug(const char *tag, const char *message);

		/**
		   Print an error message.
		   \param tag the message tag.
		   \param message the message.
		*/
        static void logError(const char *tag, const char *message);

		/**
		   Print an exception message.
		   \param tag the message tag.
		   \param error A CCSoomlaError from which to extract the message.
		*/
        static void logException(const char *tag, CCSoomlaError *error);
    };
};

#endif //__CCStoreUtils_H_
