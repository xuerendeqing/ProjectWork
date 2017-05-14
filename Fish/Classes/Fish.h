#ifndef _FISH_H_
#define _FISH_H_

#include "GameDefine.h"
#include "FishBezierTo.h"

class Fish :public Sprite
{
public:
	Fish();

	virtual ~Fish();

	static Fish *create(unsigned short type, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2);

	virtual bool init(unsigned short type,unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2);

	virtual void initFish(unsigned short type, unsigned short m_Direction, Vec2 m_start, Vec2 m_end, Vec2 m_control_1, Vec2 m_control_2);

	void FishDestroy();

	void MoveFinishCallBack();

	void FishBlink();

	void createGold();

	void IinitCreateLockImage();//创建锁定图标
	

	void PauseFishAction();//暂停鱼的活动

	void RecoverFishAction();//恢复鱼的活动


	Vec2 m_lastPoint;
	FishBezierTo *m_first;

	float m_speedTime;
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Color3B m_originColor;

	float m_delay;
	unsigned short m_ActiveFrames, m_Coin,m_FishType;
	const char *m_String;
	Animation* createAnimation(std::string prefixName, unsigned short framesNum, float delay);

	void updateShine(float dt);
	void unpause(float dt);
	
};

#endif