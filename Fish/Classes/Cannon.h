#ifndef _CANNON_H_
#define _CANNON_H_

#include "GameDefine.h"
class UILayer;
class Cannon :public Sprite
{
public:
	Cannon();

	virtual ~Cannon();

	static Cannon *create(UILayer *s_UILayer);

	bool init(UILayer *s_UILayer);

	void RotationToFire(Vec2 m_Point);
	void CannonAction();
	UILayer *c_UILayer;

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 m_Direction;
	
	float m_Rotation;

	void ScaleCallbackA();
	void ScaleCallbackB();
	void Fire();
};
#endif