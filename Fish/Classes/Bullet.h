#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameDefine.h"
class Cannon;
class Bullet :public Sprite
{
public:
	Bullet();

	virtual ~Bullet();

	static Bullet *create(Cannon *m_cannon, unsigned short m_CannonType, unsigned short cannonValue);

	bool init(Cannon *m_cannon, unsigned short m_CannonType, unsigned short cannonValue);

	void shootTo(Vec2 targetDirection);

	void ShowNet();

	BulletStatus m_status;
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 ptLastStart;
	const char *m_BulletString, *m_NetString;
	unsigned short m_Speed, m_reflectTimes,m_bulletType;
	float getBulletMoveTime(Vec2 startPos, Vec2 endPos);
	//射击的子弹在超出屏幕后反弹
	void reflect();
	void BulletDestroy();
};
#endif