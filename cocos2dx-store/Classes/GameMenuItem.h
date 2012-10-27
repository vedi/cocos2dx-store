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