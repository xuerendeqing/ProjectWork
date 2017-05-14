#ifndef _TOUCH_EFFECT_H_
#define _TOUCH_EFFECT_H_

#include "GameDefine.h"

class TouchEffect : public Sprite
{
public:
	TouchEffect();

	virtual ~TouchEffect();

	CREATE_FUNC(TouchEffect);

	virtual bool init();

	void playEffect(const Vec2& point);
private:

	Vector<SpriteFrame*> m_effectArray;

	void setHide();
};

#endif 
