#ifndef _BACK_LAYER_H_
#define _BACK_LAYER_H_

#include "GameDefine.h"

class BackLayer :public Layer
{
public:
	BackLayer();

	virtual ~BackLayer();

	virtual bool init();

	CREATE_FUNC(BackLayer);

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

};
#endif
