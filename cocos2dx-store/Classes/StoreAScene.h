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

#ifndef __STOREA_SCENE_H__
#define __STOREA_SCENE_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class StoreAScene : public cocos2d::CCLayerColor
{
private:
	void createListViewItem(CCPoint& origin, CCMenu* menu, CCSize& visibleSize, int tag, const char* img);
	string itemIdFromTag(int tag);
	static int tagFromItemId(const char* itemId);
	
	static CCLabelTTF* goodsPriceBalanceLabels[4];
	static CCLabelTTF* pLabelBalance;
	
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
	void menuBackCallback(CCObject* pSender);
    void menuGetMoreCallback(CCObject* pSender);
	void menuChooseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(StoreAScene);

	// The back key clicked
    virtual void keyBackClicked()
	{
		menuBackCallback(NULL);
	}
	
	static void setCurrencyBalanceLabel();
	static void setPriceBalanceLabel(const char* itemId);
};

#endif // __MainScene_SCENE_H__
