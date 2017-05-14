#ifndef _WATER_LAYER_H_
#define _WATER_LAYER_H_

#include "GameDefine.h"
class WaterLayer :public Sprite
{
public:
	WaterLayer();

	virtual ~WaterLayer();

	virtual bool init();

	CREATE_FUNC(WaterLayer);

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float w_delay;
	unsigned short w_ActiveFrames;
	const char *w_String;
	Animation* createAnimation(std::string prefixName, unsigned short framesNum, float delay);
};

#endif