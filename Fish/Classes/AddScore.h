#ifndef _ADD_SCORE_H_
#define _ADD_SCORE_H_

#include "GameDefine.h"

class AddScore :public Sprite
{
public:
	AddScore();

	virtual ~AddScore();

	static AddScore* create(unsigned short m_Coin);

	bool init(unsigned short m_Coin);

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	void addScroeActionCallback();
};
#endif