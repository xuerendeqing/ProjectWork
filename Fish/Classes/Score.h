#ifndef _SCORE_H_
#define _SCORE_H_
#include "GameDefine.h"
class Score :public Sprite
{
public:
	Score();

	virtual ~Score();

	static Score* create(unsigned short m_Coin, Vec2 point);

	bool init(unsigned short m_Coin, Vec2 point);

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	void ScoreActionCallback();
};

#endif