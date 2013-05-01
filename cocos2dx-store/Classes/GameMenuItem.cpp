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

#include "GameMenuItem.h"

const unsigned int kZoomActionTag = 0xc0c05002;

GameMenuItem* GameMenuItem::itemWithLabel(CCNode*label, CCObject* target, SEL_MenuHandler selector)
{
	GameMenuItem *pRet = new GameMenuItem();
	pRet->initWithLabel(label, target, selector);
	pRet->autorelease();
	return pRet;
}

void GameMenuItem::selected()
{
	// subclass to change the default action
	if(isEnabled())
	{
		CCMenuItem::selected();

		CCAction *action = getActionByTag(kZoomActionTag);
		if (action)
		{
			this->stopAction(action);
		}
		else
		{
			m_fOriginalScale = this->getScale();
		}

		CCAction *zoomAction = CCEaseElasticOut::create(CCScaleTo::create(0.5f, m_fOriginalScale * mScaleFactor));
		zoomAction->setTag(kZoomActionTag);
		this->runAction(zoomAction);
	}
}

void GameMenuItem::unselected()
{
	// subclass to change the default action
	if (isEnabled())
	{
		CCMenuItem::unselected();
		this->stopActionByTag(kZoomActionTag);
		CCAction *zoomAction = CCEaseElasticOut::create(CCScaleTo::create(0.5f, m_fOriginalScale));
		zoomAction->setTag(kZoomActionTag);
		this->runAction(zoomAction);
	}
}