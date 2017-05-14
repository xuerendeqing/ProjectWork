#ifndef _GOLD_H_
#define _GOLD_H_

#include "GameDefine.h"

class Gold :public Sprite
{
public:
	Gold();

	virtual ~Gold();

	static Gold* create(GoldType type,Vec2 point);

	bool init(GoldType type, Vec2 point);
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
protected:
	float g_delay;
	unsigned short g_GoldFrames, m_GoldSpeed;
	const char *g_String;
	Animation* createAnimation(std::string prefixName, unsigned short framesNum, float delay);
	Vec2 m_targetPoint;
	void GlodActionCallback();
};
#endif