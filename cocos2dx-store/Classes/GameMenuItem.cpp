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
	if(m_bIsEnabled)
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
	if (m_bIsEnabled)
	{
		CCMenuItem::unselected();
		this->stopActionByTag(kZoomActionTag);
		CCAction *zoomAction = CCEaseElasticOut::create(CCScaleTo::create(0.5f, m_fOriginalScale));
		zoomAction->setTag(kZoomActionTag);
		this->runAction(zoomAction);
	}
}