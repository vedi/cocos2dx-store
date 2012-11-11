/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __GameMenuItem_H__
#define __GameMenuItem_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameMenuItem : public CCMenuItemLabel
{
private:
	
public:
	GameMenuItem():
	  mScaleFactor(1.1f)
	{

	}

	static GameMenuItem * itemWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector);

	virtual void selected();
	virtual void unselected();

	void setScaleFactor(float scale)
	{
		mScaleFactor = scale;
	}

protected:
	float mScaleFactor;

};

#endif