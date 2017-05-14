#ifndef _SET_LAYER_H_
#define _SET_LAYER_H_

#include "GameDefine.h"

class SetLayer :public Layer
{
public:
	SetLayer();

	virtual ~SetLayer();

	CREATE_FUNC(SetLayer);

	virtual bool init();
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	void SetCloseCallback(Ref* pSender);//¹Ø±Õ»Øµ÷

	void MusicCallback(Ref* sender,Control::EventType controlEvent);

	void SoundCallback(Ref* sender, Control::EventType controlEvent);

	void EffectCallback(Ref* sender, Control::EventType controlEvent);
};
#endif
