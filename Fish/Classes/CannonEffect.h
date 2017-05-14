#ifndef _CANNON_EFFECT_H_
#define _CANNON_EFFECT_H_

#include "GameDefine.h"

class CannonEffect :public Sprite
{
public:
	CannonEffect();

	virtual ~CannonEffect();

	CREATE_FUNC(CannonEffect);

	virtual bool init();

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float e_delay;
	unsigned short e_ActiveFrames;
	const char *e_String;
	Animation* createAnimation(std::string prefixName, unsigned short framesNum, float delay);

	void EffectDestroy();
};
#endif
